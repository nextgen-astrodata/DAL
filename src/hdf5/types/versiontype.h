#ifndef __VERSIONTYPE__
#define __VERSIONTYPE__

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

class VersionType {
public:
  unsigned major;
  unsigned minor;
  unsigned release;

  VersionType(unsigned major = 0, unsigned minor = 0, unsigned release = 0): major(major), minor(minor), release(release) {}

  VersionType(const std::string &str): major(0), minor(0), release(0) {
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

  std::string toString() const {
    std::ostringstream oss(std::ostringstream::out);

    oss << major << "." << minor << "." << release;

    return oss.str();
  }

  /*!
   * Compares *this with other. Returns:
   *   -1 if *this <  other
   *    0 if *this == other
   *   +1 if *this >  other
   */
  int cmp(const VersionType &other) const {
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

  bool operator <(const VersionType &other) const {
    return cmp(other) < 0;
  }

  bool operator <=(const VersionType &other) const {
    return cmp(other) <= 0;
  }

  bool operator >(const VersionType &other) const {
    return cmp(other) > 0;
  }

  bool operator >=(const VersionType &other) const {
    return cmp(other) >= 0;
  }

  bool operator ==(const VersionType &other) const {
    return cmp(other) == 0;
  }

  bool operator !=(const VersionType &other) const {
    return cmp(other) != 0;
  }
};

}

#endif
