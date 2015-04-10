#pragma once

#include <functional>

namespace clap {
class ScopeGuard {
  std::function<void()> f;
public: 
  template<class Callable> 
  ScopeGuard(Callable && fct) : f(std::forward<Callable>(fct)) {}
  ~ScopeGuard() { f(); }
};
}
