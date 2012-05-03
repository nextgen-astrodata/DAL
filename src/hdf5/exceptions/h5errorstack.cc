#include "dal_config.h"
#include "dal_version.h"
#include "h5errorstack.h"

namespace DAL {

class GlobalDisableErrorPrinting {
public:
  GlobalDisableErrorPrinting(): dep(quietErrors() ? new DisableErrorPrinting : NULL) {}
  ~GlobalDisableErrorPrinting() { delete dep; }
private:
  bool quietErrors() const;

  const DisableErrorPrinting *dep;

};

static GlobalDisableErrorPrinting gdep;

bool GlobalDisableErrorPrinting::quietErrors() const {
#ifndef QUIET_HDF5_ERRORS
  return false;
#endif

  // Don't cause us to abort already
  if (!check_hdf5_versions())
    return false;

  return true;  
}

}

