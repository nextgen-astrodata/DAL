#ifndef __BEAMFORMEDFILE__
#define __BEAMFORMEDFILE__

#include <string>
#include <hdf5.h>
#include "hdf5core/h5attribute.h"
#include "CommonAttributesFile.h"
#include "HDF5Group.h"
#include "HDF5Dataset.h"

/*
 * These classes implement the LOFAR ICD003, which describes the file
 * format for Beam-Formed Data.
 */

class BeamFormedFile;
class SysLogGroup;
class ProcessHistoryGroup;
class SAPGroup;
class BeamGroup;
class CoordinatesGroup;
class CoordinateTypeGroup;
class TimeCoordinateGroup;
class SpectralCoordinateGroup;
class StokesGroup;

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
  SAPGroup                subArrayPointing( unsigned nr );

  SysLogGroup             sysLog();
};

class SysLogGroup: public HDF5Group {
protected:
  SysLogGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class BeamFormedFile;
};

class ProcessHistoryGroup: public HDF5Group {
public:
  Attribute<bool>         parsetObs();
  Attribute<bool>         logPresto();
  Attribute<bool>         parFile();

protected:
  ProcessHistoryGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class SAPGroup;
  friend class BeamGroup;
};

class SAPGroup: public HDF5Group {
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
  BeamGroup               beam( unsigned nr );

protected:
  SAPGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class BeamFormedFile;
};

class BeamGroup: public HDF5Group {
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
  StokesGroup             stokes( unsigned nr );

  CoordinatesGroup        coordinates();

protected:
  BeamGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class SAPGroup;
};

class CoordinatesGroup: public HDF5Group {
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

  CoordinateTypeGroup     coordinate( unsigned nr );

protected:
  CoordinatesGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class BeamGroup;
};

class CoordinateTypeGroup: public HDF5Group {
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
  CoordinateTypeGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class CoordinatesGroup;
};

class TimeCoordinateGroup: public CoordinateTypeGroup {
protected:
  TimeCoordinateGroup( const hid_gc &parent, const std::string &name ): CoordinateTypeGroup(parent, name) {}

  friend class CoordinatesGroup;
};

class SpectralCoordinateGroup: public CoordinateTypeGroup {
protected:
  SpectralCoordinateGroup( const hid_gc &parent, const std::string &name ): CoordinateTypeGroup(parent, name) {}

  friend class CoordinatesGroup;
};

class StokesGroup: public HDF5Dataset<float> {
public:
  Attribute<std::string>  stokesComponent();
  AttributeV<unsigned>    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  StokesGroup( const hid_gc &parent, const std::string &name ): HDF5Dataset<float>(parent, name) {}

  friend class BeamGroup;
};

#endif

