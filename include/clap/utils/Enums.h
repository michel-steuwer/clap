#include <ostream>

namespace clap {
  /// @namespace Constant Contains wrapper utilities for OpenCL constants
  namespace Constant {
    /// @brief Strongly typed wrapper for an error
    struct cl_error { const long int value; };
    
    /// @brief Strongly typed wrapper for a memory flag
    struct cl_mem_flags { const long unsigned int value; };
    
    /// @brief Strongly typed wrapper for a command queue property
    struct cl_command_queue_properties { const long unsigned int value; };

    std::ostream& operator<< ( std::ostream &out, 
                               const cl_error& value);
    std::ostream& operator<< ( std::ostream &out, 
                               const cl_mem_flags& value);
    std::ostream& operator<< ( std::ostream &out,
                               const cl_command_queue_properties& value);
  }
}


