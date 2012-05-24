#include "dal/hdf5/Node.h"
#include "dal/hdf5/Attribute.h"
#include "dal/hdf5/Group.h"
#include <string>

using namespace std;

namespace DAL {

Node::Node( Group &parent, const std::string &name )
:
  minVersion(parent.minVersion),
  parent(parent.group()),
  _name(name),
  data(parent.data)
{
  const std::string parentName = parent.name();

  if (parentName.empty())
    // parent is the root group
    data.parentNodePath = "/";
  else if (parentName[0] == '/')
    // absolute path
    data.parentNodePath = parentName;
  else  
    // relative path (note: HDF5 does not support /../ like UNIX does)
    if (data.parentNodePath == "/")
      data.parentNodePath = "/" + parent.name();
    else  
      data.parentNodePath = data.parentNodePath + "/" + parent.name();
}

Node::Node( const hid_gc &parent, const std::string &name )
:
  parent(parent),
  _name(name)
{
}

VersionType Node::fileVersion()
{
  return data.fileVersion;
}

bool Node::canWrite() const
{
  return data.canWrite;
}

}
