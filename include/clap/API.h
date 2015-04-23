#pragma once

// [Standard includes]
#include <tuple>
#include <chrono>
#include <array>

// [External includes]
#include "CL/cl.h"
#include "CL/cl_deprecated.h"

// [Local includes]
#include "clap/Stat/API.h"
#include "clap/utils/ScopeGuard.h"
#include "clap/utils/function_traits.h"
#include "clap/feature.h"

namespace clap {
/**
 * @class API
 * @brief API and vendor implementation forward class.
 * @details 
 * Defines the prototypes of the OpenCL-API functions and get pointers on the
 * ICD loader functions.
 *
 * The wrapper times the execution of the vendor implementation and counts the number of
 * invocations if requested.
 */
struct API {
  /// @brief Enum containing all API functions
  /// @note This should NOT be a class enum since it is used for indexing in an std::array
  enum Fct { 
#define CLFUNC(X) X,
#include "clap/clfunc.inc"
#undef CLFUNC
    API_FUNCTION_COUNT
  };

  /// @brief Lookup a function type by its name
  /// @tparam fct The function identifier 
  template<Fct fct> struct lookup { using type = void; }; 

  /// @brief Alias for API function type
  /// @tparam fct The function identifier 
  template<Fct fct>  using fctptr_t = typename lookup<fct>::type;

  /// @brief Alias for API function return type
  /// @tparam fct The function identifier
  template<Fct fct>  using return_t = 
  typename function_traits<fctptr_t<fct>>::result_t;

  /// @brief Alias for API function parameter type
  /// @tparam fct The function identifier
  /// @tparam i Argument index
  template<Fct fct, int i>  using argument_t = 
  typename function_traits<fctptr_t<fct>>::template arg<i>::type;

  /// @brief Get function pointer on ICD loader
  /// @tparam fct The function identifier 
  /// @return a function pointer on the ICD function
  /// @note This function bypasses the stat gathering performed by \ref exec.
  ///       It should be used by the hook implementations only.
  template<Fct fct> [[gnu::pure]] static inline fctptr_t<fct> getVendorImpl();

  /// @brief Get original function name
  /// @param fct The function identifier
  /// @return A string representation of the idendifier
  static const std::string& funcname(Fct fct);

#ifdef TRACK_API_CALLS
  /// @brief Profile information for the host functions
  /// @note Only enabled if TRACK_API_CALLS is set
  static std::array<clap::Stat::HostFunction, API::API_FUNCTION_COUNT> profile;
#endif

  /// @brief API call sink
  /// @tparam fct Function identifier for the hook
  /// @tparam args The function argument types are deduced from the call
  /// @param args The arguments to forward to the vendor implementation
  /// @return Whatever the vendor implementation returns
  template<API::Fct fct, typename ... Args>
  static inline API::return_t<fct> exec(Args&&... args); 
};

// Define type traits for the API types
#define CLFUNC(X) \
  template<> \
  struct API::lookup<API:: X > { using type = decltype(&:: X ); };
#include "clap/clfunc.inc"
#undef CLFUNC

// ICD loader dispatch is defined in the source file
#define CLFUNC(X) template<> API::fctptr_t<API:: X > API::getVendorImpl<API:: X >();
#include "clfunc.inc"
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

