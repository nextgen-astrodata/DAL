#include "TBB_File.h"

using namespace std;

namespace LDA {

TBB_File::TBB_File( const string &filename, enum HDF5FileBase::fileMode mode )
:
  CommonAttributesFile(filename, mode)
{
}

TBB_Station TBB_File::station( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "Station_%03u", nr);

  return TBB_Station(group(), string(buf));
}

Attribute<string> TBB_File::triggerType()
{
  return Attribute<string>(group(), "TRIGGER_TYPE");
}

TBB_Trigger TBB_File::triggerData()
{
  char buf[128];
  snprintf(buf, sizeof buf, "TRIGGER_DATA");

  const string type =
    triggerType().exists()
        ? triggerType().get()
        : "";

  if (type == "Unknown") {
    return TBB_UnknownTrigger(group(), string(buf));
  }

  // unknown type
  return TBB_Trigger(group(), string(buf));
}

TBB_SysLog TBB_File::sysLog()
{
  return TBB_SysLog(group(), "SYS_LOG");
}

Attribute<string> TBB_Station::stationName()
{
  return Attribute<string>(group(), "STATION_NAME");
}

Attribute< vector<double> > TBB_Station::stationPositionValue()
{
  return Attribute< vector<double> >(group(), "STATION_POSITION_VALUE");
}

Attribute< vector<string> > TBB_Station::stationPositionUnit()
{
  return Attribute< vector<string> >(group(), "STATION_POSITION_UNIT");
}

Attribute<string> TBB_Station::stationPositionFrame()
{
  return Attribute<string>(group(), "STATION_POSITION_FRAME");
}

Attribute< vector<double> > TBB_Station::beamDirectionValue()
{
  return Attribute< vector<double> >(group(), "BEAM_DIRECTION_VALUE");
}

Attribute< vector<string> > TBB_Station::beamDirectionUnit()
{
  return Attribute< vector<string> >(group(), "BEAM_DIRECTION_UNIT");
}

Attribute<string> TBB_Station::beamDirectionFrame()
{
  return Attribute<string>(group(), "BEAM_DIRECTION_FRAME");
}

Attribute<double> TBB_Station::clockOffsetValue()
{
  return Attribute<double>(group(), "CLOCK_OFFSET_VALUE");
}

Attribute<string> TBB_Station::clockOffsetUnit()
{
  return Attribute<string>(group(), "CLOCK_OFFSET_UNIT");
}

Attribute<double> TBB_Station::triggerOffset()
{
  return Attribute<double>(group(), "TRIGGER_OFFSET");
}

Attribute<unsigned> TBB_Station::nofDipoles()
{
  return Attribute<unsigned>(group(), "NOF_DIPOLES");
}

TBB_DipoleDataset TBB_Station::dipole( unsigned station, unsigned rsp, unsigned rcu )
{
  char buf[128];
  snprintf(buf, sizeof buf, "Dipole_%03u%03u%03u", station, rsp, rcu);

  return TBB_DipoleDataset(group(), string(buf));
}

Attribute<unsigned> TBB_DipoleDataset::stationID()
{
  return Attribute<unsigned>(group(), "STATION_ID");
}

Attribute<unsigned> TBB_DipoleDataset::rspID()
{
  return Attribute<unsigned>(group(), "RSP_ID");
}

Attribute<unsigned> TBB_DipoleDataset::rcuID()
{
  return Attribute<unsigned>(group(), "RCU_ID");
}

Attribute<double> TBB_DipoleDataset::sampleFrequencyValue()
{
  return Attribute<double>(group(), "SAMPLE_FREQUENCY_VALUE");
}

Attribute<string> TBB_DipoleDataset::sampleFrequencyUnit()
{
  return Attribute<string>(group(), "SAMPLE_FREQUENCY_UNIT");
}

Attribute<unsigned> TBB_DipoleDataset::time()
{
  return Attribute<unsigned>(group(), "TIME");
}

Attribute<unsigned> TBB_DipoleDataset::sampleNumber()
{
  return Attribute<unsigned>(group(), "SAMPLE_NUMBER");
}

Attribute<unsigned> TBB_DipoleDataset::samplesPerFrame()
{
  return Attribute<unsigned>(group(), "SAMPLES_PER_FRAME");
}

Attribute<unsigned> TBB_DipoleDataset::dataLength()
{
  return Attribute<unsigned>(group(), "DATA_LENGTH");
}

Attribute<unsigned> TBB_DipoleDataset::nyquistZone()
{
  return Attribute<unsigned>(group(), "NYQUIST_ZONE");
}

Attribute<double> TBB_DipoleDataset::ADC2Voltage()
{
  return Attribute<double>(group(), "ADC2VOLTAGE");
}

Attribute<double> TBB_DipoleDataset::cableDelay()
{
  return Attribute<double>(group(), "CABLE_DELAY");
}

Attribute<string> TBB_DipoleDataset::cableDelayUnit()
{
  return Attribute<string>(group(), "CABLE_DELAY_UNIT");
}

