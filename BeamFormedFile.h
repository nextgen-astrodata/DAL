#ifndef __BEAMFORMEDFILE__
#define __BEAMFORMEDFILE__

#include <string>
#include <hdf5.h>
#include "hdf5core/h5attribute.h"
#include "HDF5File.h"
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

class BeamFormedFile: public HDF5File {
public:
  BeamFormedFile( const std::string &filename, enum fileMode mode = READ );

  Attribute<std::string>  telescope();
  Attribute<std::string>  observer();

  Attribute<std::string>  projectID();
  Attribute<std::string>  projectTitle();
  Attribute<std::string>  projectPI();
  Attribute<std::string>  projectCOI();
  Attribute<std::string>  projectContact();

  Attribute<std::string>  observationID();

  Attribute<std::string>  observationStartUTC();
  Attribute<double>       observationStartMJD();
  Attribute<std::string>  observationStartTAI();

  Attribute<std::string>  observationEndUTC();
  Attribute<double>       observationEndMJD();
  Attribute<std::string>  observationEndTAI();

  Attribute<unsigned>     observationNofStations();
  AttributeV<std::string> observationStationsList();

  Attribute<unsigned>     observationNofBitsPerSample();
  Attribute<double>       clockFrequency();
  Attribute<std::string>  clockFrequencyUnit();
  Attribute<std::string>  antennaSet();
  Attribute<std::string>  filterSelection();
  Attribute<std::string>  target();

  Attribute<std::string>  systemVersion();
  Attribute<std::string>  pipelineName();
  Attribute<std::string>  pipelineVersion();
  Attribute<std::string>  notes();

  SAPGroup                sap( unsigned nr );
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

