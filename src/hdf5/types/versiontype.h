#ifndef __VERSIONTYPE__
#define __VERSIONTYPE__

#include <sstream>
#include <string>

namespace DAL {

class VersionType {
public:
  unsigned major;
  unsigned minor;
  unsigned release;

  VersionType(unsigned major = 0, unsigned minor = 0, unsigned release = 0): major(major), minor(minor), release(release) {}

  VersionType(const std::string &str): major(0), minor(0), release(0) {
    std::istringstream iss(std::istringstream::in);

    oss >> major >> "." >> minor >> "." >> release;
  }

  std::string toString() const {
    std::ostringstream oss(std::ostringstream::out);

    oss << major << "." << minor << "." << release;

    return oss.str();
  }

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

#endif
