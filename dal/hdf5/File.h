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
#ifndef DAL_FILE_H
#define DAL_FILE_H

#include <string>
#include <hdf5.h>
#include "types/versiontype.h"
#include "Group.h"
#include "Attribute.h"

namespace dal {

/*!
 * A File object encapsulates the data and provides the functions to operate on a HDF5 file.
 *
 * Note on reopening files and destructing File objects:
 * Best practise is to destruct all references to a file's contents (groups, datasets, attributes, etc)
 * before destructing or close()ing the File object itself. And not to reopen a file while HDF5 still has it open.
 *
 * HDF5 can only close a file once all references to its contents have been closed. As long as HDF5 references
 * remain open, HDF5 leaves the file open (usually possible). You could reopen the file with the same mode;
 * HDF5 will try to keep both accesses to the file consistent (may fail on distributed file systems).
 * If you want to reopen a read-write file as read-only, drop all references, close() it, then open() it.
 *
 * For more detail, see the HDF5 Reference/API Manual on H5Fopen() and H5Fclose().
 */
class File: public Group {
public:
  /*!
   * Create default File object.
   * This is intended to be able to have a container that contains a File object before the filename is known.
   * Once the filename is known, use open() to initialize further.
   */
  File();

  /*!
   * Try to open or create `filename` with open mode `mode` and treat `versionAttrName` as the version attribute name.
   * For an existing file, the specified version attribute must exist. For a new file, it will be created.
   * The default value skips Node tracking (except Group's GROUPTYPE) and versioning.
   *
   * See the class description for more info on reopening and closing files.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *    >>> del f
   *
   *    # Open (and close) the same file for reading
   *    >>> f = File("example.h5", File.READ)
   *    >>> del f
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  File( const std::string &filename, FileMode mode = READ, const std::string &versionAttrName = "");

  /*!
   * Destruct File object.
   */
  virtual ~File();

  /*!
   * Assign the rhs object to this object and return a reference to this object.
   * If the operation succeeds, the previous state of this object (if any) is destructed.
   * If the operation fails, an exception is thrown.
   */
  File& operator=(File rhs);

  /*!
   * Store the pair of File objects (first, second) into (second, first).
   * Specialization of std::swap(). Always succeeds.
   */
  friend void swap(File& first, File& second);

  /*!
   * Open or create `filename` with open mode `mode` and treat `versionAttrName` as the version attribute name.
   * Upon return, the previously opened file reference (if any) has been closed.
   * If an exception is thrown, the previously opened file reference (if any) is unaltered.
   *
   * See the File(filename, mode, versionAttrName) constructor for more info.
   * See the class description for more info on reopening and closing files.
   */
  void open( const std::string &filename, FileMode mode = READ, const std::string &versionAttrName = "");

  /*!
   * Indicate that this File object will not be used anymore to access the underlying HDF5 file (if any),
   * possibly until a subsequent call to open().
   *
   * See the class description for more info on reopening and closing files.
   */
  virtual void close();

  /*!
   * Commit any changes to disk.
   */
  void flush();

  /*!
   * Returns whether this file exists (i.e. true).
   */
  virtual bool exists() const;

  /*!
   * Returns the version attribute using the `versionAttrName` passed when the file was opened or created.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Set and get the file version
   *    >>> f.version(VersionType(1,2,3))
   *
   *    # version() reports the version
   *    >>> str(f.version().get())
   *    '1.2.3'
   *
   *    # Groups and attributes inherit the Version
   *    >>> g = Group(f, "GROUP")
   *    >>> str(g.version())
   *    '1.2.3'
   *
   *    # Note: changing the version affects
   *    # already existing group objects.
   *    >>> f.version.set(VersionType(4,5,6))
   *    >>> str(f.version().get())
   *    '4.5.6'
   *    >>> str(g.version.get())
   *    '4.5.6'
   *
   *    # Reload other objects to refresh the file info,
   *    # including the newly set version.
   *    >>> g = Group(f, "GROUP")
   *    >>> str(g.version())
   *    '4.5.6'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  Attribute<VersionType> version();

private:
  virtual void open( hid_t parent, const std::string &name );

  hid_gc openFile( const std::string &filename, FileMode mode ) const;
  void initFileNodes();
};

}

#endif

