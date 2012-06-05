#include "Group.h"
#include <hdf5.h>

using namespace std;

namespace DAL {

Group::Group( const Group &other )
:
  Node(other.parent, other._name),
  _group(other._group),
  mapInitialised(false)
{
}

Group::Group( Group &parent, const std::string &name )
:
  Node(parent, name),
  mapInitialised(false)
{
}

Group::Group( const hid_gc &fileid )
:
  Node(fileid, ""),
  _group(fileid),
  mapInitialised(false)
{
}

Group::~Group() {
  freeNodeMap();
}

void Group::create() {
  hid_gc_noref gcpl(H5Pcreate(H5P_GROUP_CREATE), H5Pclose, "Could not create group creation property list for group " + _name);

  _group = hid_gc(H5Gcreate2(parent, _name.c_str(), H5P_DEFAULT, gcpl, H5P_DEFAULT), H5Gclose, "Could not create group " + _name);
}

bool Group::exists() const {
  // The root group always exists, but H5Lexists won't work on it
  if (_name == "/")
    return true;

  return H5Lexists(parent, _name.c_str(), H5P_DEFAULT) > 0; // does this check whether the link is a group?
}

void Group::remove() const {
  if (H5Ldelete(parent, _name.c_str(), H5P_DEFAULT) < 0)
    throw HDF5Exception("Could not delete group " + _name); 
}

void Group::set( const Group &other, bool deepcopy ) {
  if (exists()) {
    // maybe rename the attribute instead, in case the copying fails?
    remove();
  }

  hid_gc ocpl(H5Pcreate(H5P_OBJECT_COPY), H5Pclose, "Could not create object creation property list for group " + _name);

  if (!deepcopy) {
    // do a shallow copy
    if (H5Pset_copy_object(ocpl, H5O_COPY_SHALLOW_HIERARCHY_FLAG) < 0) {
      throw HDF5Exception("Could not enable shallow copy mode for group " + _name);
    }
  }

  // H5Ocopy allows us to copy all properties, subgroups, etc, even across files
  if (H5Ocopy(other.parent, other._name.c_str(), parent, _name.c_str(), ocpl, H5P_DEFAULT) < 0)
    throw HDF5Exception("Could not copy object for group " + _name);
}

hid_gc Group::open( hid_t parent, const std::string &name ) const
{
  return hid_gc(H5Gopen2(parent, name.c_str(), H5P_DEFAULT), H5Gclose, "Could not open group " + _name);
}

void Group::initNodes()
{
  addNode(new Attribute<string>(*this, "GROUPTYPE"));
}

Attribute<string> Group::groupType()
{
  return getNode("GROUPTYPE");
}

const hid_gc &Group::group() {
  // deferred opening of group, as it may need to be created first
  if (!_group.isset())
    _group = open(parent, _name);

  return _group;
}

void Group::addNode( Node *attr )
{
  if (!attr)
    throw DALValueError("attr cannot be NULL");

  if (nodeMap.find(attr->name()) != nodeMap.end())
    throw DALValueError("Node already exists: " + attr->name()); 

  nodeMap[attr->name()] = attr;
}

void Group::ensureNodesExist()
{
  if (!exists())
    throw DALException("Cannot access nodes in a non-existing group " + _name);

  if (!mapInitialised) {
    initNodes();
    mapInitialised = true;
  }
}

ImplicitDowncast<Node> Group::getNode( const std::string &name )
{
  ensureNodesExist();
 
  if (nodeMap.find(name) == nodeMap.end())
    throw DALValueError(string("Node not found: ") + name);

  return *nodeMap[name];
}

vector<string> Group::nodeNames() {
  ensureNodesExist();

  vector<string> names;
  names.reserve(nodeMap.size());

  for( map<string, Node*>::const_iterator i = nodeMap.begin(); i != nodeMap.end(); ++i ) {
    names.push_back(i->first);
  }

  return names;
}

void Group::freeNodeMap()
{
  for( map<string, Node*>::const_iterator i = nodeMap.begin(); i != nodeMap.end(); ++i ) {
    delete i->second;
  }

  nodeMap.clear();
}

vector<string> Group::memberNames() {
  vector<string> names;
  H5G_info_t groupInfo;

  if (H5Gget_info(group(), &groupInfo) < 0)
    throw HDF5Exception("could not get info for group " + _name);

  // Loop around H5Lget_name_by_idx(). Can also use H5Literate(), but it is more fuss for what we need here.
  char linkName[128];
  hid_gc_noref lapl(H5Pcreate(H5P_LINK_ACCESS), H5Pclose, "Could not create link access property list for group " + _name);
  for (size_t i = 0; i < groupInfo.nlinks; i++) {
    ssize_t size = H5Lget_name_by_idx(group(), ".", H5_INDEX_CRT_ORDER, H5_ITER_NATIVE, i, linkName, sizeof linkName, lapl);
    if (size < 0)
      throw HDF5Exception("could not get link name by index for group " + _name);

    names.push_back(linkName);
  }

  return names;
}

}

