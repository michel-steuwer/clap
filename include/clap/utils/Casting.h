/**
 * Casting utilities for LLVM-style RTTI.
 * isa<T>: returns true if the argument is a T
 * dyn_cast<T>: returns a casted pointer is the arg is a T.
 * downcast_switch: takes a list of functions and try to downcast for each.
 */
#pragma once
#include <clap/utils/function_traits.h>

namespace clap {

/// @brief Check if an object is of type T
/// @tparam X Type to check against
/// @tparam Y Source type (deduced)
/// @param Val Object to convert
/// @return true if Val is a X
/// @note read LLVM 'RTTI' doc to know how to make it work for
///  other classes
template <class X, class Y>
inline bool isa(const Y &Val) 
{ return X::classof(&Val); }

/// @brief Try to convert a From to a To
/// @tparam To Type to convert to
/// @tparam From Source type (deduced)
/// @param v Object to convert
/// @return v converted to a To* or null
/// @note read LLVM 'RTTI' doc to know how to make it work for
///  other classes
template <class To, class From>
inline To* dyn_cast(From &v) 
{ return To::classof(v) ? static_cast<To*>(v) : nullptr; }

/// @cond HIDDEN_SYMBOLS
/// Implementation details

/// @brief Same thing as dyn_cast but for const objects
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
      using fct_t = function_traits<Fct>;
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
      using fct_t = function_traits<Fct>;
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

/// @endcond

/// @brief Try to downcast an object and execute a function if successful
/// @tparam Object The type of the object to downcast
/// @tparam A list of callable types taking a single argument
/// @param t Object to downcast
/// @param cases The list of cases
/// @return False if all cases fail, true otherwise
template<typename Object, typename... Cases>
bool downcast_switch(Object* t, Cases&&... cases) 
{
  return detail::DownCastSwitch<Object>(t)
    (std::forward<Cases>(cases)...);
}

} // namespace clap

