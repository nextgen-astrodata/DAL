#include "BF_File.h"

using namespace std;

namespace DAL {

BF_File::BF_File( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  CommonAttributesFile(filename, mode)
{
}

void BF_File::initNodes() {
  CommonAttributesFile::initNodes();

  addNode( new Attribute<string>(group(), "CREATE_OFFLINE_ONLINE") );
  addNode( new Attribute<string>(group(), "BF_FORMAT") );
  addNode( new Attribute<string>(group(), "BF_VERSION") );
  addNode( new Attribute<string>(group(), "EXPTIME_START_UTC") );
  addNode( new Attribute<double>(group(), "EXPTIME_START_MJD") );
  addNode( new Attribute<string>(group(), "EXPTIME_START_TAI") );
  addNode( new Attribute<string>(group(), "EXPTIME_END_UTC") );
  addNode( new Attribute<double>(group(), "EXPTIME_END_MJD") );
  addNode( new Attribute<string>(group(), "EXPTIME_END_TAI") );
  addNode( new Attribute<double>(group(), "TOTAL_INTEGRATION_TIME") );
  addNode( new Attribute<string>(group(), "OBSERVATION_DATATYPE") );
  addNode( new Attribute<double>(group(), "SUB_ARRAY_POINTING_DIAMETER") );
  addNode( new Attribute<double>(group(), "BANDWIDTH") );
  addNode( new Attribute<double>(group(), "BEAM_DIAMETER") );
  addNode( new Attribute< vector<double> >(group(), "WEATHER_TEMPERATURE") );
  addNode( new Attribute< vector<double> >(group(), "WEATHER_HUMIDITY") );
  addNode( new Attribute< vector<double> >(group(), "SYSTEM_TEMPERATURE") );
  addNode( new Attribute<unsigned>(group(), "NOF_SUB_ARRAY_POINTINGS") );
}

Attribute<string> BF_File::createOfflineOnline()
{
  return getNode("CREATE_OFFLINE_ONLINE");
}

Attribute<string> BF_File::BFFormat()
{
  return getNode("BF_FORMAT");
}

Attribute<string> BF_File::BFVersion()
{
  return getNode("BF_VERSION");
}

Attribute<string> BF_File::expTimeStartUTC()
{
  return getNode("EXPTIME_START_UTC");
}

Attribute<double> BF_File::expTimeStartMJD()
{
  return getNode("EXPTIME_START_MJD");
}

Attribute<string> BF_File::expTimeStartTAI()
{
  return getNode("EXPTIME_START_TAI");
}

Attribute<string> BF_File::expTimeEndUTC()
{
  return getNode("EXPTIME_END_UTC");
}

Attribute<double> BF_File::expTimeEndMJD()
{
  return getNode("EXPTIME_END_MJD");
}

Attribute<string> BF_File::expTimeEndTAI()
{
  return getNode("EXPTIME_END_TAI");
}

Attribute<double> BF_File::totalIntegrationTime()
{
  return getNode("TOTAL_INTEGRATION_TIME");
}

Attribute<string> BF_File::observationDatatype()
{
  return getNode("OBSERVATION_DATATYPE");
}

Attribute<double> BF_File::subArrayPointingDiameter()
{
  return getNode("SUB_ARRAY_POINTING_DIAMETER");
}

Attribute<double> BF_File::bandwidth()
{
  return getNode("BANDWIDTH");
}

Attribute<double> BF_File::beamDiameter()
{
  return getNode("BEAM_DIAMETER");
}

Attribute< vector<double> > BF_File::weatherTemperature()
{
  return getNode("WEATHER_TEMPERATURE");
}

Attribute< vector<double> > BF_File::weatherHumidity()
{
  return getNode("WEATHER_HUMIDITY");
}

Attribute< vector<double> > BF_File::systemTemperature()
{
  return getNode("SYSTEM_TEMPERATURE");
}

Attribute<unsigned> BF_File::nofSubArrayPointings()
{
  return getNode("NOF_SUB_ARRAY_POINTINGS");
}

string BF_File::subArrayPointingName( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "SUB_ARRAY_POINTING_%03u", nr);

  return string(buf);
}

BF_SubArrayPointing BF_File::subArrayPointing( unsigned nr )
{
  return BF_SubArrayPointing(group(), subArrayPointingName(nr));
}

BF_SysLog BF_File::sysLog()
{
  return BF_SysLog(group(), "SYS_LOG");
}

void BF_ProcessingHistory::initNodes() {
  addNode( new Attribute<bool>(group(), "PARSET_OBS") );
  addNode( new Attribute<bool>(group(), "LOG_PRESTO") );
  addNode( new Attribute<bool>(group(), "PARFILE") );
}

Attribute<bool> BF_ProcessingHistory::parsetObs()
{
  return getNode("PARSET_OBS");
}

Attribute<bool> BF_ProcessingHistory::logPresto()
{
  return getNode("LOG_PRESTO");
}

Attribute<bool> BF_ProcessingHistory::parFile()
{
  return getNode("PARFILE");
}

void BF_SubArrayPointing::initNodes() {
  addNode( new Attribute<unsigned>(group(), "NOF_STATIONS") );
  addNode( new Attribute< vector<string> >(group(), "STATIONS_LIST") );
  addNode( new Attribute<double>(group(), "POINT_RA") );
  addNode( new Attribute<double>(group(), "POINT_DEC") );
  addNode( new Attribute<double>(group(), "CLOCK_RATE") );
  addNode( new Attribute<string>(group(), "CLOCK_RATE_UNIT") );
  addNode( new Attribute<unsigned>(group(), "NOF_SAMPLES") );
  addNode( new Attribute<double>(group(), "SAMPLING_RATE") );
  addNode( new Attribute<string>(group(), "SAMPLING_RATE_UNIT") );
  addNode( new Attribute<double>(group(), "SAMPLING_TIME") );
  addNode( new Attribute<string>(group(), "SAMPLING_TIME_UNIT") );
  addNode( new Attribute<unsigned>(group(), "CHANNELS_PER_SUBBAND") );
  addNode( new Attribute<double>(group(), "SUBBAND_WIDTH") );
  addNode( new Attribute<string>(group(), "SUBBAND_WIDTH_UNIT") );
  addNode( new Attribute<double>(group(), "CHANNEL_WIDTH") );
  addNode( new Attribute<string>(group(), "CHANNEL_WIDTH_UNIT") );
  addNode( new Attribute<unsigned>(group(), "NOF_BEAMS") );
}

Attribute<unsigned> BF_SubArrayPointing::nofStations()
{
  return getNode("NOF_STATIONS");
}

Attribute< vector<string> > BF_SubArrayPointing::stationsList()
{
  return getNode("STATIONS_LIST");
}

Attribute<double> BF_SubArrayPointing::pointRA()
{
  return getNode("POINT_RA");
}

Attribute<double> BF_SubArrayPointing::pointDEC()
{
  return getNode("POINT_DEC");
}

Attribute<double> BF_SubArrayPointing::clockRate()
{
  return getNode("CLOCK_RATE");
}

Attribute<string> BF_SubArrayPointing::clockRateUnit()
{
  return getNode("CLOCK_RATE_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::nofSamples()
{
  return getNode("NOF_SAMPLES");
}

Attribute<double> BF_SubArrayPointing::samplingRate()
{
  return getNode("SAMPLING_RATE");
}

Attribute<string> BF_SubArrayPointing::samplingRateUnit()
{
  return getNode("SAMPLING_RATE_UNIT");
}

Attribute<double> BF_SubArrayPointing::samplingTime()
{
  return getNode("SAMPLING_TIME");
}

Attribute<string> BF_SubArrayPointing::samplingTimeUnit()
{
  return getNode("SAMPLING_TIME_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::channelsPerSubband()
{
  return getNode("CHANNELS_PER_SUBBAND");
}

Attribute<double> BF_SubArrayPointing::subbandWidth()
{
  return getNode("SUBBAND_WIDTH");
}

Attribute<string> BF_SubArrayPointing::subbandWidthUnit()
{
  return getNode("SUBBAND_WIDTH_UNIT");
}

Attribute<double> BF_SubArrayPointing::channelWidth()
{
  return getNode("CHANNEL_WIDTH");
}

Attribute<string> BF_SubArrayPointing::channelWidthUnit()
{
  return getNode("CHANNEL_WIDTH_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::nofBeams()
{
  return getNode("NOF_BEAMS");
}

string BF_SubArrayPointing::beamName( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "BEAM_%03u", nr);

  return string(buf);
}

BF_BeamGroup BF_SubArrayPointing::beam( unsigned nr )
{
  return BF_BeamGroup(group(), beamName(nr));
}

void BF_BeamGroup::initNodes() {
  addNode( new Attribute<unsigned>(group(), "NOF_STATIONS") );
  addNode( new Attribute< vector<string> >(group(), "STATIONS_LIST") );
  addNode( new Attribute<double>(group(), "POINT_RA") );
  addNode( new Attribute<double>(group(), "POINT_DEC") );
  addNode( new Attribute<double>(group(), "POINT_OFFSET_RA") );
  addNode( new Attribute<double>(group(), "POINT_OFFSET_DEC") );
  addNode( new Attribute<double>(group(), "BEAM_DIAMETER_RA") );
  addNode( new Attribute<double>(group(), "BEAM_DIAMETER_DEC") );
  addNode( new Attribute<double>(group(), "BEAM_FREQUENCY_CENTER") );
  addNode( new Attribute<string>(group(), "BEAM_FREQUENCY_CENTER_UNIT") );
  addNode( new Attribute<bool>(group(), "FOLDED_DATA") );
  addNode( new Attribute<double>(group(), "FOLD_PERIOD") );
  addNode( new Attribute<string>(group(), "FOLD_PERIOD_UNIT") );
  addNode( new Attribute<string>(group(), "DEDISPERSION") );
  addNode( new Attribute<double>(group(), "DEDISPERSION_MEASURE") );
  addNode( new Attribute<string>(group(), "DEDISPERSION_MEASURE_UNIT") );
  addNode( new Attribute<bool>(group(), "BARYCENTERED") );
  addNode( new Attribute<unsigned>(group(), "NOF_STOKES") );
  addNode( new Attribute< vector<string> >(group(), "STOKES_COMPONENTS") );
  addNode( new Attribute<bool>(group(), "COMPLEX_VOLTAGES") );
  addNode( new Attribute<string>(group(), "SIGNAL_SUM") );
}

Attribute<unsigned> BF_BeamGroup::nofStations()
{
  return getNode("NOF_STATIONS");
}

Attribute< vector<string> > BF_BeamGroup::stationsList()
{
  return getNode("STATIONS_LIST");
}

Attribute<double> BF_BeamGroup::pointRA()
{
  return getNode("POINT_RA");
}

Attribute<double> BF_BeamGroup::pointDEC()
{
  return getNode("POINT_DEC");
}

Attribute<double> BF_BeamGroup::pointOffsetRA()
{
  return getNode("POINT_OFFSET_RA");
}

Attribute<double> BF_BeamGroup::pointOffsetDEC()
{
  return getNode("POINT_OFFSET_DEC");
}

Attribute<double> BF_BeamGroup::beamDiameterRA()
{
  return getNode("BEAM_DIAMETER_RA");
}

Attribute<double> BF_BeamGroup::beamDiameterDEC()
{
  return getNode("BEAM_DIAMETER_DEC");
}

Attribute<double> BF_BeamGroup::beamFrequencyCenter()
{
  return getNode("BEAM_FREQUENCY_CENTER");
}

Attribute<string> BF_BeamGroup::beamFrequencyCenterUnit()
{
  return getNode("BEAM_FREQUENCY_CENTER_UNIT");
}

Attribute<bool> BF_BeamGroup::foldedData()
{
  return getNode("FOLDED_DATA");
}

Attribute<double> BF_BeamGroup::foldPeriod()
{
  return getNode("FOLD_PERIOD");
}

Attribute<string> BF_BeamGroup::foldPeriodUnit()
{
  return getNode("FOLD_PERIOD_UNIT");
}

Attribute<string> BF_BeamGroup::dedispersion()
{
  return getNode("DEDISPERSION");
}

Attribute<double> BF_BeamGroup::dedispersionMeasure()
{
  return getNode("DEDISPERSION_MEASURE");
}

Attribute<string> BF_BeamGroup::dedispersionMeasureUnit()
{
  return getNode("DEDISPERSION_MEASURE_UNIT");
}

Attribute<bool> BF_BeamGroup::barycentered()
{
  return getNode("BARYCENTERED");
}

Attribute<unsigned> BF_BeamGroup::nofStokes()
{
  return getNode("NOF_STOKES");
}

Attribute< vector<string> > BF_BeamGroup::stokesComponents()
{
  return getNode("STOKES_COMPONENTS");
}

Attribute<bool> BF_BeamGroup::complexVoltages()
{
  return getNode("COMPLEX_VOLTAGES");
}

Attribute<string> BF_BeamGroup::signalSum()
{
  return getNode("SIGNAL_SUM");
}

string BF_BeamGroup::stokesName( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "STOKES_%01u", nr);

  return string(buf);
}

string BF_BeamGroup::coordinatesName()
{
  return "COORDINATES";
}

BF_StokesDataset BF_BeamGroup::stokes( unsigned nr )
{
  return BF_StokesDataset(group(), stokesName(nr));
}

CoordinatesGroup BF_BeamGroup::coordinates()
{
  return CoordinatesGroup(group(), coordinatesName());
}

void BF_StokesDataset::initNodes()
{
  addNode( new Attribute<string>(group(), "STOKES_COMPONENT") );
  addNode( new Attribute< vector<unsigned> >(group(), "NOF_CHANNELS") );
  addNode( new Attribute<unsigned>(group(), "NOF_SUBBANDS") );
  addNode( new Attribute<unsigned>(group(), "NOF_SAMPLES") );
}

Attribute<string> BF_StokesDataset::stokesComponent()
{
  return getNode("STOKES_COMPONENT");
}

Attribute< vector<unsigned> > BF_StokesDataset::nofChannels()
{
  return getNode("NOF_CHANNELS");
}

Attribute<unsigned> BF_StokesDataset::nofSubbands()
{
  return getNode("NOF_SUBBANDS");
}

Attribute<unsigned> BF_StokesDataset::nofSamples()
{
  return getNode("NOF_SAMPLES");
}

}

