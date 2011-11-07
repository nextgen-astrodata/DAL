#ifndef __HDF5FILE__
#define __HDF5FILE__

#include <string>
#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/HDF5Node.h"
#include "hdf5/HDF5Attribute.h"

namespace LDA {

class HDF5FileBase: public HDF5NodeSet {
public:
  enum fileMode { READ = 1, READWRITE = 2, CREATE = 3 };

  /*!
   * Open or create an HDF5 file called `filename`.
   */
  HDF5FileBase( const std::string &filename, enum fileMode mode );

  /*!
   * Commit any changes to disk.
   */
  void flush();

  virtual const hid_gc &group() { return _group; }

protected:
  const hid_gc _group;
  const std::string filename;
  const fileMode fileMode;

private:
  hid_t open( const std::string &filename, enum fileMode mode ) const;
};

}

#endif

