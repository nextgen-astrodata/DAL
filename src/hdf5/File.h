#ifndef __HDF5_FILE_BASE__
#define __HDF5_FILE_BASE__

#include <string>
#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/Group.h"
#include "hdf5/Attribute.h"

namespace DAL {

class File: public Group {
public:
  enum fileMode { READ = 1, READWRITE = 2, CREATE = 3 };

  /*!
   * Open or create an HDF5 file called `filename`.
   *
   * Python example:
   * \code
   *    # Create and close a new HDF5 file called "example.h5"
   *    >>> f = File("example.h5", File.CREATE)
   *    >>> del f
   *
   *    # Open (and close) the same file for reading
   *    >>> f = File("example.h5", File.READ)
   *    >>> del f
   *
   *    # Clean up
   *    >>> import os
   *    >>> os.remove("example.h5")
   * \endcode
   */
  File( const std::string &filename, enum fileMode mode, const std::string versionAttrName = "VERSION" );

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
   *    >>> f = File("example.h5", File.CREATE)
   *
   *    # Set and get the file version
   *    >>> f.setFileVersion(VersionType(1,2,3))
   *
   *    # fileVersion() reports the version
   *    >>> str(f.fileVersion())
   *    '1.2.3'
   *
   *    # Groups and attributes inherit the Version
   *    >>> g = Group(f, "GROUP")
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
   *    >>> g = Group(f, "GROUP")
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

