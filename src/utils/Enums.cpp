#include "utils/Enums.h"

#include <CL/cl.h>

// If it is just a value return its stringified form
#define CASE(X) \
  case X: out << #X

// If it is a bitfield append the value to the stream and mask it out
#define BITFIELD(X) \
  if(value & X) { out << (first?"":"|") << #X; first = false; value ^= X; }

namespace he {
namespace Constant {

std::ostream& operator<< (std::ostream &out, const cl_mem_flags& e){
  bool first = true;
  auto value = e.value;
  BITFIELD(CL_MEM_READ_WRITE)
  BITFIELD(CL_MEM_READ_WRITE)
  BITFIELD(CL_MEM_WRITE_ONLY)
  BITFIELD(CL_MEM_READ_ONLY)
  BITFIELD(CL_MEM_USE_HOST_PTR)
  BITFIELD(CL_MEM_ALLOC_HOST_PTR)
  BITFIELD(CL_MEM_COPY_HOST_PTR)
#ifdef CL_VERSION_X_Y
  BITFIELD(CL_MEM_HOST_WRITE_ONLY)
  BITFIELD(CL_MEM_HOST_READ_ONLY)
  BITFIELD(CL_MEM_HOST_NO_ACCESS) 
#endif
  if(first) out << "???";
  if(value) out << (first?"":"|") << "???";
  return out;
}

std::ostream& operator<< (std::ostream &out, const cl_error& e){
  switch(e.value) {
    CASE(CL_SUCCESS);
    CASE(CL_DEVICE_NOT_FOUND);
    CASE(CL_DEVICE_NOT_AVAILABLE);
    CASE(CL_COMPILER_NOT_AVAILABLE);
    CASE(CL_MEM_OBJECT_ALLOCATION_FAILURE);
    CASE(CL_OUT_OF_RESOURCES);
    CASE(CL_OUT_OF_HOST_MEMORY);
    CASE(CL_PROFILING_INFO_NOT_AVAILABLE);
    CASE(CL_MEM_COPY_OVERLAP);
    CASE(CL_IMAGE_FORMAT_MISMATCH);
    CASE(CL_IMAGE_FORMAT_NOT_SUPPORTED);
    CASE(CL_BUILD_PROGRAM_FAILURE);
    CASE(CL_MAP_FAILURE);
#ifdef CL_VERSION_1_1
    CASE(CL_MISALIGNED_SUB_BUFFER_OFFSET);
    CASE(CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST);
    CASE(CL_INVALID_PROPERTY);
#endif
    CASE(CL_INVALID_VALUE);
    CASE(CL_INVALID_DEVICE_TYPE);
    CASE(CL_INVALID_PLATFORM);
    CASE(CL_INVALID_DEVICE);
    CASE(CL_INVALID_CONTEXT);
    CASE(CL_INVALID_QUEUE_PROPERTIES);
    CASE(CL_INVALID_COMMAND_QUEUE);
    CASE(CL_INVALID_HOST_PTR);
    CASE(CL_INVALID_MEM_OBJECT);
    CASE(CL_INVALID_IMAGE_FORMAT_DESCRIPTOR);
    CASE(CL_INVALID_IMAGE_SIZE);
    CASE(CL_INVALID_SAMPLER);
    CASE(CL_INVALID_BINARY);
    CASE(CL_INVALID_BUILD_OPTIONS);
    CASE(CL_INVALID_PROGRAM);
    CASE(CL_INVALID_PROGRAM_EXECUTABLE);
    CASE(CL_INVALID_KERNEL_NAME);
    CASE(CL_INVALID_KERNEL_DEFINITION);
    CASE(CL_INVALID_KERNEL);
    CASE(CL_INVALID_ARG_INDEX);
    CASE(CL_INVALID_ARG_VALUE);
    CASE(CL_INVALID_ARG_SIZE);
    CASE(CL_INVALID_KERNEL_ARGS);
    CASE(CL_INVALID_WORK_DIMENSION);
    CASE(CL_INVALID_WORK_GROUP_SIZE);
    CASE(CL_INVALID_WORK_ITEM_SIZE);
    CASE(CL_INVALID_GLOBAL_OFFSET);
    CASE(CL_INVALID_EVENT_WAIT_LIST);
    CASE(CL_INVALID_EVENT);
    CASE(CL_INVALID_OPERATION);
    CASE(CL_INVALID_GL_OBJECT);
    CASE(CL_INVALID_BUFFER_SIZE);
    CASE(CL_INVALID_MIP_LEVEL);
    CASE(CL_INVALID_GLOBAL_WORK_SIZE);
#ifdef CL_VERSION_1_2
    CASE(CL_COMPILE_PROGRAM_FAILURE);
    CASE(CL_LINKER_NOT_AVAILABLE);
    CASE(CL_LINK_PROGRAM_FAILURE);
    CASE(CL_DEVICE_PARTITION_FAILED);
    CASE(CL_KERNEL_ARG_INFO_NOT_AVAILABLE);
    CASE(CL_INVALID_IMAGE_DESCRIPTOR);
    CASE(CL_INVALID_COMPILER_OPTIONS);
    CASE(CL_INVALID_LINKER_OPTIONS);
    CASE(CL_INVALID_DEVICE_PARTITION_COUNT); 
#endif 
    default: out << "???";
  }
  return out;
}

std::ostream& operator<< ( std::ostream &out, const cl_command_queue_properties& e) {
  bool first = true;
  auto value = e.value;
  if(value == 0)
    return out;
  BITFIELD(CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)
  BITFIELD(CL_QUEUE_PROFILING_ENABLE)
  if(first) out << "???";
  if(value) out << (first?"":"|") << "???";
  return out;
}

} // namespace Constant
} // namespace He

