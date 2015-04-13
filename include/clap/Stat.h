#pragma once

#ifdef TRACK_KERNEL_ARGUMENTS
#include <cstdint>
#include <algorithm>
#endif

#include <CL/cl.h>
#include <memory>
#include <vector>

#include "clap/feature.h"
#include "clap/utils/Casting.h"
namespace Stat {

// ******************************************************************
// Properties shared by multiple objects.

/// @brief Any object with a unique identifier
template <typename T>
struct Identifiable {
  /// @brief Counter for instances of T
  static int count;

  /// @brief A unique identifier for this counter
  int id;
  
  /// @brief Constructor: sets and increments the id
  Identifiable() { id = ++count; }  
};
template <typename T> int Identifiable<T>::count( 0 );

#ifdef TRACK_REFCOUNT
/// @brief Any reference counted object
// Instead of counting only the current reference count, we track the 
// total number of retain and release. 
struct RefCounted {
  /// @brief Number of retain (the reference count starts at 1)
  int retain = 1;

  /// @brief Number of release
  int release = 0;
};
# define __RefCounted , RefCounted
#else
# define __RefCounted
#endif

#ifdef TRACK_EVENTS
/// Any object with an associated event
struct Timeable {
  cl_event _event = nullptr;
  bool forced_event = false;
  long queued = 0;
  long submit = 0;
  long start = 0;
  long end = 0;
};
# define __Timeable , Timeable
#else
# define __Timeable
#endif

/// Any object in a command queue
struct Enqueued {
  /// @brief ID of the queued used for the operation.
  cl_command_queue queue_id;
};

/// Any object with a size
struct Sizeable {
  /// @brief Size of the object
  std::size_t size = 0;
};


// ******************************************************************
/// @brief Properties wrapper. 
/// @details Exposes inheritance through CRTP and provides an alias for the TL.
/// @tparam T The list of properties to inherit from
template<typename... T>
struct AttributeSet : public T... {
  /// @brief Alias of the type list
  using attribute_t = AttributeSet<T...>;
};



// ******************************************************************
// Helper classes

/// @brief An NDRange, used to specify local/global sizes and offsets.
struct NDRange {
  /// @brief dimensionality
  unsigned int dim = 0;
  /// @brief Size in the x dimension
  size_t x = 0;
  /// @brief Size in the y dimension
  size_t y = 0;
  /// @brief Size in the z dimension
  size_t z = 0;

  /// @brief Default constructor, creates an empty range
  NDRange(){}

  /// @brief Initialize a range from an array
  /// @param dim Size of the array
  /// @param p Array of sizes
  NDRange(unsigned int dim, const size_t *p)
    : dim{p?dim:0}
  {
    if(p) {
      x = dim>0?p[0]:0;
      y = dim>1?p[1]:0;
      z = dim>2?p[2]:0;
    }
  }
};

/// @brief An enqueued memory operation.
struct MemOperation: public AttributeSet<Identifiable<MemOperation>, 
                                         Enqueued __Timeable> {
  /// @brief Type of memory operation
  /// @var type Memory operation type
  enum class Type { 
    Read,      /// < A read operation from host to device
    Write,     /// < A write operation from host to device
    Copy_scr,  /// < The source of a copy operation
    Copy_dst   /// < The destination of a copy operation
  } type;
  
  cl_mem _mem;
  
  bool blocking;
};

#ifdef TRACK_KERNEL_ARGUMENTS
/// @brief Kernel argument.
struct KernelArgument: public AttributeSet<Sizeable> {
  /// @brief Type of kernel argument
  enum class Type { 
    MemObject, 
    Data, 
    Local
    /*, Sampler*/ 
  } type;

  KernelArgument(Type t, const size_t s)
   : type(t)
  { size = s; }
  virtual ~KernelArgument(){}

  virtual KernelArgument* clone() const = 0;
};

namespace Argument {
namespace detail {
template<typename T>
struct Cloneable : public KernelArgument {
  Cloneable(Type t, const size_t s)
    : KernelArgument(t,s)
  {}

  KernelArgument* clone() const override 
  { return new T(static_cast<const T&>(*this)); }
};
} 

/// @brief kernel argument representing a memory object
struct MemObject final: public detail::Cloneable<MemObject> {
  int mem_object_id = -1;
  MemObject(int id)
    : detail::Cloneable<MemObject>{KernelArgument::Type::MemObject,sizeof(cl_mem)}
    , mem_object_id{id}
  {}

