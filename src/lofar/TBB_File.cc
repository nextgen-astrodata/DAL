#include "TBB_File.h"

using namespace std;

namespace DAL {

TBB_File::TBB_File( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  CommonAttributesFile(filename, mode)
{
}

vector<TBB_Station> TBB_File::stations()
{
  const string stPrefix("STATION_");
  vector<TBB_Station> stationGroups;
  vector<string> membNames(memberNames());

  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be stations and fill the vector with objects of the right type.
    if (it->find(stPrefix) == 0) {
      stationGroups.push_back(station(it->substr(stPrefix.size())));
    }
  }

  return stationGroups;
}

TBB_Station TBB_File::station( const string &stationName )
{
  return TBB_Station(*this, "STATION_" + stationName);
}

Attribute<string> TBB_File::triggerType()
{
  return Attribute<string>(*this, "TRIGGER_TYPE");
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
    return TBB_UnknownTrigger(*this, string(buf));
  }

  // unknown type
  return TBB_Trigger(*this, string(buf));
}

TBB_SysLog TBB_File::sysLog()
{
  return TBB_SysLog(*this, "SYS_LOG");
}

Attribute<string> TBB_Station::stationName()
{
  return Attribute<string>(*this, "STATION_NAME");
}

Attribute< vector<double> > TBB_Station::stationPositionValue()
{
  return Attribute< vector<double> >(*this, "STATION_POSITION_VALUE");
}

Attribute< vector<string> > TBB_Station::stationPositionUnit()
{
  return Attribute< vector<string> >(*this, "STATION_POSITION_UNIT");
}

Attribute<string> TBB_Station::stationPositionFrame()
{
  return Attribute<string>(*this, "STATION_POSITION_FRAME");
}

Attribute< vector<double> > TBB_Station::beamDirectionValue()
{
  return Attribute< vector<double> >(*this, "BEAM_DIRECTION_VALUE");
}

Attribute< vector<string> > TBB_Station::beamDirectionUnit()
{
  return Attribute< vector<string> >(*this, "BEAM_DIRECTION_UNIT");
}

Attribute<string> TBB_Station::beamDirectionFrame()
{
  return Attribute<string>(*this, "BEAM_DIRECTION_FRAME");
}

Attribute<double> TBB_Station::clockOffsetValue()
{
  return Attribute<double>(*this, "CLOCK_OFFSET_VALUE");
}

Attribute<string> TBB_Station::clockOffsetUnit()
{
  return Attribute<string>(*this, "CLOCK_OFFSET_UNIT");
}

Attribute<double> TBB_Station::triggerOffset()
{
  return Attribute<double>(*this, "TRIGGER_OFFSET");
}

vector<TBB_DipoleDataset> TBB_Station::dipoles()
{
  const string dpPrefix("DIPOLE_");
  vector<TBB_DipoleDataset> dipoleDatasets;

  vector<string> membNames(memberNames());
  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be dipoles and fill the vector with objects of the right type.
    if (it->find(dpPrefix) == 0) {
      dipoleDatasets.push_back(dipole(it->substr(dpPrefix.size())));
    }
  }

  return dipoleDatasets;
}

TBB_DipoleDataset TBB_Station::dipole( const string &dipoleName )
{
  return TBB_DipoleDataset(*this, "DIPOLE_" + dipoleName);
}

Attribute<unsigned> TBB_DipoleDataset::stationID()
{
  return Attribute<unsigned>(*this, "STATION_ID");
}

Attribute<unsigned> TBB_DipoleDataset::rspID()
{
  return Attribute<unsigned>(*this, "RSP_ID");
}

Attribute<unsigned> TBB_DipoleDataset::rcuID()
{
  return Attribute<unsigned>(*this, "RCU_ID");
}

Attribute<double> TBB_DipoleDataset::sampleFrequencyValue()
{
  return Attribute<double>(*this, "SAMPLE_FREQUENCY_VALUE");
}

Attribute<string> TBB_DipoleDataset::sampleFrequencyUnit()
{
  return Attribute<string>(*this, "SAMPLE_FREQUENCY_UNIT");
}

Attribute<unsigned> TBB_DipoleDataset::time()
{
  return Attribute<unsigned>(*this, "TIME");
}

Attribute<unsigned> TBB_DipoleDataset::sampleNumber()
{
  return Attribute<unsigned>(*this, "SAMPLE_NUMBER");
}

Attribute<unsigned> TBB_DipoleDataset::samplesPerFrame()
{
  return Attribute<unsigned>(*this, "SAMPLES_PER_FRAME");
}

Attribute<unsigned> TBB_DipoleDataset::dataLength()
{
  return Attribute<unsigned>(*this, "DATA_LENGTH");
}

Attribute<unsigned> TBB_DipoleDataset::nyquistZone()
{
  return Attribute<unsigned>(*this, "NYQUIST_ZONE");
}

Attribute<double> TBB_DipoleDataset::ADC2Voltage()
{
  return Attribute<double>(*this, "ADC2VOLTAGE");
}

Attribute<double> TBB_DipoleDataset::cableDelay()
{
  return Attribute<double>(*this, "CABLE_DELAY");
}

Attribute<string> TBB_DipoleDataset::cableDelayUnit()
{
  return Attribute<string>(*this, "CABLE_DELAY_UNIT");
}

