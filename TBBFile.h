#ifndef __TBBFILE__
#define __TBBFILE__

#include <string>
#include <hdf5.h>
#include "HDF5Attribute.h"
#include "CommonAttributesFile.h"
#include "HDF5GroupBase.h"
#include "HDF5DatasetBase.h"

namespace LDA {

class TBBFile;
class TBB_SysLog;
class TBB_Station;
class TBB_Trigger;
class TBB_UnknownTrigger;
class TBB_VHECRTrigger;
class TBB_Dipole;

/*!
 * Interface for TBB Time-Series Data as described in ICD001.
 */
class TBBFile: public CommonAttributesFile {
public:
  /*!
   * Open `filename` for reading/writing/creation.
   */
  TBBFile( const std::string &filename, enum fileMode mode = READ );

  TBB_SysLog             sysLog();
  TBB_Station            station( unsigned nr );

  Attribute<std::string> triggerType();
  TBB_Trigger            triggerData();
};

class TBB_SysLog: public HDF5GroupBase {
protected:
  TBB_SysLog( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class TBBFile;
};

class TBB_Station: public HDF5GroupBase {
public:
  Attribute<std::string>                stationName();

  Attribute< std::vector<double> >      stationPositionValue();
  Attribute< std::vector<std::string> > stationPositionUnit();
  Attribute<std::string>                stationPositionFrame();

  Attribute< std::vector<double> >      beamDirectionValue();
  Attribute< std::vector<std::string> > beamDirectionUnit();
  Attribute<std::string>                beamDirectionFrame();

  Attribute<double>                     clockOffsetValue();
  Attribute<std::string>                clockOffsetUnit();

  Attribute<double>                     triggerOffset();

  Attribute<unsigned>                   nofDipoles();

  TBB_Dipole                            dipole( unsigned station, unsigned rsp, unsigned rcu );

protected:
  TBB_Station( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class TBBFile;
};

class TBB_Dipole: public HDF5DatasetBase<short> {
protected:
  TBB_Dipole( const hid_gc &parent, const std::string &name ): HDF5DatasetBase<short>(parent, name) {}

  friend class TBB_Station;
};

class TBB_Trigger: public HDF5GroupBase {
protected:
  TBB_Trigger( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class TBBFile;
};

class TBB_UnknownTrigger: public TBB_Trigger {
public:
  Attribute<std::string> metadata();

protected:
  TBB_UnknownTrigger( const hid_gc &parent, const std::string &name ): TBB_Trigger(parent, name) {}

  friend class TBBFile;
};

class TBB_VHECRTrigger: public TBB_Trigger {
public:
  Attribute<std::string> triggerSource();

  Attribute<unsigned>    triggerTime();
  Attribute<unsigned>    triggerSampleNumber();

  Attribute<unsigned>    paramCoincidenceChannels();
  Attribute<double>      paramCoincidenceTime();

  Attribute<std::string> paramDirectionFit();
  Attribute<double>      paramElevationMin();
  Attribute<double>      paramFitVarianceMax();

  Attribute<unsigned>    coincidenceChannels();

  Attribute< std::vector<unsigned> > rcuID();
  Attribute< std::vector<unsigned> > time();
  Attribute< std::vector<unsigned> > sampleNumber();

  Attribute< std::vector<unsigned> > pulseSum();
  Attribute< std::vector<unsigned> > pulseWidth();
  Attribute< std::vector<unsigned> > pulsePeak();
  Attribute< std::vector<unsigned> > pulsePowerPre();
  Attribute< std::vector<unsigned> > pulsePowerPost();

  Attribute< std::vector<unsigned> > nofMissedTriggers();

  Attribute<double>      fitDirectionAzimuth();
  Attribute<double>      fitDirectionElevation();
  Attribute<double>      fitDirectionDistance();
  Attribute<double>      fitDirectionVariance();

protected:
  TBB_VHECRTrigger( const hid_gc &parent, const std::string &name ): TBB_Trigger(parent, name) {}

  friend class TBBFile;
};


}

#endif