Attribute<string> TBB_DipoleDataset::feed()
{
  return Attribute<string>(group(), "FEED");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaPositionValue()
{
  return Attribute< vector<double> >(group(), "ANTENNA_POSITION_VALUE");
}

Attribute<string> TBB_DipoleDataset::antennaPositionUnit()
{
  return Attribute<string>(group(), "ANTENNA_POSITION_UNIT");
}

Attribute<string> TBB_DipoleDataset::antennaPositionFrame()
{
  return Attribute<string>(group(), "ANTENNA_POSITION_FRAME");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaOrientationValue()
{
  return Attribute< vector<double> >(group(), "ANTENNA_ORIENTATION_VALUE");
}

Attribute<string> TBB_DipoleDataset::antennaOrientationUnit()
{
  return Attribute<string>(group(), "ANTENNA_ORIENTATION_UNIT");
}

Attribute<string> TBB_DipoleDataset::antennaOrientationFrame()
{
  return Attribute<string>(group(), "ANTENNA_ORIENTATION_FRAME");
}

Attribute< vector<double> > TBB_DipoleDataset::tileBeamValue()
{
  return Attribute< vector<double> >(group(), "TILE_BEAM_VALUE");
}

Attribute<string> TBB_DipoleDataset::tileBeamUnit()
{
  return Attribute<string>(group(), "TILE_BEAM_UNIT");
}

Attribute<string> TBB_DipoleDataset::tileBeamFrame()
{
  return Attribute<string>(group(), "TILE_BEAM_FRAME");
}

Attribute<string> TBB_DipoleDataset::tileCoefUnit()
{
  return Attribute<string>(group(), "TILE_COEF_UNIT");
}

Attribute< vector<unsigned> > TBB_DipoleDataset::tileBeamCoefs()
{
  return Attribute< vector<unsigned> >(group(), "TILE_BEAM_COEFS");
}

Attribute< vector<double> > TBB_DipoleDataset::tileDipolePositionValue()
{
  return Attribute< vector<double> >(group(), "TILE_DIPOLE_POSITION_VALUE");
}

Attribute<string> TBB_DipoleDataset::tileDipolePositionUnit()
{
  return Attribute<string>(group(), "TILE_DIPOLE_POSITION_UNIT");
}

Attribute<string> TBB_DipoleDataset::tileDipolePositionFrame()
{
  return Attribute<string>(group(), "TILE_DIPOLE_POSITION_FRAME");
}

Attribute<string> TBB_UnknownTrigger::metadata()
{
  return Attribute<string>(group(), "METADATA");
}

Attribute<string> TBB_VHECRTrigger::triggerSource()
{
  return Attribute<string>(group(), "TRIGGER_SOURCE");
}

Attribute<unsigned> TBB_VHECRTrigger::triggerTime()
{
  return Attribute<unsigned>(group(), "TRIGGER_TIME");
}

Attribute<unsigned> TBB_VHECRTrigger::triggerSampleNumber()
{
  return Attribute<unsigned>(group(), "TRIGGER_SAMPLE_NUMBER");
}

Attribute<unsigned> TBB_VHECRTrigger::paramCoincidenceChannels()
{
  return Attribute<unsigned>(group(), "PARAM_COINCIDENCE_CHANNELS");
}

Attribute<double> TBB_VHECRTrigger::paramCoincidenceTime()
{
  return Attribute<double>(group(), "PARAM_COINCIDENCE_TIME");
}

Attribute<string> TBB_VHECRTrigger::paramDirectionFit()
{
  return Attribute<string>(group(), "PARAM_DIRECTION_FIT");
}

Attribute<double> TBB_VHECRTrigger::paramElevationMin()
{
  return Attribute<double>(group(), "PARAM_ELEVATION_MIN");
}

Attribute<double> TBB_VHECRTrigger::paramFitVarianceMax()
{
  return Attribute<double>(group(), "PARAM_FIT_VARIANCE_MAX");
}

Attribute<unsigned> TBB_VHECRTrigger::coincidenceChannels()
{
  return Attribute<unsigned>(group(), "COINCIDENCE_CHANNELS");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::rcuID()
{
  return Attribute< vector<unsigned> >(group(), "RCU_ID");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::time()
{
  return Attribute< vector<unsigned> >(group(), "TIME");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::sampleNumber()
{
  return Attribute< vector<unsigned> >(group(), "SAMPLE_NUMBER");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulseSum()
{
  return Attribute< vector<unsigned> >(group(), "PULSE_SUM");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulseWidth()
{
  return Attribute< vector<unsigned> >(group(), "PULSE_WIDTH");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePeak()
{
  return Attribute< vector<unsigned> >(group(), "PULSE_PEAK");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePowerPre()
{
  return Attribute< vector<unsigned> >(group(), "PULSE_POWER_PRE");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePowerPost()
{
  return Attribute< vector<unsigned> >(group(), "PULSE_POWER_POST");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::nofMissedTriggers()
{
  return Attribute< vector<unsigned> >(group(), "NOF_MISSED_TRIGGERS");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionAzimuth()
{
  return Attribute<double>(group(), "FIT_DIRECTION_AZIMUTH");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionElevation()
{
  return Attribute<double>(group(), "FIT_DIRECTION_ELEVATION");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionDistance()
{
  return Attribute<double>(group(), "FIT_DIRECTION_DISTANCE");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionVariance()
{
  return Attribute<double>(group(), "FIT_DIRECTION_VARIANCE");
}

}

