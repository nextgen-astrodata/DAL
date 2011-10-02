#ifndef __BEAMFORMEDFILE__
#define __BEAMFORMEDFILE__

#include <string>
#include <hdf5.h>
#include "hdf5core/h5attribute.h"
#include "CommonAttributesFile.h"
#include "HDF5GroupBase.h"
#include "HDF5DatasetBase.h"

namespace LDA {

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

/*!
 * Interface for Beam-formed Data as described in ICD003.
 */
class BeamFormedFile: public CommonAttributesFile {
public:
  /*!
   * Open `filename` for reading/writing/creation.
   */
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

  Attribute< std::vector<double> >      weatherTemperature();
  Attribute< std::vector<double> >      weatherHumidity();
  Attribute< std::vector<double> >      systemTemperature();

  Attribute<unsigned>     nofSubArrayPointings();
  BF_SubArrayPointing     subArrayPointing( unsigned nr );

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
  Attribute< std::vector<std::string> > stationsList();

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
  BF_BeamGroup            beam( unsigned nr );

protected:
  BF_SubArrayPointing( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BeamFormedFile;
};

class BF_BeamGroup: public HDF5GroupBase {
public:
  Attribute<unsigned>     nofStations();
  Attribute< std::vector<std::string> > stationsList();

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
  Attribute< std::vector<std::string> > stokesComponents();
  Attribute<bool>         complexVoltages();
  Attribute<std::string>  signalSum();
  BF_StokesDataset        stokes( unsigned nr );

  CoordinatesGroup        coordinates();

protected:
  BF_BeamGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BF_SubArrayPointing;
};

class CoordinatesGroup: public HDF5GroupBase {
public:
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

protected:
  CoordinatesGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  friend class BF_BeamGroup;
};

class Coordinate: public HDF5GroupBase {
public:
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
  Attribute< std::vector<unsigned> >    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  BF_StokesDataset( const hid_gc &parent, const std::string &name ): HDF5DatasetBase<float>(parent, name) {}

  friend class BF_BeamGroup;
};

}

#endif

