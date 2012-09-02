/* Copyright 2011-2012  ASTRON, Netherlands Institute for Radio Astronomy
 * This file is part of the Data Access Library (DAL).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DAL_GROUP_H
#define DAL_GROUP_H

#include <string>
#include <vector>
#include <map>
#include <hdf5.h>
#include "types/implicitdowncast.h"
#include "Node.h"
#include "Attribute.h"

namespace DAL {

/*!
 * Wraps an HDF5 group, providing core functionality.
 *
 * A Group maintains a set of registered Nodes that it
 * expects to be present.
 */
class Group: public Node {
public:
  Group();

  Group( Group &parent, const std::string &name );

  Group( const Group &other );

  virtual ~Group();

  Group& operator=(Group rhs);

  friend void swap(Group& first, Group& second);

  /*!
   * Add this group to the HDF5 file.
   *
   * Note: any attributes and subgroups must be added separately.
   */
  virtual Group& create();

  /*!
   * Returns whether this group exists as a HDF5 group or dataset in the HDF5 file.
   */
  virtual bool exists() const;

  /*!
   * Removes this group/dataset from the HDF5 file.
   * (Actually, a link to this data set is removed, but since we do not offer a
   * way to create multiple links to a group, the group is indeed removed from the file.)
   * Any members of this group will also be removed, although they will appear
   * to still exists until all references to them have been dropped (like with Unix files).
   * If this is a dataset, external files (if any) are not touched.
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

protected:
  //! hid of the Group. Always read it through group().
  hid_gc _group;


  friend Node::Node( Group &parent, const std::string &name );
  /*!
   * Exposes the HDF5 object ID of this group. Opens the group if needed.
   */
  const hid_gc &group(); // protected w/ friend above to keep hid_gc inside DAL

  // initNodes() does not have to be virtual, as long as any new sub-classes
  // that have initNodes() also have their own virtual open() like the one here.
  void initNodes();

  /*!
   * Add a node to the node map. Ownerschip is taken. Do not pass NULL.
   */
  void addNode( Node *attr );

  std::vector<std::string> memberNames();

  //! Constructor for root group (in File) only
  Group( const hid_gc &fileId, FileInfo fileInfo );

private:
  //! The map containing all (registered) nodes in this set
  std::map<std::string, Node*> nodeMap;

  virtual void open( hid_t parent, const std::string &name );

  void freeNodeMap();
};

}

#endif

