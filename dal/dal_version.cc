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
#include <cstdio>
#include <hdf5.h>

namespace DAL {

using namespace std;

string get_lib_version() {
  return DAL_VERSION;
}

string get_dal_hdf5_version() {
  return get_current_hdf5_header_version();
}

string get_current_hdf5_lib_version() {
  char buf[128];
  unsigned maj, min, rel;

  H5get_libversion(&maj, &min, &rel);

  snprintf(buf, sizeof buf, "%u.%u.%u", maj, min, rel);

  return string(buf);
}

}

