extern "C" {
#include <dlfcn.h>
}
#include <iostream>
#include "clap/API.h"

using namespace clap;

#ifdef TRACK_API_CALLS
std::array<Stat::HostFunction, API::API_FUNCTION_COUNT> API::profile;
#endif

// Vendor implementation lookup 
#define CLFUNC(X) \
template<> API::fctptr_t<API:: X > API::getVendorImpl<API:: X >() { \
  using safe_dlsym_t = API::fctptr_t<API:: X >(*)(void *, const char *);\
  static auto _nat = reinterpret_cast<safe_dlsym_t>(dlsym)(RTLD_NEXT, #X); \
  if(_nat == nullptr) std::clog << "Linker lookup failed for " << API::funcname(API:: X) << std::endl; \
  return _nat; }
#include "clap/clfunc.def"
#undef CLFUNC 

// enum to string util
const std::string& API::funcname(Fct fct) {
  static const std::string names[API::API_FUNCTION_COUNT+1] = {
#define CLFUNC(X) #X,
#include "clap/clfunc.def"
#undef CLFUNC
    "marker"
  };
  return names[fct];
}


