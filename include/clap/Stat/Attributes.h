#pragma once

// [Standard includes]
#include <memory>
#include <vector>
#include <string>
#ifdef TRACK_KERNEL_ARGUMENTS
# include <cstdint>
# include <algorithm>
#endif

// [External includes]
#include <CL/cl.h>

// [Internal includes]
#include "clap/feature.h"
#include "clap/utils/Casting.h"

namespace clap {
namespace Stat {

// ******************************************************************
// Properties shared by multiple objects.

/// @brief Any object with a unique identifier
template <typename T>
struct Identifiable {
  /// @brief A unique identifier for this counter
  std::size_t id;
  
  /// @brief Constructor: sets and increments the id
  Identifiable() : id(++count) { }  

  Identifiable(const Identifiable & other)
    : id{other.id} {}

private:
  /// @brief Counter for instances of T 
  static int count;
};
template <typename T> int Identifiable<T>::count( 0 );

/// @brief Objects with unique identifiers.
/// @detail Unique identifiers are monotonically increasing, they are
///   used to find the relative ordering for operations of different types.
struct UniqueIdentifiable {
  /// @brief A unique identifier
  const std::size_t id;

  // @brief Constructor: sets and increments the id
  UniqueIdentifiable() : id(++getCount()) { }  

private:
  std::size_t &getCount() {
    static std::size_t count = 0;
    return count;
  }
};

#ifdef TRACK_REFCOUNT
/// @brief Any reference counted object
// Instead of counting only the current reference count, we track the 
// total number of retain and release. 
struct RefCounted {
  /// @brief Number of retain (the reference count starts at 1)
  int retain = 1;

  /// @brief Number of release
  int release = 0;
};
# define __RefCounted , RefCounted
#else
# define __RefCounted
#endif

#ifdef TRACK_EVENTS
/// Any object with an associated event
struct Timeable {
  cl_event _event = nullptr;
  bool forced_event = false;
};
# define __Timeable , Timeable
#else
# define __Timeable
#endif

/// Any object in a command queue
struct Enqueued {
  /// @brief ID of the queued used for the operation.
  cl_command_queue queue_id;
};

/// Any object with a size
struct Sizeable {
  /// @brief Size of the object
  std::size_t size = 0;
};

namespace detail {
template<typename From, typename To>
struct Cloneable : public From {
  template<typename ... Args>
  Cloneable(Args&&... args)
    : From(std::forward<Args>(args)...)
  {}

  std::unique_ptr<From> clone() const override 
  { return std::unique_ptr<From>{new To(static_cast<const To&>(*this))}; }
};
} // namespace detail 

// ******************************************************************
/// @brief Properties wrapper. 
/// @details Exposes inheritance through CRTP and provides an alias for the TL.
/// @tparam T The list of properties to inherit from
template<typename... T>
struct AttributeSet : public T... {
  /// @brief Alias of the type list
  using attribute_t = AttributeSet<T...>;
};

} // namespace Stat
} // namespace clap 
