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
#include "BF_File.h"

using namespace std;

namespace DAL {

BF_File::BF_File() {}

BF_File::BF_File( const std::string &filename, FileMode mode )
:
  CLA_File(filename, mode)
{
  openFile(mode);
}

BF_File::~BF_File() {}

void BF_File::open( const std::string &filename, FileMode mode )
{
  // As long as we have no member vars, keep open() and close() simple. See CLA_File::open().
  CLA_File::open(filename, mode);

  openFile(mode);
}

void BF_File::close()
{
  CLA_File::close();
}

void BF_File::openFile( FileMode mode )
{
  initFileNodes();

  if (mode == CREATE || mode == CREATE_EXCL) {
    fileType().create().set("bf");
    docName() .create().set("ICD 3: Beam-Formed Data");
    docVersion()       .set(VersionType(2, 5)); // already created by File
  } else {
    bool isBfFileType = false;
    try {
      isBfFileType = fileType().get() == "bf" || fileType().get() == "dynspec"; // dynspec is very similar
    } catch (DALException& ) {
    }
    if (!isBfFileType) {
      throw DALException("Failed to open BF file: A BF file must have FILETYPE=\"bf\".");
    }
  }
}

void BF_File::initFileNodes() {
  CLA_File::initNodes();
  addNode( new Attribute<string>(*this, "CREATE_OFFLINE_ONLINE") );
  addNode( new Attribute<string>(*this, "BF_FORMAT") );
  addNode( new Attribute<string>(*this, "BF_VERSION") );
  addNode( new Attribute<double>(*this, "TOTAL_INTEGRATION_TIME") );
  addNode( new Attribute<string>(*this, "TOTAL_INTEGRATION_TIME_UNIT") );
  addNode( new Attribute<string>(*this, "OBSERVATION_DATATYPE") );
  addNode( new Attribute<double>(*this, "SUB_ARRAY_POINTING_DIAMETER") );
  addNode( new Attribute<string>(*this, "SUB_ARRAY_POINTING_DIAMETER_UNIT") );
  addNode( new Attribute<double>(*this, "BANDWIDTH") );
  addNode( new Attribute<string>(*this, "BANDWIDTH_UNIT") );
  addNode( new Attribute<double>(*this, "BEAM_DIAMETER") );
  addNode( new Attribute<string>(*this, "BEAM_DIAMETER_UNIT") );
  addNode( new Attribute<unsigned>(*this, "OBSERVATION_NOF_SUB_ARRAY_POINTINGS") );
  addNode( new Attribute<unsigned>(*this, "NOF_SUB_ARRAY_POINTINGS") );
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

Attribute<double> BF_File::totalIntegrationTime()
{
  return getNode("TOTAL_INTEGRATION_TIME");
}

Attribute<string> BF_File::totalIntegrationTimeUnit()
{
  return getNode("TOTAL_INTEGRATION_TIME_UNIT");
}  
  
Attribute<string> BF_File::observationDatatype()
{
  return getNode("OBSERVATION_DATATYPE");
}

Attribute<double> BF_File::subArrayPointingDiameter()
{
  return getNode("SUB_ARRAY_POINTING_DIAMETER");
}

Attribute<string> BF_File::subArrayPointingDiameterUnit()
{
  return getNode("SUB_ARRAY_POINTING_DIAMETER_UNIT");
}  
  
Attribute<double> BF_File::bandwidth()
{
  return getNode("BANDWIDTH");
}

Attribute<string> BF_File::bandwidthUnit()
{
  return getNode("BANDWIDTH_UNIT");
}
  
Attribute<double> BF_File::beamDiameter()
{
  return getNode("BEAM_DIAMETER");
}

Attribute<string> BF_File::beamDiameterUnit()
{
  return getNode("BEAM_DIAMETER_UNIT");
}
  
Attribute<unsigned> BF_File::observationNofSubArrayPointings()
{
  return getNode("OBSERVATION_NOF_SUB_ARRAY_POINTINGS");
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
  return BF_SubArrayPointing(*this, subArrayPointingName(nr));
}


BF_SysLog BF_File::sysLog()
{
  return BF_SysLog(*this, "SYS_LOG");
}


BF_SubArrayPointing::BF_SubArrayPointing( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void BF_SubArrayPointing::initNodes() {
  Group::initNodes();
  addNode( new Attribute<string>(*this, "EXPTIME_START_UTC") );
  addNode( new Attribute<string>(*this, "EXPTIME_END_UTC") );
  addNode( new Attribute<double>(*this, "EXPTIME_START_MJD") );
  addNode( new Attribute<double>(*this, "EXPTIME_END_MJD") );
  addNode( new Attribute<double>(*this, "TOTAL_INTEGRATION_TIME") );
  addNode( new Attribute<string>(*this, "TOTAL_INTEGRATION_TIME_UNIT") );
  addNode( new Attribute<double>(*this, "POINT_RA") );
  addNode( new Attribute<string>(*this, "POINT_RA_UNIT") );
  addNode( new Attribute<double>(*this, "POINT_DEC") );
  addNode( new Attribute<string>(*this, "POINT_DEC_UNIT") );
  addNode( new Attribute< vector<double> >(*this, "POINT_ALTITUDE") );
  addNode( new Attribute< vector<string> >(*this, "POINT_ALTITUDE_UNIT") );
  addNode( new Attribute< vector<double> >(*this, "POINT_AZIMUTH") );
  addNode( new Attribute< vector<string> >(*this, "POINT_AZIMUTH_UNIT") );
  addNode( new Attribute<unsigned>(*this, "OBSERVATION_NOF_BEAMS") );
  addNode( new Attribute<unsigned>(*this, "NOF_BEAMS") );
}

Attribute<string> BF_SubArrayPointing::expTimeStartUTC()
{
  return getNode("EXPTIME_START_UTC");
}

Attribute<string> BF_SubArrayPointing::expTimeEndUTC()
{
  return getNode("EXPTIME_END_UTC");
}

Attribute<double> BF_SubArrayPointing::expTimeStartMJD()
{
  return getNode("EXPTIME_START_MJD");
}

Attribute<double> BF_SubArrayPointing::expTimeEndMJD()
{
  return getNode("EXPTIME_END_MJD");
}

Attribute<double> BF_SubArrayPointing::totalIntegrationTime()
{
  return getNode("TOTAL_INTEGRATION_TIME");
}

Attribute<string> BF_SubArrayPointing::totalIntegrationTimeUnit()
{
  return getNode("TOTAL_INTEGRATION_TIME_UNIT");
}  

Attribute<double> BF_SubArrayPointing::pointRA()
{
  return getNode("POINT_RA");
}

Attribute<string> BF_SubArrayPointing::pointRAUnit()
{
  return getNode("POINT_RA_UNIT");
}

Attribute<double> BF_SubArrayPointing::pointDEC()
{
  return getNode("POINT_DEC");
}

Attribute<string> BF_SubArrayPointing::pointDECUnit()
{
  return getNode("POINT_DEC_UNIT");
}

Attribute< vector<double> > BF_SubArrayPointing::pointAltitude()
{
  return getNode("POINT_ALTITUDE");
}

Attribute< vector<string> > BF_SubArrayPointing::pointAltitudeUnit()
{
  return getNode("POINT_ALTITUDE_UNIT");
}

Attribute< vector<double> > BF_SubArrayPointing::pointAzimuth()
{
  return getNode("POINT_AZIMUTH");
}

Attribute< vector<string> > BF_SubArrayPointing::pointAzimuthUnit()
{
  return getNode("POINT_AZIMUTH_UNIT");
}

Attribute<unsigned> BF_SubArrayPointing::observationNofBeams()
{
  return getNode("OBSERVATION_NOF_BEAMS");
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

BF_ProcessingHistory BF_SubArrayPointing::processHistory()
{
  return BF_ProcessingHistory(*this, "PROCESS_HISTORY");
}

BF_BeamGroup BF_SubArrayPointing::beam( unsigned nr )
{
  return BF_BeamGroup(*this, beamName(nr));
}


BF_BeamGroup::BF_BeamGroup( Group &parent, const std::string &name )
:
  Group(parent, name)
{
}

void BF_BeamGroup::initNodes() {
  Group::initNodes();
  addNode( new Attribute< vector<string> >(*this, "TARGETS") );
  addNode( new Attribute<unsigned>(*this, "NOF_STATIONS") );
  addNode( new Attribute< vector<string> >(*this, "STATIONS_LIST") );
  addNode( new Attribute<unsigned>(*this, "NOF_SAMPLES") );
  addNode( new Attribute<double>(*this, "SAMPLING_RATE") );
  addNode( new Attribute<string>(*this, "SAMPLING_RATE_UNIT") );
  addNode( new Attribute<double>(*this, "SAMPLING_TIME") );
  addNode( new Attribute<string>(*this, "SAMPLING_TIME_UNIT") );
  addNode( new Attribute<unsigned>(*this, "CHANNELS_PER_SUBBAND") );
  addNode( new Attribute<double>(*this, "SUBBAND_WIDTH") );
  addNode( new Attribute<string>(*this, "SUBBAND_WIDTH_UNIT") );
  addNode( new Attribute<double>(*this, "CHANNEL_WIDTH") );
  addNode( new Attribute<string>(*this, "CHANNEL_WIDTH_UNIT") );
  addNode( new Attribute<string>(*this, "TRACKING") );
  addNode( new Attribute<double>(*this, "POINT_RA") );
  addNode( new Attribute<string>(*this, "POINT_RA_UNIT") );
  addNode( new Attribute<double>(*this, "POINT_DEC") );
  addNode( new Attribute<string>(*this, "POINT_DEC_UNIT") );
  addNode( new Attribute<double>(*this, "POINT_OFFSET_RA") );
  addNode( new Attribute<string>(*this, "POINT_OFFSET_RA_UNIT") );
  addNode( new Attribute<double>(*this, "POINT_OFFSET_DEC") );
  addNode( new Attribute<string>(*this, "POINT_OFFSET_DEC_UNIT") );
  addNode( new Attribute<double>(*this, "BEAM_DIAMETER_RA") );
  addNode( new Attribute<string>(*this, "BEAM_DIAMETER_RA_UNIT") );
  addNode( new Attribute<double>(*this, "BEAM_DIAMETER_DEC") );
  addNode( new Attribute<string>(*this, "BEAM_DIAMETER_DEC_UNIT") );
  addNode( new Attribute<double>(*this, "BEAM_FREQUENCY_CENTER") );
  addNode( new Attribute<string>(*this, "BEAM_FREQUENCY_CENTER_UNIT") );
  addNode( new Attribute<bool>(*this, "FOLDED_DATA") );
  addNode( new Attribute<double>(*this, "FOLD_PERIOD") );
  addNode( new Attribute<string>(*this, "FOLD_PERIOD_UNIT") );
  addNode( new Attribute<string>(*this, "DEDISPERSION") );
  addNode( new Attribute<double>(*this, "DISPERSION_MEASURE") );
  addNode( new Attribute<string>(*this, "DISPERSION_MEASURE_UNIT") );
  addNode( new Attribute<bool>(*this, "BARYCENTERED") );
  addNode( new Attribute<unsigned>(*this, "OBSERVATION_NOF_STOKES") );
  addNode( new Attribute<unsigned>(*this, "NOF_STOKES") );
  addNode( new Attribute< vector<string> >(*this, "STOKES_COMPONENTS") );
  addNode( new Attribute<bool>(*this, "COMPLEX_VOLTAGE") );
  addNode( new Attribute<string>(*this, "SIGNAL_SUM") );
}

Attribute< vector<string> > BF_BeamGroup::targets()
{
  return getNode("TARGETS");
}

Attribute<unsigned> BF_BeamGroup::nofStations()
{
  return getNode("NOF_STATIONS");
}

Attribute< vector<string> > BF_BeamGroup::stationsList()
{
  return getNode("STATIONS_LIST");
}

Attribute<unsigned> BF_BeamGroup::nofSamples()
{
  return getNode("NOF_SAMPLES");
}

Attribute<double> BF_BeamGroup::samplingRate()
{
  return getNode("SAMPLING_RATE");
}

Attribute<string> BF_BeamGroup::samplingRateUnit()
{
  return getNode("SAMPLING_RATE_UNIT");
}

Attribute<double> BF_BeamGroup::samplingTime()
{
  return getNode("SAMPLING_TIME");
}

Attribute<string> BF_BeamGroup::samplingTimeUnit()
{
  return getNode("SAMPLING_TIME_UNIT");
}

Attribute<unsigned> BF_BeamGroup::channelsPerSubband()
{
  return getNode("CHANNELS_PER_SUBBAND");
}

Attribute<double> BF_BeamGroup::subbandWidth()
{
  return getNode("SUBBAND_WIDTH");
}

Attribute<string> BF_BeamGroup::subbandWidthUnit()
{
  return getNode("SUBBAND_WIDTH_UNIT");
}

Attribute<double> BF_BeamGroup::channelWidth()
{
  return getNode("CHANNEL_WIDTH");
}

Attribute<string> BF_BeamGroup::channelWidthUnit()
{
  return getNode("CHANNEL_WIDTH_UNIT");
}

Attribute<string> BF_BeamGroup::tracking()
{
  return getNode("TRACKING");
}

Attribute<double> BF_BeamGroup::pointRA()
{
  return getNode("POINT_RA");
}

Attribute<string> BF_BeamGroup::pointRAUnit()
{
  return getNode("POINT_RA_UNIT");
}

Attribute<double> BF_BeamGroup::pointDEC()
{
  return getNode("POINT_DEC");
}

Attribute<string> BF_BeamGroup::pointDECUnit()
{
  return getNode("POINT_DEC_UNIT");
}

Attribute<double> BF_BeamGroup::pointOffsetRA()
{
  return getNode("POINT_OFFSET_RA");
}

Attribute<string> BF_BeamGroup::pointOffsetRAUnit()
{
  return getNode("POINT_OFFSET_RA_UNIT");
}

Attribute<double> BF_BeamGroup::pointOffsetDEC()
{
  return getNode("POINT_OFFSET_DEC");
}

Attribute<string> BF_BeamGroup::pointOffsetDECUnit()
{
  return getNode("POINT_OFFSET_DEC_UNIT");
}

Attribute<double> BF_BeamGroup::beamDiameterRA()
{
  return getNode("BEAM_DIAMETER_RA");
}

Attribute<string> BF_BeamGroup::beamDiameterRAUnit()
{
  return getNode("BEAM_DIAMETER_RA_UNIT");
}

Attribute<double> BF_BeamGroup::beamDiameterDEC()
{
  return getNode("BEAM_DIAMETER_DEC");
}

Attribute<string> BF_BeamGroup::beamDiameterDECUnit()
{
  return getNode("BEAM_DIAMETER_DEC_UNIT");
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

Attribute<double> BF_BeamGroup::dispersionMeasure()
{
  return getNode("DISPERSION_MEASURE");
}

Attribute<string> BF_BeamGroup::dispersionMeasureUnit()
{
  return getNode("DISPERSION_MEASURE_UNIT");
}

Attribute<bool> BF_BeamGroup::barycentered()
{
  return getNode("BARYCENTERED");
}

Attribute<unsigned> BF_BeamGroup::observationNofStokes()
{
  return getNode("OBSERVATION_NOF_STOKES");
}

Attribute<unsigned> BF_BeamGroup::nofStokes()
{
  return getNode("NOF_STOKES");
}

Attribute< vector<string> > BF_BeamGroup::stokesComponents()
{
  return getNode("STOKES_COMPONENTS");
}

Attribute<bool> BF_BeamGroup::complexVoltage()
{
  return getNode("COMPLEX_VOLTAGE");
}

Attribute<string> BF_BeamGroup::signalSum()
{
  return getNode("SIGNAL_SUM");
}

BF_ProcessingHistory BF_BeamGroup::processHistory()
{
  return BF_ProcessingHistory(*this, "PROCESS_HISTORY");
}

CoordinatesGroup BF_BeamGroup::coordinates()
{
  return CoordinatesGroup(*this, coordinatesName());
}

BF_StokesDataset BF_BeamGroup::stokes( unsigned nr )
{
  return BF_StokesDataset(*this, stokesName(nr));
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


BF_StokesDataset::BF_StokesDataset( Group &parent, const std::string &name )
:
  Dataset<float>(parent, name)
{
}

void BF_StokesDataset::initNodes()
{
  Dataset::initNodes();
  addNode( new Attribute<string>(*this, "DATATYPE") );
  addNode( new Attribute<string>(*this, "STOKES_COMPONENT") );
  addNode( new Attribute< vector<unsigned> >(*this, "NOF_CHANNELS") );
  addNode( new Attribute<unsigned>(*this, "NOF_SUBBANDS") );
  addNode( new Attribute<unsigned>(*this, "NOF_SAMPLES") );
}

Attribute<string> BF_StokesDataset::dataType()
{
  return getNode("DATATYPE");
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

