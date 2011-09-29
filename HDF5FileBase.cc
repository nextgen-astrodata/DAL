#include "HDF5FileBase.h"

using namespace std;

namespace LDA {

HDF5FileBase::HDF5FileBase( const string &filename, enum HDF5FileBase::fileMode mode )
:
  // see docs on H5Fclose for caveats when closing the file while having subgroups open
  // (in normal circumstances, HDF5 will only close the file if all access to it has been
  // completed: any open group identifiers (etc) will remain functioning)
  HDF5Node(""),
  _group(hid_gc(open(filename, mode), H5Fclose, mode == CREATE ? "Could not create file" : "Could not open file")),
  filename(filename),
  fileMode(mode)
{
}

hid_t HDF5FileBase::open( const string &filename, enum HDF5FileBase::fileMode mode ) const
{
  switch (mode) {
    case CREATE:
      return H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    case READ:  
      return H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    case READWRITE:  
      return H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

    default:
      return 0;
  }
}

void HDF5FileBase::flush() const
{
  H5Fflush(group(), H5F_SCOPE_GLOBAL);
}

}
