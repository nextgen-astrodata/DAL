#ifndef __BEAMFORMEDFILE__
#define __BEAMFORMEDFILE__

#include <string>
#include <hdf5.h>
#include "hdf5core/h5attribute.h"
#include "CLAFile.h"
#include "HDF5Group.h"
#include "HDF5Dataset.h"

/*
 * These classes implement the LOFAR ICD003, which describes the file
 * format for Beam-Formed Data.
 */

class BeamFormedFile;
class SAPGroup;
class BeamGroup;
class StokesGroup;

class BeamFormedFile: public CLAFile {
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

protected:
  BeamGroup( const hid_gc &parent, const std::string &name ): HDF5Group(parent, name) {}

  friend class SAPGroup;
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

