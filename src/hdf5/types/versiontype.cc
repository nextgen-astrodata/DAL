#include "hdf5/types/versiontype.h"
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
