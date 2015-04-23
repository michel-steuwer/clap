#pragma once

// [External includes]
#include <CL/cl.h>

// [Internal includes]
#include "clap/Stat/Attributes.h"

namespace clap {
namespace Stat {

// ******************************************************************
// OpenCL objects

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

} // namespace Stat
} // namespace clap

