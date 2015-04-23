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

namespace clap {
namespace Stat {

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

} // namespace Stat
} // namespace clap 

