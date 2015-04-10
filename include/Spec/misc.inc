#ifdef TRACK_KERNEL_ARGUMENTS
template<>
struct Profiler::Hook<API::clSetKernelArg> {
  static inline int exec( cl_kernel kernel,
                          cl_uint arg_index,
                          size_t arg_size,
                          const void *arg_value )
  {
    auto ret = API::exec<API::clSetKernelArg>
      (kernel,arg_index,arg_size,arg_value);

    if(ret == CL_SUCCESS) {
      // alias profiler objects
      auto& args = get().kernels[kernel].arguments;
      const auto mem_objs = get().memobjs;

      // resize array if necessary 
      if(args.size() < arg_index+1)
        args.resize(arg_index+1);

      // if arg_value is NULL, it is a local memory
      if(arg_value == nullptr) {
        args[arg_index].reset(new Stat::Argument::Local(arg_size));
      }
      // Otherwise try to look it up in the memory object map
      else if(arg_size == sizeof(cl_mem) && 
              mem_objs.find(*(cl_mem*)arg_value) != std::end(mem_objs)) {
        const int id = mem_objs.at(*(cl_mem*)arg_value).id;
        args[arg_index].reset(new Stat::Argument::MemObject(id));
      }
      // raw data, just copy it
      else {
        args[arg_index].reset(new Stat::Argument::Data(arg_value, arg_size));
      }
    }
    return ret;
  }
};
#endif


