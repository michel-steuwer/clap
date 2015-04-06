#include <ostream>

namespace he {
  namespace Constant {
    struct cl_error { const long int value; };
    struct cl_mem_flags { const long unsigned int value; };
    struct cl_command_queue_properties { const long unsigned int value; };
    std::ostream& operator<< ( std::ostream &out, 
                               const cl_error& value);
    std::ostream& operator<< ( std::ostream &out, 
                               const cl_mem_flags& value);
    std::ostream& operator<< ( std::ostream &out,
                               const cl_command_queue_properties& value);
  }
}


