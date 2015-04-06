#include "utils/hash.h"
#include <cstdint>
#include <cstring>

namespace he {
namespace sha1 {
namespace detail {
  constexpr std::uint32_t rol(const std::uint32_t value, const std::uint32_t steps)
  { return ((value << steps) | (value >> (32 - steps))); }

  void hash(std::uint32_t* digest, std::uint32_t* w)
  {
    auto a = digest[0];
    auto b = digest[1];
    auto c = digest[2];
    auto d = digest[3];
    auto e = digest[4];

#define sha1macro(func,val) \
    const auto t = rol(a, 5) + (func) + e + val + w[round]; \
    e = d; d = c; \
    c = rol(b, 30); \
    b = a; a = t; 

    int round = 0;
    for(;round < 16;++round) {
      sha1macro((b & c) | (~b & d), 0x5a827999);
    }
    for(;round < 20;++round) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro((b & c) | (~b & d), 0x5a827999);
    }
    for(;round < 40;++round) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro(b ^ c ^ d, 0x6ed9eba1);
    }
    for(;round < 60;++round) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro((b & c) | (b & d) | (c & d), 0x8f1bbcdc);
    }
    for(;round < 80;++round) {
      w[round] = rol((w[round - 3] ^ w[round - 8] ^ w[round - 14] ^ w[round - 16]), 1);
      sha1macro(b ^ c ^ d, 0xca62c1d6);
    }
#undef sha1macro

    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;
  }
} // namespace detail

std::string hash(const void* src, const size_t length)
{
  std::uint8_t hash[20];
  std::uint32_t digest[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };
  const std::uint8_t* barray = reinterpret_cast<const std::uint8_t*>(src);
  std::uint32_t w[80];

  int curBlk = 0, lastBlkPos = 0;

  while (curBlk <= (int)length - 64) {
    for (int pos = 0, end = curBlk + 64; curBlk < end; curBlk += 4) 
      w[pos++] = (std::uint32_t) barray[curBlk + 3]
        | (((std::uint32_t) barray[curBlk + 2]) << 8)
        | (((std::uint32_t) barray[curBlk + 1]) << 16)
        | (((std::uint32_t) barray[curBlk]) << 24);
    detail::hash(digest, w);
  }

  std::memset(w,0,16*4);
  for (;lastBlkPos < (int)length - curBlk; ++lastBlkPos)
    w[lastBlkPos >> 2] |= (std::uint32_t) barray[lastBlkPos + curBlk] << ((3 - (lastBlkPos & 3)) << 3);
  w[lastBlkPos >> 2] |= 0x80 << ((3 - (lastBlkPos & 3)) << 3);
  
  if (length - curBlk >= 56) {
    detail::hash(digest, w);
    std::memset(w,0,16*4); 
  }
  w[15] = length << 3;
  detail::hash(digest, w);

  for (int hashByte = 20; --hashByte >= 0;) 
    hash[hashByte] = (digest[hashByte >> 2] >> (((3 - hashByte) & 0x3) << 3)) & 0xff;

  std::string hex;
  hex.reserve(40);
  for (int i = 0; i < 20; i++) {
    static const char dec2hex[17] = "0123456789abcdef";
    hex += dec2hex[(hash[i] >> 4) & 15];
    hex += dec2hex[ hash[i]       & 15];
  }
  return hex;
}
} // namespace sha1
} // namespace he
