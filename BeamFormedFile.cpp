#include "BeamFormedFile.h"

using namespace std;

BeamFormedFile::BeamFormedFile( const string &filename, enum HDF5File::fileMode mode )
:
  CLAFile(filename, mode)
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

SAPGroup BeamFormedFile::subArrayPointing( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "SUB_ARRAY_POINTING_%03u", nr);

  return SAPGroup(group(), string(buf));
}

SysLogGroup BeamFormedFile::sysLog()
{
  return SysLogGroup(group(), "SYS_LOG");
}

Attribute<bool> ProcessHistoryGroup::parsetObs()
{
  return Attribute<bool>(group(), "PARSET_OBS");
}

Attribute<bool> ProcessHistoryGroup::logPresto()
{
  return Attribute<bool>(group(), "LOG_PRESTO");
}

Attribute<bool> ProcessHistoryGroup::parFile()
{
  return Attribute<bool>(group(), "PARFILE");
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

CoordinatesGroup BeamGroup::coordinates()
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

CoordinateTypeGroup CoordinatesGroup::coordinate( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "COORDINATE_%01u", nr);

  return CoordinateTypeGroup(group(), string(buf));
}

Attribute<string> CoordinateTypeGroup::coordinateType()
{
  return Attribute<string>(group(), "COORDINATE_TYPE");
}

AttributeV<string> CoordinateTypeGroup::storageType()
{
  return AttributeV<string>(group(), "STORAGE_TYPE");
}

Attribute<unsigned> CoordinateTypeGroup::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

AttributeV<string> CoordinateTypeGroup::axisNames()
{
  return AttributeV<string>(group(), "AXIS_NAMES");
}

AttributeV<string> CoordinateTypeGroup::axisUnits()
{
  return AttributeV<string>(group(), "AXIS_UNITS");
}

AttributeV<double> CoordinateTypeGroup::referenceValue()
{
  return AttributeV<double>(group(), "REFERENCE_VALUE");
}

AttributeV<double> CoordinateTypeGroup::referencePixel()
{
  return AttributeV<double>(group(), "REFERENCE_PIXEL");
}

AttributeV<double> CoordinateTypeGroup::increment()
{
  return AttributeV<double>(group(), "INCREMENT");
}

AttributeV<double> CoordinateTypeGroup::pc()
{
  return AttributeV<double>(group(), "PC");
}

AttributeV<double> CoordinateTypeGroup::axisValuesPixel()
{
  return AttributeV<double>(group(), "AXIS_VALUES_PIXEL");
}

AttributeV<double> CoordinateTypeGroup::axisValuesWorld()
{
  return AttributeV<double>(group(), "AXIS_VALUES_WORLD");
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

