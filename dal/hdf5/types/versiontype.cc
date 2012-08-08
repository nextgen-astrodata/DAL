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
#include "versiontype.h"
#include <sstream>
#include <string>

namespace DAL {

// stupid GNU
#ifdef major
#undef major
#endif

// stupid GNU
#ifdef minor
#undef minor
#endif

VersionType::VersionType(unsigned major, unsigned minor, unsigned release)
:
  major(major),
  minor(minor),
  release(release)
{
}

VersionType::VersionType(const std::string &str)
:
  major(0),
  minor(0),
  release(0)
{
  std::istringstream iss(str, std::istringstream::in);
  char dot = '\0';

  iss >> major;
  iss >> dot;

  if (dot != '.' || !iss.good())
    return;

  iss >> minor;
  iss >> dot;

  if (dot != '.' || !iss.good())
    return;

  iss >> release;
}

std::string VersionType::toString() const {
  std::ostringstream oss(std::ostringstream::out);

  oss << major << "." << minor << "." << release;

  return oss.str();
}

int VersionType::cmp(const VersionType &other) const {
  if( major < other.major )
    return -1;

  if( major > other.major )
    return +1;

  if( minor < other.minor )
    return -1;

  if( minor > other.minor )
    return +1;

  if( release < other.release )
    return -1;

  if( release > other.release )
    return +1;

  return 0;  
}

bool VersionType::operator <(const VersionType &other) const {
  return cmp(other) < 0;
}

bool VersionType::operator <=(const VersionType &other) const {
  return cmp(other) <= 0;
}

bool VersionType::operator >(const VersionType &other) const {
  return cmp(other) > 0;
}

bool VersionType::operator >=(const VersionType &other) const {
  return cmp(other) >= 0;
}

bool VersionType::operator ==(const VersionType &other) const {
  return cmp(other) == 0;
}

bool VersionType::operator !=(const VersionType &other) const {
  return cmp(other) != 0;
}

}
