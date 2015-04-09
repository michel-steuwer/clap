/**
 * Function type traits:
 * get the return type and the type an argument from any callable object
 */
#pragma once

#include <tuple>

namespace He {
namespace detail {
// Helper struct to extract function traits
template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};

template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> {
  using result_t = Ret;
  
  enum { nargs = sizeof...(Args) };
  
  template <size_t i>
  struct arg {
    using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
  };
};

template <typename T, typename Ret, typename... Args>
struct function_traits<Ret(T::*)(Args...) const> {
  using result_t = Ret;

  enum { nargs = sizeof...(Args) };

  template <size_t i>
  struct arg {
    using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
  };
};

template <typename T>
struct function_traits<T&> : public function_traits<T> {};
template <typename T>
struct function_traits<const T&> : public function_traits<T> {};
template <typename T>
struct function_traits<volatile T&> : public function_traits<T> {};
template <typename T>
struct function_traits<const volatile T&> : public function_traits<T> {};
template <typename T>
struct function_traits<T&&> : public function_traits<T> {};
template <typename T>
struct function_traits<const T&&> : public function_traits<T> {};
template <typename T>
struct function_traits<volatile T&&> : public function_traits<T> {};
template <typename T>
struct function_traits<const volatile T&&> : public function_traits<T> {};

} // namespace detail
} // namespace He

