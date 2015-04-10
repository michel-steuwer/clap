#pragma once

#include <tuple>
#include <chrono>
#include <array>

#include "CL/cl.h"
#include "CL/cl_deprecated.h"

#include "clap/Stat.h"
#include "clap/utils/ScopeGuard.h"
#include "clap/utils/function_traits.h"
#include "clap/feature.h"

namespace clap {
/**
 * API and vendor implementation forward class.
 * Defines the prototypes of the OpenCL API functions and get pointers on the
 * ICD loader functions.
 */
struct API {
  /// @brief Enum containing all API functions
  enum Fct { 
#define CLFUNC(X) X,
#include "clap/clfunc.def"
#undef CLFUNC
    API_FUNCTION_COUNT
  };

  /// @brief lookup a function type by its name
  template<Fct fct> struct lookup { using type = void; }; 

  /// @brief Alias for API function type
  template<Fct fct>  using fctptr_t = typename lookup<fct>::type;

  /// @brief Alias for API function return type
  template<Fct fct>  using return_t = 
    typename detail::function_traits<fctptr_t<fct>>::result_t;

  /// @brief Alias for API function parameter type
  template<Fct fct, int i>  using argument_t = 
    typename detail::function_traits<fctptr_t<fct>>::template arg<i>::type;

  /// @brief Get function pointer on ICD loader
  template<Fct fct> [[gnu::pure]] static inline fctptr_t<fct> getVendorImpl();

  /// @brief Get original function name
  static const std::string& funcname(Fct fct);

#ifdef TRACK_API_CALLS
  /// @brief Profile information for the host functions
  static std::array<Stat::HostFunction, API::API_FUNCTION_COUNT> profile;
#endif

  /// @brief API call sink
  template<API::Fct fct, typename ... Args>
  static inline API::return_t<fct> exec(Args&&... args); 
};

// Define type traits for the API types
#define CLFUNC(X) \
  template<> \
  struct API::lookup<API:: X > { using type = decltype(&:: X ); };
#include "clap/clfunc.def"
#undef CLFUNC

// ICD loader dispatch is defined in the source file
#define CLFUNC(X) template<> API::fctptr_t<API:: X > API::getVendorImpl<API:: X >();
#include "clfunc.def"
#undef CLFUNC

// Sink: time and forward
template<API::Fct fct, typename ... Args>
inline API::return_t<fct> API::exec(Args&&... args) 
{
#ifdef TRACK_API_CALLS
  // start timer
  const auto start = std::chrono::high_resolution_clock::now();
  ScopeGuard guard{[=]{
    // stop timer
    auto end = std::chrono::high_resolution_clock::now();
    // register call
    API::profile[fct] += std::chrono::duration<double>(end-start).count();
  }};
#endif
  // forward
  return API::getVendorImpl<fct>()(std::forward<Args>(args)...);
}

} // namespace clap

