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
#ifndef DAL_DAL_VERSION_H
#define DAL_DAL_VERSION_H

#include <string>
#include <cstdio>
#include <hdf5.h>

namespace dal {

/*!
 * Return the version of this DAL library.
 */
std::string get_lib_version();

/*!
 * Return the version of the first release of this DAL library (DAL 2).
 */
std::string get_first_release_lib_version();

/*!
 * Return the version of HDF5 headers used to compile the DAL
 */
std::string get_dal_hdf5_version();

/*!
 * Return the version of HDF5 headers currently in use.
 */
static std::string get_current_hdf5_header_version() {
  // this code needs to be in a header file, to let
  // the client compiler fill in H5_VERS_* below.
  //
  // Note: we do not use H5_PACKAGE_VERSION as that might
  // include sub-release information that messes up our
  // version check systems (i.e. "1.8.4-patch1").

#define LOFARDAL_QUOTE_(x) #x
#define LOFARDAL_QUOTE(x) LOFARDAL_QUOTE_(x)

  return std::string(LOFARDAL_QUOTE(H5_VERS_MAJOR) "." LOFARDAL_QUOTE(H5_VERS_MINOR) "." LOFARDAL_QUOTE(H5_VERS_RELEASE));

#undef LOFARDAL_QUOTE
#undef LOFARDAL_QUOTE_

}

/*!
 * Return the version of HDF5 library currently in use.
 */
std::string get_current_hdf5_lib_version();

/*!
 * Returns true if the hdf5 versions used to compile
 * the DAL and to compile the client code are the same.
 */
static bool check_hdf5_versions() {
  // this code needs to be in a header file, to let
  // the client compiler fill in H5_PACKAGE_VERSION.

  // client HDF5 header should be the same version as used by DAL
  if (get_current_hdf5_header_version() != get_dal_hdf5_version())
    return false;

  // client HDF5 library should be the same version as used by DAL
  if (get_current_hdf5_lib_version() != get_dal_hdf5_version())
    return false;

  // all HDF5 versions used are the same
  return true;  
}

}

#endif

