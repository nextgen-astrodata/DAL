#include "hdf5/HDF5Node.h"

namespace DAL {

HDF5NodeSet::~HDF5NodeSet()
{
  freeNodeMap();
}

void HDF5NodeSet::addNode( HDF5Node *attr )
{
  if (!attr)
    throw DALValueError("attr cannot be NULL");

  if (nodeMap.find(attr->name()) != nodeMap.end())
    throw DALValueError(std::string("Node already exists: ") + name); 

  nodeMap[attr->name()] = attr;
}

ImplicitDowncast<HDF5Node> HDF5NodeSet::getNode( const std::string &name )
{
  if (!exists())
throw DALException("Cannot access nodes in a non-existing group");

  if (!mapInitialised) {
    initNodes();
    mapInitialised = true;
  }
 
  if (nodeMap.find(name) == nodeMap.end())
    throw DALValueError(std::string("Node not found: ") + name); 

  return *nodeMap[name];
}

void HDF5NodeSet::freeNodeMap()
{
  for( std::map<std::string, HDF5Node*>::const_iterator i = nodeMap.begin(); i != nodeMap.end(); ++i ) {
    delete i->second;
  }

  nodeMap.clear();
}

}
