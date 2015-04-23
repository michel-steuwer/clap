#pragma once

// [External includes]
#include <CL/cl.h>

// [Internal includes]
#include "clap/Stat/Attributes.h"

namespace clap {
namespace Stat {

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

} // namespace Stat
} // namespace clap 

