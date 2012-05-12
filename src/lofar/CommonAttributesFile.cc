#include "CommonAttributesFile.h"

using namespace std;

namespace DAL {

CommonAttributesFile::CommonAttributesFile( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  HDF5FileBase(filename, mode, "ICD_VERSION")
{
}

void CommonAttributesFile::initNodes()
{
  HDF5FileBase::initNodes();

  addNode( new Attribute<string>(*this, "GROUPTYPE") );
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
  addNode( new Attribute<string>(*this, "TARGET") );
  addNode( new Attribute<string>(*this, "SYSTEM_VERSION") );
  addNode( new Attribute<string>(*this, "PIPELINE_NAME") );
  addNode( new Attribute<string>(*this, "PIPELINE_VERSION") );
  addNode( new Attribute<string>(*this, "ICD_NUMBER") );
  addNode( new Attribute<string>(*this, "ICD_VERSION") );
  addNode( new Attribute<string>(*this, "NOTES") );
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

