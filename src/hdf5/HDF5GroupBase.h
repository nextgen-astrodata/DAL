#ifndef __HDF5_GROUP_BASE__
#define __HDF5_GROUP_BASE__

#include <string>
#include <vector>
#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/HDF5Node.h"

namespace DAL {

template<typename T> class Attribute;

/*!
 * Wraps an HDF5 group, providing core functionality.
 *
 * An HDF5GroupBase maintains a set of registered HDF5Nodes that it
 * expects to be present.
 */
class HDF5GroupBase: public HDF5Node {
public:
  HDF5GroupBase( HDF5GroupBase &parent, const std::string &name );

  HDF5GroupBase( const HDF5GroupBase &other );

  virtual ~HDF5GroupBase();

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
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *
   *    # Create a group
   *    >>> g = HDF5GroupBase(f, "GROUP")
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
  void set( const HDF5GroupBase &other, bool deepcopy );

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

  /*!
   * Add a node to the map. Ownerschip is taken.
   */
  void addNode( HDF5Node *attr );

  /*!
   * Remove all registered nodes from the map and delete them.
   */
  void freeNodeMap();

protected:
  hid_gc _group;

  virtual void initNodes();

  virtual hid_gc open( hid_t parent, const std::string &name ) const;

  std::vector<std::string> memberNames();

  // constructor for root group
  HDF5GroupBase( const hid_gc &fileid );

private:
  //! The map containing all (registered) nodes in this set
  std::map<std::string, HDF5Node*> nodeMap;

  //! Whether nodeMap is initialised through initNodes()
  bool mapInitialised;

  //! Makes sure that nodeMap can be accessed
  void ensureNodesExist();
};

}

// make sure that Attribute is actually defined
#include "hdf5/HDF5Attribute.h"

#endif

