#ifndef __HDF5NODE__
#define __HDF5NODE__

#include <string>

namespace LDA {

/*
 * Represents a node in the HDF5 hierarchy (the root group or a subgroup).
 */
class HDF5Node {
public:
  HDF5Node( const std::string &name ): _name(name) {}

  std::string name() const { return _name; }

protected:
  const std::string _name;

private:
  HDF5Node &operator=( const HDF5Node & );
};

}

#endif

