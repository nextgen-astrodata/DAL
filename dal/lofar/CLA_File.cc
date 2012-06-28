#include "CLA_File.h"

using namespace std;

namespace DAL {

CLA_File::CLA_File( const std::string &filename, enum File::fileMode mode )
:
  File(filename, mode, "DOC_VERSION")
{
}

void CLA_File::initNodes()
{
  File::initNodes();

  addNode( new Attribute<string>(*this, "FILENAME") );
  addNode( new Attribute<string>(*this, "FILEDATE") );
  addNode( new Attribute<string>(*this, "FILETYPE") );
  addNode( new Attribute<string>(*this, "TELESCOPE") );
  addNode( new Attribute<string>(*this, "OBSERVER") );
  addNode( new Attribute<string>(*this, "PROJECT_ID") );
  addNode( new Attribute<string>(*this, "PROJECT_TITLE") );
  addNode( new Attribute<string>(*this, "PROJECT_PI") );
  addNode( new Attribute<string>(*this, "PROJECT_CO_I") );
  addNode( new Attribute<string>(*this, "PROJECT_CONTACT") );
  addNode( new Attribute<string>(*this, "OBSERVATION_ID") );
  addNode( new Attribute<string>(*this, "OBSERVATION_START_UTC") );
  addNode( new Attribute<double>(*this, "OBSERVATION_START_MJD") );
  addNode( new Attribute<string>(*this, "OBSERVATION_START_TAI") );
  addNode( new Attribute<string>(*this, "OBSERVATION_END_UTC") );
  addNode( new Attribute<double>(*this, "OBSERVATION_END_MJD") );
  addNode( new Attribute<string>(*this, "OBSERVATION_END_TAI") );
  addNode( new Attribute<unsigned>(*this, "OBSERVATION_NOF_STATIONS") );
  addNode( new Attribute< vector<string> >(*this, "OBSERVATION_STATIONS_LIST") );
  addNode( new Attribute<double>(*this, "OBSERVATION_FREQUENCY_MAX") );
  addNode( new Attribute<double>(*this, "OBSERVATION_FREQUENCY_MIN") );
  addNode( new Attribute<double>(*this, "OBSERVATION_FREQUENCY_CENTER") );
  addNode( new Attribute<string>(*this, "OBSERVATION_FREQUENCY_UNIT") );
  addNode( new Attribute<unsigned>(*this, "OBSERVATION_NOF_BITS_PER_SAMPLE") );
  addNode( new Attribute<double>(*this, "CLOCK_FREQUENCY") );
  addNode( new Attribute<string>(*this, "CLOCK_FREQUENCY_UNIT") );
  addNode( new Attribute<string>(*this, "ANTENNA_SET") );
  addNode( new Attribute<string>(*this, "FILTER_SELECTION") );
  addNode( new Attribute< vector<string> >(*this, "TARGETS") );
  addNode( new Attribute<string>(*this, "SYSTEM_VERSION") );
  addNode( new Attribute<string>(*this, "PIPELINE_NAME") );
  addNode( new Attribute<string>(*this, "PIPELINE_VERSION") );
  addNode( new Attribute<string>(*this, "DOC_NAME") );
  addNode( new Attribute<string>(*this, "DOC_VERSION") );
  addNode( new Attribute<string>(*this, "NOTES") );
}

Attribute<string> CLA_File::fileName()
{
  return getNode("FILENAME");
}

Attribute<string> CLA_File::fileDate()
{
  return getNode("FILEDATE");
}

Attribute<string> CLA_File::fileType()
{
  return getNode("FILETYPE");
}

Attribute<string> CLA_File::telescope()
{
  return getNode("TELESCOPE");
}

Attribute<string> CLA_File::observer()
{
  return getNode("OBSERVER");
}

Attribute<string> CLA_File::projectID()
{
  return getNode("PROJECT_ID");
}

Attribute<string> CLA_File::projectTitle()
{
  return getNode("PROJECT_TITLE");
}

Attribute<string> CLA_File::projectPI()
{
  return getNode("PROJECT_PI");
}

Attribute<string> CLA_File::projectCOI()
{
  return getNode("PROJECT_CO_I");
}

Attribute<string> CLA_File::projectContact()
{
  return getNode("PROJECT_CONTACT");
}

Attribute<string> CLA_File::observationID()
{
  return getNode("OBSERVATION_ID");
}

Attribute<string> CLA_File::observationStartUTC()
{
  return getNode("OBSERVATION_START_UTC");
}

Attribute<double> CLA_File::observationStartMJD()
{
  return getNode("OBSERVATION_START_MJD");
}

Attribute<string> CLA_File::observationStartTAI()
{
  return getNode("OBSERVATION_START_TAI");
}

Attribute<string> CLA_File::observationEndUTC()
{
  return getNode("OBSERVATION_END_UTC");
}

Attribute<double> CLA_File::observationEndMJD()
{
  return getNode("OBSERVATION_END_MJD");
}

Attribute<string> CLA_File::observationEndTAI()
{
  return getNode("OBSERVATION_END_TAI");
}

Attribute<unsigned> CLA_File::observationNofStations()
{
  return getNode("OBSERVATION_NOF_STATIONS");
}

Attribute< vector<string> > CLA_File::observationStationsList()
{
  return getNode("OBSERVATION_STATIONS_LIST");
}

Attribute<double> CLA_File::observationFrequencyMax()
{
  return getNode("OBSERVATION_FREQUENCY_MAX");
}

Attribute<double> CLA_File::observationFrequencyMin()
{
  return getNode("OBSERVATION_FREQUENCY_MIN");
}

Attribute<double> CLA_File::observationFrequencyCenter()
{
  return getNode("OBSERVATION_FREQUENCY_CENTER");
}

Attribute<string> CLA_File::observationFrequencyUnit()
{
  return getNode("OBSERVATION_FREQUENCY_UNIT");
}

Attribute<unsigned> CLA_File::observationNofBitsPerSample()
{
  return getNode("OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> CLA_File::clockFrequency()
{
  return getNode("CLOCK_FREQUENCY");
}

Attribute<string> CLA_File::clockFrequencyUnit()
{
  return getNode("CLOCK_FREQUENCY_UNIT");
}

Attribute<string> CLA_File::antennaSet()
{
  return getNode("ANTENNA_SET");
}

Attribute<string> CLA_File::filterSelection()
{
  return getNode("FILTER_SELECTION");
}

Attribute< vector<string> > CLA_File::targets()
{
  return getNode("TARGETS");
}

Attribute<string> CLA_File::systemVersion()
{
  return getNode("SYSTEM_VERSION");
}

Attribute<string> CLA_File::pipelineName()
{
  return getNode("PIPELINE_NAME");
}

Attribute<string> CLA_File::pipelineVersion()
{
  return getNode("PIPELINE_VERSION");
}

Attribute<string> CLA_File::docName()
{
  return getNode("DOC_NAME");
}

Attribute<string> CLA_File::docVersion()
{
  return getNode("DOC_VERSION");
}

Attribute<string> CLA_File::notes()
{
  return getNode("NOTES");
}

}

