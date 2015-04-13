#pragma once

// [Standard includes]
#include <functional>
#include <utility>

namespace clap {
/// @brief RAII-style callback
class ScopeGuard {
  /// @brief Callback triggered when the object goes out of scope
  std::function<void()> f;
public: 
  /// @brief Constructor
  /// @tparam Callable Any callable type
  /// @param fct A callable object
  template<class Callable> 
  ScopeGuard(Callable && fct) 
    : f(std::forward<Callable>(std::move(fct))) 
  {}

  /// @brief Destructor: triggers the callback
  ~ScopeGuard() { f(); }
};
}
