#include "HDF5FileBase.h"

using namespace std;

namespace DAL {

HDF5FileBase::HDF5FileBase( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  // see docs on H5Fclose for caveats when closing the file while having subgroups open
  // (in normal circumstances, HDF5 will only close the file if all access to it has been
  // completed: any open group identifiers (etc) will remain functioning)
  HDF5NodeSet(""),
  _group(hid_gc(open(filename, mode), H5Fclose, mode == CREATE ? "Could not create file" : "Could not open file")),
  filename(filename),
  fileMode(mode)
{
}

hid_t HDF5FileBase::open( const std::string &filename, enum HDF5FileBase::fileMode mode ) const
{

  switch (mode) {
    case CREATE:
      {
        hid_gc_noref fapl(H5Pcreate(H5P_FILE_ACCESS), H5Pclose, "Could not create file access property list");

        // we will use HDF5 1.8+ features, which must be enabled by raising the
        // minimum HDF5 version required to read this file.
        if (H5Pset_libver_bounds(fapl, H5F_LIBVER_18, H5F_LIBVER_LATEST) < 0)
          return -1;

        return H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, fapl);
      }  

    case READ:  
      return H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

    case READWRITE:  
      return H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

    default:
      return 0;
  }
}

void HDF5FileBase::flush()
{
  H5Fflush(group(), H5F_SCOPE_GLOBAL);
}

}

