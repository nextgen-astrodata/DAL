#ifndef __HDF5NODE__
#define __HDF5NODE__

#include <string>
#include "hdf5core/hid_gc.h"

namespace LDA {

/*!
 * Represents a node in the HDF5 hierarchy (an attribute, group, or dataset).
 */
class HDF5Node {
public:
  HDF5Node( const std::string &name ): _name(name) {}

  /*!
   * Returns the HDF5 name of this node.
   */
  std::string name() const { return _name; }

protected:
  const std::string _name;

private:
  HDF5Node &operator=( const HDF5Node & );
};

/*!
 * Represents a set in the HDF5 hierarchy (a file, group or dataset;
 * anything that can have attributes and hold other nodes).
 */
class HDF5NodeSet: public HDF5Node {
public:
  HDF5NodeSet( const std::string &name ): HDF5Node(name) {}

  /*!
   * Returns the HDF5 identifier for this set.
   */
  virtual const hid_gc &group() = 0;
};


}

#endif

