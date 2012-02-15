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
std::string get_current_hdf5_header_version() {
  // this code needs to be in a header file, to let
  // the client compiler fill in H5_PACKAGE_VERSION below.

  return std::string(H5_PACKAGE_VERSION);
}

/*
 * Return the version of HDF5 library currently in use.
 */
std::string get_current_hdf5_lib_version();

/*
 * Returns true if the hdf5 versions used to compile
 * the DAL and to compile the client code are the same.
 */
bool check_hdf5_versions() {
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

