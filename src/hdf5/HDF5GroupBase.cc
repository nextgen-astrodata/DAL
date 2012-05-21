#include "HDF5GroupBase.h"
#include <hdf5.h>

using namespace std;

namespace DAL {

HDF5GroupBase::HDF5GroupBase( const HDF5GroupBase &other )
:
  HDF5NodeSet(other.parent, other._name),
  _group(other._group)
{
}

HDF5GroupBase::HDF5GroupBase( HDF5NodeSet &parent, const std::string &name )
:
  HDF5NodeSet(parent, name)
{
}

HDF5GroupBase::HDF5GroupBase( const hid_gc &fileid )
:
  HDF5NodeSet(fileid, ""),
  _group(fileid)
{
}

HDF5GroupBase::~HDF5GroupBase() {
}

void HDF5GroupBase::create() {
  hid_gc_noref gcpl(H5Pcreate(H5P_GROUP_CREATE), H5Pclose, "Could not create group creation property list (gcpl)");

  _group = hid_gc(H5Gcreate2(parent, _name.c_str(), H5P_DEFAULT, gcpl, H5P_DEFAULT), H5Gclose, "Could not create group");
}

bool HDF5GroupBase::exists() const {
  // The root group always exists, but H5Lexists won't work on it
  if (_name == "/")
    return true;

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

hid_gc HDF5GroupBase::open( hid_t parent, const std::string &name ) const
{
  return hid_gc(H5Gopen2(parent, name.c_str(), H5P_DEFAULT), H5Gclose, "Could not open group");
}

void HDF5GroupBase::initNodes()
{
  addNode(new Attribute<string>(*this, "GROUPTYPE"));
}

Attribute<string> HDF5GroupBase::groupType()
{
  return getNode("GROUPTYPE");
}

const hid_gc &HDF5GroupBase::group() {
  // deferred opening of group, as it may need to be created first
  if (!_group.isset())
    _group = open(parent, _name);

  return _group;
}

vector<string> HDF5GroupBase::memberNames() {
  vector<string> names;
  H5G_info_t groupInfo;

  if (H5Gget_info(group(), &groupInfo) < 0)
    throw HDF5Exception("could not get group info");

  // Loop around H5Lget_name_by_idx(). Can also use H5Literate(), but it is more fuss for what we need here.
  char linkName[128];
  hid_gc_noref lapl(H5Pcreate(H5P_LINK_ACCESS), H5Pclose, "Could not create link access property list");
  for (size_t i = 0; i < groupInfo.nlinks; i++) {
    ssize_t size = H5Lget_name_by_idx(group(), ".", H5_INDEX_CRT_ORDER, H5_ITER_NATIVE, i, linkName, sizeof linkName, lapl);
    if (size < 0)
      throw HDF5Exception("could not get link name by index");

    names.push_back(linkName);
  }

  return names;
}

}

