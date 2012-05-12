#ifndef __HDF5GROUP__
#define __HDF5GROUP__

#include <string>
#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5Node.h"

namespace DAL {

/*!
 * Wraps an HDF5 group, providing core functionality.
 */
class HDF5GroupBase: public HDF5NodeSet {
public:
  HDF5GroupBase( HDF5NodeSet &parent, const std::string &name );

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

protected:
  hid_gc _group;

  virtual void initNodes();

  virtual hid_gc open( hid_t parent, const std::string &name ) const;

  // constructor for root group
  HDF5GroupBase( const hid_gc &fileid );
};

}

#endif

