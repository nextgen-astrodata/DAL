#include "BeamFormedFile.h"

using namespace std;

BeamFormedFile::BeamFormedFile( const string &filename, enum HDF5File::fileMode mode )
:
  HDF5File(filename, mode)
{
}

Attribute<string> BeamFormedFile::telescope()
{
  return Attribute<string>(group(), "TELESCOPE");
}

Attribute<string> BeamFormedFile::observer()
{
  return Attribute<string>(group(), "OBSERVER");
}

Attribute<string> BeamFormedFile::projectID()
{
  return Attribute<string>(group(), "PROJECT_ID");
}

Attribute<string> BeamFormedFile::projectTitle()
{
  return Attribute<string>(group(), "PROJECT_TITLE");
}

Attribute<string> BeamFormedFile::projectPI()
{
  return Attribute<string>(group(), "PROJECT_PI");
}

Attribute<string> BeamFormedFile::projectCOI()
{
  return Attribute<string>(group(), "PROJECT_CO_I");
}

Attribute<string> BeamFormedFile::projectContact()
{
  return Attribute<string>(group(), "PROJECT_CONTACT");
}

Attribute<string> BeamFormedFile::observationID()
{
  return Attribute<string>(group(), "OBSERVATION_ID");
}

Attribute<string> BeamFormedFile::observationStartUTC()
{
  return Attribute<string>(group(), "OBSERVATION_START_UTC");
}

Attribute<double> BeamFormedFile::observationStartMJD()
{
  return Attribute<double>(group(), "OBSERVATION_START_MJD");
}

Attribute<string> BeamFormedFile::observationStartTAI()
{
  return Attribute<string>(group(), "OBSERVATION_START_TAI");
}

Attribute<string> BeamFormedFile::observationEndUTC()
{
  return Attribute<string>(group(), "OBSERVATION_END_UTC");
}

Attribute<double> BeamFormedFile::observationEndMJD()
{
  return Attribute<double>(group(), "OBSERVATION_END_MJD");
}

Attribute<string> BeamFormedFile::observationEndTAI()
{
  return Attribute<string>(group(), "OBSERVATION_END_TAI");
}

Attribute<unsigned> BeamFormedFile::observationNofStations()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_STATIONS");
}

AttributeV<string> BeamFormedFile::observationStationsList()
{
  return AttributeV<string>(group(), "OBSERVATION_STATIONS_LIST");
}

Attribute<unsigned> BeamFormedFile::observationNofBitsPerSample()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> BeamFormedFile::clockFrequency()
{
  return Attribute<double>(group(), "CLOCK_FREQUENCY");
}

Attribute<string> BeamFormedFile::clockFrequencyUnit()
{
  return Attribute<string>(group(), "CLOCK_FREQUENCY_UNIT");
}

Attribute<string> BeamFormedFile::antennaSet()
{
  return Attribute<string>(group(), "ANTENNA_SET");
}

Attribute<string> BeamFormedFile::filterSelection()
{
  return Attribute<string>(group(), "FILTER_SELECTION");
}

Attribute<string> BeamFormedFile::systemVersion()
{
  return Attribute<string>(group(), "SYSTEM_VERSION");
}

Attribute<string> BeamFormedFile::pipelineName()
{
  return Attribute<string>(group(), "PIPELINE_NAME");
}

Attribute<string> BeamFormedFile::pipelineVersion()
{
  return Attribute<string>(group(), "PIPELINE_VERSION");
}

Attribute<string> BeamFormedFile::notes()
{
  return Attribute<string>(group(), "NOTES");
}

Attribute<string> BeamFormedFile::target()
{
  return Attribute<string>(group(), "TARGET");
}

SAPGroup BeamFormedFile::sap( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "SUB_ARRAY_POINTING_%03u", nr);

  return SAPGroup(group(), string(buf));
}

Attribute<unsigned> SAPGroup::nofStations()
{
  return Attribute<unsigned>(group(), "NOF_STATIONS");
}

AttributeV<string> SAPGroup::stationsList()
{
  return AttributeV<string>(group(), "STATIONS_LIST");
}

Attribute<double> SAPGroup::pointRA()
{
  return Attribute<double>(group(), "POINT_RA");
}

Attribute<double> SAPGroup::pointDEC()
{
  return Attribute<double>(group(), "POINT_DEC");
}

Attribute<double> SAPGroup::clockRate()
{
  return Attribute<double>(group(), "CLOCK_RATE");
}

