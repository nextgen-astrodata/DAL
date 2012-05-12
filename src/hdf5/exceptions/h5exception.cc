#include "hdf5/exceptions/h5exception.h"
#include <sstream>

using namespace std;

namespace DAL {

HDF5Exception::HDF5Exception(const std::string &msg, const HDF5ErrorStack &stack)
:
  DALException(msg),
  stack(stack)
{
}

std::string HDF5Exception::stackSummary() const {
  if (stack.stack.empty())
    return "";

  ostringstream oss(ostringstream::out);

  const size_t n = stack.stack.size();

  // include a summary of the first and the last stack line

  oss << stack.stack[0].shortDesc();

  if (n > 1)
    oss << " (" << stack.stack[n - 1].desc << ")";

  return oss.str();
}

}
