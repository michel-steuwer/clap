#pragma once

// [Standard includes]
#include <memory>
#include <vector>
#include <string>
#ifdef TRACK_KERNEL_ARGUMENTS
# include <cstdint>
# include <algorithm>
#endif

// [External includes]
#include <CL/cl.h>

// [Internal includes]
#include "clap/feature.h"
#include "clap/utils/Casting.h"

namespace Stat {

// ******************************************************************
// Properties shared by multiple objects.

/// @brief Any object with a unique identifier
template <typename T>
struct Identifiable {
  /// @brief A unique identifier for this counter
  std::size_t id;
  
  /// @brief Constructor: sets and increments the id
  Identifiable() : id(++count) { }  

  Identifiable(const Identifiable & other)
    : id{other.id} {}

private:
  /// @brief Counter for instances of T 
  static int count;
};
template <typename T> int Identifiable<T>::count( 0 );

/// @brief Objects with unique identifiers.
/// @detail Unique identifiers are monotonically increasing, they are
///   used to find the relative ordering for operations of different types.
struct UniqueIdentifiable {
  /// @brief A unique identifier
  const std::size_t id;

  // @brief Constructor: sets and increments the id
  UniqueIdentifiable() : id(++getCount()) { }  

private:
  std::size_t &getCount() {
    static std::size_t count = 0;
    return count;
  }
};

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
                                         UniqueIdentifiable,
                                         Enqueued __Timeable> {
  /// @brief Type of memory operation
  /// @var type Memory operation type
  enum class Type { 
    Read,      /// < A read operation from host to device
    Write,     /// < A write operation from host to device
    Copy_src,  /// < The source of a copy operation
    Copy_dst   /// < The destination of a copy operation
  } type;
  
  cl_mem mem_id;
  
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
struct KernelInstance final
  : public AttributeSet<Identifiable<KernelInstance>, 
                        UniqueIdentifiable,
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
struct Memory final 
  : public AttributeSet<Identifiable<Memory> __RefCounted > {

  /// @brief Type of memory object.
  enum class Type { Buffer, Image, Subbuffer } type;

  /// @brief Allocated size, in bytes.
  size_t size = 0;

  /// @brief Allocation flags.
  cl_mem_flags flags = 0;
};

/// @brief cl_kernel stats.
struct Kernel final 
  : public AttributeSet<Identifiable<Kernel> __RefCounted> {

  /// @brief OpenCL handle on the program containing this kernel
  cl_program program_id = nullptr; // FK

  /// @brief Name of the kernel function
  std::string name;
  
#ifdef TRACK_KERNEL_ARGUMENTS
  /// @brief List of arguments
  /// @note Only available if TRACK_KERNEL_ARGUMENTS is set
  std::vector<std::unique_ptr<KernelArgument>> arguments;
#endif
};

/// @brief cl_program stats.
struct Program final 
  : public AttributeSet<Identifiable<Program> __RefCounted> {
  
  /// @brief Options used when the program was built.
  std::string build_options;

#ifdef TRACK_PROGRAMS
  /// @brief Hash of the device code (SHA-1 by default)
  /// @note Only available if TRACK_PROGRAMS is set
  std::string hash;
#endif
};

/// @brief cl_command_queue stats.
struct CommandQueue final 
  : public AttributeSet<Identifiable<CommandQueue> __RefCounted> {
  
  /// @brief OpenCL handle representing this object
  cl_device_id device_id = nullptr; // FK

  /// @brief Properties used for construction
  /// @warning OpenCL 2.0 introduced default properties for command queues which cannot
  ///  be queried. We need to find a way to do this.
  cl_command_queue_properties properties;
};

/// @brief cl_device_id stats.
struct Device final 
  : public AttributeSet<Identifiable<Device> 
#ifdef CL_VERSION_1_2
                         __RefCounted /* Only reference counted since OCL 1.2 */
#endif
                         > {

  /// @brief OpenCL device handle
  /// Unlike the other objects, devices are not created directly. Instead
  /// the profiler inspects the context creation and tracks the associated
  /// devices.
  cl_device_id device_id;

  /// @brief context id
  cl_context context_id;
};

/// @brief cl_context stats.
struct Context final : public AttributeSet<Identifiable<Context> __RefCounted> {};


// ******************************************************************
// host profiling

#ifdef TRACK_API_CALLS
/// @brief Stats for the host functions.
struct HostFunction final {
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

