#pragma once

namespace clap {
namespace Stat {

/// @brief An NDRange, used to specify local/global sizes and offsets.
struct NDRange {
  /// @brief dimensionality
  unsigned int dim = 0;
  /// @brief Size in the x dimension
  size_t x = 0;
  /// @brief Size in the y dimension
  size_t y = 0;
  /// @brief Size in the z dimension
  size_t z = 0;

  /// @brief Default constructor, creates an empty range
  NDRange(){}

  /// @brief Initialize a range from an array
  /// @param dim Size of the array
  /// @param p Array of sizes
  NDRange(unsigned int dim, const size_t *p)
    : dim{p?dim:0}
  {
    if(p) {
      x = dim>0?p[0]:0;
      y = dim>1?p[1]:0;
      z = dim>2?p[2]:0;
    }
  }
};

} // namespace Stat
} // namespace clap 

