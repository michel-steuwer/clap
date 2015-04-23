#pragma once

// [Internal includes]
#include "clap/Stat/Attributes.h"

namespace clap {
namespace Stat {

/// @brief cl_context stats.
struct Context final 
  : public AttributeSet<Identifiable<Context> __RefCounted> {};

} // namespace Stat
} // namespace clap 

