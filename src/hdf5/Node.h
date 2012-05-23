#ifndef __HDF5_NODE__
#define __HDF5_NODE__

#include <string>
#include <map>
#include <vector>
#include <typeinfo>
#include "hdf5/exceptions/h5exception.h"
#include "hdf5/types/hid_gc.h"
#include "hdf5/types/implicitdowncast.h"
#include "hdf5/types/versiontype.h"

namespace DAL {

class Group;

/*!
 * Represents a node in the HDF5 hierarchy (an attribute, group, or dataset).
 */
class Node {
public:
  Node( Group &parent, const std::string &name );

  virtual ~Node() {}

  /*!
   * Returns the HDF5 name of this node.
   */
  std::string name() const { return _name; }

  /*!
   * Returns whether this element exists in the HDF5 file.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # An open file always exists
   *    >>> f.exists()
   *    True
   *
   *    # Reference an attribute in the file
   *    >>> a = AttributeString(f, "EXAMPLE_ATTRIBUTE")
   *
   *    # Initially, the attribute does not exist
   *    >>> a.exists()
   *    False
   *
   *    # If we create it, it does exist
   *    >>> a.create()
   *    <...>
   *    >>> a.exists()
   *    True
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
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
   *    >>> f = File("example.h5", File.CREATE)
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
   *    >>> f = File("example.h5", File.CREATE)
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
  bool supported() { return minVersion <= fileVersion(); }

  /*!
   * Whether the file was opened for writing.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
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
   *    >>> f = File("example.h5", File.READ)
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
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Query the file name
   *    >>> f.fileName()
   *    'example.h5'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  std::string fileName() const { return data.fileName; }

  /*!
   * The name of the HDF5 directory containing this node. The
   * file object has parentNodePath() == "".
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *    >>> g = Group(f, "GROUP")
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
/*
  std::string className() const { return typeid(*this).name(); }
*/
protected:
  hid_gc parent;
  std::string _name;

  Node( const hid_gc &parent, const std::string &name );

  /*!
   * Data that will be propagated through the object tree,
   * if subgroups and attributes are accessed.
   *
   * Propagation only occurs at object creation. Thus
   * if any of these properties are changed, already existing
   * objects representing subnodes are not updated.
   */
  struct PropagatedData {
    //! The file version as it was set when this object was created
    VersionType fileVersion;

    //! True if this file was opened for writing (CREATE or READWRITE)
    bool canWrite;

    //! Name of the file containing this node.
    std::string fileName;

    //! Name of the HDF5 directory containing this node.
    std::string parentNodePath;

    PropagatedData(): canWrite(false) {}
  };

  PropagatedData data;
};

}

// make sure that Group is defined
#include "hdf5/Group.h"

#endif

