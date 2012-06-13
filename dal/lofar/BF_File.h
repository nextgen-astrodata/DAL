#ifndef DAL_BF_FILE_H
#define DAL_BF_FILE_H

#include <string>
#include <hdf5.h>
#include "dal/hdf5/Attribute.h"
#include "dal/hdf5/Group.h"
#include "dal/hdf5/Dataset.h"
#include "dal/lofar/CLA_File.h"
#include "dal/lofar/Coordinates.h"

namespace DAL {

class BF_File;
class BF_SysLog;
class BF_ProcessingHistory;
class BF_SubArrayPointing;
class BF_BeamGroup;
class BF_StokesDataset;

/*!
 * Interface for Beam-formed Data.
 */
class BF_File: public CLA_File {
public:
  /*!
   * Open `filename` for reading/writing/creation.
   */
  BF_File( const std::string &filename, enum fileMode mode = READ );

  Attribute<std::string>  createOfflineOnline();
  Attribute<std::string>  BFFormat();
  Attribute<std::string>  BFVersion();

  Attribute<std::string>  expTimeStartUTC();
  Attribute<double>       expTimeStartMJD();
  Attribute<std::string>  expTimeStartTAI();

  Attribute<std::string>  expTimeEndUTC();
  Attribute<double>       expTimeEndMJD();
  Attribute<std::string>  expTimeEndTAI();

  Attribute<double>       totalIntegrationTime();
  Attribute<std::string>  totalIntegrationTimeUnit();
  
  Attribute<std::string>  observationDatatype();

  Attribute<double>       subArrayPointingDiameter();
  Attribute<std::string>  subArrayPointingDiameterUnit();
  Attribute<double>       bandwidth();
  Attribute<std::string>  bandwidthUnit();
  Attribute<double>       beamDiameter();
  Attribute<std::string>  beamDiameterUnit();
  
  Attribute< std::vector<double> >      weatherTemperature();
  Attribute<std::string>                weatherTemperatureUnit();
  Attribute< std::vector<double> >      weatherHumidity();
  Attribute<std::string>                weatherHumidityUnit();
  Attribute< std::vector<double> >      systemTemperature();
  Attribute<std::string>                systemTemperatureUnit();
  
  Attribute<unsigned>     nofSubArrayPointings();
  virtual BF_SubArrayPointing subArrayPointing( unsigned nr );

  BF_SysLog               sysLog();
protected:
  virtual void                    initNodes();

  std::string                     subArrayPointingName( unsigned nr );
};

class BF_SysLog: public Group {
public:
  BF_SysLog( Group &parent, const std::string &name ): Group(parent, name) {}
};

class BF_ProcessingHistory: public Group {
public:
  BF_ProcessingHistory( Group &parent, const std::string &name ): Group(parent, name) {}

  Attribute<bool>         parsetObs();
  Attribute<bool>         logPresto();
  Attribute<bool>         parFile();

protected:
  virtual void            initNodes();
};

class BF_SubArrayPointing: public Group {
public:
  BF_SubArrayPointing( Group &parent, const std::string &name ): Group(parent, name) {}

  Attribute<unsigned>     nofStations();
  Attribute< std::vector<std::string> > stationsList();

  Attribute<double>       pointRA();
  Attribute<double>       pointDEC();

  Attribute<double>       clockRate();
  Attribute<std::string>  clockRateUnit();

  Attribute<unsigned>     nofSamples();
  Attribute<double>       samplingRate();
  Attribute<std::string>  samplingRateUnit();
  Attribute<double>       samplingTime();
  Attribute<std::string>  samplingTimeUnit();

  Attribute<unsigned>     channelsPerSubband();

  Attribute<double>       subbandWidth();
  Attribute<std::string>  subbandWidthUnit();

  Attribute<double>       channelWidth();
  Attribute<std::string>  channelWidthUnit();

  Attribute<unsigned>     nofBeams();
  virtual BF_BeamGroup    beam( unsigned nr );

protected:
  virtual void            initNodes();

  std::string             beamName( unsigned nr );
};

class BF_BeamGroup: public Group {
public:
  BF_BeamGroup( Group &parent, const std::string &name ): Group(parent, name) {}

  Attribute<unsigned>     nofStations();
  Attribute< std::vector<std::string> > stationsList();

  Attribute<double>       pointRA();
  Attribute<double>       pointDEC();

  Attribute<double>       pointOffsetRA();
  Attribute<double>       pointOffsetDEC();

  Attribute<double>       beamDiameterRA();
  Attribute<double>       beamDiameterDEC();
  Attribute<double>       beamFrequencyCenter();
  Attribute<std::string>  beamFrequencyCenterUnit();

  Attribute<bool>         foldedData();
  Attribute<double>       foldPeriod();
  Attribute<std::string>  foldPeriodUnit();

  Attribute<std::string>  dedispersion();
  Attribute<double>       dedispersionMeasure();
  Attribute<std::string>  dedispersionMeasureUnit();

  Attribute<bool>         barycentered();

  Attribute<unsigned>     nofStokes();
  Attribute< std::vector<std::string> > stokesComponents();
  Attribute<bool>         complexVoltages();
  Attribute<std::string>  signalSum();
  virtual BF_StokesDataset stokes( unsigned nr );

  virtual CoordinatesGroup coordinates();

protected:
  virtual void            initNodes();

  std::string             stokesName( unsigned nr );
  std::string             coordinatesName();
};

class BF_StokesDataset: public Dataset<float> {
public:
  BF_StokesDataset( Group &parent, const std::string &name ): Dataset<float>(parent, name) {}

  Attribute<std::string>  stokesComponent();
  Attribute< std::vector<unsigned> >    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  virtual void            initNodes();
};

}

#endif

