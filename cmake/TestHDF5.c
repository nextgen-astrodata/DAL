#include <hdf5.h>

int main( int argc, char *argv[] ) {
  (void)argc;
  (void)argv;

  unsigned maj, min, rel;

  if (H5get_libversion(&maj, &min, &rel) < 0)
    // could not obtain version info from library
    return 2;

  printf("HDF5 header  version: %u.%u.%u\n", H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE);
  printf("HDF5 library version: %u.%u.%u\n", maj, min, rel);

  if (maj != H5_VERS_MAJOR || min != H5_VERS_MINOR || rel != H5_VERS_RELEASE)
    // library is a different version than headers -- HDF5 code will refuse to run
    return 1;

  // hdf5.h and libhdf5.so versions match
  return 0;  
}

