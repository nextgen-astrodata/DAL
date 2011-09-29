#include "BeamFormedFile.h"

using namespace std;

BeamFormedFile::BeamFormedFile( const string &filename, enum HDF5File::fileMode mode )
:
  CommonAttributesFile(filename, mode)
{
}

Attribute<string> BeamFormedFile::createOfflineOnline()
{
  return Attribute<string>(group(), "CREATE_OFFLINE_ONLINE");
}

Attribute<string> BeamFormedFile::BFFormat()
{
  return Attribute<string>(group(), "BF_FORMAT");
}

Attribute<string> BeamFormedFile::BFVersion()
{
  return Attribute<string>(group(), "BF_VERSION");
}

Attribute<string> BeamFormedFile::expTimeStartUTC()
{
  return Attribute<string>(group(), "EXPTIME_START_UTC");
}

Attribute<double> BeamFormedFile::expTimeStartMJD()
{
  return Attribute<double>(group(), "EXPTIME_START_MJD");
}

Attribute<string> BeamFormedFile::expTimeStartTAI()
{
  return Attribute<string>(group(), "EXPTIME_START_TAI");
}

Attribute<string> BeamFormedFile::expTimeEndUTC()
{
  return Attribute<string>(group(), "EXPTIME_END_UTC");
}

Attribute<double> BeamFormedFile::expTimeEndMJD()
{
  return Attribute<double>(group(), "EXPTIME_END_MJD");
}

Attribute<string> BeamFormedFile::expTimeEndTAI()
{
  return Attribute<string>(group(), "EXPTIME_END_TAI");
}

Attribute<double> BeamFormedFile::totalIntegrationTime()
{
  return Attribute<double>(group(), "TOTAL_INTEGRATION_TIME");
}

Attribute<string> BeamFormedFile::observationDatatype()
{
  return Attribute<string>(group(), "OBSERVATION_DATATYPE");
}

Attribute<double> BeamFormedFile::subArrayPointingDiameter()
{
  return Attribute<double>(group(), "SUB_ARRAY_POINTING_DIAMETER");
}

Attribute<double> BeamFormedFile::bandwidth()
{
  return Attribute<double>(group(), "BANDWIDTH");
}

Attribute<double> BeamFormedFile::beamDiameter()
{
  return Attribute<double>(group(), "BEAM_DIAMETER");
}

AttributeV<double> BeamFormedFile::weatherTemperature()
{
  return AttributeV<double>(group(), "WEATHER_TEMPERATURE");
}

AttributeV<double> BeamFormedFile::weatherHumidity()
{
  return AttributeV<double>(group(), "WEATHER_HUMIDITY");
}

AttributeV<double> BeamFormedFile::systemTemperature()
{
  return AttributeV<double>(group(), "SYSTEM_TEMPERATURE");
}

Attribute<unsigned> BeamFormedFile::nofSubArrayPointings()
{
  return Attribute<unsigned>(group(), "NOF_SUB_ARRAY_POINTINGS");
}

BF_SubArrayPointing BeamFormedFile::subArrayPointing( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "SUB_ARRAY_POINTING_%03u", nr);

  return BF_SubArrayPointing(group(), string(buf));
}

SysLog BeamFormedFile::sysLog()
{
  return SysLog(group(), "SYS_LOG");
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

AttributeV<string> BF_SubArrayPointing::stationsList()
{
  return AttributeV<string>(group(), "STATIONS_LIST");
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

BF_BeamGroup BF_SubArrayPointing::beam( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "BEAM_%03u", nr);

  return BF_BeamGroup(group(), string(buf));
}

Attribute<unsigned> BF_BeamGroup::nofStations()
{
  return Attribute<unsigned>(group(), "NOF_STATIONS");
}

AttributeV<string> BF_BeamGroup::stationsList()
{
  return AttributeV<string>(group(), "STATIONS_LIST");
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

Attribute<unsigned> BF_BeamGroup::nofStokes()
{
  return Attribute<unsigned>(group(), "NOF_STOKES");
}

AttributeV<string> BF_BeamGroup::stokesComponents()
{
  return AttributeV<string>(group(), "STOKES_COMPONENTS");
}

Attribute<bool> BF_BeamGroup::complexVoltages()
{
  return Attribute<bool>(group(), "COMPLEX_VOLTAGES");
}

Attribute<string> BF_BeamGroup::signalSum()
{
  return Attribute<string>(group(), "SIGNAL_SUM");
}

BF_StokesDataset BF_BeamGroup::stokes( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "STOKES_%01u", nr);

  return BF_StokesDataset(group(), string(buf));
}

CoordinatesGroup BF_BeamGroup::coordinates()
{
  return CoordinatesGroup(group(), "COORDINATES");
}

AttributeV<double> CoordinatesGroup::refLocationValue()
{
  return AttributeV<double>(group(), "REF_LOCATION_VALUE");
}

AttributeV<string> CoordinatesGroup::refLocationUnit()
{
  return AttributeV<string>(group(), "REF_LOCATION_UNIT");
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

AttributeV<string> CoordinatesGroup::coordinateTypes()
{
  return AttributeV<string>(group(), "COORDINATE_TYPES");
}

Coordinate CoordinatesGroup::coordinate( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "COORDINATE_%01u", nr);

  const vector<string> types =
    coordinateTypes().exists()
        ? coordinateTypes().get()
        : vector<string>();

  if (types.size() > nr) {
    if (types[nr] == "Time") {
      return TimeCoordinate(group(), string(buf));
    }

    if (types[nr] == "Spectral") {
      return SpectralCoordinate(group(), string(buf));
    }
  }  

  // unknown type
  return Coordinate(group(), string(buf));
}

Attribute<string> Coordinate::coordinateType()
{
  return Attribute<string>(group(), "COORDINATE_TYPE");
}

AttributeV<string> Coordinate::storageType()
{
  return AttributeV<string>(group(), "STORAGE_TYPE");
}

Attribute<unsigned> Coordinate::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

AttributeV<string> Coordinate::axisNames()
{
  return AttributeV<string>(group(), "AXIS_NAMES");
}

AttributeV<string> Coordinate::axisUnits()
{
  return AttributeV<string>(group(), "AXIS_UNITS");
}

AttributeV<double> Coordinate::referenceValue()
{
  return AttributeV<double>(group(), "REFERENCE_VALUE");
}

AttributeV<double> Coordinate::referencePixel()
{
  return AttributeV<double>(group(), "REFERENCE_PIXEL");
}

AttributeV<double> Coordinate::increment()
{
  return AttributeV<double>(group(), "INCREMENT");
}

AttributeV<double> Coordinate::pc()
{
  return AttributeV<double>(group(), "PC");
}

AttributeV<double> Coordinate::axisValuesPixel()
{
  return AttributeV<double>(group(), "AXIS_VALUES_PIXEL");
}

AttributeV<double> Coordinate::axisValuesWorld()
{
  return AttributeV<double>(group(), "AXIS_VALUES_WORLD");
}

Attribute<string> BF_StokesDataset::stokesComponent()
{
  return Attribute<string>(group(), "STOKES_COMPONENT");
}

AttributeV<unsigned> BF_StokesDataset::nofChannels()
{
  return AttributeV<unsigned>(group(), "NOF_CHANNELS");
}

Attribute<unsigned> BF_StokesDataset::nofSubbands()
{
  return Attribute<unsigned>(group(), "NOF_SUBBANDS");
}

Attribute<unsigned> BF_StokesDataset::nofSamples()
{
  return Attribute<unsigned>(group(), "NOF_SAMPLES");
}

