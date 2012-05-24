#ifndef __TBB_FILE__
#define __TBB_FILE__

#include <string>
#include <vector>
#include <hdf5.h>
#include "dal/hdf5/Attribute.h"
#include "dal/hdf5/Group.h"
#include "dal/hdf5/Dataset.h"
#include "dal/lofar/CommonAttributesFile.h"

namespace DAL {

class TBB_File;
class TBB_SysLog;
class TBB_Station;
class TBB_DipoleDataset;
class TBB_Trigger;
class TBB_UnknownTrigger;
class TBB_VHECRTrigger;

/*!
 * Interface for TBB Time-Series Data.
 */
class TBB_File: public CommonAttributesFile {
public:
  /*!
   * Open `filename` for reading/writing/creation.
   */
  TBB_File( const std::string &filename, enum fileMode mode = READ );

  virtual TBB_SysLog     sysLog();
  virtual std::vector<TBB_Station> stations();
  virtual TBB_Station    station( const std::string &stationName );

  Attribute<std::string> triggerType();
  virtual TBB_Trigger    triggerData();
};

class TBB_SysLog: public Group {
public:
  TBB_SysLog( Group &parent, const std::string &name ): Group(parent, name) {}
};

class TBB_Station: public Group {
public:
  TBB_Station( Group &parent, const std::string &name ): Group(parent, name) {}

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

  virtual std::vector<TBB_DipoleDataset> dipoles();
  virtual TBB_DipoleDataset             dipole( const std::string &dipoleName );
};

class TBB_DipoleDataset: public Dataset<short> {
public:
  TBB_DipoleDataset( Group &parent, const std::string &name ): Dataset<short>(parent, name) {}

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

class TBB_Trigger: public Group {
public:
  TBB_Trigger( Group &parent, const std::string &name ): Group(parent, name) {}
};

class TBB_UnknownTrigger: public TBB_Trigger {
public:
  TBB_UnknownTrigger( Group &parent, const std::string &name ): TBB_Trigger(parent, name) {}

  Attribute<std::string> metadata();
};

class TBB_VHECRTrigger: public TBB_Trigger {
public:
  TBB_VHECRTrigger( Group &parent, const std::string &name ): TBB_Trigger(parent, name) {}

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

