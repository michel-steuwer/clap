/**
 * Casting utilities for LLVM-style RTTI.
 * isa<T>: returns true if the argument is a T
 * dyn_cast<T>: returns a casted pointer is the arg is a T.
 * downcast_switch: takes a list of functions and try to downcast for each.
 */
#pragma once
#include <utils/function_traits.h>

namespace He {
// isa<T>
template <class X, class Y>
inline bool isa(const Y &Val) 
{ return X::classof(&Val); }

// dyn_cast<T>
template <class To, class From>
inline To* dyn_cast(From &v) 
{ return To::classof(v) ? static_cast<To*>(v) : nullptr; }

template <class To, class From>
inline const To* dyn_cast(const From &v) 
{ return To::classof(v) ? static_cast<const To*>(v) : nullptr; }

// downcast_switch
namespace detail {
template<typename T>
struct DownCastSwitch {
  T* ptr;

  DownCastSwitch(T* p) : ptr{p} {}

  template<typename Fct, typename... Fcts>
  struct COR {
    static bool apply(T* ptr, Fct fct, Fcts... fcts) {
      using fct_t = He::detail::function_traits<Fct>;
      using arg_t = typename fct_t::template arg<0>::type;
      if(auto c_ptr = dyn_cast<typename std::remove_pointer<arg_t>::type>(ptr)) {
        fct(c_ptr);
        return true;
      }
      return COR<Fcts...>::apply(ptr, std::forward<Fcts>(fcts)...);
    }
  };

  template<typename Fct>
  struct COR<Fct> {
    static bool apply(T *ptr, Fct &&fct){
      using fct_t = He::detail::function_traits<Fct>;
      using arg_t = typename fct_t::template arg<0>::type;
      if(auto c_ptr = dyn_cast<typename std::remove_pointer<arg_t>::type>(ptr)) {
        fct(c_ptr);
        return true;
      }
      return false;
    }
  };

  template <typename... Fs>
  bool operator()(Fs&&... f)  
  {
    return COR<Fs...>::apply(ptr, std::forward<Fs>(f)...);
  }
};
} // namespace detail

template<typename T>
detail::DownCastSwitch<T> downcast_switch(T* t) {
  return detail::DownCastSwitch<T>(t);
}

} // namespace He

