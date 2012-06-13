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
   * VersionType("2.1").toString() == "2.1.0"
   */
  VersionType(const std::string &str);

  /*!
   * Returns this version in string form (major.minor.release)
   */
  std::string toString() const;

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
