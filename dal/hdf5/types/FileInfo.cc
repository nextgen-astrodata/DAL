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

#include <cstddef>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>

#include <vector>
#include "FileInfo.h"

using namespace std;

namespace DAL {

FileInfo::FileInfo() : ptr(new FileInfoType) { }

FileInfo::FileInfo(const std::string& fullFileName, FileMode fileMode,
                   const std::string& versionAttrName)
: ptr(new FileInfoType(fullFileName, openOtherDirname(fullFileName),
                       fileMode, versionAttrName)) { }

FileInfo::FileInfo(const FileInfo& other) : ptr(other.ptr) {
  ptr->refCount += 1;
}

FileInfo::~FileInfo() {
  if (--ptr->refCount == 0) {
    ::close(ptr->fdirfd);
    delete ptr;
  }
}

FileInfo& FileInfo::operator=(FileInfo rhs) {
  swap(*this, rhs);
  return *this;
}

void swap(FileInfo& fi0, FileInfo& fi1) {
  // no need to fiddle with the refCount
  std::swap(fi0.ptr, fi1.ptr);
}

const string& FileInfo::fileName() const {
  return ptr->fileName;
}

int FileInfo::fileDirfd() const {
  return ptr->fdirfd;
}

FileInfo::FileMode FileInfo::fileMode() const {
  return ptr->fileMode;
}

const std::string& FileInfo::versionAttrName() const {
  return ptr->versionAttrName;
}

VersionType& FileInfo::fileVersion() const {
  return ptr->fileVersion;
}

void FileInfo::setFileVersion(const VersionType& newVersion) {
  ptr->fileVersion = newVersion;
}

int FileInfo::openOtherDirname(const string& fileName) {
  string dirName(getDirname(fileName));
  if (dirName == ".")
    return -1;
  return ::open(dirName.c_str(), O_RDONLY);
}

// static functions
//! C++ interface to basename(3). Returns filename without path.
string FileInfo::getBasename(const string& filename) {
  vector<char> fn(filename.size() + 1);
  memcpy(&fn[0], filename.c_str(), filename.size() + 1);

  char* bn = basename(&fn[0]); // may overlap or point to static storage

  return string(bn);
}

//! C++ interface to dirname(3). Returns path of filename.
string FileInfo::getDirname(const string& filename) {
  vector<char> fn(filename.size() + 1);
  memcpy(&fn[0], filename.c_str(), filename.size() + 1);

  char* dn = dirname(&fn[0]); // may overlap or point to static storage

  return string(dn);
}

////////////////////////////////////////////////////////////////////////////////

FileInfoType::FileInfoType() : refCount(1), fdirfd(-1), fileMode(0) { }

FileInfoType::FileInfoType(const std::string& fileName, int fdirfd,
                           FileInfo::FileMode fileMode, const std::string& versionAttrName)
: refCount(1)
, fileName(fileName)
, fdirfd(fdirfd)
, fileMode(fileMode)
, versionAttrName(versionAttrName)
{ }


}

