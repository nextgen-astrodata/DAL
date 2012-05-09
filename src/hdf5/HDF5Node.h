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

class HDF5NodeSet;

/*!
 * Represents a node in the HDF5 hierarchy (an attribute, group, or dataset).
 */
class HDF5Node {
public:
  HDF5Node( HDF5NodeSet &parent, const std::string &name );

  HDF5Node( const hid_gc &parent, const std::string &name );

  virtual ~HDF5Node() {} // a destructor makes this class polymorphic, allowing dynamic_cast

  /*!
   * Returns the HDF5 name of this node.
   */
  std::string name() const { return _name; }

  /*!
   * Returns whether this element exists in the HDF5 file.
   */
  virtual bool exists() const { return false; }

  /*!
   * The minimal version required for this node to be supported. Version numbers
   * are user-defined, and matched against a fixed field in the HDF5 file
   * (see fileVersion()).
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *    >>> a = AttributeString(f, "EXAMPLE_ATTRIBUTE")
   *
   *    # The minimal required version of any node is 0.0.0 by default
   *    >>> a.minVersion
   *    VersionType('0.0.0')
   *
   *    # Setting the minimal version.
   *    >>> a.minVersion = VersionType('1.2.3')
   *
   *    # Requesting the minimal version.
   *    >>> str(a.minVersion)
   *    '1.2.3'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  VersionType minVersion;

  /*!
   * The version of the file.
   */
  VersionType fileVersion();

  /*!
   * Returns whether this node is supported by the current version.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *
   *    # Set the file's version number to 2.0.0
   *    >>> f.setFileVersion(VersionType("2.0.0"))
   *
   *    # Create some attribute to play with
   *    >>> a = AttributeString(f, "EXAMPLE_ATTR")
   *    >>> a.value = "hello world"
   *
   *    # Request the file version (any node in the file will do)
   *    >>> f.fileVersion()
   *    VersionType('2.0.0')
   *    >>> a.fileVersion()
   *    VersionType('2.0.0')
   *
   *    # If an attribute is older than the file,
   *    # it is supported and should be present.
   *    >>> a.minVersion = VersionType('1.0.0')
   *    >>> a.supported()
   *    True
   *
   *    # If an attribute is newer than the file,
   *    # it is possibly not present and therefor
   *    # not supported.
   *    >>> a.minVersion = VersionType('2.1.0')
   *    >>> a.supported()
   *    False
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  bool supported() {
    return minVersion <= fileVersion();
  }

  /*!
   * Whether the file was opened for writing.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *    >>> f.canWrite()
   *    True
   *
   *    # Can also query other nodes
   *    >>> a = AttributeString(f, "EXAMPLE_ATTR")
   *    >>> a.canWrite()
   *    True
   *
   *    # Reopen the same file read-only
   *    >>> del a
   *    >>> del f
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.READ)
   *    >>> f.canWrite()
   *    False
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  bool canWrite() const;

  /*!
   * The name of the file as it was opened.
   */
  std::string fileName() const { return data.fileName; }

  /*!
   * The name of the HDF5 directory containing this node. The
   * file object has parentNodePath() == "".
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *    >>> g = HDF5GroupBase(f, "GROUP")
   *    >>> g.create()
   *    >>> a = AttributeString(g, "ATTRIBUTE")
   *    >>> a.create()
   *    <...>
   *
   *    # Query HDF5 path info
   *    >>> f.parentNodePath()
   *    ''
   *    >>> g.parentNodePath()
   *    '/'
   *    >>> a.parentNodePath()
   *    '/GROUP'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  std::string parentNodePath() const { return data.parentNodePath; }

protected:
  hid_gc parent;
  std::string _name;

  /*!
   * Data that will be propagated through the object tree,
   * if subgroups and attributes are accessed.
   *
   * Propagation only occurs at object creation. Thus
   * if any of these properties are changed, already existing
   * objects representing subnodes are not updated.
   */
  struct PropagatedData {
    VersionType fileVersion;
    bool canWrite;

    //! Name of the file containing this node.
    std::string fileName;

    //! Name of the HDF5 directory containing this node.
    std::string parentNodePath;

    PropagatedData(): canWrite(false) {}
  };

  PropagatedData data;
};

/*!
 * Represents a set in the HDF5 hierarchy (a file, group or dataset;
 * anything that can have attributes and hold other nodes).
 */
class HDF5NodeSet: public HDF5Node {
public:
  HDF5NodeSet( const hid_gc &parent, const std::string &name );
  HDF5NodeSet( HDF5NodeSet &parent, const std::string &name );

  virtual ~HDF5NodeSet();

  /*!
   * Returns the HDF5 identifier for this set, which is required
   * when accessing substructures.
   */
  virtual const hid_gc &group() = 0;

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

