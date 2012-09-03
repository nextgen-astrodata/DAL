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
#include "Group.h"

using namespace std;

namespace dal {

Node::Node()
:
  parent(hid_gc()),
  _name(),
  minVersion(0),
  fileInfo()
{
}

Node::Node( Group &parent, const std::string &name )
:
  parent(parent.group()), // .group(): friend-allowed
  _name(name),
  minVersion(parent.minVersion),
  fileInfo(parent.fileInfo)
{
}

//! Constructor for Node of root group (in File) only.
Node::Node( const hid_gc &parent, const std::string &name, FileInfo fileInfo )
:
  parent(parent),
  _name(name),
  minVersion(),
  fileInfo(fileInfo)
{
}

Node::~Node() {}

Node& Node::operator=(Node rhs)
{
  swap(*this, rhs);
  return *this;
}

void swap(Node& first, Node& second)
{
  swap(first.parent, second.parent);
  swap(first._name, second._name);
  std::swap(first.minVersion, second.minVersion);
  swap(first.fileInfo, second.fileInfo);
}


/*
 * Just forward the calls. For a few values, this is preferable, because then
 * we can stick the FileInfo ref counting into a separate class FileInfoRef.
 */
const string& Node::filename() const {
  return fileInfo.filename();
}

Node::FileMode Node::fileMode() const {
  return fileInfo.fileMode();
}

bool Node::canWrite() const {
  FileMode mode = fileMode();
  return mode == CREATE || mode == CREATE_EXCL || mode == READWRITE;
}

const std::string& Node::versionAttrName() const {
  return fileInfo.versionAttrName();
}

int Node::fileDirfd() const {
  return fileInfo.fileDirfd();
}

VersionType& Node::fileInfoVersion() const {
  return fileInfo.fileVersion();
}

void Node::setFileInfoVersion(const VersionType& newVersion) {
  fileInfo.setFileVersion(newVersion);
}

}

