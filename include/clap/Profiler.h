#pragma once

#include <map>
#include "clap/Stat.h"
#include "clap/API.h"
#include "clap/feature.h"

#ifdef DEBUG_TRACK_OVERHEAD
#include <chrono>
#include "clap/utils/ScopeGuard.h"
#endif

#ifdef TRACK_PROGRAMS
#include "clap/utils/hash.h"
#endif

namespace clap {

struct Profiler {
  /// @brief wrapper to time overhead in profiling mode
  template<API::Fct fct, typename ... Args>
  static inline API::return_t<fct> exec(Args&&... args) {
#ifdef DEBUG_TRACK_OVERHEAD
    // start timer
    const auto start = std::chrono::high_resolution_clock::now();
    He::ScopeGuard guard{[=]{
      // stop timer
      auto end = std::chrono::high_resolution_clock::now();
      // register call
      API::profile[fct].total_time += std::chrono::duration<double>(end-start).count();
    }};
#endif
    return Hook<fct>::exec(std::forward<Args>(args)...);
  }

  ~Profiler();
  
  /// @brief Singleton access
  inline static Profiler& get() { return *m_p; }

  /// @brief Log dump, triggered during static storage cleanup
  void dumpLogs();

  inline const Stat::Device& getDevice(cl_device_id id) const 
  { return devices.at(id); } 

  inline const Stat::Program& getProgram(cl_program id) const 
  { return programs.at(id); }

  inline const Stat::Kernel& getKernel(cl_kernel id) const
  { return kernels.at(id); }

  inline const Stat::CommandQueue& getCommandQueue(cl_command_queue id) const
  { return com_queues.at(id); }


private:
  /// @brief We need a helper struct to partially specialize the exec method
  template<API::Fct fct> struct Hook;
  
  /// @brief List of kernels
  std::map<cl_kernel, Stat::Kernel> kernels;

  /// @brief list of memory objects
  std::map<cl_mem, Stat::Memory> memobjs;

  /// @brief list of programs
  std::map<cl_program, Stat::Program> programs;

  /// @brief list of command queues
  std::map<cl_command_queue, Stat::CommandQueue> com_queues;

  /// @brief list of devices
  std::map<cl_device_id, Stat::Device> devices;

  // @brief list of contexts
  std::map<cl_context, Stat::Context> contexts;

  /// @brief Singleton (will leak intentionally, see source for detail)
  static Profiler *m_p;

  Profiler();
};

// Default behavior: passthrough
template<API::Fct fct>
struct Profiler::Hook {
  template<typename ... Args>
    static inline auto exec(Args&&... args) -> API::return_t<fct>
  {
    return API::exec<fct>(std::forward<Args>(args)...);
  }
};

// Specializations
#include "clap/Spec/creational.inc"
#include "clap/Spec/queue.inc"
#ifdef TRACK_REFCOUNT
#include "clap/Spec/refcount.inc"
#endif
#include "clap/Spec/compiler.inc"
#include "clap/Spec/misc.inc"

} // namespace clap

