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
#ifndef DAL_NODE_H
#define DAL_NODE_H

#include <string>
#include <vector>
#include <typeinfo>
#include "types/hid_gc.h"
#include "types/FileInfo.h"
#include "types/versiontype.h"

namespace DAL {

class Group;

/*!
 * Represents a node in the HDF5 hierarchy (an attribute, group, or dataset).
 */
class Node {
public:
  /*!
   * File open/create mode.
   * If the filename already exists, CREATE will truncate it, while CREATE_EXCL will throw.
   * None means not opened. It is used internally; not for DAL users.
   *
   * For why this needs to be here, see the FileInfo class description.
   */
  typedef /*FileInfo::FileMode*/int FileMode; // TODO: have SWIG declare FileInfo::FileMode constants, also as Node members
  // Not an enum, because enums cannot be forward declared (until C++11) and
  // we (only) need all values here. The enum here instead would give a circular dep with FileInfo.
  //static const FileMode NONE        = 0; // value used in FileInfoType only
  static const FileMode READ        = 1;
  static const FileMode READWRITE   = 2;
  static const FileMode CREATE      = 3;
  static const FileMode CREATE_EXCL = 4;


  Node();

  Node( Group &parent, const std::string &name );

  virtual ~Node();

  Node& operator=(Node rhs);

  friend void swap(Node& first, Node& second);

  /*!
   * Returns the HDF5 name of this node.
   */
  std::string name() const { return _name; }

  /*!
   * Returns whether this Node exists in the HDF5 file.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # An open file always exists
   *    >>> f.exists()
   *    True
   *
   *    # Reference an attribute in the file
   *    >>> a = AttributeString(f, "EXAMPLE_ATTRIBUTE")
   *
   *    # Initially, the attribute does not exist
   *    >>> a.exists()
   *    False
   *
   *    # If we create it, it does exist
   *    >>> a.create()
   *    <...>
   *    >>> a.exists()
   *    True
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  virtual bool exists() const { return false; }

  /*!
   * Returns whether this node is supported by the current version.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Set the file's version number to 2.6.0.
   *    # Pass three integers or pass a string.
   *    >>> f.fileVersion(VersionType("2.6.0"))
   *
   *    # Create some attribute to play with
   *    >>> a = AttributeString(f, "EXAMPLE_ATTR")
   *    >>> a.value = "hello world"
   *
   *    # Request the file version (any node in the file will do)
   *    >>> f.fileVersion()
   *    VersionType('2.6.0')
   *    >>> a.fileVersion()
   *    VersionType('2.6.0')
   *
   *    # If an attribute is older than the file,
   *    # it is supported and should be present.
   *    >>> a.minVersion = VersionType('2.5.0')
   *    >>> a.supported()
   *    True
   *
   *    # If an attribute is newer than the file,
   *    # it is possibly not present and therefor
   *    # not supported.
   *    >>> a.minVersion = VersionType('2.7.0')
   *    >>> a.supported()
   *    False
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  bool supported() { return minVersion <= fileInfoVersion(); }

/*
  std::string className() const { return typeid(*this).name(); }
*/

  /*!
   * The name of the file as it was opened.
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Query the file name
   *    >>> f.fileName()
   *    'example.h5'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  const std::string& fileName() const;

  //! Returns the mode the file was opened with.
  FileMode fileMode() const;

  /*!
   * Whether the file was opened for writing. Derived from fileMode().
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *    >>> f.canWrite()
   *    True
   *
   *    # Can also query other nodes
   *    >>> a = AttributeString(f, "EXAMPLE_ATTR")
   *    >>> a.canWrite()
   *    True
   *
   *    # Reopen the same file read-only
   *    >>> del a
   *    >>> del f
   *    >>> f = File("example.h5", File.READ)
   *    >>> f.canWrite()
   *    False
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  bool canWrite() const;

  //! Returns name of the version attribute.
  const std::string& versionAttrName() const;

protected:
  hid_gc parent;
  std::string _name;

  /*!
   * The minimal version required for this node to be supported. Version numbers
   * are user-defined, and matched against a fixed field in the HDF5 file
   * (see fileVersion()).
   *
   * Python example:
   * \code
   *    # Create a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *    >>> a = AttributeString(f, "EXAMPLE_ATTRIBUTE")
   *
   *    # The minimal required version of any node is 0.0.0 by default
   *    >>> a.minVersion
   *    VersionType('0.0.0')
   *
   *    # Setting the minimal version.
   *    >>> a.minVersion = VersionType('1.2.3')
   *
   *    # Requesting the minimal version.
   *    >>> str(a.minVersion)
   *    '1.2.3'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  VersionType minVersion; // TODO: move this elsewhere?

  FileInfo fileInfo; // proxy/reference object to reference-counted structure

  //! Constructor for Node of root group (in File) only
  Node( const hid_gc &parent, const std::string &name, FileInfo fileInfo);

  /*!
   * The file descriptor of the name of the dir in the file as it was opened,
   * or -1 if "." or failed to open. Needed for a HDF5 issue workaround.
   */
  int fileDirfd() const;

  /*!
   * Returns the in-memory stored file version.
   */
  VersionType& fileInfoVersion() const; // keep protected to avoid escaped dangling ref in applications

  /*!
   * Set the in-memory stored file version. HDF5 file remains unchanged.
   * Use only after changing the version attribute in the HDF5 file (or for init).
   */
  void setFileInfoVersion(const VersionType& newVersion);
};

}

#endif

