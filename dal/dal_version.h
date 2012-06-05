#ifndef __DALVERSION__
#define __DALVERSION__

#include <string>
#include <cstdio>
#include <hdf5.h>

namespace DAL {

/*
 * Return the version of this DAL library.
 */
std::string get_lib_version();

/*
 * Return the version of HDF5 headers used to compile the DAL
 */
std::string get_dal_hdf5_version();

/*
 * Return the version of HDF5 headers currently in use.
 */
static std::string get_current_hdf5_header_version() {
  // this code needs to be in a header file, to let
  // the client compiler fill in H5_VERS_* below.
  //
  // Note: we do not use H5_PACKAGE_VERSION as that might
  // include sub-release information that messes up our
  // version check systems (i.e. "1.8.4-patch1").

#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)

  return std::string(QUOTE(H5_VERS_MAJOR) "." QUOTE(H5_VERS_MINOR) "." QUOTE(H5_VERS_RELEASE));

#undef QUOTE
#undef _QUOTE

}

/*
 * Return the version of HDF5 library currently in use.
 */
std::string get_current_hdf5_lib_version();

/*
 * Returns true if the hdf5 versions used to compile
 * the DAL and to compile the client code are the same.
 */
static bool check_hdf5_versions() {
  // this code needs to be in a header file, to let
  // the client compiler fill in H5_PACKAGE_VERSION.

  // client HDF5 header should be the same version as used by DAL
  if (get_current_hdf5_header_version() != get_dal_hdf5_version())
    return false;

  // client HDF5 library should be the same version as used by DAL
  if (get_current_hdf5_lib_version() != get_dal_hdf5_version())
    return false;

  // all HDF5 versions used are the same
  return true;  
}

}

#endif

