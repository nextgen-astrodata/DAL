#ifndef __HDF5_GROUP_BASE__
#define __HDF5_GROUP_BASE__

#include <string>
#include <vector>
#include <hdf5.h>
#include "types/hid_gc.h"
#include "Node.h"

namespace DAL {

template<typename T> class Attribute;

/*!
 * Wraps an HDF5 group, providing core functionality.
 *
 * An Group maintains a set of registered Nodes that it
 * expects to be present.
 */
class Group: public Node {
public:
  Group( Group &parent, const std::string &name );

  Group( const Group &other );

  virtual ~Group();

  /*!
   * Add this group to the HDF5 file.
   *
   * Note: any attributes and subgroups must be added separately.
   */
  virtual void create();

  /*!
   * Returns whether this group exists in the HDF5 file.
   */
  virtual bool exists() const;

  /*!
   * Removes this group from the HDF5 file.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Create a group
   *    >>> g = Group(f, "GROUP")
   *    >>> g.create()
   *    >>> g.exists()
   *    True
   *
   *    # Delete the group
   *    >>> g.remove()
   *    >>> g.exists()
   *    False
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  void remove() const;

  /*!
   * Copies all members from another group into this one.
   *
   * If `deepcopy` is set, subgroups and datasets are copied as well.
   */
  void set( const Group &other, bool deepcopy );

  Attribute<std::string> groupType();

  /*!
   * Exposes the HDF5 object ID of this group. Opens the group
   * if needed.
   */
  virtual const hid_gc &group();

  /*!
   * Returns a list of the HDF5 names of all nodes registered
   * in this class.
   */
  std::vector<std::string> nodeNames();

#ifndef SWIG

  /*!
   * Returns a reference to a node from the map. initNodes() is called
   * if needed, and an exception is thrown if the group
   * has not been opened or created yet.
   *
   * ImplicitDowncast<Node> allows getNode to be automatically
   * cast to the required type (a subclass of Node), for example:
   *
   * Attribute<int> &attr = getNode("MY_INTEGER");
   *
   * It is the responsibility of the caller to request a type
   * that is compatible with the type of object that is retrieved.
   * If not, an std::bad_cast exception is thrown.
   */
  ImplicitDowncast<Node> getNode( const std::string &name );

#endif

  /*!
   * Add a node to the map. Ownerschip is taken.
   */
  void addNode( Node *attr );

  /*!
   * Remove all registered nodes from the map and delete them.
   */
  void freeNodeMap();

protected:
  hid_gc _group;

  virtual void initNodes();

  virtual hid_gc open( hid_t parent, const std::string &name ) const;

  std::vector<std::string> memberNames();

  // constructor for root group (and default initialized sub-class obj; undesirable)
  Group( const hid_gc &fileId );

private:
  //! The map containing all (registered) nodes in this set
  std::map<std::string, Node*> nodeMap;

  //! Whether nodeMap is initialised through initNodes()
  bool mapInitialised;

  //! Makes sure that nodeMap can be accessed
  void ensureNodesExist();
};

}

// make sure that Attribute is actually defined
#include "Attribute.h"

#endif

