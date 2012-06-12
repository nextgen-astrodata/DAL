#include "File.h"

using namespace std;

namespace DAL {

File::File( const std::string &filename, enum File::fileMode mode, const std::string &versionAttrName )
:
  // see docs on H5Fclose for caveats when closing the file while having subgroups open
  // (in normal circumstances, HDF5 will only close the file if all access to it has been
  // completed: any open group identifiers (etc) will remain functioning)
  Group(open(filename, mode)),
  filename(filename),
  mode(mode),
  versionAttrName(versionAttrName)
{
  // Fill the data that will be propagated to other Nodes
  data.fileVersion = getStoredFileVersion();

  switch (mode) {
    case CREATE:
    case READWRITE:
      data.canWrite = true;
      break;

    case READ:
    default:
      data.canWrite = false;
  }

  data.fileName = filename;
  data.parentNodePath = "";
}

hid_gc File::open( const std::string &filename, enum File::fileMode mode ) const
{

  switch (mode) {
    case CREATE:
      {
        hid_gc_noref fapl(H5Pcreate(H5P_FILE_ACCESS), H5Pclose, "Could not create file access property list");

        /*
         * We want to use 1.8 features, but always be able to read back any created file.
         * We can force min and max versions, but apart from H5F_LIBVER_EARLIEST and H5F_LIBVER_LATEST,
         * there is only H5F_LIBVER_18 introduced in 1.8.6+, but not in 1.9(.108) (pre-1.10).
         * For now, set H5F_LIBVER_LATEST on all 1.8 and 1.9, and guess we may benefit from LIBVER_18 at 1.10+.
         */
#if H5_VERS_MAJOR == 1 && H5_VERS_MINOR <= 9
        if (H5Pset_libver_bounds(fapl, H5F_LIBVER_LATEST, H5F_LIBVER_LATEST) < 0)
#else // >= 1.10
        if (H5Pset_libver_bounds(fapl, H5F_LIBVER_18, H5F_LIBVER_18) < 0)
#endif
          return -1;

        return hid_gc(H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, fapl), H5Fclose, "Could not create file");
      }  

    case READ:  
      return hid_gc(H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT), H5Fclose, "Could not open file for read-only access");

    case READWRITE:  
      return hid_gc(H5Fopen(filename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT), H5Fclose, "Could not open file for read-write access");

    default:
      return 0;
  }
}

void File::flush()
{
  H5Fflush(group(), H5F_SCOPE_LOCAL);
}

VersionType File::getStoredFileVersion()
{
  Attribute<string> versionAttr(*this, versionAttrName);
  if (!versionAttr.exists())
    return VersionType();

  return VersionType(versionAttr.get());  
}

void File::setFileVersion( const VersionType &version )
{
  Attribute<string> versionAttr(*this, versionAttrName);
  if (versionAttr.exists())
    versionAttr.set(version.toString());

  // update propagation data as well
  data.fileVersion = version;
}

}

