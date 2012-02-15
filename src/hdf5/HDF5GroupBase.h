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
  HDF5GroupBase( const hid_gc &parent, const std::string &name );

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
  bool exists() const;

  /*!
   * Removes this group from the HDF5 file.
   */
  void remove() const;

  /*!
   * Copies all members from another group into this one.
   *
   * If `deepcopy` is set, subgroups and datasets are copied as well.
   */
  void set( const HDF5GroupBase &other, bool deepcopy );

  Attribute<std::string> groupType();

  virtual const hid_gc &group() {
    // deferred opening of group, as it may need to be created first
    if (!_group)
      _group = open(parent, _name);

    return *_group;
  }

protected:
  const hid_gc parent;
  hid_gc *_group;

  virtual hid_gc *open( hid_t parent, const std::string &name ) const;

  /*!
   * Add extra settings to the creation property list, before creating the group.
   */
  virtual void configure_ocpl( hid_t ocpl ) const;
};

}

#endif

