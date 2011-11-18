#include "BF_File.h"

using namespace std;

namespace LDA {

BF_File::BF_File( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  CommonAttributesFile(filename, mode)
{
}

Attribute<string> BF_File::createOfflineOnline()
{
  return Attribute<string>(group(), "CREATE_OFFLINE_ONLINE");
}

Attribute<string> BF_File::BFFormat()
{
  return Attribute<string>(group(), "BF_FORMAT");
}

Attribute<string> BF_File::BFVersion()
{
  return Attribute<string>(group(), "BF_VERSION");
}

Attribute<string> BF_File::expTimeStartUTC()
{
  return Attribute<string>(group(), "EXPTIME_START_UTC");
}

Attribute<double> BF_File::expTimeStartMJD()
{
  return Attribute<double>(group(), "EXPTIME_START_MJD");
}

Attribute<string> BF_File::expTimeStartTAI()
{
  return Attribute<string>(group(), "EXPTIME_START_TAI");
}

Attribute<string> BF_File::expTimeEndUTC()
{
  return Attribute<string>(group(), "EXPTIME_END_UTC");
}

Attribute<double> BF_File::expTimeEndMJD()
{
  return Attribute<double>(group(), "EXPTIME_END_MJD");
}

Attribute<string> BF_File::expTimeEndTAI()
{
  return Attribute<string>(group(), "EXPTIME_END_TAI");
}

Attribute<double> BF_File::totalIntegrationTime()
{
  return Attribute<double>(group(), "TOTAL_INTEGRATION_TIME");
}

Attribute<string> BF_File::observationDatatype()
{
  return Attribute<string>(group(), "OBSERVATION_DATATYPE");
}

Attribute<double> BF_File::subArrayPointingDiameter()
{
  return Attribute<double>(group(), "SUB_ARRAY_POINTING_DIAMETER");
}

Attribute<double> BF_File::bandwidth()
{
  return Attribute<double>(group(), "BANDWIDTH");
}

Attribute<double> BF_File::beamDiameter()
{
  return Attribute<double>(group(), "BEAM_DIAMETER");
}

Attribute< vector<double> > BF_File::weatherTemperature()
{
  return Attribute< vector<double> >(group(), "WEATHER_TEMPERATURE");
}

Attribute< vector<double> > BF_File::weatherHumidity()
{
  return Attribute< vector<double> >(group(), "WEATHER_HUMIDITY");
}

Attribute< vector<double> > BF_File::systemTemperature()
{
  return Attribute< vector<double> >(group(), "SYSTEM_TEMPERATURE");
}

Attribute<unsigned> BF_File::nofSubArrayPointings()
{
  return Attribute<unsigned>(group(), "NOF_SUB_ARRAY_POINTINGS");
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

Attribute<bool> BF_ProcessingHistory::parsetObs()
{
  return Attribute<bool>(group(), "PARSET_OBS");
}

Attribute<bool> BF_ProcessingHistory::logPresto()
{
  return Attribute<bool>(group(), "LOG_PRESTO");
}

Attribute<bool> BF_ProcessingHistory::parFile()
{
  return Attribute<bool>(group(), "PARFILE");
}

Attribute<unsigned> BF_SubArrayPointing::nofStations()
{
  return Attribute<unsigned>(group(), "NOF_STATIONS");
}

Attribute< vector<string> > BF_SubArrayPointing::stationsList()
{
  return Attribute< vector<string> >(group(), "STATIONS_LIST");
}

Attribute<double> BF_SubArrayPointing::pointRA()
{
  return Attribute<double>(group(), "POINT_RA");
}

Attribute<double> BF_SubArrayPointing::pointDEC()
{
  return Attribute<double>(group(), "POINT_DEC");
}

Attribute<double> BF_SubArrayPointing::clockRate()
{
  return Attribute<double>(group(), "CLOCK_RATE");
}

Attribute<string> BF_SubArrayPointing::clockRateUnit()
{
  return Attribute<string>(group(), "CLOCK_RATE_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::nofSamples()
{
  return Attribute<unsigned>(group(), "NOF_SAMPLES");
}

Attribute<double> BF_SubArrayPointing::samplingRate()
{
  return Attribute<double>(group(), "SAMPLING_RATE");
}

Attribute<string> BF_SubArrayPointing::samplingRateUnit()
{
  return Attribute<string>(group(), "SAMPLING_RATE_UNIT");
}

Attribute<double> BF_SubArrayPointing::samplingTime()
{
  return Attribute<double>(group(), "SAMPLING_TIME");
}

Attribute<string> BF_SubArrayPointing::samplingTimeUnit()
{
  return Attribute<string>(group(), "SAMPLING_TIME_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::channelsPerSubband()
{
  return Attribute<unsigned>(group(), "CHANNELS_PER_SUBBAND");
}

Attribute<double> BF_SubArrayPointing::subbandWidth()
{
  return Attribute<double>(group(), "SUBBAND_WIDTH");
}

Attribute<string> BF_SubArrayPointing::subbandWidthUnit()
{
  return Attribute<string>(group(), "SUBBAND_WIDTH_UNIT");
}

Attribute<double> BF_SubArrayPointing::channelWidth()
{
  return Attribute<double>(group(), "CHANNEL_WIDTH");
}

Attribute<string> BF_SubArrayPointing::channelWidthUnit()
{
  return Attribute<string>(group(), "CHANNEL_WIDTH_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::nofBeams()
{
  return Attribute<unsigned>(group(), "NOF_BEAMS");
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

Attribute<unsigned> BF_BeamGroup::nofStations()
{
  return Attribute<unsigned>(group(), "NOF_STATIONS");
}

Attribute< vector<string> > BF_BeamGroup::stationsList()
{
  return Attribute< vector<string> >(group(), "STATIONS_LIST");
}

Attribute<double> BF_BeamGroup::pointRA()
{
  return Attribute<double>(group(), "POINT_RA");
}

Attribute<double> BF_BeamGroup::pointDEC()
{
  return Attribute<double>(group(), "POINT_DEC");
}

Attribute<double> BF_BeamGroup::pointOffsetRA()
{
  return Attribute<double>(group(), "POINT_OFFSET_RA");
}

Attribute<double> BF_BeamGroup::pointOffsetDEC()
{
  return Attribute<double>(group(), "POINT_OFFSET_DEC");
}

Attribute<double> BF_BeamGroup::beamDiameterRA()
{
  return Attribute<double>(group(), "BEAM_DIAMETER_RA");
}

Attribute<double> BF_BeamGroup::beamDiameterDEC()
{
  return Attribute<double>(group(), "BEAM_DIAMETER_DEC");
}

Attribute<double> BF_BeamGroup::beamFrequencyCenter()
{
  return Attribute<double>(group(), "BEAM_FREQUENCY_CENTER");
}

Attribute<string> BF_BeamGroup::beamFrequencyCenterUnit()
{
  return Attribute<string>(group(), "BEAM_FREQUENCY_CENTER_UNIT");
}

Attribute<bool> BF_BeamGroup::foldedData()
{
  return Attribute<bool>(group(), "FOLDED_DATA");
}

Attribute<double> BF_BeamGroup::foldPeriod()
{
  return Attribute<double>(group(), "FOLD_PERIOD");
}

Attribute<string> BF_BeamGroup::foldPeriodUnit()
{
  return Attribute<string>(group(), "FOLD_PERIOD_UNIT");
}

Attribute<string> BF_BeamGroup::dedispersion()
{
  return Attribute<string>(group(), "DEDISPERSION");
}

Attribute<double> BF_BeamGroup::dedispersionMeasure()
{
  return Attribute<double>(group(), "DEDISPERSION_MEASURE");
}

Attribute<string> BF_BeamGroup::dedispersionMeasureUnit()
{
  return Attribute<string>(group(), "DEDISPERSION_MEASURE_UNIT");
}

Attribute<bool> BF_BeamGroup::barycenter()
{
  return Attribute<bool>(group(), "BARYCENTER");
}

Attribute<unsigned> BF_BeamGroup::nofStokes()
{
  return Attribute<unsigned>(group(), "NOF_STOKES");
}

Attribute< vector<string> > BF_BeamGroup::stokesComponents()
{
  return Attribute< vector<string> >(group(), "STOKES_COMPONENTS");
}

Attribute<bool> BF_BeamGroup::complexVoltages()
{
  return Attribute<bool>(group(), "COMPLEX_VOLTAGES");
}

Attribute<string> BF_BeamGroup::signalSum()
{
  return Attribute<string>(group(), "SIGNAL_SUM");
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

Attribute< vector<double> > CoordinatesGroup::refLocationValue()
{
  return Attribute< vector<double> >(group(), "REF_LOCATION_VALUE");
}

Attribute< vector<string> > CoordinatesGroup::refLocationUnit()
{
  return Attribute< vector<string> >(group(), "REF_LOCATION_UNIT");
}

Attribute<string> CoordinatesGroup::refLocationFrame()
{
  return Attribute<string>(group(), "REF_LOCATION_FRAME");
}

Attribute<double> CoordinatesGroup::refTimeValue()
{
  return Attribute<double>(group(), "REF_TIME_VALUE");
}

Attribute<string> CoordinatesGroup::refTimeUnit()
{
  return Attribute<string>(group(), "REF_TIME_UNIT");
}

Attribute<string> CoordinatesGroup::refTimeFrame()
{
  return Attribute<string>(group(), "REF_TIME_FRAME");
}

Attribute<unsigned> CoordinatesGroup::nofCoordinates()
{
  return Attribute<unsigned>(group(), "NOF_COORDINATES");
}

Attribute<unsigned> CoordinatesGroup::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

Attribute< vector<string> > CoordinatesGroup::coordinateTypes()
{
  return Attribute< vector<string> >(group(), "COORDINATE_TYPES");
}

string CoordinatesGroup::coordinateName( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "COORDINATE_%01u", nr);

  return string(buf);
}

string CoordinatesGroup::coordinateType( unsigned nr )
{
  if (!coordinateTypes().exists())
    return "";

  const vector<string> types = coordinateTypes().get();

  if (nr >= types.size())
    return "";

  return types[nr];
}

Coordinate CoordinatesGroup::coordinate( unsigned nr )
{
  const string type = coordinateType(nr);
  const string name = coordinateName(nr);

  if (type == "Time")
    return TimeCoordinate(group(), name);

  if (type == "Spectral")
    return SpectralCoordinate(group(), name);

  // unknown type
  return Coordinate(group(), name);
}

Attribute<string> Coordinate::coordinateType()
{
  return Attribute<string>(group(), "COORDINATE_TYPE");
}

Attribute< vector<string> > Coordinate::storageType()
{
  return Attribute< vector<string> >(group(), "STORAGE_TYPE");
}

Attribute<unsigned> Coordinate::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

Attribute< vector<string> > Coordinate::axisNames()
{
  return Attribute< vector<string> >(group(), "AXIS_NAMES");
}

Attribute< vector<string> > Coordinate::axisUnits()
{
  return Attribute< vector<string> >(group(), "AXIS_UNITS");
}

Attribute< vector<double> > Coordinate::referenceValue()
{
  return Attribute< vector<double> >(group(), "REFERENCE_VALUE");
}

Attribute< vector<double> > Coordinate::referencePixel()
{
  return Attribute< vector<double> >(group(), "REFERENCE_PIXEL");
}

Attribute< vector<double> > Coordinate::increment()
{
  return Attribute< vector<double> >(group(), "INCREMENT");
}

Attribute< vector<double> > Coordinate::pc()
{
  return Attribute< vector<double> >(group(), "PC");
}

Attribute< vector<double> > Coordinate::axisValuesPixel()
{
  return Attribute< vector<double> >(group(), "AXIS_VALUES_PIXEL");
}

Attribute< vector<double> > Coordinate::axisValuesWorld()
{
  return Attribute< vector<double> >(group(), "AXIS_VALUES_WORLD");
}

Attribute<string> BF_StokesDataset::stokesComponent()
{
  return Attribute<string>(group(), "STOKES_COMPONENT");
}

Attribute< vector<unsigned> > BF_StokesDataset::nofChannels()
{
  return Attribute< vector<unsigned> >(group(), "NOF_CHANNELS");
}

Attribute<unsigned> BF_StokesDataset::nofSubbands()
{
  return Attribute<unsigned>(group(), "NOF_SUBBANDS");
}

Attribute<unsigned> BF_StokesDataset::nofSamples()
{
  return Attribute<unsigned>(group(), "NOF_SAMPLES");
}

}

