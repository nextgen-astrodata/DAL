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

#include "FileInfo.h"

using namespace std;

namespace DAL {

FileInfo::FileInfo() : refCount(1), canWrite(false) { }

FileInfo::FileInfo(const string& fileDirName, bool canWrite, const VersionType& fileVersion)
: refCount(1)
, fileDirName(fileDirName)
, canWrite(canWrite)
, fileVersion(fileVersion)
{ }

////////////////////////////////////////////////////////////////////////////////

FileInfoRef::FileInfoRef() : ptr(new FileInfo) { }

FileInfoRef::FileInfoRef(const string& fileDirName, bool canWrite, const VersionType& fileVersion)
: ptr(new FileInfo(fileDirName, canWrite, fileVersion)) { }

FileInfoRef::FileInfoRef(const FileInfoRef& other) : ptr(other.ptr) {
  ptr->refCount += 1;
}

FileInfoRef::~FileInfoRef() {
  if (ptr->refCount == 1) {
    delete ptr;
  }
}

FileInfoRef& FileInfoRef::operator=(FileInfoRef rhs) {
  swap(*this, rhs);
  return *this;
}

void swap(FileInfoRef& fi0, FileInfoRef& fi1) {
  // no need to fiddle with the refCount
  std::swap(fi0.ptr, fi1.ptr);
}

const string& FileInfoRef::fileDirName() {
  return ptr->fileDirName;
}

bool FileInfoRef::canWrite() {
  return ptr->canWrite;
}

//TODO: how to update the version if it is changed through Attribute<VersionType> xxx ?
VersionType FileInfoRef::fileVersion() {
  return ptr->fileVersion;
}


}

