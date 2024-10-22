// [Standard includes]
#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include <algorithm>

#include <ctime> // < This is only needed because gcc doesn't fully support chrono
#include <cctype>
#include <cstdlib>

// [Internal includes]
#include "clap/Profiler.h"
#include "clap/Formatter/XML.h"
#include "clap/utils/Enums.h"
#include "clap/utils/Casting.h"

using namespace clap;

template<typename T>
using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

// xml serialization of Stat objects

// forward declarations
template<typename K, typename V>
xml::ostream& operator<< (xml::ostream&, const std::map<K,V>&);
  
template<typename V>
xml::ostream& operator<< (xml::ostream&, const std::vector<V>&);

template<typename V>
xml::ostream& operator<< (xml::ostream&, const std::list<V>&);

// OpenCL object
xml::ostream& operator<< (xml::ostream& xml, const cl_event event) {
  cl_ulong submit, queued, start, end;
  auto get = API::getVendorImpl<API::clGetEventProfilingInfo>();
  auto ret = get(event, CL_PROFILING_COMMAND_QUEUED, sizeof(cl_ulong), &queued, NULL);
  ret |= get(event, CL_PROFILING_COMMAND_SUBMIT, sizeof(cl_ulong), &submit, NULL);
  ret |= get(event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
  ret |= get(event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 
  if(ret != CL_SUCCESS) std::cerr << ret << std::endl;
  assert(ret == CL_SUCCESS);

  return xml 
    << xml::attr("queued") << queued
    << xml::attr("submit") << submit
    << xml::attr("start") << start
    << xml::attr("end") << end;
}

xml::ostream& operator<< (xml::ostream& xml, const cl_device_id id) 
{ return xml << xml::attr("device_id") << Profiler::get().getDevice(id).id; }

xml::ostream& operator<< (xml::ostream& xml, const cl_program id) 
{ return xml << xml::attr("program_id") << Profiler::get().getProgram(id).id; }

xml::ostream& operator<< (xml::ostream& xml, const cl_kernel id) 
{ return xml << xml::attr("kernel_id") << Profiler::get().getKernel(id).id; }

xml::ostream& operator<< (xml::ostream& xml, const cl_command_queue id) 
{ return xml << xml::attr("command_queue_id") << Profiler::get().getCommandQueue(id).id; }

xml::ostream& operator<< (xml::ostream& xml, const cl_mem id) 
{ return xml << xml::attr("mem_id") << Profiler::get().getMemory(id).id; }


// Attributes serialization
template<typename T>
xml::ostream& operator<< (xml::ostream& xml, const Stat::Identifiable<T>& obj) 
{ return xml << xml::attr("id") << obj.id; }

xml::ostream& operator<< (xml::ostream& xml, const Stat::UniqueIdentifiable& obj) 
{ return xml << xml::attr("unique_id") << obj.id; }

xml::ostream& operator<< (xml::ostream& xml, const Stat::Enqueued& obj) 
{ return xml << obj.queue_id; }

#ifdef TRACK_EVENTS
xml::ostream& operator<< (xml::ostream& xml, const Stat::Timeable& obj) {
  return xml 
    << xml::tag("event")
    << xml::attr("forced") << (obj.forced_event?"true":"false")
    << obj._event
    << xml::endtag();
}
#endif

#ifdef TRACK_REFCOUNT
xml::ostream& operator<< (xml::ostream& xml, const Stat::RefCounted& obj) {
  return xml 
    << xml::tag("refcount")
    << xml::attr("retain") << obj.retain
    << xml::attr("release") << obj.release
    << xml::endtag();
}
#endif

// attribute sets
namespace {
template <typename T, typename... Args> 
struct Impl {
  static inline xml::ostream& append(xml::ostream& out, const T&)
  { return out; }
};

template <typename T, typename First, typename... Args>
struct Impl<T, First, Args...> {
  static inline xml::ostream& append(xml::ostream& out, const T& value)
  { return Impl<T, Args...>::append(out << static_cast<const First&>(value),value); }
};

}

template<typename... Ts> 
xml::ostream& operator<< (xml::ostream &out, const Stat::AttributeSet<Ts...> &c)
{ return Impl<Stat::AttributeSet<Ts...>,Ts...>::append(out,c); }


// Stat serialization
xml::ostream& operator<< (xml::ostream& xml, const Stat::NDRange& value) {
  // The TAG is ommitted
  if(value.dim) xml << xml::attr("dim") << value.dim ;
  if(value.x) xml << xml::attr("x") << value.x;
  if(value.y) xml << xml::attr("y") << value.y; 
  if(value.z) xml << xml::attr("z") << value.z; 
  return xml;
}

#ifdef TRACK_KERNEL_ARGUMENTS
xml::ostream& operator<< (xml::ostream& xml, const Stat::Argument::MemObject& value) {
  return xml 
    << xml::attr("type") << "cl_mem" 
    << xml::attr("cl_mem_id") << value.mem_object_id;
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Argument::Local& value) {
  return xml 
    << xml::attr("type") << "local_mem" 
    << xml::attr("size") << value.size;
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Argument::Data& value) {
  static const char dec2hex[17] = "0123456789abcdef";
  xml 
    << xml::attr("type") << "data" 
    << xml::attr("size") << value.size
    << xml::attr("value");
  for(const auto c : value.data)
    xml 
      << dec2hex[(c >> 4) & 15]
      << dec2hex[c & 15];
  return xml;
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::KernelArgument& value) {
  using namespace Stat::Argument;
  if(!downcast_switch(&value,
    [&](const MemObject* arg) { xml << *arg; },
    [&](const Local* arg)     { xml << *arg; },
    [&](const Data* arg)      { xml << *arg; }))
    xml << "unknown";
  return xml;
}
#endif

xml::ostream& operator<< (xml::ostream& xml, const Stat::KernelInstance& obj) {
  xml 
    << xml::tag("kernel_instance")
    << xml::attr("kernel_id") << Profiler::get().getKernel(obj.kernel_id).id
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::tag("offset_range") << obj.offset << xml::endtag()
    << xml::tag("global_range") << obj.global << xml::endtag()
    << xml::tag("local_range") << obj.local << xml::endtag();

#ifdef TRACK_KERNEL_ARGUMENTS  
  for(unsigned int i = 0; i < obj.arguments.size(); ++i) 
    xml << xml::tag("argument") 
        << xml::attr("index") << i << *(obj.arguments[i].get())
        << xml::endtag();
#endif

  return xml << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Kernel& kernel) {
  return xml 
    << xml::tag("kernel") 
    << xml::attr("name") << kernel.name
    << kernel.program_id
    << (const base_type<decltype(kernel)>::attribute_t&) kernel
    << xml::endtag();
}


#ifdef TRACK_API_CALLS
xml::ostream& operator<< (xml::ostream& xml, const Stat::HostFunction& fct) {
  return xml 
    << xml::attr("instances") << fct.instances
    << xml::attr("time") << fct.time
#ifdef DEBUG_TRACK_OVERHEAD
    << xml::attr("overhead") << (int)(fct.total_time/fct.time*100-100)
#endif
    ;
}
#endif

xml::ostream& operator<< (xml::ostream& xml, const Stat::MemOperation::Type& obj) {  
  xml << xml::attr("type"); 
  switch(obj) {
    case Stat::MemOperation::Type::Read: return xml << "read";
    case Stat::MemOperation::Type::Write: return xml << "write";
    case Stat::MemOperation::Type::Copy_src: return xml << "copy_from";
    case Stat::MemOperation::Type::Copy_dst: return xml << "copy_to";
    default: return xml << "unknown";
  }
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Memory::Type& obj) {
  xml << xml::attr("type");
  switch(obj) {
    case Stat::Memory::Type::Buffer: return xml << "Buffer";
    case Stat::Memory::Type::SubBuffer: return xml << "BubBuffer";
    case Stat::Memory::Type::Image: return xml << "Image";
    default: return xml << "unknown";
  };
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::MemOperation& obj) {
  return xml
    << xml::tag("memory_operation")
    << obj.type
    << xml::attr("blocking") << (obj.blocking?"true":"false")
    << obj.mem_id
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::CommandQueue& obj) {
  return xml
    << xml::tag("queue")
    << xml::attr("properties") << Constant::cl_command_queue_properties{obj.properties}
    << obj.device_id
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Device& obj) {
  // Print the device name as well
  auto _clGetDeviceInfo = API::getVendorImpl<API::clGetDeviceInfo>();
  std::string name;
  size_t length = 0;
  _clGetDeviceInfo(const_cast<cl_device_id>(obj.device_id),CL_DEVICE_NAME,0,nullptr,&length);
  name.resize(length);
  _clGetDeviceInfo(const_cast<cl_device_id>(obj.device_id),CL_DEVICE_NAME,length,&name[0],nullptr);

  // for some reason some devices still have garbage after their names
  auto filter = [](char c){ return !(std::isprint(c) || c == '\n' || c == '\t'); };
  name.erase(std::remove_if(std::begin(name), std::end(name), filter), std::end(name));  

  return xml
    << xml::tag("device")
    << xml::attr("name") << name
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Program& obj) {
  return xml
    << xml::tag("program")
    << xml::attr("build_options") << obj.build_options
#ifdef TRACK_PROGRAMS
    << xml::attr("hash") << obj.hash
#endif
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Context& obj) {
  return xml
    << xml::tag("context")
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag();
}

xml::ostream& operator<< (xml::ostream& xml, const Stat::Memory& obj) {
  xml
    << xml::tag("mem_object")
    << obj.type;
  if(obj.type == Stat::Memory::Type::SubBuffer) {
    xml << xml::attr("parent") << Profiler::get().getMemory(obj.parent).id
        << xml::attr("offset") << obj.offset;
  }
  return xml 
    << xml::attr("flag") << Constant::cl_mem_flags{obj.flags}
    << xml::attr("size") << obj.size
    << (const base_type<decltype(obj)>::attribute_t&) obj
    << xml::endtag("mem_object");
}

// Container serialization
template<typename K, typename V>
xml::ostream& operator<< (xml::ostream& xml, const std::map<K,V>& value) {
  for(const auto& i : value) xml << i.second;
  return xml;
}

template<typename V>
xml::ostream& operator<< (xml::ostream& xml, const std::vector<V>& value) {
  for(const auto& i : value) xml << i;
  return xml;
}

template<typename V>
xml::ostream& operator<< (xml::ostream& xml, const std::list<V>& value) {
  for(const auto& i : value) xml << i;
  return xml;
}

/// @brief XML logger: triggers the XML dump during static cleanup
/// @note: the dump might be incomplete if the application calls OpenCL functions
///  in global object destructors or callbacks
struct XMLLogger {
  ~XMLLogger()
  {
    std::ofstream logfile;
    std::time_t t = std::time(NULL);
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    if(std::getenv("CLAP_SAVE_XML")){
      logfile.open (std::string{mbstr}+".xml");
    }

    xml::ostream xml = {logfile.is_open()?logfile:std::cout};
    xml << xml::tag("trace") << xml::attr("date") << mbstr
        << xml::attr("profiler_version") << PROFILER_VERSION_MAJOR << '.'
        << PROFILER_VERSION_MINOR << '.' << PROFILER_VERSION_PATCH
        << xml::attr("ocl_version")
#if defined CL_VERSION_2_0
        << "2.0"
#elif defined CL_VERSION_1_2
        << "1.2"
#elif defined CL_VERSION_1_1
        << "1.1"
#elif defined CL_VERSION_1_0
        << "1.0"
#else
# error Cannot match OpenCL version
#endif
        // Those have to be in the same order as the XML schema
        << Profiler::get().getDevices()
        << Profiler::get().getContexts()
        << Profiler::get().getCommandQueues()
        << Profiler::get().getPrograms() 
        << Profiler::get().getKernels()
        << Profiler::get().getInstances()
        << Profiler::get().getMemoryObjects()
        << Profiler::get().getMemoryOperations();

#ifdef TRACK_API_CALLS
    for(int i = 0; i < API::API_FUNCTION_COUNT; ++i) {
      if(API::profile[i].instances>0){
        xml << xml::tag("api") << xml::attr("name") << API::funcname((API::Fct)i)
            << API::profile[i] << xml::endtag();
      }
    }  
#endif
    xml << xml::endtag(/*profile*/);
  }
} logger;

