#ifdef TRACK_PROGRAMS
# include <fstream>
#endif

namespace clap {

// Creational API
template<>
struct Profiler::Hook<API::clCreateKernel> {
  static inline cl_kernel exec(cl_program  program,
                               const char *kernel_name,
                               cl_int *errcode_ret)
  {
    auto ret = API::exec<API::clCreateKernel>(program, kernel_name, errcode_ret);
    get().kernels[ret].name = kernel_name;
    get().kernels[ret].program_id = program;
    return ret;
  }
};

template<>
struct Profiler::Hook<API::clCreateBuffer> {
  static inline cl_mem exec(cl_context context, cl_mem_flags flags, 
                            size_t size, void *host_ptr, cl_int *errcode_ret)
  {
    cl_int _err;
    auto ret = API::getVendorImpl<API::clCreateBuffer>()
      (context,flags,size,host_ptr,&_err);
    if(errcode_ret != nullptr)
      *errcode_ret = _err;

    if(_err == CL_SUCCESS) {
      Stat::Memory obj;
      obj.type = Stat::Memory::Type::Buffer;
      obj.size = size;
      obj.flags = flags;
      get().memobjs[ret] = obj;
    }
    return ret;
  }
};

template<>
struct Profiler::Hook<API::clCreateContext> {
  static inline cl_context exec(const cl_context_properties *properties,
                                cl_uint num_devices,
                                const cl_device_id *devices,
                                void (CL_CALLBACK *pfn_notify)(const char*, const void*,size_t,void*),
                                void *user_data,
                                cl_int *err)
  {
    cl_int _err;
    auto ret = API::getVendorImpl<API::clCreateContext>()
      (properties, num_devices, devices, pfn_notify, user_data, &_err);
    if(err != nullptr) 
      *err = _err; 

    if(_err == CL_SUCCESS) {
      // since we have a device list, register the devices
      for(unsigned int i = 0; i < num_devices; ++i) {
        get().devices[devices[i]].device_id = devices[i];
        get().devices[devices[i]].context_id = ret;
      }
    }
    return ret;
  }
};

template<>
struct Profiler::Hook<API::clCreateContextFromType> {
  static inline cl_context exec(const cl_context_properties *properties, 
                                cl_device_type device_type,
                                void(CL_CALLBACK *pfn_notify)(const char *, const void *, size_t, void *),
                                void *user_data, 
                                cl_int *err)
  {
    cl_int _err; 
    auto ret = API::getVendorImpl<API::clCreateContextFromType>()
      (properties,device_type,pfn_notify,user_data,&_err);
    if(err != nullptr)
      *err = _err;

    if(_err == CL_SUCCESS) { 
      // We don't have the device list, but we can query it
      size_t ret_size = 0;
      API::exec<API::clGetContextInfo>
        (ret,CL_CONTEXT_DEVICES,0,nullptr,&ret_size);
      std::vector<cl_device_id> devs(ret_size/sizeof(cl_device_id));
      API::getVendorImpl<API::clGetContextInfo>()
        (ret,CL_CONTEXT_DEVICES,ret_size,&devs[0],nullptr);
      // register the devices
      for(auto dev : devs) {
        get().devices[dev].device_id = dev;
        get().devices[dev].context_id = ret;
      }
    }
    return ret;
  }
};

#if defined OPENCL_ALLOW_DEPRECATED || !defined CL_VERSION_2_0
template<>
struct Profiler::Hook<API::clCreateCommandQueue> {
  static inline cl_command_queue exec(cl_context context,
                                      cl_device_id device,
                                      cl_command_queue_properties prop,
                                      cl_int *errcode_ret)
  {
    // make sure the command queue has profiling enabled
    cl_int _err;
    auto ret = API::exec<API::clCreateCommandQueue>
      (context, device, prop | CL_QUEUE_PROFILING_ENABLE, &_err);
    if(errcode_ret != nullptr)
      *errcode_ret = _err;

    if(_err == CL_SUCCESS) {
      auto &pod = get().com_queues[ret];
      pod.properties = prop;
      pod.device_id = device;
      return ret;
    }
    return ret;
  }
};
#endif

#ifdef CL_VERSION_2_0
template<>
struct Profiler::Hook<API::clCreateCommandQueueWithProperties> {
  static inline cl_command_queue exec( cl_context context, 
                                       cl_device_id device,
                                       const cl_queue_properties *prop,
                                       cl_int *errcode_ret)
  {
    // make sure the command queue has profiling enabled
    // TODO(tlutz): how do I query the default value of a command queue?
    cl_queue_properties _prop = prop ? *prop | CL_QUEUE_PROFILING_ENABLE : CL_QUEUE_PROFILING_ENABLE;

    cl_int _err; 
    auto ret = API::exec<API::clCreateCommandQueueWithProperties>
      (context, device, &_prop, &_err);
    if(errcode_ret != nullptr) 
      *errcode_ret = _err;

    if(_err == CL_SUCCESS) {
      auto &pod = get().com_queues[ret];
      pod.properties = prop?*prop:0;
      pod.device_id = device;
      return ret;
    }
    return ret;
  }
};
#endif

#ifdef TRACK_PROGRAMS
template<>
struct Profiler::Hook<API::clCreateProgramWithSource> {
  static inline cl_program exec( cl_context context ,
                                 cl_uint count ,
                                 const char **strings ,
                                 const size_t *lengths ,
                                 cl_int *errcode_ret )
  {
    cl_int err;
    auto ret = API::exec<API::clCreateProgramWithSource>
      (context,count,strings,lengths,&err);
    if(errcode_ret != nullptr)
      *errcode_ret = err;

    if(err == CL_SUCCESS) {
      std::string source;
      if(lengths){
        std::size_t buf_size = 0;
        for(unsigned i = 0; i < count; ++i)
          buf_size+=lengths[i];

        source.resize(buf_size);
        char *ptr = &source[0];

        for(unsigned i = 0; i < count; ++i)
          ptr = std::copy(strings[i], strings[i]+lengths[i], ptr);
      }
      else {
        for(unsigned i = 0; i < count; ++i)
          source += strings[i];
      }
      using namespace clap::hashing::sha1;
      std::string proghash = hash((void*)source.data(), source.length());
      get().programs[ret].hash = proghash;

      // save the program if we were asked to
      if(getenv("CLAP_SAVE_PROGRAM")){
        std::ofstream out(proghash + ".cl");
        out.write(source.c_str(), source.length()*sizeof(char));
      }
    }
    return ret;
  }
};
#endif

}

