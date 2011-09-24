#ifndef __HDF5FILE__
#define __HDF5FILE__

#include <string>
#include <hdf5.h>
#include "HDF5Node.h"
#include "hdf5core/h5element.h"
#include "hdf5core/hid_gc.h"

class HDF5File: public HDF5Node {
public:
  enum fileMode { READ = 1, READWRITE = 2, CREATE = 3 };

  void flush() const;

  Attribute<std::string> groupType() const;
  Attribute<std::string> fileName() const;
  Attribute<std::string> fileDate() const;
  Attribute<std::string> fileType() const;

protected:
  HDF5File( const std::string &filename, enum fileMode mode );

  const hid_gc _group;
  const std::string filename;
  const fileMode fileMode;

  const hid_gc &group() const { return _group; }

private:
  hid_t open( const std::string &filename, enum fileMode mode ) const;
};

#endif

