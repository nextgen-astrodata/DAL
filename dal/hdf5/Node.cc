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
#include "Node.h"
#include "Attribute.h"
#include "Group.h"
#include <string>

using namespace std;

namespace DAL {

Node::Node()
:
  minVersion(0),
  parent(hid_gc()),
  _name("")
{
}

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

Node::~Node() {}

VersionType Node::fileVersion()
{
  return data.fileVersion;
}

bool Node::canWrite() const
{
  return data.canWrite;
}

}
