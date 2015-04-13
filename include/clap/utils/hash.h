#pragma once
#include <string>

namespace clap {
/// @namespace hasking Contains the hashing function utilities
namespace hashing {

/// @namespace sha1 SHA-1 hashing
namespace sha1 { 
/// @brief Hash raw data
/// @param src Pointer on the data to hash
/// @param length Size of the buffer, in bytes
/// @return A 40 char HEX checksum
/// @note This functions cannot do any kind of bound checking
std::string hash(const void* src, const size_t length); 
} 

/// @namespace sha256 SHA-256 hashing
namespace sha256 { 
/// @brief Hash raw data
/// @param src Pointer on the data to hash
/// @param length Size of the buffer, in bytes
/// @return A 64 char HEX checksum
/// @note This functions cannot do any kind of bound checking
std::string hash(const void* src, const size_t length); 
}

/// @namespace md5 MD5 hashing
namespace md5 { 
/// @brief Hash raw data
/// @param src Pointer on the data to hash
/// @param length Size of the buffer, in bytes
/// @return A 32 char HEX checksum
/// @note This functions cannot do any kind of bound checking
std::string hash(const void* src, const size_t length); 
}
} // namespace hash
} // namespace clap

