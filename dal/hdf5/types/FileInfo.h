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
#ifndef DAL_FILE_INFO_H
#define DAL_FILE_INFO_H

#include <string>
#include "versiontype.h"

namespace DAL {

class FileInfoType;

/*!
 * A FileInfo object is a reference to a reference counted FileInfoType object.
 * All FileInfoType members are read-only, except fileVersion.
 * For more detail, see class FileInfoType, which stores the actual data.
 */
class FileInfo {
  FileInfoType* ptr;

public:
  typedef int FileMode; // see class Node for possible values

  FileInfo();
  FileInfo(const std::string& fullFilename, FileMode fileMode,
           const std::string& versionAttrName);
  FileInfo(const FileInfo& other);
  ~FileInfo();
  FileInfo& operator=(FileInfo rhs);

  friend void swap(FileInfo& fi0, FileInfo& fi1);

  const std::string& filename() const;
  int fileDirfd() const;
  FileMode fileMode() const;
  const std::string& versionAttrName() const;
  VersionType& fileVersion() const;

  void setFileVersion(const VersionType& newVersion);


  static std::string getBasename(const std::string& filename);
  static std::string getDirname(const std::string& filename);

private:
  int openOtherDirname(const std::string& filename);
};

/*!
 * A FileInfoType object stores file-scope info that becomes known when a file is opened
 * and may be needed by any object in the HDF5 hierarchy.
 * Once set, this info cannot be changed.
 * An exception is fileVersion which is needed everywhere, but is also stored
 * as an attribute and thus may be changed.
 *
 * FileInfoType objects are reference counted using FileInfo to remain open until all
 * file objects have been closed (i.e. the moment HDF5 can close the file).
 *
 * This class is intended to be used through FileInfo only. Do not use directly.
 */
class FileInfoType {
  friend class FileInfo;


  mutable unsigned refCount;

  /*!
   * Name of the opened file without path.
   */
  const std::string filename;

  /*!
   * File descriptor of the directory of the file opened, or -1 if "." or failed to open.
   * Needed to work around an HDF5 issue related to external data sets and the cwd.
   */
  const int fdirfd;

  //! The mode the file was opened with (READWRITE, CREATE, ...).
  const FileInfo::FileMode fileMode;

  //! The name of the version attribute.
  const std::string versionAttrName;


  // The (cached) file version as stored by HDF5 in the attribute named versionAttrName.
  // Not initialized by the constructor, because we don't know for sure if the file is already open.
  VersionType fileVersion;


  FileInfoType();
  FileInfoType(const std::string& filename, const int fdirfd,
               FileInfo::FileMode fileMode, const std::string& versionAttrName);
};


}

#endif