Attribute<string> TBB_DipoleDataset::feed()
{
  return Attribute<string>(*this, "FEED");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaPositionValue()
{
  return Attribute< vector<double> >(*this, "ANTENNA_POSITION_VALUE");
}

Attribute<string> TBB_DipoleDataset::antennaPositionUnit()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_UNIT");
}

Attribute<string> TBB_DipoleDataset::antennaPositionFrame()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_FRAME");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaOrientationValue()
{
  return Attribute< vector<double> >(*this, "ANTENNA_ORIENTATION_VALUE");
}

Attribute<string> TBB_DipoleDataset::antennaOrientationUnit()
{
  return Attribute<string>(*this, "ANTENNA_ORIENTATION_UNIT");
}

Attribute<string> TBB_DipoleDataset::antennaOrientationFrame()
{
  return Attribute<string>(*this, "ANTENNA_ORIENTATION_FRAME");
}

Attribute< vector<double> > TBB_DipoleDataset::tileBeamValue()
{
  return Attribute< vector<double> >(*this, "TILE_BEAM_VALUE");
}

Attribute<string> TBB_DipoleDataset::tileBeamUnit()
{
  return Attribute<string>(*this, "TILE_BEAM_UNIT");
}

Attribute<string> TBB_DipoleDataset::tileBeamFrame()
{
  return Attribute<string>(*this, "TILE_BEAM_FRAME");
}

Attribute<string> TBB_DipoleDataset::tileCoefUnit()
{
  return Attribute<string>(*this, "TILE_COEF_UNIT");
}

Attribute< vector<unsigned> > TBB_DipoleDataset::tileBeamCoefs()
{
  return Attribute< vector<unsigned> >(*this, "TILE_BEAM_COEFS");
}

Attribute< vector<double> > TBB_DipoleDataset::tileDipolePositionValue()
{
  return Attribute< vector<double> >(*this, "TILE_DIPOLE_POSITION_VALUE");
}

Attribute<string> TBB_DipoleDataset::tileDipolePositionUnit()
{
  return Attribute<string>(*this, "TILE_DIPOLE_POSITION_UNIT");
}

Attribute<string> TBB_DipoleDataset::tileDipolePositionFrame()
{
  return Attribute<string>(*this, "TILE_DIPOLE_POSITION_FRAME");
}

Attribute<string> TBB_UnknownTrigger::metadata()
{
  return Attribute<string>(*this, "METADATA");
}

Attribute<string> TBB_VHECRTrigger::triggerSource()
{
  return Attribute<string>(*this, "TRIGGER_SOURCE");
}

Attribute<unsigned> TBB_VHECRTrigger::triggerTime()
{
  return Attribute<unsigned>(*this, "TRIGGER_TIME");
}

Attribute<unsigned> TBB_VHECRTrigger::triggerSampleNumber()
{
  return Attribute<unsigned>(*this, "TRIGGER_SAMPLE_NUMBER");
}

Attribute<unsigned> TBB_VHECRTrigger::paramCoincidenceChannels()
{
  return Attribute<unsigned>(*this, "PARAM_COINCIDENCE_CHANNELS");
}

Attribute<double> TBB_VHECRTrigger::paramCoincidenceTime()
{
  return Attribute<double>(*this, "PARAM_COINCIDENCE_TIME");
}

Attribute<string> TBB_VHECRTrigger::paramDirectionFit()
{
  return Attribute<string>(*this, "PARAM_DIRECTION_FIT");
}

Attribute<double> TBB_VHECRTrigger::paramElevationMin()
{
  return Attribute<double>(*this, "PARAM_ELEVATION_MIN");
}

Attribute<double> TBB_VHECRTrigger::paramFitVarianceMax()
{
  return Attribute<double>(*this, "PARAM_FIT_VARIANCE_MAX");
}

Attribute<unsigned> TBB_VHECRTrigger::coincidenceChannels()
{
  return Attribute<unsigned>(*this, "COINCIDENCE_CHANNELS");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::rcuID()
{
  return Attribute< vector<unsigned> >(*this, "RCU_ID");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::time()
{
  return Attribute< vector<unsigned> >(*this, "TIME");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::sampleNumber()
{
  return Attribute< vector<unsigned> >(*this, "SAMPLE_NUMBER");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulseSum()
{
  return Attribute< vector<unsigned> >(*this, "PULSE_SUM");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulseWidth()
{
  return Attribute< vector<unsigned> >(*this, "PULSE_WIDTH");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePeak()
{
  return Attribute< vector<unsigned> >(*this, "PULSE_PEAK");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePowerPre()
{
  return Attribute< vector<unsigned> >(*this, "PULSE_POWER_PRE");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::pulsePowerPost()
{
  return Attribute< vector<unsigned> >(*this, "PULSE_POWER_POST");
}

Attribute< vector<unsigned> > TBB_VHECRTrigger::nofMissedTriggers()
{
  return Attribute< vector<unsigned> >(*this, "NOF_MISSED_TRIGGERS");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionAzimuth()
{
  return Attribute<double>(*this, "FIT_DIRECTION_AZIMUTH");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionElevation()
{
  return Attribute<double>(*this, "FIT_DIRECTION_ELEVATION");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionDistance()
{
  return Attribute<double>(*this, "FIT_DIRECTION_DISTANCE");
}

Attribute<double> TBB_VHECRTrigger::fitDirectionVariance()
{
  return Attribute<double>(*this, "FIT_DIRECTION_VARIANCE");
}

}

