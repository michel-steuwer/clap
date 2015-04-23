#pragma once

// [Standard includes]
#include <string>

// [Local includes]
#include "clap/Stat/Attributes.h"

namespace clap {
namespace Stat {

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

} // namespace Stat
} // namespace clap 

