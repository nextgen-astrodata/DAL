#ifndef __BEAMFORMEDFILE__
#define __BEAMFORMEDFILE__

#include <string>
#include <hdf5.h>
#include "hdf5core/h5attribute.h"
#include "CommonAttributesFile.h"
#include "HDF5GroupBase.h"
#include "HDF5DatasetBase.h"

/*
 * These classes implement the LOFAR ICD003, which describes the file
 * format for Beam-Formed Data.
 */

class BeamFormedFile;
class SysLog;
class BF_ProcessingHistory;
class BF_SubArrayPointing;
class BF_BeamGroup;
class CoordinatesGroup;
class Coordinate;
class TimeCoordinate;
class SpectralCoordinate;
class BF_StokesDataset;

class BeamFormedFile: public CommonAttributesFile {
public:
  BeamFormedFile( const std::string &filename, enum fileMode mode = READ );

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

  AttributeV<double>      weatherTemperature();
  AttributeV<double>      weatherHumidity();
  AttributeV<double>      systemTemperature();

  Attribute<unsigned>     nofSubArrayPointings();
  BF_SubArrayPointing                subArrayPointing( unsigned nr );

  SysLog             sysLog();
};

class SysLog: public HDF5GroupBase {
protected:
  SysLog( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BeamFormedFile;
};

class BF_ProcessingHistory: public HDF5GroupBase {
public:
  Attribute<bool>         parsetObs();
  Attribute<bool>         logPresto();
  Attribute<bool>         parFile();

protected:
  BF_ProcessingHistory( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BF_SubArrayPointing;
  friend class BF_BeamGroup;
};

class BF_SubArrayPointing: public HDF5GroupBase {
public:
  Attribute<unsigned>     nofStations();
  AttributeV<std::string> stationsList();

  Attribute<double>       pointRA();
  Attribute<double>       pointDEC();

  Attribute<double>       clockRate();
  Attribute<std::string>  clockRateUnit();

  Attribute<unsigned>     nofSamples();
  Attribute<double>       samplingRate();
  Attribute<std::string>  samplingRateUnit();

  Attribute<unsigned>     channelsPerSubband();

  Attribute<double>       subbandWidth();
  Attribute<std::string>  subbandWidthUnit();

  Attribute<double>       channelWidth();
  Attribute<std::string>  channelWidthUnit();

  Attribute<unsigned>     nofBeams();
  BF_BeamGroup               beam( unsigned nr );

protected:
  BF_SubArrayPointing( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BeamFormedFile;
};

class BF_BeamGroup: public HDF5GroupBase {
public:
  Attribute<unsigned>     nofStations();
  AttributeV<std::string> stationsList();

  Attribute<double>       pointRA();
  Attribute<double>       pointDEC();

  Attribute<double>       pointOffsetRA();
  Attribute<double>       pointOffsetDEC();

  Attribute<bool>         foldedData();
  Attribute<double>       foldPeriod();
  Attribute<std::string>  foldPeriodUnit();

  Attribute<std::string>  dedispersion();
  Attribute<double>       dedispersionMeasure();
  Attribute<std::string>  dedispersionMeasureUnit();

  Attribute<unsigned>     nofStokes();
  AttributeV<std::string> stokesComponents();
  Attribute<bool>         complexVoltages();
  Attribute<std::string>  signalSum();
  BF_StokesDataset             stokes( unsigned nr );

  CoordinatesGroup        coordinates();

protected:
  BF_BeamGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BF_SubArrayPointing;
};

class CoordinatesGroup: public HDF5GroupBase {
public:
  AttributeV<double>      refLocationValue();
  AttributeV<std::string> refLocationUnit();
  Attribute<std::string>  refLocationFrame();

  Attribute<double>       refTimeValue();
  Attribute<std::string>  refTimeUnit();
  Attribute<std::string>  refTimeFrame();

  Attribute<unsigned>     nofCoordinates();
  Attribute<unsigned>     nofAxes();
  AttributeV<std::string> coordinateTypes();

  Coordinate     coordinate( unsigned nr );

protected:
  CoordinatesGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BF_BeamGroup;
};

class Coordinate: public HDF5GroupBase {
public:
  Attribute<std::string>  coordinateType();
  AttributeV<std::string> storageType();

  Attribute<unsigned>     nofAxes();
  AttributeV<std::string> axisNames();
  AttributeV<std::string> axisUnits();

  AttributeV<double>      referenceValue();
  AttributeV<double>      referencePixel();
  AttributeV<double>      increment();
  AttributeV<double>      pc();
  AttributeV<double>      axisValuesPixel();
  AttributeV<double>      axisValuesWorld();

protected:
  Coordinate( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class CoordinatesGroup;
};

class TimeCoordinate: public Coordinate {
protected:
  TimeCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}

  friend class CoordinatesGroup;
};

class SpectralCoordinate: public Coordinate {
protected:
  SpectralCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}

  friend class CoordinatesGroup;
};

class BF_StokesDataset: public HDF5DatasetBase<float> {
public:
  Attribute<std::string>  stokesComponent();
  AttributeV<unsigned>    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  BF_StokesDataset( const hid_gc &parent, const std::string &name ): HDF5DatasetBase<float>(parent, name) {}

  friend class BF_BeamGroup;
};

#endif

