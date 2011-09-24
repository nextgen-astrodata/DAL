#include "HDF5File.h"

using namespace std;

HDF5File::HDF5File( const string &filename, enum HDF5File::fileMode mode )
:
  // see docs on H5Fclose for caveats when closing the file while having subgroups open
  // (in normal circumstances, HDF5 will only close the file if all access to it has been
  // completed: any open group identifiers (etc) will remain functioning)
  HDF5Group(""),
  _group(hid_gc(open(filename, mode), H5Fclose, mode == CREATE ? "Could not create HDF5 file" : "Could not open HDF5 file")),
  filename(filename),
  fileMode(mode)
{
}

hid_t HDF5File::open( const string &filename, enum HDF5File::fileMode mode ) const
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

void HDF5File::flush() const
{
  H5Fflush(group(), H5F_SCOPE_GLOBAL);
}

Attribute<string> HDF5File::groupType() const
{
  return Attribute<string>(group(), "GROUPTYPE");
}

Attribute<string> HDF5File::fileName() const
{
  return Attribute<string>(group(), "FILENAME");
}

Attribute<string> HDF5File::fileDate() const
{
  return Attribute<string>(group(), "FILEDATE");
}

Attribute<string> HDF5File::fileType() const
{
  return Attribute<string>(group(), "FILETYPE");
}
