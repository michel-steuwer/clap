// Auto-generated file: DO NOT EDIT

#include "Profiler.h"

#ifdef CL_VERSION_1_0
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformIDs(cl_uint num_entries, cl_platform_id *platforms,
                 cl_uint *num_platforms) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetPlatformIDs>(num_entries, platforms,
                                               num_platforms);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetPlatformInfo(cl_platform_id platform, cl_platform_info param_name,
                  size_t param_value_size, void *param_value,
                  size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetPlatformInfo>(platform, param_name,
                                                param_value_size, param_value,
                                                param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceIDs(cl_platform_id platform, cl_device_type device_type,
               cl_uint num_entries, cl_device_id *devices,
               cl_uint *num_devices) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetDeviceIDs>(platform, device_type, num_entries,
                                             devices, num_devices);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetDeviceInfo(cl_device_id device, cl_device_info param_name,
                size_t param_value_size, void *param_value,
                size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetDeviceInfo>(
      device, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_context CL_API_CALL
clCreateContext(const cl_context_properties *properties, cl_uint num_devices,
                const cl_device_id *devices,
                void(CL_CALLBACK *pfn_notify)(const char *, const void *,
                                              size_t, void *),
                void *user_data,
                cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateContext>(
      properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_context CL_API_CALL
clCreateContextFromType(
    const cl_context_properties *properties, cl_device_type device_type,
    void(CL_CALLBACK *pfn_notify)(const char *, const void *, size_t, void *),
    void *user_data, cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateContextFromType>(
      properties, device_type, pfn_notify, user_data, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainContext(cl_context context) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainContext>(context);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseContext(cl_context context) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseContext>(context);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetContextInfo(cl_context context, cl_context_info param_name,
                 size_t param_value_size, void *param_value,
                 size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetContextInfo>(
      context, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainCommandQueue(cl_command_queue command_queue)
    CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainCommandQueue>(command_queue);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseCommandQueue(cl_command_queue command_queue)
    CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseCommandQueue>(command_queue);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetCommandQueueInfo(cl_command_queue command_queue,
                      cl_command_queue_info param_name, size_t param_value_size,
                      void *param_value,
                      size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetCommandQueueInfo>(
      command_queue, param_name, param_value_size, param_value,
      param_value_size_ret);
}

#if defined OPENCL_ALLOW_DEPRECATED || !defined CL_VERSION_1_1
extern "C"
[[gnu::visibility("default")]]
CL_API_ENTRY cl_int CL_API_CALL
clSetCommandQueueProperty(cl_command_queue               command_queue ,
                          cl_command_queue_properties    properties ,
                          cl_bool                         enable ,
                          cl_command_queue_properties *  old_properties )
CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clSetCommandQueueProperty>(command_queue,
properties,
enable,
old_properties);
}
#endif

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreateBuffer(cl_context context, cl_mem_flags flags, size_t size,
               void *host_ptr, cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateBuffer>(context, flags, size, host_ptr,
                                             errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainMemObject(cl_mem memobj) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainMemObject>(memobj);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseMemObject(cl_mem memobj) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseMemObject>(memobj);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetSupportedImageFormats(
    cl_context context, cl_mem_flags flags, cl_mem_object_type image_type,
    cl_uint num_entries, cl_image_format *image_formats,
    cl_uint *num_image_formats) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetSupportedImageFormats>(
      context, flags, image_type, num_entries, image_formats,
      num_image_formats);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetMemObjectInfo(cl_mem memobj, cl_mem_info param_name,
                   size_t param_value_size, void *param_value,
                   size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetMemObjectInfo>(
      memobj, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetImageInfo(cl_mem image, cl_image_info param_name, size_t param_value_size,
               void *param_value,
               size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetImageInfo>(
      image, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainSampler(cl_sampler sampler) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainSampler>(sampler);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseSampler(cl_sampler sampler) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseSampler>(sampler);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetSamplerInfo(cl_sampler sampler, cl_sampler_info param_name,
                 size_t param_value_size, void *param_value,
                 size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetSamplerInfo>(
      sampler, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithSource(cl_context context, cl_uint count,
                          const char **strings, const size_t *lengths,
                          cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateProgramWithSource>(context, count, strings,
                                                        lengths, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithBinary(cl_context context, cl_uint num_devices,
                          const cl_device_id *device_list,
                          const size_t *lengths, const unsigned char **binaries,
                          cl_int *binary_status,
                          cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateProgramWithBinary>(
      context, num_devices, device_list, lengths, binaries, binary_status,
      errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainProgram(cl_program program) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainProgram>(program);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseProgram(cl_program program) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseProgram>(program);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clBuildProgram(cl_program program, cl_uint num_devices,
               const cl_device_id *device_list, const char *options,
               void(CL_CALLBACK *pfn_notify)(cl_program, void *),
               void *user_data) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clBuildProgram>(program, num_devices, device_list,
                                             options, pfn_notify, user_data);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetProgramInfo(cl_program program, cl_program_info param_name,
                 size_t param_value_size, void *param_value,
                 size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetProgramInfo>(
      program, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetProgramBuildInfo(cl_program program, cl_device_id device,
                      cl_program_build_info param_name, size_t param_value_size,
                      void *param_value,
                      size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetProgramBuildInfo>(
      program, device, param_name, param_value_size, param_value,
      param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_kernel CL_API_CALL
clCreateKernel(cl_program program, const char *kernel_name,
               cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateKernel>(program, kernel_name, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clCreateKernelsInProgram(cl_program program, cl_uint num_kernels,
                         cl_kernel *kernels,
                         cl_uint *num_kernels_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateKernelsInProgram>(
      program, num_kernels, kernels, num_kernels_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainKernel(cl_kernel kernel) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainKernel>(kernel);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseKernel(cl_kernel kernel) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseKernel>(kernel);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetKernelArg(cl_kernel kernel, cl_uint arg_index, size_t arg_size,
               const void *arg_value) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clSetKernelArg>(kernel, arg_index, arg_size,
                                             arg_value);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetKernelInfo(cl_kernel kernel, cl_kernel_info param_name,
                size_t param_value_size, void *param_value,
                size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetKernelInfo>(
      kernel, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetKernelWorkGroupInfo(
    cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name,
    size_t param_value_size, void *param_value,
    size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetKernelWorkGroupInfo>(
      kernel, device, param_name, param_value_size, param_value,
      param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clWaitForEvents(cl_uint num_events,
                const cl_event *event_list) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clWaitForEvents>(num_events, event_list);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetEventInfo(cl_event event, cl_event_info param_name,
               size_t param_value_size, void *param_value,
               size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetEventInfo>(
      event, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainEvent(cl_event event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clRetainEvent>(event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseEvent(cl_event event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clReleaseEvent>(event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetEventProfilingInfo(cl_event event, cl_profiling_info param_name,
                        size_t param_value_size, void *param_value,
                        size_t *param_value_size_ret)
    CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clGetEventProfilingInfo>(
      event, param_name, param_value_size, param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clFlush(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clFlush>(command_queue);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clFinish(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clFinish>(command_queue);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadBuffer(cl_command_queue command_queue, cl_mem buffer,
                    cl_bool blocking_read, size_t offset, size_t size,
                    void *ptr, cl_uint num_events_in_wait_list,
                    const cl_event *event_wait_list,
                    cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueReadBuffer>(
      command_queue, buffer, blocking_read, offset, size, ptr,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteBuffer(cl_command_queue command_queue, cl_mem buffer,
                     cl_bool blocking_write, size_t offset, size_t size,
                     const void *ptr, cl_uint num_events_in_wait_list,
                     const cl_event *event_wait_list,
                     cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueWriteBuffer>(
      command_queue, buffer, blocking_write, offset, size, ptr,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBuffer(cl_command_queue command_queue, cl_mem src_buffer,
                    cl_mem dst_buffer, size_t src_offset, size_t dst_offset,
                    size_t size, cl_uint num_events_in_wait_list,
                    const cl_event *event_wait_list,
                    cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueCopyBuffer>(
      command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadImage(cl_command_queue command_queue, cl_mem image,
                   cl_bool blocking_read, const size_t *origin,
                   const size_t *region, size_t row_pitch, size_t slice_pitch,
                   void *ptr, cl_uint num_events_in_wait_list,
                   const cl_event *event_wait_list,
                   cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueReadImage>(
      command_queue, image, blocking_read, origin, region, row_pitch,
      slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteImage(cl_command_queue command_queue, cl_mem image,
                    cl_bool blocking_write, const size_t *origin,
                    const size_t *region, size_t input_row_pitch,
                    size_t input_slice_pitch, const void *ptr,
                    cl_uint num_events_in_wait_list,
                    const cl_event *event_wait_list,
                    cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueWriteImage>(
      command_queue, image, blocking_write, origin, region, input_row_pitch,
      input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyImage(cl_command_queue command_queue, cl_mem src_image,
                   cl_mem dst_image, const size_t *src_origin,
                   const size_t *dst_origin, const size_t *region,
                   cl_uint num_events_in_wait_list,
                   const cl_event *event_wait_list,
                   cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueCopyImage>(
      command_queue, src_image, dst_image, src_origin, dst_origin, region,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyImageToBuffer(cl_command_queue command_queue, cl_mem src_image,
                           cl_mem dst_buffer, const size_t *src_origin,
                           const size_t *region, size_t dst_offset,
                           cl_uint num_events_in_wait_list,
                           const cl_event *event_wait_list,
                           cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueCopyImageToBuffer>(
      command_queue, src_image, dst_buffer, src_origin, region, dst_offset,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBufferToImage(cl_command_queue command_queue, cl_mem src_buffer,
                           cl_mem dst_image, size_t src_offset,
                           const size_t *dst_origin, const size_t *region,
                           cl_uint num_events_in_wait_list,
                           const cl_event *event_wait_list,
                           cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueCopyBufferToImage>(
      command_queue, src_buffer, dst_image, src_offset, dst_origin, region,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void *CL_API_CALL
clEnqueueMapBuffer(cl_command_queue command_queue, cl_mem buffer,
                   cl_bool blocking_map, cl_map_flags map_flags, size_t offset,
                   size_t size, cl_uint num_events_in_wait_list,
                   const cl_event *event_wait_list, cl_event *event,
                   cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueMapBuffer>(
      command_queue, buffer, blocking_map, map_flags, offset, size,
      num_events_in_wait_list, event_wait_list, event, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void *CL_API_CALL
clEnqueueMapImage(cl_command_queue command_queue, cl_mem image,
                  cl_bool blocking_map, cl_map_flags map_flags,
                  const size_t *origin, const size_t *region,
                  size_t *image_row_pitch, size_t *image_slice_pitch,
                  cl_uint num_events_in_wait_list,
                  const cl_event *event_wait_list, cl_event *event,
                  cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueMapImage>(
      command_queue, image, blocking_map, map_flags, origin, region,
      image_row_pitch, image_slice_pitch, num_events_in_wait_list,
      event_wait_list, event, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueUnmapMemObject(cl_command_queue command_queue, cl_mem memobj,
                        void *mapped_ptr, cl_uint num_events_in_wait_list,
                        const cl_event *event_wait_list,
                        cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueUnmapMemObject>(
      command_queue, memobj, mapped_ptr, num_events_in_wait_list,
      event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueNDRangeKernel(cl_command_queue command_queue, cl_kernel kernel,
                       cl_uint work_dim, const size_t *global_work_offset,
                       const size_t *global_work_size,
                       const size_t *local_work_size,
                       cl_uint num_events_in_wait_list,
                       const cl_event *event_wait_list,
                       cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueNDRangeKernel>(
      command_queue, kernel, work_dim, global_work_offset, global_work_size,
      local_work_size, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueNativeKernel(cl_command_queue command_queue,
                      void(CL_CALLBACK *user_func)(void *), void *args,
                      size_t cb_args, cl_uint num_mem_objects,
                      const cl_mem *mem_list, const void **args_mem_loc,
                      cl_uint num_events_in_wait_list,
                      const cl_event *event_wait_list,
                      cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueNativeKernel>(
      command_queue, user_func, args, cb_args, num_mem_objects, mem_list,
      args_mem_loc, num_events_in_wait_list, event_wait_list, event);
}

#if defined OPENCL_ALLOW_DEPRECATED || !defined CL_VERSION_2_0
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_command_queue
    CL_API_CALL
    clCreateCommandQueue(cl_context context, cl_device_id device,
                         cl_command_queue_properties properties,
                         cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateCommandQueue>(context, device, properties,
                                                   errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_sampler CL_API_CALL
clCreateSampler(cl_context context, cl_bool normalized_coords,
                cl_addressing_mode addressing_mode, cl_filter_mode filter_mode,
                cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clCreateSampler>(
      context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueTask(cl_command_queue command_queue, cl_kernel kernel,
              cl_uint num_events_in_wait_list, const cl_event *event_wait_list,
              cl_event *event) CL_API_SUFFIX__VERSION_1_0 {
  return He::Profiler::exec<He::API::clEnqueueTask>(
      command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
}
#endif

#endif

#ifdef CL_VERSION_1_1
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreateSubBuffer(cl_mem buffer, cl_mem_flags flags,
                  cl_buffer_create_type buffer_create_type,
                  const void *buffer_create_info,
                  cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clCreateSubBuffer>(
      buffer, flags, buffer_create_type, buffer_create_info, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetMemObjectDestructorCallback(cl_mem memobj,
                                 void(CL_CALLBACK *pfn_notify)(cl_mem, void *),
                                 void *user_data) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clSetMemObjectDestructorCallback>(
      memobj, pfn_notify, user_data);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_event CL_API_CALL
clCreateUserEvent(cl_context context,
                  cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clCreateUserEvent>(context, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetUserEventStatus(cl_event event,
                     cl_int execution_status) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clSetUserEventStatus>(event, execution_status);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetEventCallback(cl_event event, cl_int command_exec_callback_type,
                   void(CL_CALLBACK *pfn_notify)(cl_event, cl_int, void *),
                   void *user_data) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clSetEventCallback>(
      event, command_exec_callback_type, pfn_notify, user_data);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueReadBufferRect(cl_command_queue command_queue, cl_mem buffer,
                        cl_bool blocking_read, const size_t *buffer_offset,
                        const size_t *host_offset, const size_t *region,
                        size_t buffer_row_pitch, size_t buffer_slice_pitch,
                        size_t host_row_pitch, size_t host_slice_pitch,
                        void *ptr, cl_uint num_events_in_wait_list,
                        const cl_event *event_wait_list,
                        cl_event *event) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueReadBufferRect>(
      command_queue, buffer, blocking_read, buffer_offset, host_offset, region,
      buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch,
      ptr, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWriteBufferRect(cl_command_queue command_queue, cl_mem buffer,
                         cl_bool blocking_write, const size_t *buffer_offset,
                         const size_t *host_offset, const size_t *region,
                         size_t buffer_row_pitch, size_t buffer_slice_pitch,
                         size_t host_row_pitch, size_t host_slice_pitch,
                         const void *ptr, cl_uint num_events_in_wait_list,
                         const cl_event *event_wait_list,
                         cl_event *event) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueWriteBufferRect>(
      command_queue, buffer, blocking_write, buffer_offset, host_offset, region,
      buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch,
      ptr, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueCopyBufferRect(cl_command_queue command_queue, cl_mem src_buffer,
                        cl_mem dst_buffer, const size_t *src_origin,
                        const size_t *dst_origin, const size_t *region,
                        size_t src_row_pitch, size_t src_slice_pitch,
                        size_t dst_row_pitch, size_t dst_slice_pitch,
                        cl_uint num_events_in_wait_list,
                        const cl_event *event_wait_list,
                        cl_event *event) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueCopyBufferRect>(
      command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region,
      src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch,
      num_events_in_wait_list, event_wait_list, event);
}

#if defined OPENCL_ALLOW_DEPRECATED || !defined CL_VERSION_1_2
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage2D(cl_context context, cl_mem_flags flags,
                const cl_image_format *image_format, size_t image_width,
                size_t image_height, size_t image_row_pitch, void *host_ptr,
                cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clCreateImage2D>(
      context, flags, image_format, image_width, image_height, image_row_pitch,
      host_ptr, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage3D(cl_context context, cl_mem_flags flags,
                const cl_image_format *image_format, size_t image_width,
                size_t image_height, size_t image_depth, size_t image_row_pitch,
                size_t image_slice_pitch, void *host_ptr,
                cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clCreateImage3D>(
      context, flags, image_format, image_width, image_height, image_depth,
      image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMarker(cl_command_queue command_queue,
                cl_event *event) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueMarker>(command_queue, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueWaitForEvents(cl_command_queue command_queue, cl_uint num_events,
                       const cl_event *event_list) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueWaitForEvents>(command_queue, num_events,
                                                     event_list);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueBarrier(cl_command_queue command_queue) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clEnqueueBarrier>(command_queue);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clUnloadCompiler(void) CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clUnloadCompiler>();
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void *CL_API_CALL
clGetExtensionFunctionAddress(const char *func_name)
    CL_API_SUFFIX__VERSION_1_1 {
  return He::Profiler::exec<He::API::clGetExtensionFunctionAddress>(func_name);
}
#endif

#endif

#ifdef CL_VERSION_1_2
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clCreateSubDevices(cl_device_id in_device,
                   const cl_device_partition_property *properties,
                   cl_uint num_devices, cl_device_id *out_devices,
                   cl_uint *num_devices_ret) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clCreateSubDevices>(
      in_device, properties, num_devices, out_devices, num_devices_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clRetainDevice(cl_device_id device) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clRetainDevice>(device);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clReleaseDevice(cl_device_id device) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clReleaseDevice>(device);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreateImage(cl_context context, cl_mem_flags flags,
              const cl_image_format *image_format,
              const cl_image_desc *image_desc, void *host_ptr,
              cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clCreateImage>(context, flags, image_format,
                                            image_desc, host_ptr, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_program CL_API_CALL
clCreateProgramWithBuiltInKernels(
    cl_context context, cl_uint num_devices, const cl_device_id *device_list,
    const char *kernel_names, cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clCreateProgramWithBuiltInKernels>(
      context, num_devices, device_list, kernel_names, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clCompileProgram(cl_program program, cl_uint num_devices,
                 const cl_device_id *device_list, const char *options,
                 cl_uint num_input_headers, const cl_program *input_headers,
                 const char **header_include_names,
                 void(CL_CALLBACK *pfn_notify)(cl_program, void *),
                 void *user_data) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clCompileProgram>(
      program, num_devices, device_list, options, num_input_headers,
      input_headers, header_include_names, pfn_notify, user_data);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_program CL_API_CALL
clLinkProgram(cl_context context, cl_uint num_devices,
              const cl_device_id *device_list, const char *options,
              cl_uint num_input_programs, const cl_program *input_programs,
              void(CL_CALLBACK *pfn_notify)(cl_program, void *),
              void *user_data, cl_int *errcode_ret) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clLinkProgram>(
      context, num_devices, device_list, options, num_input_programs,
      input_programs, pfn_notify, user_data, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clUnloadPlatformCompiler(cl_platform_id platform) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clUnloadPlatformCompiler>(platform);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetKernelArgInfo(cl_kernel kernel, cl_uint arg_indx,
                   cl_kernel_arg_info param_name, size_t param_value_size,
                   void *param_value,
                   size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clGetKernelArgInfo>(kernel, arg_indx, param_name,
                                                 param_value_size, param_value,
                                                 param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueFillBuffer(cl_command_queue command_queue, cl_mem buffer,
                    const void *pattern, size_t pattern_size, size_t offset,
                    size_t size, cl_uint num_events_in_wait_list,
                    const cl_event *event_wait_list,
                    cl_event *event) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clEnqueueFillBuffer>(
      command_queue, buffer, pattern, pattern_size, offset, size,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueFillImage(cl_command_queue command_queue, cl_mem image,
                   const void *fill_color, const size_t *origin,
                   const size_t *region, cl_uint num_events_in_wait_list,
                   const cl_event *event_wait_list,
                   cl_event *event) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clEnqueueFillImage>(
      command_queue, image, fill_color, origin, region, num_events_in_wait_list,
      event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMigrateMemObjects(cl_command_queue command_queue,
                           cl_uint num_mem_objects, const cl_mem *mem_objects,
                           cl_mem_migration_flags flags,
                           cl_uint num_events_in_wait_list,
                           const cl_event *event_wait_list,
                           cl_event *event) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clEnqueueMigrateMemObjects>(
      command_queue, num_mem_objects, mem_objects, flags,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueMarkerWithWaitList(cl_command_queue command_queue,
                            cl_uint num_events_in_wait_list,
                            const cl_event *event_wait_list,
                            cl_event *event) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clEnqueueMarkerWithWaitList>(
      command_queue, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueBarrierWithWaitList(cl_command_queue command_queue,
                             cl_uint num_events_in_wait_list,
                             const cl_event *event_wait_list,
                             cl_event *event) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clEnqueueBarrierWithWaitList>(
      command_queue, num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void *CL_API_CALL
clGetExtensionFunctionAddressForPlatform(
    cl_platform_id platform, const char *func_name) CL_API_SUFFIX__VERSION_1_2 {
  return He::Profiler::exec<He::API::clGetExtensionFunctionAddressForPlatform>(
      platform, func_name);
}

#endif

#ifdef CL_VERSION_2_0
extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_command_queue
    CL_API_CALL
    clCreateCommandQueueWithProperties(cl_context context, cl_device_id device,
                                       const cl_queue_properties *properties,
                                       cl_int *errcode_ret)
        CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clCreateCommandQueueWithProperties>(
      context, device, properties, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_mem CL_API_CALL
clCreatePipe(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size,
             cl_uint pipe_max_packets, const cl_pipe_properties *properties,
             cl_int *errcode_ret) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clCreatePipe>(context, flags, pipe_packet_size,
                                           pipe_max_packets, properties,
                                           errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clGetPipeInfo(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size,
              void *param_value,
              size_t *param_value_size_ret) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clGetPipeInfo>(pipe, param_name, param_value_size,
                                            param_value, param_value_size_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void *CL_API_CALL
clSVMAlloc(cl_context context, cl_svm_mem_flags flags, size_t size,
           cl_uint alignment) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clSVMAlloc>(context, flags, size, alignment);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY void CL_API_CALL
clSVMFree(cl_context context, void *svm_pointer) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clSVMFree>(context, svm_pointer);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_sampler CL_API_CALL
clCreateSamplerWithProperties(cl_context context,
                              const cl_sampler_properties *normalized_coords,
                              cl_int *errcode_ret) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clCreateSamplerWithProperties>(
      context, normalized_coords, errcode_ret);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetKernelArgSVMPointer(cl_kernel kernel, cl_uint arg_index,
                         const void *arg_value) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clSetKernelArgSVMPointer>(kernel, arg_index,
                                                       arg_value);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clSetKernelExecInfo(cl_kernel kernel, cl_kernel_exec_info param_name,
                    size_t param_value_size,
                    const void *param_value) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clSetKernelExecInfo>(
      kernel, param_name, param_value_size, param_value);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSVMFree(cl_command_queue command_queue, cl_uint num_svm_pointers,
                 void *svm_pointers[] ,
                 void(CL_CALLBACK *pfn_free_func)(cl_command_queue, cl_uint,
                                                  void *[], void *),
                 void *user_data, cl_uint num_events_in_wait_list,
                 const cl_event *event_wait_list,
                 cl_event *event) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clEnqueueSVMFree>(
      command_queue, num_svm_pointers, svm_pointers, pfn_free_func, user_data,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSVMMemcpy(cl_command_queue command_queue, cl_bool blocking_copy,
                   void *dst_ptr, const void *src_ptr, size_t size,
                   cl_uint num_events_in_wait_list,
                   const cl_event *event_wait_list,
                   cl_event *event) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clEnqueueSVMMemcpy>(
      command_queue, blocking_copy, dst_ptr, src_ptr, size,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSVMMemFill(cl_command_queue command_queue, void *svm_ptr,
                    const void *pattern, size_t pattern_size, size_t size,
                    cl_uint num_events_in_wait_list,
                    const cl_event *event_wait_list,
                    cl_event *event) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clEnqueueSVMMemFill>(
      command_queue, svm_ptr, pattern, pattern_size, size,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSVMMap(cl_command_queue command_queue, cl_bool blocking_map,
                cl_map_flags flags, void *svm_ptr, size_t size,
                cl_uint num_events_in_wait_list,
                const cl_event *event_wait_list,
                cl_event *event) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clEnqueueSVMMap>(
      command_queue, blocking_map, flags, svm_ptr, size,
      num_events_in_wait_list, event_wait_list, event);
}

extern "C" [[gnu::visibility("default")]] CL_API_ENTRY cl_int CL_API_CALL
clEnqueueSVMUnmap(cl_command_queue command_queue, void *svm_ptr,
                  cl_uint num_events_in_wait_list,
                  const cl_event *event_wait_list,
                  cl_event *event) CL_API_SUFFIX__VERSION_2_0 {
  return He::Profiler::exec<He::API::clEnqueueSVMUnmap>(
      command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event);
}

#endif
