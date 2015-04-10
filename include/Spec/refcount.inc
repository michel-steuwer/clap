// retain/release
#define HELIUM_RETAIN_RELEASE(Func,Handle,Cont)         \
template<>                                              \
struct Profiler::Hook<API::clRetain ## Func> {      \
  static inline cl_int exec(Handle obj) {               \
    auto ret = API::exec<API::clRetain ## Func>(obj);   \
    if(ret== CL_SUCCESS)                                \
      get(). Cont [obj].retain++;                       \
    return ret;                                         \
  }                                                     \
};                                                      \
template<>                                              \
struct Profiler::Hook<API::clRelease ## Func> {     \
  static inline cl_int exec(Handle mem) {               \
    auto ret = API::exec<API::clRelease ## Func>(mem);  \
    if(ret== CL_SUCCESS)                                \
      get(). Cont [mem].release++;                      \
    return ret;                                         \
  }                                                     \
}

HELIUM_RETAIN_RELEASE(MemObject, cl_mem, memobjs);
HELIUM_RETAIN_RELEASE(Kernel, cl_kernel, kernels);
HELIUM_RETAIN_RELEASE(Program, cl_program, programs);
HELIUM_RETAIN_RELEASE(Context, cl_context, contexts);
HELIUM_RETAIN_RELEASE(CommandQueue, cl_command_queue, com_queues);
#ifdef CL_VERSION_1_2
HELIUM_RETAIN_RELEASE(Device, cl_device_id, devices);
#endif

#undef HELIUM_RETAIN_RELEASE
 
