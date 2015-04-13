/**
 * Function type traits:
 * get the return type and the type an argument from any callable object
 */
#pragma once

#include <tuple>

namespace clap {

/// @brief Get type information from something callable
/// @tparam T An object which defines the function operator
template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};

/// @brief Get type information from afunction pointer
/// @tparam Ret Return type
/// @tparam Args Argument types
template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> {
  /// @brief Alias for the return type
  using result_t = Ret;
  
  /// @brief Number of parameters
  enum { nargs = sizeof...(Args) };
  
  /// @brief Wrapper struct for the arguments
  /// @tparam i Parameter index
  template <size_t i>
  struct arg {
    /// @brief Type of the ith argument
    using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
  };
};


/// @brief Get type information from a member function pointer
/// @tparam Target class
/// @tparam Ret Return type
/// @tparam Args Argument types
template <typename T, typename Ret, typename... Args>
struct function_traits<Ret(T::*)(Args...) const> {
  /// @brief Alias for the return type
  using result_t = Ret;

  /// @brief Number of parameters
  enum { nargs = sizeof...(Args) };

  /// @brief Wrapper struct for the arguments
  /// @tparam i Parameter index
  template <size_t i>
  struct arg {
    /// @brief Type of the ith argument
    using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
  };
};


/// @cond HIDDEN_SYMBOLS
// define aliases for different crv variants
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
/// @endcond

} // namespace clap

