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
#include "File.h"
#include "Attribute.h"

using namespace std;

namespace dal {

File::File() {}

File::File( const std::string &filename, FileMode mode, const std::string &versionAttrName )
:
  // Store the file hid as the group hid.
  Group(openFile(filename, mode), FileInfo(filename, mode, versionAttrName))
{
  if (!versionAttrName.empty()) {
    // To make specialized VersionType [gs]et() functions usable, access HDF5 version string attribute around it.
    // Not passed in initializer, because eval order of openFile(), FileInfo() is unspecified.
    Attribute<string> h5StoredVersionAttr(*this, versionAttrName);

    if (mode == CREATE || mode == CREATE_EXCL) {
      // In-memory version already default initialized.
      string defaultVersion(VersionType().to_string());
      h5StoredVersionAttr.create().set(defaultVersion);
    } else {
      // Try to set in-memory version from HDF5 attribute.
      setFileInfoVersion(h5StoredVersionAttr.get());
    }

    initFileNodes();
  }
}

File::~File() {}

File& File::operator=(File rhs)
{
  swap(*this, rhs);
  return *this;
}

void swap(File& first, File& second)
{
  swap(static_cast<Group&>(first), static_cast<Group&>(second));
}

void File::open( const std::string &filename, FileMode mode, const std::string &versionAttrName )
{
  File ftmp(filename, mode, versionAttrName);
  swap(*this, ftmp);
}

void File::close()
{
  File ftmp;
  swap(*this, ftmp);
}

hid_gc File::openFile( const std::string &filename, FileMode mode ) const
{
  switch (mode) {
    case CREATE:
    case CREATE_EXCL:
      {
        hid_gc_noref fapl(H5Pcreate(H5P_FILE_ACCESS), H5Pclose, "Could not create file access property list to create file " + filename);

        /* We use the latest version to create the file, for maximum efficiency. HDF5 offers very little
           choice here. */
        if (H5Pset_libver_bounds(fapl, H5F_LIBVER_LATEST, H5F_LIBVER_LATEST) < 0)
          throw DALException("Could not set HDF5 version bounds to create forward compatible file");

        unsigned flags;
        if (mode == CREATE)
          flags = H5F_ACC_TRUNC;
        else // mode == CREATE_EXCL
          flags = H5F_ACC_EXCL;

        return hid_gc(H5Fcreate(filename.c_str(), flags, H5P_DEFAULT, fapl), H5Fclose, "Could not create file " + filename);
      }  

    case READ:  
      return hid_gc(H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT), H5Fclose, "Could not open file for read-only access; file " + filename);

    case READWRITE:  
      return hid_gc(H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT), H5Fclose, "Could not open file for read-write access; file " + filename);

    default:
      throw DALValueError("Could not open file: unknown mode argument");
  }
}

void File::flush()
{
  H5Fflush(group(), H5F_SCOPE_GLOBAL);
}

bool File::exists() const
{
  return true;
}

Attribute<VersionType> File::version()
{
  return getNode(versionAttrName());
}

void File::initFileNodes()
{
  addNode( new Attribute<VersionType>(*this, versionAttrName()) );
}

void File::open( hid_t parent, const std::string &name )
{
  (void)parent;
  (void)name;

  throw DALException("File does not support lazy open");
}


}