Attribute<string> SAPGroup::clockRateUnit()
{
  return Attribute<string>(group(), "CLOCK_RATE_UNIT");
}

Attribute<unsigned> SAPGroup::nofSamples()
{
  return Attribute<unsigned>(group(), "NOF_SAMPLES");
}

Attribute<double> SAPGroup::samplingRate()
{
  return Attribute<double>(group(), "SAMPLING_RATE");
}

Attribute<string> SAPGroup::samplingRateUnit()
{
  return Attribute<string>(group(), "SAMPLING_RATE_UNIT");
}

Attribute<unsigned> SAPGroup::channelsPerSubband()
{
  return Attribute<unsigned>(group(), "CHANNELS_PER_SUBBAND");
}

Attribute<double> SAPGroup::subbandWidth()
{
  return Attribute<double>(group(), "SUBBAND_WIDTH");
}

Attribute<string> SAPGroup::subbandWidthUnit()
{
  return Attribute<string>(group(), "SUBBAND_WIDTH_UNIT");
}

Attribute<double> SAPGroup::channelWidth()
{
  return Attribute<double>(group(), "CHANNEL_WIDTH");
}

Attribute<string> SAPGroup::channelWidthUnit()
{
  return Attribute<string>(group(), "CHANNEL_WIDTH_UNIT");
}


Attribute<unsigned> SAPGroup::nofBeams()
{
  return Attribute<unsigned>(group(), "NOF_BEAMS");
}

BeamGroup SAPGroup::beam( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "BEAM_%03u", nr);

  return BeamGroup(group(), string(buf));
}

Attribute<unsigned> BeamGroup::nofStations()
{
  return Attribute<unsigned>(group(), "NOF_STATIONS");
}

AttributeV<string> BeamGroup::stationsList()
{
  return AttributeV<string>(group(), "STATIONS_LIST");
}

Attribute<double> BeamGroup::pointRA()
{
  return Attribute<double>(group(), "POINT_RA");
}

Attribute<double> BeamGroup::pointDEC()
{
  return Attribute<double>(group(), "POINT_DEC");
}

Attribute<double> BeamGroup::pointOffsetRA()
{
  return Attribute<double>(group(), "POINT_OFFSET_RA");
}

Attribute<double> BeamGroup::pointOffsetDEC()
{
  return Attribute<double>(group(), "POINT_OFFSET_DEC");
}

Attribute<bool> BeamGroup::foldedData()
{
  return Attribute<bool>(group(), "FOLDED_DATA");
}

Attribute<double> BeamGroup::foldPeriod()
{
  return Attribute<double>(group(), "FOLD_PERIOD");
}

Attribute<string> BeamGroup::foldPeriodUnit()
{
  return Attribute<string>(group(), "FOLD_PERIOD_UNIT");
}

Attribute<string> BeamGroup::dedispersion()
{
  return Attribute<string>(group(), "DEDISPERSION");
}

Attribute<double> BeamGroup::dedispersionMeasure()
{
  return Attribute<double>(group(), "DEDISPERSION_MEASURE");
}

Attribute<string> BeamGroup::dedispersionMeasureUnit()
{
  return Attribute<string>(group(), "DEDISPERSION_MEASURE_UNIT");
}

Attribute<unsigned> BeamGroup::nofStokes()
{
  return Attribute<unsigned>(group(), "NOF_STOKES");
}

AttributeV<string> BeamGroup::stokesComponents()
{
  return AttributeV<string>(group(), "STOKES_COMPONENTS");
}

Attribute<bool> BeamGroup::complexVoltages()
{
  return Attribute<bool>(group(), "COMPLEX_VOLTAGES");
}

Attribute<string> BeamGroup::signalSum()
{
  return Attribute<string>(group(), "SIGNAL_SUM");
}

StokesGroup BeamGroup::stokes( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "STOKES_%01u", nr);

  return StokesGroup(group(), string(buf));
}

Attribute<string> StokesGroup::stokesComponent()
{
  return Attribute<string>(group(), "STOKES_COMPONENT");
}

AttributeV<unsigned> StokesGroup::nofChannels()
{
  return AttributeV<unsigned>(group(), "NOF_CHANNELS");
}

Attribute<unsigned> StokesGroup::nofSubbands()
{
  return Attribute<unsigned>(group(), "NOF_SUBBANDS");
}

Attribute<unsigned> StokesGroup::nofSamples()
{
  return Attribute<unsigned>(group(), "NOF_SAMPLES");
}

