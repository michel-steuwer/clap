#pragma once

// [Standard includes]
#include <memory>
#include <vector>
#include <string>
#ifdef TRACK_KERNEL_ARGUMENTS
# include <cstdint>
# include <algorithm>
#endif

// [Internal includes]
#include "clap/Stat/Attributes.h"
#include "clap/Stat/NDRange.h"

namespace clap {
namespace Stat {

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

  virtual std::unique_ptr<KernelArgument> clone() const = 0;
};

namespace Argument {

/// @brief kernel argument representing a memory object
struct MemObject final
  : public detail::Cloneable<KernelArgument,MemObject> {

  int mem_object_id = -1;
  MemObject(int id)
    : detail::Cloneable<KernelArgument,MemObject>{KernelArgument::Type::MemObject,sizeof(cl_mem)}
    , mem_object_id{id}
  {}

  static bool classof(const KernelArgument *arg)
  { return arg->type == KernelArgument::Type::MemObject; }
};

/// @brief Attribute representing raw data
struct Data final
  : public detail::Cloneable<KernelArgument,Data> { 

  std::vector<std::uint8_t> data;
  Data(const void *vptr, const size_t size)
    : detail::Cloneable<KernelArgument,Data>{KernelArgument::Type::Data,size}
  {
    const std::uint8_t *ptr = static_cast<const std::uint8_t*>(vptr);
    data.resize(size);
    std::copy(ptr, ptr+size, std::begin(data));
  }

  static bool classof(const KernelArgument *arg)
  { return arg->type == KernelArgument::Type::Data; }
};

/// @brief Attribute representing local memory
struct Local final
  : public detail::Cloneable<KernelArgument,Local> {

  Local(size_t size)
    : detail::Cloneable<KernelArgument,Local>{KernelArgument::Type::Local,size}
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

} // namespace Stat
} //namespace clap 

