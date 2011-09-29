#ifndef __H5EXCEPTION__
#define __H5EXCEPTION__

#include <stdexcept>

namespace LDA {

class HDF5Exception: public std::runtime_error
{
public:
  HDF5Exception(const std::string &msg): std::runtime_error(msg) {}
};

}

#endif

