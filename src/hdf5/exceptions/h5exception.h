#ifndef __H5EXCEPTION__
#define __H5EXCEPTION__

#include <stdexcept>
#include <sstream>
#include <string>
#include "hdf5/exceptions/h5errorstack.h"

namespace DAL {

class DALException: public std::runtime_error
{
public:
  DALException(const std::string &msg): std::runtime_error(msg) {}
};

class DALValueError: public DALException
{
public:
  DALValueError(const std::string &msg): DALException(msg) {}
};

class DALIndexError: public DALValueError
{
public:
  DALIndexError(const std::string &msg): DALValueError(msg) {}
};

class HDF5Exception: public DALException
{
public:
  HDF5Exception(const std::string &msg, const HDF5ErrorStack &stack = HDF5ErrorStack()): DALException(msg), stack(stack) {}

  HDF5ErrorStack stack;

  std::string stackSummary() const {
    if (stack.stack.empty())
      return "";

    std::ostringstream oss(std::ostringstream::out);

    const size_t n = stack.stack.size();

    // include a summary of the first and the last stack line

    oss << stack.stack[0].shortDesc();

    if (n > 1)
      oss << " (" << stack.stack[n - 1].desc << ")";

    return oss.str();
  }
};

}

#endif

