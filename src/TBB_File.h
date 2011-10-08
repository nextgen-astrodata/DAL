#ifndef __TBB_FILE__
#define __TBB_FILE__

#include <string>
#include <hdf5.h>
#include "HDF5Attribute.h"
#include "CommonAttributesFile.h"
#include "HDF5GroupBase.h"
#include "HDF5DatasetBase.h"

namespace LDA {

class TBB_File;
class TBB_SysLog;
class TBB_Station;
class TBB_DipoleDataset;
class TBB_Trigger;
class TBB_UnknownTrigger;
class TBB_VHECRTrigger;

/*!
 * Interface for TBB Time-Series Data as described in ICD001.
 */
class TBB_File: public CommonAttributesFile {
public:
  /*!
   * Open `filename` for reading/writing/creation.
   */
  TBB_File( const std::string &filename, enum fileMode mode = READ );

  TBB_SysLog             sysLog();
  TBB_Station            station( unsigned nr );

  Attribute<std::string> triggerType();
  TBB_Trigger            triggerData();
};

class TBB_SysLog: public HDF5GroupBase {
public:
  TBB_SysLog( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}
};

class TBB_Station: public HDF5GroupBase {
public:
  TBB_Station( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

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

  TBB_DipoleDataset                     dipole( unsigned station, unsigned rsp, unsigned rcu );
};

class TBB_DipoleDataset: public HDF5DatasetBase<short> {
public:
  TBB_DipoleDataset( const hid_gc &parent, const std::string &name ): HDF5DatasetBase<short>(parent, name) {}

  Attribute<unsigned>                   stationID();
  Attribute<unsigned>                   rspID();
  Attribute<unsigned>                   rcuID();

  Attribute<double>                     sampleFrequencyValue();
  Attribute<std::string>                sampleFrequencyUnit();

  Attribute<unsigned>                   time();
  Attribute<unsigned>                   sampleNumber();

  Attribute<unsigned>                   samplesPerFrame();
  Attribute<unsigned>                   dataLength();
  Attribute<unsigned>                   nyquistZone();
  Attribute<double>                     ADC2Voltage();

  Attribute<double>                     cableDelay();
  Attribute<std::string>                cableDelayUnit();

  Attribute<std::string>                feed();
  Attribute< std::vector<double> >      antennaPositionValue();
  Attribute<std::string>                antennaPositionUnit();
  Attribute<std::string>                antennaPositionFrame();

  Attribute< std::vector<double> >      antennaOrientationValue();
  Attribute<std::string>                antennaOrientationUnit();
  Attribute<std::string>                antennaOrientationFrame();

  Attribute< std::vector<double> >      tileBeamValue();
  Attribute<std::string>                tileBeamUnit();
  Attribute<std::string>                tileBeamFrame();

  Attribute<std::string>                tileCoefUnit();
  Attribute< std::vector<unsigned> >    tileBeamCoefs();

  Attribute< std::vector<double> >      tileDipolePositionValue(); // todo: make this a 3D vector
  Attribute<std::string>                tileDipolePositionUnit();
  Attribute<std::string>                tileDipolePositionFrame();
};

class TBB_Trigger: public HDF5GroupBase {
public:
  TBB_Trigger( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}
};

class TBB_UnknownTrigger: public TBB_Trigger {
public:
  TBB_UnknownTrigger( const hid_gc &parent, const std::string &name ): TBB_Trigger(parent, name) {}

  Attribute<std::string> metadata();
};

class TBB_VHECRTrigger: public TBB_Trigger {
public:
  TBB_VHECRTrigger( const hid_gc &parent, const std::string &name ): TBB_Trigger(parent, name) {}

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
};


}

#endif

