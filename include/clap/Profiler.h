#pragma once

// [Standard includes]
#include <map>
#ifdef DEBUG_TRACK_OVERHEAD
# include <chrono>
#endif

// [Local includes]
#include "clap/Stat.h"
#include "clap/API.h"
#include "clap/feature.h"
#ifdef DEBUG_TRACK_OVERHEAD
# include "clap/utils/ScopeGuard.h"
#endif
#ifdef TRACK_PROGRAMS
# include "clap/utils/hash.h"
#endif

namespace clap {

/// @class Profiler
/// @brief Proxy between the OpenCL implementation and the vendor implementation
/// @details The Profiler struct maintains a set of stats for each entities in the model
///  The inner class Hooks is overloaded for each function we want to intercept.
/// @warning The singleton instance intentionally leaks: some OpenCL calls could still
///  technically be performed during static cleanup, so leaking it is the only way to
///  catch those.
struct Profiler {
  /// @brief wrapper to time overhead in profiling mode
  /// @tparam fct The function ID to call
  /// @tparam Args The parameters are automatically deduced from the call site
  /// @param args The arguments to forward to the hook
  /// @return Whatever the vendor function returns
  template<API::Fct fct, typename ... Args>
  static inline API::return_t<fct> exec(Args&&... args) {
#ifdef DEBUG_TRACK_OVERHEAD
    // start timer
    const auto start = std::chrono::high_resolution_clock::now();
    ScopeGuard guard{[=]{
      // stop timer
      auto end = std::chrono::high_resolution_clock::now();
      // register call
      API::profile[fct].total_time += std::chrono::duration<double>(end-start).count();
    }};
#endif
    return Hook<fct>::exec(std::forward<Args>(args)...);
  }

  /// @note The destructor is currently never called
  ~Profiler();
  
  /// @brief Singleton access
  /// @return The profiler instance
  inline static Profiler& get() { return *m_p; }

  /// @brief Log dump, triggered during static storage cleanup
  void dumpLogs();

  /// @brief Read-only access to device stat
  /// @param id The device ID
  /// @return the Stat for the required Device
  /// @throw std::out_of_range if the id is not valid
  inline const Stat::Device& getDevice(cl_device_id id) const 
  { return devices.at(id); } 

  /// @brief Read-only access to program stat
  /// @param id The program id
  /// @return the Stat for the required Proram
  /// @throw std::out_of_range if the id is not valid
  inline const Stat::Program& getProgram(cl_program id) const 
  { return programs.at(id); }

  /// @brief Read-only access to a kernel stat
  /// @param id The kernel id
  /// @return the Stat for the required Kernel
  /// @throw std::out_of_range if the id is not valid
  inline const Stat::Kernel& getKernel(cl_kernel id) const
  { return kernels.at(id); }

  /// @brief Read-only access to a command queue
  /// @param id The command queue id
  /// @return the Stat for the required CommandQueue
  /// @throw std::out_of_range if the id is not valid
  inline const Stat::CommandQueue& getCommandQueue(cl_command_queue id) const
  { return com_queues.at(id); }


private:
  /// @brief We need a helper struct to partially specialize the exec method
  template<API::Fct fct> struct Hook;
  
  /// @brief List of Kernel objects
  std::map<cl_kernel, Stat::Kernel> kernels;

  /// @brief List of Memory objects
  std::map<cl_mem, Stat::Memory> memobjs;

  /// @brief List of Program objects
  std::map<cl_program, Stat::Program> programs;

  /// @brief List of CommandQueue objects
  std::map<cl_command_queue, Stat::CommandQueue> com_queues;

  /// @brief List of Device objects
  std::map<cl_device_id, Stat::Device> devices;

  // @brief List of Context objects
  std::map<cl_context, Stat::Context> contexts;

  /// @brief Singleton 
  /// @warning This object will leak intentionally, see source for detail
  static Profiler *m_p;
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
/// @cond HIDDEN_SYMBOLS
/// implementation details
#include "clap/Spec/creational.inc"
#include "clap/Spec/queue.inc"
#ifdef TRACK_REFCOUNT
#include "clap/Spec/refcount.inc"
#endif
#include "clap/Spec/compiler.inc"
#include "clap/Spec/misc.inc"
/// @endcond
} // namespace clap

