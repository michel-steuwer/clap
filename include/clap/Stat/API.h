#pragma once

namespace clap {
namespace Stat {

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

} // namespace Stat
} // namespace clap

