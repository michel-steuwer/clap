namespace clap {

template<>
struct Profiler::Hook<API::clBuildProgram> {
  static inline cl_int exec( cl_program program,
                             cl_uint num_devices,
                             const cl_device_id *device_list,
                             const char *options,
                             void (*pfn_notify)(cl_program, void *user_data),
                             void *user_data)
  {
    auto ret = API::exec<API::clBuildProgram>
      (program, num_devices, device_list, options, pfn_notify, user_data);
    if(ret == CL_SUCCESS && options) 
      get().programs[program].build_options = options;
    return ret;
  }
};

}