  static bool classof(const KernelArgument *arg)
  { return arg->type == KernelArgument::Type::MemObject; }
};

/// @brief Attribute representing raw data
struct Data final: public detail::Cloneable<Data> { 
  std::vector<std::uint8_t> data;
  Data(const void *vptr, const size_t size)
    : detail::Cloneable<Data>{KernelArgument::Type::Data,size}
  {
    const std::uint8_t *ptr = static_cast<const std::uint8_t*>(vptr);
    data.resize(size);
    std::copy(ptr, ptr+size, std::begin(data));
  }

  static bool classof(const KernelArgument *arg)
  { return arg->type == KernelArgument::Type::Data; }
};

/// @brief Attribute representing local memory
struct Local final: public detail::Cloneable<Local> {
  Local(size_t size)
    : detail::Cloneable<Local>{KernelArgument::Type::Local,size}
  {}

  static bool classof(const KernelArgument *arg)
  { return arg->type == KernelArgument::Type::Local; }
};
} // namespace argument
#endif


/// @brief An enqueued kernel instance.
struct KernelInstance : public AttributeSet<Identifiable<KernelInstance>, 
                                            Enqueued __Timeable> {
  /// @brief Kernel ID of the launched kernel (FK)
  cl_kernel kernel_id = nullptr;
  NDRange offset;
  NDRange global;
  NDRange local;
#ifdef TRACK_KERNEL_ARGUMENTS
  std::vector<std::unique_ptr<KernelArgument>> arguments;
#endif
};

// ******************************************************************
// OpenCL objects

/// @brief cl_mem stats.
struct Memory final : public AttributeSet<Identifiable<Memory> __RefCounted > {
  /// @brief Type of memory object.
  enum class Type { Buffer, Image, Subbuffer } type;

  /// @brief Allocated size, in bytes.
  size_t size = 0;

  /// @brief Allocation flags.
  cl_mem_flags flags = 0;

  /// @brief List of memory operations using this buffer.
  std::vector<MemOperation> operations;
};

/// @brief cl_kernel stats.
struct Kernel final : public AttributeSet<Identifiable<Kernel> __RefCounted> {
  /// @brief OpenCL handle on the program containing this kernel
  cl_program program_id = nullptr; // FK

  /// @brief Name of the kernel function
  std::string name;
  
  /// @brief List of instances
  std::vector<KernelInstance> instances;

#ifdef TRACK_KERNEL_ARGUMENTS
  /// @brief List of arguments
  /// @note Only available if TRACK_KERNEL_ARGUMENTS is set
  std::vector<std::unique_ptr<KernelArgument>> arguments;
#endif
};

/// @brief cl_program stats.
struct Program final : public AttributeSet<Identifiable<Program> __RefCounted> {
  /// @brief Options used when the program was built.
  std::string build_options;

#ifdef TRACK_PROGRAMS
  /// @brief Hash of the device code (SHA-1 by default)
  /// @note Only available if TRACK_PROGRAMS is set
  std::string hash;
#endif
};

/// @brief cl_command_queue stats.
struct CommandQueue final : public AttributeSet<Identifiable<CommandQueue> __RefCounted> {
  /// @brief OpenCL handle representing this oject
  cl_device_id device_id = nullptr; // FK

  /// @brief Properties used for construction
  /// @warning OpenCL 2.0 introduced default properties for command queues which cannot
  ///  be queried. We need to find a way to do this.
  cl_command_queue_properties properties;
};

/// @brief cl_device_id stats.
struct Device final : public AttributeSet<Identifiable<Device> 
#ifdef CL_VERSION_1_2
                                          __RefCounted /* Only reference counted since OCL 1.2 */
#endif
                                          > {

  /// @brief Name as returned by CL_DEVICE_NAME
  std::string name;
};

/// @brief cl_context stats.
struct Context final : public AttributeSet<Identifiable<Context> __RefCounted> {};


// ******************************************************************
// host profiling

#ifdef TRACK_API_CALLS
/// @brief Stats for the host functions.
struct HostFunction {
  /// @brief Number of invocations.
  unsigned int instances = 0;

  /// @brief Total time spent executing this function (excluding hooks).
  double time = 0;

#ifdef DEBUG_TRACK_OVERHEAD
  /// @brief Total time spent executing this function (including hooks).
  /// @note Only available if DEBUG_TRACK_OVERHEAD is set.
  double total_time = 0;
#endif

  /// @brief Add an instance
  /// @param t time spent for the invocation.
  HostFunction& operator+=(const double t) {
    instances++;
    time += t;
    return *this;
  }
};
#endif

}

