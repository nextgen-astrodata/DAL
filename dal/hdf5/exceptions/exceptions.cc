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
#include "exceptions.h"
#include <sstream>

using namespace std;

namespace DAL {

HDF5Exception::HDF5Exception(const std::string &msg, const HDF5ErrorStack &stack)
:
  DALException(msg),
  stack(stack)
{
}

HDF5Exception::~HDF5Exception() throw() {
}

std::string HDF5Exception::stackSummary() const {
  const vector<struct HDF5StackLine> errorstack = stack.stack();

  if (errorstack.empty())
    return "";

  ostringstream oss(ostringstream::out);

  const size_t n = errorstack.size();

  // include a summary of the first and the last stack line

  oss << errorstack[0].shortDesc();

  if (n > 1)
    oss << " (" << errorstack[n - 1].desc << ")";

  return oss.str();
}

}
