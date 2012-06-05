/*
 * Print HDF5 version info and set the exit status accordingly.
 * Scenarios:
 *
 *   exit code 0: library and header versions match. A single version number is printed on stdout.
 *   exit code 1: library and header versions do not match. Both version numbers are printed on stdout.
 *   exit code 2: could not retrieve library version number. Nothing is printed on stdout.
 */

#include <hdf5.h>

int main( int argc, char *argv[] ) {
  (void)argc;
  (void)argv;

  unsigned maj, min, rel;

  if (H5get_libversion(&maj, &min, &rel) < 0)
    // could not obtain version info from library
    return 2;

  if (maj != H5_VERS_MAJOR || min != H5_VERS_MINOR || rel != H5_VERS_RELEASE) {
    printf("header: %u.%u.%u library: %u.%u.%u",
      H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE,
      maj, min, rel);

    // library is a different version than headers -- HDF5 code will refuse to run
    return 1;
  }

  printf("%u.%u.%u", maj, min, rel);

  // hdf5.h and libhdf5.so versions match
  return 0;  
}

