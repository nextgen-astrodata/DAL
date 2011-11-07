#ifndef __BF_FILE__
#define __BF_FILE__

#include <string>
#include <hdf5.h>
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5GroupBase.h"
#include "hdf5/HDF5DatasetBase.h"
#include "lofar/CommonAttributesFile.h"

namespace LDA {

class BF_File;
class BF_SysLog;
class BF_ProcessingHistory;
class BF_SubArrayPointing;
class BF_BeamGroup;
class CoordinatesGroup;
class Coordinate;
class TimeCoordinate;
class SpectralCoordinate;
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
  BF_SubArrayPointing     subArrayPointing( unsigned nr );

  BF_SysLog             sysLog();
};

class BF_SysLog: public HDF5GroupBase {
public:
  BF_SysLog( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}
};

class BF_ProcessingHistory: public HDF5GroupBase {
public:
  BF_ProcessingHistory( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute<bool>         parsetObs();
  Attribute<bool>         logPresto();
  Attribute<bool>         parFile();
};

class BF_SubArrayPointing: public HDF5GroupBase {
public:
  BF_SubArrayPointing( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

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
  BF_BeamGroup            beam( unsigned nr );
};

class BF_BeamGroup: public HDF5GroupBase {
public:
  BF_BeamGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

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

  Attribute<bool>         barycenter();

  Attribute<unsigned>     nofStokes();
  Attribute< std::vector<std::string> > stokesComponents();
  Attribute<bool>         complexVoltages();
  Attribute<std::string>  signalSum();
  BF_StokesDataset        stokes( unsigned nr );

  CoordinatesGroup        coordinates();
};

class CoordinatesGroup: public HDF5GroupBase {
public:
  CoordinatesGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute< std::vector<double> >      refLocationValue();
  Attribute< std::vector<std::string> > refLocationUnit();
  Attribute<std::string>  refLocationFrame();

  Attribute<double>       refTimeValue();
  Attribute<std::string>  refTimeUnit();
  Attribute<std::string>  refTimeFrame();

  Attribute<unsigned>     nofCoordinates();
  Attribute<unsigned>     nofAxes();
  Attribute< std::vector<std::string> > coordinateTypes();

  Coordinate              coordinate( unsigned nr );
};

class Coordinate: public HDF5GroupBase {
public:
  Coordinate( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute<std::string>  coordinateType();
  Attribute< std::vector<std::string> > storageType();

  Attribute<unsigned>     nofAxes();
  Attribute< std::vector<std::string> > axisNames();
  Attribute< std::vector<std::string> > axisUnits();

  Attribute< std::vector<double> >      referenceValue();
  Attribute< std::vector<double> >      referencePixel();
  Attribute< std::vector<double> >      increment();
  Attribute< std::vector<double> >      pc();
  Attribute< std::vector<double> >      axisValuesPixel();
  Attribute< std::vector<double> >      axisValuesWorld();
};

class TimeCoordinate: public Coordinate {
public:
  TimeCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}
};

class SpectralCoordinate: public Coordinate {
public:
  SpectralCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}
};

class BF_StokesDataset: public HDF5DatasetBase<float> {
public:
  BF_StokesDataset( const hid_gc &parent, const std::string &name ): HDF5DatasetBase<float>(parent, name) {}

  Attribute<std::string>  stokesComponent();
  Attribute< std::vector<unsigned> >    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();
};

}

#endif

