#include "CommonAttributesFile.h"

using namespace std;

namespace DAL {

CommonAttributesFile::CommonAttributesFile( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  HDF5FileBase(filename, mode)
{
}

void CommonAttribtusFile::initNodes()
{
  addNode( Attribute<string>(group(), "GROUPTYPE") );
  addNode( Attribute<string>(group(), "FILENAME") );
  addNode( Attribute<string>(group(), "FILEDATE") );
  addNode( Attribute<string>(group(), "FILETYPE") );
  addNode( Attribute<string>(group(), "TELESCOPE") );
  addNode( Attribute<string>(group(), "OBSERVER") );
  addNode( Attribute<string>(group(), "PROJECT_ID") );
  addNode( Attribute<string>(group(), "PROJECT_TITLE") );
  addNode( Attribute<string>(group(), "PROJECT_PI") );
  addNode( Attribute<string>(group(), "PROJECT_CO_I") );
  addNode( Attribute<string>(group(), "PROJECT_CONTACT") );
  addNode( Attribute<string>(group(), "OBSERVATION_ID") );
  addNode( Attribute<string>(group(), "OBSERVATION_START_UTC") );
  addNode( Attribute<double>(group(), "OBSERVATION_START_MJD") );
  addNode( Attribute<string>(group(), "OBSERVATION_START_TAI") );
  addNode( Attribute<string>(group(), "OBSERVATION_END_UTC") );
  addNode( Attribute<double>(group(), "OBSERVATION_END_MJD") );
  addNode( Attribute<string>(group(), "OBSERVATION_END_TAI") );
  addNode( Attribute<unsigned>(group(), "OBSERVATION_NOF_STATIONS") );
  addNode( Attribute< vector<string> >(group(), "OBSERVATION_STATIONS_LIST") );
  addNode( Attribute<double>(group(), "OBSERVATION_FREQUENCY_MAX") );
  addNode( Attribute<double>(group(), "OBSERVATION_FREQUENCY_MIN") );
  addNode( Attribute<double>(group(), "OBSERVATION_FREQUENCY_CENTER") );
  addNode( Attribute<string>(group(), "OBSERVATION_FREQUENCY_UNIT") );
  addNode( Attribute<unsigned>(group(), "OBSERVATION_NOF_BITS_PER_SAMPLE") );
  addNode( Attribute<double>(group(), "CLOCK_FREQUENCY") );
  addNode( Attribute<string>(group(), "CLOCK_FREQUENCY_UNIT") );
  addNode( Attribute<string>(group(), "ANTENNA_SET") );
  addNode( Attribute<string>(group(), "FILTER_SELECTION") );
  addNode( Attribute<string>(group(), "TARGET") );
  addNode( Attribute<string>(group(), "SYSTEM_VERSION") );
  addNode( Attribute<string>(group(), "PIPELINE_NAME") );
  addNode( Attribute<string>(group(), "PIPELINE_VERSION") );
  addNode( Attribute<string>(group(), "ICD_NUMBER") );
  addNode( Attribute<string>(group(), "ICD_VERSION") );
  addNode( Attribute<string>(group(), "NOTES") );
}

Attribute<string> CommonAttributesFile::groupType()
{
  return getNode("GROUPTYPE");
}

Attribute<string> CommonAttributesFile::fileName()
{
  return getNode("FILENAME");
}

Attribute<string> CommonAttributesFile::fileDate()
{
  return getNode("FILEDATE");
}

Attribute<string> CommonAttributesFile::fileType()
{
  return getNode("FILETYPE");
}

Attribute<string> CommonAttributesFile::telescope()
{
  return getNode("TELESCOPE");
}

Attribute<string> CommonAttributesFile::observer()
{
  return getNode("OBSERVER");
}

Attribute<string> CommonAttributesFile::projectID()
{
  return getNode("PROJECT_ID");
}

Attribute<string> CommonAttributesFile::projectTitle()
{
  return getNode("PROJECT_TITLE");
}

Attribute<string> CommonAttributesFile::projectPI()
{
  return getNode("PROJECT_PI");
}

Attribute<string> CommonAttributesFile::projectCOI()
{
  return getNode("PROJECT_CO_I");
}

Attribute<string> CommonAttributesFile::projectContact()
{
  return getNode("PROJECT_CONTACT");
}

Attribute<string> CommonAttributesFile::observationID()
{
  return getNode("OBSERVATION_ID");
}

Attribute<string> CommonAttributesFile::observationStartUTC()
{
  return getNode("OBSERVATION_START_UTC");
}

Attribute<double> CommonAttributesFile::observationStartMJD()
{
  return getNode("OBSERVATION_START_MJD");
}

Attribute<string> CommonAttributesFile::observationStartTAI()
{
  return getNode("OBSERVATION_START_TAI");
}

Attribute<string> CommonAttributesFile::observationEndUTC()
{
  return getNode("OBSERVATION_END_UTC");
}

Attribute<double> CommonAttributesFile::observationEndMJD()
{
  return getNode("OBSERVATION_END_MJD");
}

Attribute<string> CommonAttributesFile::observationEndTAI()
{
  return getNode("OBSERVATION_END_TAI");
}

Attribute<unsigned> CommonAttributesFile::observationNofStations()
{
  return getNode("OBSERVATION_NOF_STATIONS");
}

Attribute< vector<string> > CommonAttributesFile::observationStationsList()
{
  return getNode("OBSERVATION_STATIONS_LIST");
}

Attribute<double> CommonAttributesFile::observationFrequencyMax()
{
  return getNode("OBSERVATION_FREQUENCY_MAX");
}

Attribute<double> CommonAttributesFile::observationFrequencyMin()
{
  return getNode("OBSERVATION_FREQUENCY_MIN");
}

Attribute<double> CommonAttributesFile::observationFrequencyCenter()
{
  return getNode("OBSERVATION_FREQUENCY_CENTER");
}

Attribute<string> CommonAttributesFile::observationFrequencyUnit()
{
  return getNode("OBSERVATION_FREQUENCY_UNIT");
}

Attribute<unsigned> CommonAttributesFile::observationNofBitsPerSample()
{
  return getNode("OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> CommonAttributesFile::clockFrequency()
{
  return getNode("CLOCK_FREQUENCY");
}

Attribute<string> CommonAttributesFile::clockFrequencyUnit()
{
  return getNode("CLOCK_FREQUENCY_UNIT");
}

Attribute<string> CommonAttributesFile::antennaSet()
{
  return getNode("ANTENNA_SET");
}

Attribute<string> CommonAttributesFile::filterSelection()
{
  return getNode("FILTER_SELECTION");
}

Attribute<string> CommonAttributesFile::target()
{
  return getNode("TARGET");
}

Attribute<string> CommonAttributesFile::systemVersion()
{
  return getNode("SYSTEM_VERSION");
}

Attribute<string> CommonAttributesFile::pipelineName()
{
  return getNode("PIPELINE_NAME");
}

Attribute<string> CommonAttributesFile::pipelineVersion()
{
  return getNode("PIPELINE_VERSION");
}

Attribute<string> CommonAttributesFile::ICDNumber()
{
  return getNode("ICD_NUMBER");
}

Attribute<string> CommonAttributesFile::ICDVersion()
{
  return getNode("ICD_VERSION");
}

Attribute<string> CommonAttributesFile::notes()
{
  return getNode("NOTES");
}

}

