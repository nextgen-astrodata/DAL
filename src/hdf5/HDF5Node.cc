#include "hdf5/HDF5Node.h"
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5GroupBase.h"
#include <string>

using namespace std;

namespace DAL {

HDF5Node::HDF5Node( HDF5GroupBase &parent, const std::string &name )
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

HDF5Node::HDF5Node( const hid_gc &parent, const std::string &name )
:
  parent(parent),
  _name(name)
{
}

VersionType HDF5Node::fileVersion()
{
  return data.fileVersion;
}

bool HDF5Node::canWrite() const
{
  return data.canWrite;
}

}
