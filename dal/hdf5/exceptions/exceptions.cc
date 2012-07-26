#include "dal/hdf5/exceptions/exceptions.h"
#include <sstream>

using namespace std;

namespace DAL {

HDF5Exception::HDF5Exception(const std::string &msg, const HDF5ErrorStack &stack)
:
  DALException(msg),
  stack(stack)
{
}

HDF5Exception::~HDF5Exception() throw() {
}

std::string HDF5Exception::stackSummary() const {
  const vector<struct HDF5StackLine> errorstack = stack.stack();

  if (errorstack.empty())
    return "";

  ostringstream oss(ostringstream::out);

  const size_t n = errorstack.size();

  // include a summary of the first and the last stack line

  oss << errorstack[0].shortDesc();

  if (n > 1)
    oss << " (" << errorstack[n - 1].desc << ")";

  return oss.str();
}

}
