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

namespace DAL {

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
    docVersion()       .set(VersionType(2, 5)); // already created by File
  } else {
    bool isTbbFileType = false;
    try {
      isTbbFileType = fileType().get() == "tbb";
    } catch (DALException& ) {
    }
    if (!isTbbFileType) {
      throw DALException("Failed to open TBB file: A TBB file must have FILETYPE=\"tbb\".");
    }
  }
}

void TBB_File::initFileNodes() {
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
      stationGroups.push_back(TBB_Station(*this, *it));
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

void TBB_Trigger::open( hid_t /*parent*/, const std::string &/*name*/ )
{
  initNodes();
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


TBB_Station::TBB_Station( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void TBB_Station::open( hid_t /*parent*/, const std::string &/*name*/ )
{
  initNodes();
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

vector<TBB_DipoleDataset> TBB_Station::dipoles()
{
  const string dpPrefix("DIPOLE_");
  vector<TBB_DipoleDataset> dipoleDatasets;

  vector<string> membNames(memberNames());
  for (vector<string>::const_iterator it(membNames.begin()); it != membNames.end(); ++it) {
    // Filter the names that appear to be dipoles and fill the vector with objects of the right type.
    if (it->find(dpPrefix) == 0) {
      dipoleDatasets.push_back(TBB_DipoleDataset(*this, *it));
    }
  }

  return dipoleDatasets;
}

TBB_DipoleDataset TBB_Station::dipole( unsigned stationID, unsigned rspID, unsigned rcuID )
{
  return TBB_DipoleDataset(*this, dipoleDatasetName(stationID, rspID, rcuID));
}

string TBB_Station::dipoleDatasetName( unsigned stationID, unsigned rspID, unsigned rcuID )
{
  char buf[sizeof("DIPOLE_") + 3*3]; // sizeof("...") includes space for the '\0'
  snprintf(buf, sizeof buf, "DIPOLE_%03u%03u%03u", stationID, rspID, rcuID);

  return string(buf);
}


TBB_DipoleDataset::TBB_DipoleDataset( Group &parent, const std::string &name )
:
  Dataset<short>(parent, name)
{
}

void TBB_DipoleDataset::open( hid_t /*parent*/, const std::string &/*name*/ )
{
  initNodes();
}

void TBB_DipoleDataset::initNodes() {
  Dataset::initNodes();
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

}

