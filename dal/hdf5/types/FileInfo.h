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
#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <string>

#include "versiontype.h"

namespace DAL {

/*!
 * A FileInfo object stores file-scope info that becomes known when a file is opened
 * and may be needed by any object in the HDF5 hierarchy.
 * Once set, this info cannot be changed.
 * An exception is fileVersion which is needed everywhere, but is also stored
 * as an attribute and thus may be changed.
 *
 * FileInfo objects are reference counted using FileInfoRef to remain open until all
 * file objects have been closed (i.e. the moment HDF5 can close the file).
 *
 * This class is intended to be used through FileInfoRef only. Do not use directly.
 */
class FileInfo {
  friend class FileInfoRef;

  mutable unsigned refCount;

  /*!
   * Directory name of the file opened (no trailing '/'). If no dir was specified, it is ".".
   * Needed to work around an HDF5 issue related to external data sets and the cwd.
   */
  const std::string fileDirName;

  //! True if the file was opened for writing (CREATE, CREATE_EXCL, or READWRITE).
  const bool canWrite;

  //! The file version as stored. In general, caching attributes is undesirable.
  const VersionType fileVersion;


  FileInfo();
  FileInfo(const std::string& fileDirName, bool canWrite, const VersionType& fileVersion);
};

/*!
 * A FileInfoRef refers a FileInfo object, possible along with other FileInfoRef objects.
 * All FileInfo members are accessed read-only only, except fileVersion.
 * For more detail, see class FileInfo.
 */
class FileInfoRef {
  FileInfo* ptr;

public:
  FileInfoRef();
  FileInfoRef(const std::string& fileDirName, bool canWrite, const VersionType& fileVersion);
  FileInfoRef(const FileInfoRef& other);
  ~FileInfoRef();
  FileInfoRef& operator=(FileInfoRef rhs);

  friend void swap(FileInfoRef& fi0, FileInfoRef& fi1);

  const std::string& fileDirName();
  bool canWrite();
  VersionType fileVersion();
};

}

#endif

