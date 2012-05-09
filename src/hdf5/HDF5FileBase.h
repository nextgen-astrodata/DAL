#ifndef __HDF5FILE__
#define __HDF5FILE__

#include <string>
#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/HDF5GroupBase.h"
#include "hdf5/HDF5Attribute.h"

namespace DAL {

class HDF5FileBase: public HDF5GroupBase {
public:
  enum fileMode { READ = 1, READWRITE = 2, CREATE = 3 };

  /*!
   * Open or create an HDF5 file called `filename`.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *    >>> del f
   *
   *    # Open (and close) the same file for reading
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.READ)
   *    >>> del f
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  HDF5FileBase( const std::string &filename, enum fileMode mode, const std::string versionAttrName = "VERSION" );

  /*!
   * Commit any changes to disk.
   */
  void flush();

  virtual bool exists() const { return true; }

  /*!
   * The name of the file.
   */
  const std::string filename;

  /*!
   * The mode in which the file is opened.
   */
  const fileMode mode;

  /*!
   * The name of the attribute containing the file version.
   */
  const std::string versionAttrName;

  /*!
   * Stores the given version in the HDF5 file.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
   *
   *    # Set and get the file version
   *    >>> f.setFileVersion(VersionType(1,2,3))
   *
   *    # fileVersion() reports the version
   *    >>> str(f.fileVersion())
   *    '1.2.3'
   *
   *    # Groups and attributes inherit the Version
   *    >>> g = HDF5GroupBase(f, "GROUP")
   *    >>> str(g.fileVersion())
   *    '1.2.3'
   *
   *    # Note: changing the version does not affect
   *    # already existing group objects.
   *    >>> f.setFileVersion(VersionType(4,5,6))
   *    >>> str(f.fileVersion())
   *    '4.5.6'
   *    >>> str(g.fileVersion())
   *    '1.2.3'
   *
   *    # Reload other objects to refresh the file info,
   *    # including the newly set version.
   *    >>> g = HDF5GroupBase(f, "GROUP")
   *    >>> str(g.fileVersion())
   *    '4.5.6'
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  void setFileVersion( const VersionType &version );

protected:
  /*!
   * Return the version as stored in the HDF5 file.
   * A default value is returned if the attribute does not exist.
   */
  VersionType getStoredFileVersion();

private:
  hid_gc open( const std::string &filename, enum fileMode mode ) const;
};

}

#endif

