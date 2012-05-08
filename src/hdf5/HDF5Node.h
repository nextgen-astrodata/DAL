#ifndef __HDF5NODE__
#define __HDF5NODE__

#include <string>
#include <map>
#include <vector>
#include "hdf5/exceptions/h5exception.h"
#include "hdf5/types/hid_gc.h"
#include "hdf5/types/implicitdowncast.h"
#include "hdf5/types/versiontype.h"

namespace DAL {

/*!
 * Represents a node in the HDF5 hierarchy (an attribute, group, or dataset).
 */
class HDF5Node {
public:
  HDF5Node( const std::string &name ): _name(name) {}

  virtual ~HDF5Node() {} // a destructor makes this class polymorphic, allowing dynamic_cast

  /*!
   * Returns the HDF5 name of this node.
   */
  std::string name() const { return _name; }

  /*!
   * The minimal version required for this node to be supported.
   */
  VersionType minVersion;

  /*!
   * Returns whether this element exists in the HDF5 file.
   */
  virtual bool exists() const { return false; }

protected:
  std::string _name;
  VersionType _minVersion;
};

/*!
 * Represents a set in the HDF5 hierarchy (a file, group or dataset;
 * anything that can have attributes and hold other nodes).
 */
class HDF5NodeSet: public HDF5Node {
public:
  HDF5NodeSet( const std::string &name );

  virtual ~HDF5NodeSet();

  /*!
   * Returns the HDF5 identifier for this set, which is required
   * when accessing substructures.
   */
  virtual const hid_gc &group() = 0;

  VersionType fileVersion();

  /*!
   * Returns a list of the HDF5 names of all nodes.
   */
  std::vector<std::string> nodeNames();

#ifndef SWIG

  /*!
   * Returns a reference to a node from the map. initNodes() is called
   * if needed, and an exception is thrown if the group
   * has not been opened or created yet.
   *
   * ImplicitDowncast<HDF5Node> allows getNode to be automatically
   * cast to the required type (a subclass of HDF5Node), for example:
   *
   * Attribute<int> &attr = getNode("MY_INTEGER");
   *
   * It is the responsibility of the caller to request a type
   * that is compatible with the type of object that is retrieved.
   * If not, an std::bad_cast exception is thrown.
   */
  ImplicitDowncast<HDF5Node> getNode( const std::string &name );

#endif

protected:
  /*!
   * Add all known nodes to the map. This function will be called
   * when a node is requested.
   */
  virtual void initNodes() {}

  /*!
   * Add a node to the map. Ownerschip is taken.
   */
  void addNode( HDF5Node *attr );

  /*!
   * Remove all registered nodes from the map and delete them.
   */
  void freeNodeMap();

private:
  // The map containing all (registered) nodes in this set
  std::map<std::string, HDF5Node*> nodeMap;

  // Whether nodeMap is initialised through initNodes()
  bool mapInitialised;

  // Makes sure that nodeMap can be accessed
  void ensureNodesExist();
};

}

#endif

