// helpers
#ifdef TRACK_EVENTS
namespace {
  // RAII style guard to make sure the events are overridden properly
  struct EventGuard {
    cl_event *event; // user provided event
    cl_event *pod;   // timeable pod event reference

    EventGuard(cl_event *&e, Stat::Timeable &p) : event{e}, pod{&p._event}
    { 
      if(e == nullptr) {
        e = pod; 
        p.forced_event = true;
      }
    }

    // retain event and override pod if it was provided
    ~EventGuard() 
    { 
      if(event) {
        *pod = *event;
        API::getVendorImpl<API::clRetainEvent>()(*event);
      }
    }
  };
}
#endif

// Queue API

template<>
struct Profiler::Executor<API::clEnqueueNDRangeKernel> {
  static inline cl_int exec(cl_command_queue command_queue,
                            cl_kernel kernel,
                            cl_uint work_dim,
                            const size_t *global_work_offset,
                            const size_t *global_work_size,
                            const size_t *local_work_size,
                            cl_uint num_events_in_wait_list,
                            const cl_event *event_wait_list,
                            cl_event *event)
{
   const auto &kernel_stat = get().kernels.at(kernel);

   Stat::KernelInstance inst;
   inst.offset = {work_dim,global_work_offset};
   inst.global = {work_dim,global_work_size};
   inst.local = {work_dim,local_work_size};
   inst.kernel_id = kernel_stat.id;
   inst.queue_id = get().com_queues[command_queue].id;

    cl_int ret;
    {
#ifdef TRACK_EVENTS
      EventGuard e{event,inst};
#endif
      ret = API::exec<API::clEnqueueNDRangeKernel>
        (command_queue,kernel,work_dim,global_work_offset,
         global_work_size,local_work_size,num_events_in_wait_list,
         event_wait_list,event);
    }
    
    if(ret == CL_SUCCESS) { 
#ifdef TRACK_KERNEL_ARGUMENTS
      for(const auto& ptr : kernel_stat.arguments)
        inst.arguments.emplace_back(ptr?ptr->clone():nullptr);
#endif
      get().kernels[kernel].instances.emplace_back(std::move(inst));
    }
    return ret;
  }
};

template<> 
struct Profiler::Executor<API::clEnqueueReadBuffer> {
  static inline cl_int exec(cl_command_queue command_queue,
                            cl_mem buffer,
                            cl_bool blocking_read,
                            size_t offset,
                            size_t cb,
                            void *ptr,
                            cl_uint num_events_in_wait_list,
                            const cl_event *event_wait_list,
                            cl_event *event) 
  {
    Stat::MemOperation op; 
    op.type = Stat::MemOperation::Type::Read;
    op.blocking = blocking_read;
    op.queue_id = get().com_queues[command_queue].id;
    
    cl_int ret;
    {
#ifdef TRACK_EVENTS
      EventGuard e{event,op};
#endif
      ret = API::exec<API::clEnqueueReadBuffer>
        (command_queue,buffer,blocking_read,offset,cb,ptr,
         num_events_in_wait_list,event_wait_list,event);
    }

    if(ret == CL_SUCCESS) 
      get().memobjs[buffer].operations.push_back(op);
    return ret;
  }
};

template<> 
struct Profiler::Executor<API::clEnqueueWriteBuffer> {
  static inline cl_int exec(cl_command_queue command_queue,
                            cl_mem buffer,
                            cl_bool blocking,
                            size_t offset,
                            size_t cb,
                            const void *ptr,
                            cl_uint num_events_in_wait_list,
                            const cl_event *event_wait_list,
                            cl_event *event) 
  {
    Stat::MemOperation op; 
    op.type = Stat::MemOperation::Type::Write;
    op.blocking = blocking;
    op.queue_id = get().com_queues[command_queue].id;

    cl_int ret;
    {
#ifdef TRACK_EVENTS
      EventGuard e{event,op}; 
#endif
      ret = API::exec<API::clEnqueueWriteBuffer>
        (command_queue,buffer,blocking,offset,cb,ptr,
         num_events_in_wait_list,event_wait_list,event);
    }

    if(ret == CL_SUCCESS) 
      get().memobjs[buffer].operations.push_back(op);
    return ret;
  }
};

