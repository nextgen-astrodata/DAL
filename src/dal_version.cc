#include "dal_config.h"
#include "dal_version.h"
#include <cstdio>
#include <hdf5.h>

namespace DAL {

using namespace std;

string get_lib_version() {
  return DAL_VERSION;
}

string get_dal_hdf5_version() {
  return H5_PACKAGE_VERSION;
}

string get_current_hdf5_lib_version() {
  char buf[128];
  unsigned maj, min, rel;

  H5get_libversion(&maj, &min, &rel);

  snprintf(buf, sizeof buf, "%u.%u.%u", maj, min, rel);

  return string(buf);
}

}

