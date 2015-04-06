#pragma once
#include <string>

namespace he {
namespace sha1   { std::string hash(const void* src, const size_t length); } 
namespace sha256 { std::string hash(const void* src, const size_t length); }
namespace md5    { std::string hash(const void* src, const size_t length); }
}

