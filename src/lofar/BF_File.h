#ifndef __BF_FILE__
#define __BF_FILE__

#include <string>
#include <hdf5.h>
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5GroupBase.h"
#include "hdf5/HDF5DatasetBase.h"
#include "lofar/CommonAttributesFile.h"
#include "lofar/Coordinates.h"

namespace DAL {

class BF_File;
class BF_SysLog;
class BF_ProcessingHistory;
class BF_SubArrayPointing;
class BF_BeamGroup;
class BF_StokesDataset;

/*!
 * Interface for Beam-formed Data as described in ICD003.
 */
class BF_File: public CommonAttributesFile {
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

  Attribute<std::string>  observationDatatype();

  Attribute<double>       subArrayPointingDiameter();
  Attribute<double>       bandwidth();
  Attribute<double>       beamDiameter();

  Attribute< std::vector<double> >      weatherTemperature();
  Attribute< std::vector<double> >      weatherHumidity();
  Attribute< std::vector<double> >      systemTemperature();

  Attribute<unsigned>     nofSubArrayPointings();
  virtual BF_SubArrayPointing subArrayPointing( unsigned nr );

  BF_SysLog               sysLog();
protected:
  virtual void                    initNodes();

  std::string                     subArrayPointingName( unsigned nr );
};

class BF_SysLog: public HDF5GroupBase {
public:
  BF_SysLog( HDF5NodeSet &parent, const std::string &name ): HDF5GroupBase(parent, name) {}
};

class BF_ProcessingHistory: public HDF5GroupBase {
public:
  BF_ProcessingHistory( HDF5NodeSet &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute<bool>         parsetObs();
  Attribute<bool>         logPresto();
  Attribute<bool>         parFile();

protected:
  virtual void            initNodes();
};

class BF_SubArrayPointing: public HDF5GroupBase {
public:
  BF_SubArrayPointing( HDF5NodeSet &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

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

class BF_BeamGroup: public HDF5GroupBase {
public:
  BF_BeamGroup( HDF5NodeSet &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

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

class BF_StokesDataset: public HDF5DatasetBase<float> {
public:
  BF_StokesDataset( HDF5NodeSet &parent, const std::string &name ): HDF5DatasetBase<float>(parent, name) {}

  Attribute<std::string>  stokesComponent();
  Attribute< std::vector<unsigned> >    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  virtual void            initNodes();
};

}

#endif

