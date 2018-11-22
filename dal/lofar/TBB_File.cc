/* Copyright 2011-2012  ASTRON, Netherlands Institute for Radio Astronomy
 * This file is part of the Data Access Library (DAL).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "TBB_File.h"

using namespace std;

namespace dal {

TBB_File::TBB_File() {}

TBB_File::TBB_File( const std::string &filename, FileMode mode )
:
  CLA_File(filename, mode)
{
  openFile(mode);
}

TBB_File::~TBB_File() {}

void TBB_File::open( const std::string &filename, FileMode mode )
{
  // As long as we have no member vars, keep open() and close() simple. See CLA_File::open().
  CLA_File::open(filename, mode);

  openFile(mode);
}

void TBB_File::close()
{
  CLA_File::close();
}

void TBB_File::openFile( FileMode mode )
{
  initFileNodes();

  if (mode == CREATE || mode == CREATE_EXCL) {
    fileType().create().set("tbb");
    docName() .create().set("ICD 1: TBB Time-Series Data");
    docVersion()       .set(VersionType(3, 3)); // already created by File
  } else {
    bool isTbbFileType = false;
    try {
      isTbbFileType = fileType().get() == "tbb";
    } catch (DALException& ) {
    }
    if (!isTbbFileType) {
      throw DALException("Failed to open TBB file: A TBB file must have FILETYPE=\"tbb\".");
    }

    if (operatingMode().get() == "spectral" && docVersion().get() < VersionType(3, 3)) {
      throw DALException("Invalid version for TBB spectral operating mode.");
    }
  }
}

void TBB_File::initFileNodes() {
  CLA_File::initNodes();
  addNode( new Attribute<string>(*this, "OPERATING_MODE") );
  addNode( new Attribute<unsigned>(*this, "NOF_STATIONS") );
}

Attribute<string> TBB_File::operatingMode()
{
  return Attribute<string>(*this, "OPERATING_MODE");
}

Attribute<unsigned> TBB_File::nofStations()
{
  return Attribute<unsigned>(*this, "NOF_STATIONS");
}

vector<TBB_Station> TBB_File::stations()
{
  const string stPrefix("STATION_");
  vector<TBB_Station> stationGroups;
  vector<string> membNames(memberNames());

  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be stations and fill the vector with objects of the right type.
    if (it->find(stPrefix) == 0) {
      TBB_Station statioGroup(*this, *it);
      if(statioGroup.isHDF5Group()) {
        stationGroups.push_back(statioGroup);
      }
    }
  }

  return stationGroups;
}

TBB_Station TBB_File::station( const std::string &stationName )
{
  return TBB_Station(*this, stationGroupName(stationName));
}

string TBB_File::stationGroupName( const std::string &stationName) {
  return "STATION_" + stationName;
}

TBB_Trigger TBB_File::trigger()
{
  return TBB_Trigger(*this, "TRIGGER");
}


TBB_Trigger::TBB_Trigger( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void TBB_Trigger::initNodes() {
  Group::initNodes();
  addNode( new Attribute<string>(*this, "TRIGGER_TYPE") );
  addNode( new Attribute<int>(*this, "TRIGGER_VERSION") );
  addNode( new Attribute<int>(*this, "PARAM_COINCIDENCE_CHANNELS") );
  addNode( new Attribute<double>(*this, "PARAM_COINCIDENCE_TIME") );
  addNode( new Attribute<string>(*this, "PARAM_DIRECTION_FIT") );
  addNode( new Attribute<double>(*this, "PARAM_ELEVATION_MIN") );
  addNode( new Attribute<double>(*this, "PARAM_FIT_VARIANCE_MAX") );

  // optional parameters for version >= 3.3 "spectral" operatingMode, default to 0.
  // ICD states that non-filled-in parameters should/can be present, and should contain 0 by default.
  addNode( new Attribute<double>(*this, "TRIGGER_DISPERSION_MEASURE") );
  addNode( new Attribute<string>(*this, "TRIGGER_DISPERSION_MEASURE_UNIT") );
  addNode( new Attribute<vector<unsigned> >(*this, "TIME") );
  addNode( new Attribute<vector<unsigned> >(*this, "SAMPLE_NUMBER") );
  addNode( new Attribute<string>(*this, "FIT_DIRECTION_COORDINATE_SYSTEM") );
  addNode( new Attribute<double>(*this, "FIT_DIRECTION_ANGLE1") );
  addNode( new Attribute<double>(*this, "FIT_DIRECTION_ANGLE2") );
  addNode( new Attribute<double>(*this, "FIT_DIRECTION_DISTANCE") );
  addNode( new Attribute<double>(*this, "FIT_DIRECTION_VARIANCE") );
  addNode( new Attribute<double>(*this, "REFERENCE_FREQUENCY") );
  addNode( new Attribute<vector<double> >(*this, "OBSERVATORY_COORDINATES") );
  addNode( new Attribute<string>(*this, "OBSERVATORY_COORDINATES_COORDINATE_SYSTEM") );
  addNode( new Attribute<string>(*this, "TRIGGER_ID") );
  addNode( new Attribute<string>(*this, "ADDITIONAL_INFO") );

}

Attribute<string> TBB_Trigger::triggerType()
{
  return Attribute<string>(*this, "TRIGGER_TYPE");
}

Attribute<int> TBB_Trigger::triggerVersion()
{
  return Attribute<int>(*this, "TRIGGER_VERSION");
}

Attribute<int> TBB_Trigger::paramCoincidenceChannels()
{
  return Attribute<int>(*this, "PARAM_COINCIDENCE_CHANNELS");
}

Attribute<double> TBB_Trigger::paramCoincidenceTime()
{
  return Attribute<double>(*this, "PARAM_COINCIDENCE_TIME");
}

Attribute<string> TBB_Trigger::paramDirectionFit()
{
  return Attribute<string>(*this, "PARAM_DIRECTION_FIT");
}

Attribute<double> TBB_Trigger::paramElevationMin()
{
  return Attribute<double>(*this, "PARAM_ELEVATION_MIN");
}

Attribute<double> TBB_Trigger::paramFitVarianceMax()
{
  return Attribute<double>(*this, "PARAM_FIT_VARIANCE_MAX");
}

Attribute<double> TBB_Trigger::triggerDispersionMeasure()
{
  return Attribute<double>(*this, "TRIGGER_DISPERSION_MEASURE");
}

Attribute<string> TBB_Trigger::triggerDispersionMeasureUnit()
{
  return Attribute<string>(*this, "TRIGGER_DISPERSION_MEASURE_UNIT");
}

Attribute<vector<unsigned> > TBB_Trigger::time()
{
  return Attribute<vector<unsigned> >(*this, "TIME");
}

Attribute<vector<unsigned> > TBB_Trigger::sampleNumber()
{
  return Attribute<vector<unsigned> >(*this, "SAMPLE_NUMBER");
}

Attribute<string> TBB_Trigger::fitDirectionCoordinateSystem()
{
  return Attribute<string>(*this, "FIT_DIRECTION_COORDINATE_SYSTEM");
}

Attribute<double> TBB_Trigger::fitDirectionAngle1()
{
  return Attribute<double>(*this, "FIT_DIRECTION_ANGLE1");
}

Attribute<double> TBB_Trigger::fitDirectionAngle2()
{
  return Attribute<double>(*this, "FIT_DIRECTION_ANGLE2");
}

Attribute<double> TBB_Trigger::fitDirectionDistance()
{
  return Attribute<double>(*this, "FIT_DIRECTION_DISTANCE");
}

Attribute<double> TBB_Trigger::fitDirectionVariance()
{
  return Attribute<double>(*this, "FIT_DIRECTION_VARIANCE");
}

Attribute<double> TBB_Trigger::referenceFrequency()
{
  return Attribute<double>(*this, "REFERENCE_FREQUENCY");
}

Attribute<vector<double> > TBB_Trigger::observatoryCoordinates()
{
  return Attribute<vector<double> >(*this, "OBSERVATORY_COORDINATES");
}

Attribute<string> TBB_Trigger::observatoryCoordinatesCoordinateSystem()
{
  return Attribute<string>(*this, "OBSERVATORY_COORDINATES_COORDINATE_SYSTEM");
}

Attribute<string> TBB_Trigger::triggerId()
{
  return Attribute<string>(*this, "TRIGGER_ID");
}

Attribute<string> TBB_Trigger::additionalInfo()
{
  return Attribute<string>(*this, "ADDITIONAL_INFO");
}

TBB_Station::TBB_Station( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void TBB_Station::initNodes() {
  Group::initNodes();
  addNode( new Attribute<string>(*this, "STATION_NAME") );
  addNode( new Attribute< vector<double> >(*this, "STATION_POSITION") );
  addNode( new Attribute<string>(*this, "STATION_POSITION_UNIT") );
  addNode( new Attribute<string>(*this, "STATION_POSITION_FRAME") );
  addNode( new Attribute< vector<double> >(*this, "BEAM_DIRECTION") );
  addNode( new Attribute<string>(*this, "BEAM_DIRECTION_UNIT") );
  addNode( new Attribute<string>(*this, "BEAM_DIRECTION_FRAME") );
  addNode( new Attribute<double>(*this, "CLOCK_OFFSET") );
  addNode( new Attribute<string>(*this, "CLOCK_OFFSET_UNIT") );
  addNode( new Attribute<unsigned>(*this, "NOF_DIPOLES") );
}

Attribute<string> TBB_Station::stationName()
{
  return Attribute<string>(*this, "STATION_NAME");
}

Attribute< vector<double> > TBB_Station::stationPosition()
{
  return Attribute< vector<double> >(*this, "STATION_POSITION");
}

Attribute<string> TBB_Station::stationPositionUnit()
{
  return Attribute<string>(*this, "STATION_POSITION_UNIT");
}

Attribute<string> TBB_Station::stationPositionFrame()
{
  return Attribute<string>(*this, "STATION_POSITION_FRAME");
}

Attribute< vector<double> > TBB_Station::beamDirection()
{
  return Attribute< vector<double> >(*this, "BEAM_DIRECTION");
}

Attribute<string> TBB_Station::beamDirectionUnit()
{
  return Attribute<string>(*this, "BEAM_DIRECTION_UNIT");
}

Attribute<string> TBB_Station::beamDirectionFrame()
{
  return Attribute<string>(*this, "BEAM_DIRECTION_FRAME");
}

Attribute<double> TBB_Station::clockOffset()
{
  return Attribute<double>(*this, "CLOCK_OFFSET");
}

Attribute<string> TBB_Station::clockOffsetUnit()
{
  return Attribute<string>(*this, "CLOCK_OFFSET_UNIT");
}

Attribute<unsigned> TBB_Station::nofDipoles()
{
  return Attribute<unsigned>(*this, "NOF_DIPOLES");
}

vector<TBB_DipoleDataset> TBB_Station::dipoles() {
  return dipoleDataSets();
}

vector<TBB_DipoleDataset> TBB_Station::dipoleDataSets()
{
  const string dpPrefix("DIPOLE_");
  vector<TBB_DipoleDataset> dipoleDatasets;

  vector<string> membNames(memberNames());
  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be dipoles and fill the vector with objects of the right type.
    if (it->find(dpPrefix) == 0) {
      TBB_DipoleDataset dipoleDataset(*this, *it);
      if(dipoleDataset.isHDF5DataSet()) {
        dipoleDatasets.push_back(dipoleDataset);
      }
    }
  }

  return dipoleDatasets;
}

vector<TBB_DipoleGroup> TBB_Station::dipoleGroups()
{
  const string dpPrefix("DIPOLE_");
  vector<TBB_DipoleGroup> dipoleGroups;

  vector<string> membNames(memberNames());
  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be dipoles and fill the vector with objects of the right type.
    if (it->find(dpPrefix) == 0) {
      TBB_DipoleGroup dipoleGroup(*this, *it);
      if(dipoleGroup.isHDF5Group()) {
        dipoleGroups.push_back(dipoleGroup);
      }
    }
  }

  return dipoleGroups;
}

TBB_DipoleDataset TBB_Station::dipole( unsigned stationID, unsigned rspID, unsigned rcuID ) {
  return dipole(stationID, rspID, rcuID);
}

TBB_DipoleDataset TBB_Station::dipoleDataSet( unsigned stationID, unsigned rspID, unsigned rcuID )
{
  return TBB_DipoleDataset(*this, dipoleDatasetName(stationID, rspID, rcuID));
}

TBB_DipoleGroup TBB_Station::dipoleGroup( unsigned stationID, unsigned rspID, unsigned rcuID )
{
  return TBB_DipoleGroup(*this, dipoleDatasetName(stationID, rspID, rcuID));
}

string TBB_Station::dipoleDatasetName( unsigned stationID, unsigned rspID, unsigned rcuID )
{
  char buf[sizeof("DIPOLE_") + 3*3]; // sizeof("...") includes space for the '\0'
  snprintf(buf, sizeof buf, "DIPOLE_%03u%03u%03u", stationID, rspID, rcuID);

  return string(buf);
}

TBB_DipoleGroup::TBB_DipoleGroup( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void TBB_DipoleGroup::initNodes() {
  Group::initNodes();
  addNode( new Attribute<unsigned>(*this, "STATION_ID") );
  addNode( new Attribute<unsigned>(*this, "RSP_ID") );
  addNode( new Attribute<unsigned>(*this, "RCU_ID") );
  addNode( new Attribute<double>(*this, "SAMPLE_FREQUENCY") );
  addNode( new Attribute<string>(*this, "SAMPLE_FREQUENCY_UNIT") );
  addNode( new Attribute<unsigned>(*this, "NYQUIST_ZONE") );
  addNode( new Attribute<double>(*this, "ADC2VOLTAGE") );
  addNode( new Attribute<double>(*this, "CABLE_DELAY") );
  addNode( new Attribute<string>(*this, "CABLE_DELAY_UNIT") );
  addNode( new Attribute<double>(*this, "DIPOLE_CALIBRATION_DELAY") );
  addNode( new Attribute<string>(*this, "DIPOLE_CALIBRATION_DELAY_UNIT") );
  addNode( new Attribute< vector<complex<double> > >(*this, "DIPOLE_CALIBRATION_DELAY_GAIN_CURVE") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_POSITION") );
  addNode( new Attribute<string>(*this, "ANTENNA_POSITION_UNIT") );
  addNode( new Attribute<string>(*this, "ANTENNA_POSITION_FRAME") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_NORMAL_VECTOR") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_ROTATION_MATRIX") );
  addNode( new Attribute< vector<double> >(*this, "TILE_BEAM") );
  addNode( new Attribute<string>(*this, "TILE_BEAM_UNIT") );
  addNode( new Attribute<string>(*this, "TILE_BEAM_FRAME") );
  addNode( new Attribute<double>(*this, "DISPERSION_MEASURE") );
  addNode( new Attribute<string>(*this, "DISPERSION_MEASURE_UNIT") );
  addNode( new Attribute<unsigned>(*this, "NOF_SUBBANDS") );
  addNode( new Attribute<vector<unsigned> >(*this, "SUBBANDS") );
}

Attribute<unsigned> TBB_DipoleGroup::stationID()
{
  return Attribute<unsigned>(*this, "STATION_ID");
}

Attribute<unsigned> TBB_DipoleGroup::rspID()
{
  return Attribute<unsigned>(*this, "RSP_ID");
}

Attribute<unsigned> TBB_DipoleGroup::rcuID()
{
  return Attribute<unsigned>(*this, "RCU_ID");
}

Attribute<double> TBB_DipoleGroup::sampleFrequency()
{
  return Attribute<double>(*this, "SAMPLE_FREQUENCY");
}

Attribute<string> TBB_DipoleGroup::sampleFrequencyUnit()
{
  return Attribute<string>(*this, "SAMPLE_FREQUENCY_UNIT");
}

Attribute<unsigned> TBB_DipoleGroup::nyquistZone()
{
  return Attribute<unsigned>(*this, "NYQUIST_ZONE");
}

Attribute<double> TBB_DipoleGroup::adc2voltage()
{
  return Attribute<double>(*this, "ADC2VOLTAGE");
}

Attribute<double> TBB_DipoleGroup::cableDelay()
{
  return Attribute<double>(*this, "CABLE_DELAY");
}

Attribute<string> TBB_DipoleGroup::cableDelayUnit()
{
  return Attribute<string>(*this, "CABLE_DELAY_UNIT");
}

Attribute<double> TBB_DipoleGroup::dipoleCalibrationDelay()
{
  return Attribute<double>(*this, "DIPOLE_CALIBRATION_DELAY");
}

Attribute<string> TBB_DipoleGroup::dipoleCalibrationDelayUnit()
{
  return Attribute<string>(*this, "DIPOLE_CALIBRATION_DELAY_UNIT");
}

Attribute< vector<complex<double> > > TBB_DipoleGroup::dipoleCalibrationGainCurve()
{
  return Attribute< vector<complex<double> > >(*this, "DIPOLE_CALIBRATION_DELAY_GAIN_CURVE");
}

Attribute< vector<double> > TBB_DipoleGroup::antennaPosition()
{
  return Attribute< vector<double> >(*this, "ANTENNA_POSITION");
}

Attribute<string> TBB_DipoleGroup::antennaPositionUnit()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_UNIT");
}

Attribute<string> TBB_DipoleGroup::antennaPositionFrame()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_FRAME");
}

Attribute< vector<double> > TBB_DipoleGroup::antennaNormalVector()
{
  return Attribute< vector<double> >(*this, "ANTENNA_NORMAL_VECTOR");
}

Attribute< vector<double> > TBB_DipoleGroup::antennaRotationMatrix()
{
  return Attribute< vector<double> >(*this, "ANTENNA_ROTATION_MATRIX");
}

Attribute< vector<double> > TBB_DipoleGroup::tileBeam()
{
  return Attribute< vector<double> >(*this, "TILE_BEAM");
}

Attribute<string> TBB_DipoleGroup::tileBeamUnit()
{
  return Attribute<string>(*this, "TILE_BEAM_UNIT");
}

Attribute<string> TBB_DipoleGroup::tileBeamFrame()
{
  return Attribute<string>(*this, "TILE_BEAM_FRAME");
}

Attribute<double> TBB_DipoleGroup::dispersionMeasure()
{
  return Attribute<double>(*this, "DISPERSION_MEASURE");
}

Attribute<string> TBB_DipoleGroup::dispersionMeasureUnit()
{
  return Attribute<string>(*this, "DISPERSION_MEASURE_UNIT");
}

Attribute<unsigned> TBB_DipoleGroup::nofSubbands()
{
  return Attribute<unsigned>(*this, "NOF_SUBBANDS");
}

Attribute<vector<unsigned> > TBB_DipoleGroup::subbands()
{
  return Attribute<vector<unsigned> >(*this, "SUBBANDS");
}

vector<TBB_SubbandDataset> TBB_DipoleGroup::subbandDatasets()
{
  const string sbPrefix("SB_");
  vector<TBB_SubbandDataset> subbandDatasets;

  vector<string> membNames(memberNames());
  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be dipoles and fill the vector with objects of the right type.
    if (it->find(sbPrefix) == 0) {
      TBB_SubbandDataset subbandDataset(*this, *it);
      if(subbandDataset.isHDF5DataSet()) {
        subbandDatasets.push_back(subbandDataset);
      }
    }
  }

  return subbandDatasets;
}

TBB_SubbandDataset TBB_DipoleGroup::subband( unsigned subband_nr )
{
  return TBB_SubbandDataset(*this, subbandDatasetName(subband_nr));
}

string TBB_DipoleGroup::subbandDatasetName( unsigned subband_nr )
{
  char buf[sizeof("SB_") + 3]; // sizeof("...") includes space for the '\0'
  snprintf(buf, sizeof buf, "SB_%03u", subband_nr);

  return string(buf);
}


TBB_DipoleDataset::TBB_DipoleDataset( Group &parent, const std::string &name )
:
  Dataset<short>(parent, name)
{
}

void TBB_DipoleDataset::initNodes() {
  Dataset<short>::initNodes();
  addNode( new Attribute<unsigned>(*this, "STATION_ID") );
  addNode( new Attribute<unsigned>(*this, "RSP_ID") );
  addNode( new Attribute<unsigned>(*this, "RCU_ID") );
  addNode( new Attribute<double>(*this, "SAMPLE_FREQUENCY") );
  addNode( new Attribute<string>(*this, "SAMPLE_FREQUENCY_UNIT") );
  addNode( new Attribute<unsigned>(*this, "TIME") );
  addNode( new Attribute<unsigned>(*this, "SAMPLE_NUMBER") );
  addNode( new Attribute<unsigned>(*this, "SAMPLES_PER_FRAME") );
  addNode( new Attribute<unsigned long long>(*this, "DATA_LENGTH") );
  addNode( new Attribute< vector<Range> >(*this, "FLAG_OFFSETS") );
  addNode( new Attribute<unsigned>(*this, "NYQUIST_ZONE") );
  addNode( new Attribute<double>(*this, "CABLE_DELAY") );
  addNode( new Attribute<string>(*this, "CABLE_DELAY_UNIT") );
  addNode( new Attribute<double>(*this, "DIPOLE_CALIBRATION_DELAY") );
  addNode( new Attribute<string>(*this, "DIPOLE_CALIBRATION_DELAY_UNIT") );
  addNode( new Attribute< vector<complex<double> > >(*this, "DIPOLE_CALIBRATION_DELAY_GAIN_CURVE") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_POSITION") );
  addNode( new Attribute<string>(*this, "ANTENNA_POSITION_UNIT") );
  addNode( new Attribute<string>(*this, "ANTENNA_POSITION_FRAME") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_NORMAL_VECTOR") );
  addNode( new Attribute< vector<double> >(*this, "ANTENNA_ROTATION_MATRIX") );
  addNode( new Attribute< vector<double> >(*this, "TILE_BEAM") );
  addNode( new Attribute<string>(*this, "TILE_BEAM_UNIT") );
  addNode( new Attribute<string>(*this, "TILE_BEAM_FRAME") );
  addNode( new Attribute<double>(*this, "DISPERSION_MEASURE") );
  addNode( new Attribute<string>(*this, "DISPERSION_MEASURE_UNIT") );
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

Attribute<double> TBB_DipoleDataset::sampleFrequency()
{
  return Attribute<double>(*this, "SAMPLE_FREQUENCY");
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

Attribute<unsigned long long> TBB_DipoleDataset::dataLength()
{
  return Attribute<unsigned long long>(*this, "DATA_LENGTH");
}

Attribute< vector<Range> > TBB_DipoleDataset::flagOffsets()
{
  return Attribute< vector<Range> >(*this, "FLAG_OFFSETS");
}

Attribute<unsigned> TBB_DipoleDataset::nyquistZone()
{
  return Attribute<unsigned>(*this, "NYQUIST_ZONE");
}

Attribute<double> TBB_DipoleDataset::cableDelay()
{
  return Attribute<double>(*this, "CABLE_DELAY");
}

Attribute<string> TBB_DipoleDataset::cableDelayUnit()
{
  return Attribute<string>(*this, "CABLE_DELAY_UNIT");
}

Attribute<double> TBB_DipoleDataset::dipoleCalibrationDelay()
{
  return Attribute<double>(*this, "DIPOLE_CALIBRATION_DELAY");
}

Attribute<string> TBB_DipoleDataset::dipoleCalibrationDelayUnit()
{
  return Attribute<string>(*this, "DIPOLE_CALIBRATION_DELAY_UNIT");
}

Attribute< vector<complex<double> > > TBB_DipoleDataset::dipoleCalibrationGainCurve()
{
  return Attribute< vector<complex<double> > >(*this, "DIPOLE_CALIBRATION_DELAY_GAIN_CURVE");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaPosition()
{
  return Attribute< vector<double> >(*this, "ANTENNA_POSITION");
}

Attribute<string> TBB_DipoleDataset::antennaPositionUnit()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_UNIT");
}

Attribute<string> TBB_DipoleDataset::antennaPositionFrame()
{
  return Attribute<string>(*this, "ANTENNA_POSITION_FRAME");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaNormalVector()
{
  return Attribute< vector<double> >(*this, "ANTENNA_NORMAL_VECTOR");
}

Attribute< vector<double> > TBB_DipoleDataset::antennaRotationMatrix()
{
  return Attribute< vector<double> >(*this, "ANTENNA_ROTATION_MATRIX");
}

Attribute< vector<double> > TBB_DipoleDataset::tileBeam()
{
  return Attribute< vector<double> >(*this, "TILE_BEAM");
}

Attribute<string> TBB_DipoleDataset::tileBeamUnit()
{
  return Attribute<string>(*this, "TILE_BEAM_UNIT");
}

Attribute<string> TBB_DipoleDataset::tileBeamFrame()
{
  return Attribute<string>(*this, "TILE_BEAM_FRAME");
}

Attribute<double> TBB_DipoleDataset::dispersionMeasure()
{
  return Attribute<double>(*this, "DISPERSION_MEASURE");
}

Attribute<string> TBB_DipoleDataset::dispersionMeasureUnit()
{
  return Attribute<string>(*this, "DISPERSION_MEASURE_UNIT");
}

TBB_SubbandDataset::TBB_SubbandDataset( Group &parent, const std::string &name )
:
  Dataset<short>(parent, name)
{
}

void TBB_SubbandDataset::initNodes() {
  Dataset<short>::initNodes();
  addNode( new Attribute<unsigned>(*this, "TIME") );
  addNode( new Attribute<double>(*this, "CENTRAL_FREQUENCY") );
  addNode( new Attribute<string>(*this, "CENTRAL_FREQUENCY_UNIT") );
  addNode( new Attribute<double>(*this, "BANDWIDTH") );
  addNode( new Attribute<string>(*this, "BANDWIDTH_UNIT") );
  addNode( new Attribute<double>(*this, "TIME_RESOLUTION") );
  addNode( new Attribute<string>(*this, "TIME_RESOLUTION_UNIT") );
  addNode( new Attribute<unsigned>(*this, "BAND_NUMBER") );
  addNode( new Attribute<unsigned>(*this, "SLICE_NUMBER") );
  addNode( new Attribute<unsigned>(*this, "SAMPLES_PER_FRAME") );
  addNode( new Attribute<unsigned long long>(*this, "DATA_LENGTH") );
  addNode( new Attribute< vector<Range> >(*this, "FLAG_OFFSETS") );
}

Attribute<unsigned> TBB_SubbandDataset::time()
{
  return Attribute<unsigned>(*this, "TIME");
}

Attribute<double> TBB_SubbandDataset::centralFrequency()
{
  return Attribute<double>(*this, "CENTRAL_FREQUENCY");
}

Attribute<string> TBB_SubbandDataset::centralFrequencyUnit()
{
  return Attribute<string>(*this, "CENTRAL_FREQUENCY_UNIT");
}

Attribute<double> TBB_SubbandDataset::bandwidth()
{
  return Attribute<double>(*this, "BANDWIDTH");
}

Attribute<string> TBB_SubbandDataset::bandwidthUnit()
{
  return Attribute<string>(*this, "BANDWIDTH_UNIT");
}

Attribute<double> TBB_SubbandDataset::timeResolution()
{
  return Attribute<double>(*this, "TIME_RESOLUTION");
}

Attribute<string> TBB_SubbandDataset::timeResolutionUnit()
{
  return Attribute<string>(*this, "TIME_RESOLUTION_UNIT");
}

Attribute<unsigned> TBB_SubbandDataset::bandNumber()
{
  return Attribute<unsigned>(*this, "BAND_NUMBER");
}

Attribute<unsigned> TBB_SubbandDataset::sliceNumber()
{
  return Attribute<unsigned>(*this, "SLICE_NUMBER");
}

Attribute<unsigned> TBB_SubbandDataset::samplesPerFrame()
{
  return Attribute<unsigned>(*this, "SAMPLES_PER_FRAME");
}

Attribute<unsigned long long> TBB_SubbandDataset::dataLength()
{
  return Attribute<unsigned long long>(*this, "DATA_LENGTH");
}

Attribute< vector<Range> > TBB_SubbandDataset::flagOffsets()
{
  return Attribute< vector<Range> >(*this, "FLAG_OFFSETS");
}

}

