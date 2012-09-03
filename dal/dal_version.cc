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
#include "dal/dal_config.h"
#include "dal/dal_version.h"
#include <hdf5.h>

namespace dal {

using namespace std;

VersionType version() {
  return VersionType(DAL_VERSION_MAJOR, DAL_VERSION_MINOR, DAL_VERSION_RELEASE);
}

VersionType version_first_release() {
  /*
   * The first DAL 2.x release version was 2.5.0, because the 
   * bf draft spec was 2.04.xx at the time (tbb was at 2.02.xx).
   */
  return VersionType(2, 5, 0);
}

VersionType version_hdf5_headers_dal() {
  // return the 'current' hdf5 header version
  return version_hdf5_headers_current();
}

VersionType version_hdf5() {
  unsigned maj, min, rel;

  H5get_libversion(&maj, &min, &rel);

  return VersionType(maj, min, rel);
}

}

