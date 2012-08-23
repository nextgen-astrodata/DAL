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
#ifndef DAL_VERSIONTYPE_H
#define DAL_VERSIONTYPE_H

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

/*!
 * Encodes a version such as 1.2.3.
 *
 * Python example:
 * \code
 *    # Initialisation through (major, minor, release) values
 *    >>> v = VersionType(1,2,3)
 *    >>> str(v)
 *    '1.2.3'
 *
 *    # Initialisation through a version string
 *    >>> v = VersionType('1.2.3')
 *    >>> str(v)
 *    '1.2.3'
 *
 *    # Retrieve individual fields
 *    >>> v = VersionType('1.2.3')
 *    >>> v.major
 *    1
 *    >>> v.minor
 *    2
 *    >>> v.release
 *    3
 *
 *    # Compare versions
 *    >>> old = VersionType('1.2.3')
 *    >>> new = VersionType('3.2.1')
 *    >>> old < new
 *    True
 *    >>> old > new
 *    False
 *    >>> old == new
 *    False
 * \endcode
 */
struct VersionType {
  unsigned major;
  unsigned minor;
  unsigned release;

  VersionType(unsigned major = 0, unsigned minor = 0, unsigned release = 0);

  /*!
   * Convert a string of format major.minor.release. Any fields that could
   * not be converted are set to 0. For example:
   *
   * VersionType("2.1").to_string() == "2.1.0"
   */
  VersionType(const std::string &str);

  /*!
   * Returns this version in string form (major.minor.release)
   */
  std::string to_string() const;

  /*!
   * Compares *this with other. Returns:
   *   -1 if *this <  other
   *    0 if *this == other
   *   +1 if *this >  other
   */
  int cmp(const VersionType &other) const;

  bool operator <(const VersionType &other) const;
  bool operator <=(const VersionType &other) const;
  bool operator >(const VersionType &other) const;
  bool operator >=(const VersionType &other) const;
  bool operator ==(const VersionType &other) const;
  bool operator !=(const VersionType &other) const;
};

}

#endif
