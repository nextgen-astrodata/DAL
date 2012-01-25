#include "HDF5GroupBase.h"
#include <hdf5.h>

using namespace std;

namespace LDA {

HDF5GroupBase::HDF5GroupBase( const HDF5GroupBase &other )
:
  HDF5NodeSet(other._name),
  parent(other.parent),
  _group(other._group ? new hid_gc(*other._group) : 0)
{
}

HDF5GroupBase::HDF5GroupBase( const hid_gc &parent, const std::string &name )
:
  HDF5NodeSet(name),
  parent(parent),
  _group(0)
{
}

HDF5GroupBase::~HDF5GroupBase() {
  delete _group;
}

void HDF5GroupBase::create() {
  hid_gc_noref gcpl(H5Pcreate(H5P_GROUP_CREATE), H5Pclose, "Could not create group creation property list (gcpl)");

  configure_ocpl(gcpl);

  delete _group; _group = 0;
  _group = new hid_gc(H5Gcreate2(parent, _name.c_str(), H5P_DEFAULT, gcpl, H5P_DEFAULT), H5Gclose, "Could not create group");
}

void HDF5GroupBase::configure_ocpl( hid_t ocpl ) const {
  // make sure we use dense storage to be able to store attributes >64 kB in size
  if (H5Pset_link_phase_change(ocpl, 0, 0) < 0)
    throw HDF5Exception("Could not configure group for dense storage");
}

bool HDF5GroupBase::exists() const {
  return H5Lexists(parent, _name.c_str(), H5P_DEFAULT) > 0; // does this check whether the link is a group?
}

void HDF5GroupBase::remove() const {
  if (H5Ldelete(parent, _name.c_str(), H5P_DEFAULT) < 0)
    throw HDF5Exception("Could not delete group"); 
}

void HDF5GroupBase::set( const HDF5GroupBase &other, bool deepcopy ) {
  if (exists()) {
    // maybe rename the attribute instead, in case the copying fails?
    remove();
  }

  hid_gc ocpl(H5Pcreate(H5P_OBJECT_COPY), H5Pclose, "Could not create property list");

  if (!deepcopy) {
    // do a shallow copy
    if (H5Pset_copy_object(ocpl, H5O_COPY_SHALLOW_HIERARCHY_FLAG) < 0) {
      throw HDF5Exception("Could not enable shallow copy mode");
    }
  }

  // H5Ocopy allows us to copy all properties, subgroups, etc, even across files
  if (H5Ocopy(other.parent, other._name.c_str(), parent, _name.c_str(), ocpl, H5P_DEFAULT) < 0)
    throw HDF5Exception("Could not copy element");
}

hid_gc *HDF5GroupBase::open( hid_t parent, const std::string &name ) const
{
  return new hid_gc(H5Gopen2(parent, name.c_str(), H5P_DEFAULT), H5Gclose, "Could not open group");
}

Attribute<string> HDF5GroupBase::groupType()
{
  return Attribute<string>(group(), "GROUPTYPE");
}

}

