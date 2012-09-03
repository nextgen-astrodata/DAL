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
#include "Flagging.h"

#include <sstream>

using namespace std;

namespace dal {

Range::Range() : begin(0), end(0) {}

Range::Range(unsigned long long begin, unsigned long long end) : begin(begin), end(end) {}

string Range::to_string() {
  ostringstream oss;

  oss << '[' << this->begin << ',' << this->end << ')';

  return oss.str();
}

}

