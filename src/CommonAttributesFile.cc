#include "CommonAttributesFile.h"

using namespace std;

namespace LDA {

CommonAttributesFile::CommonAttributesFile( const string &filename, enum HDF5FileBase::fileMode mode )
:
  HDF5FileBase(filename, mode)
{
}

Attribute<string> CommonAttributesFile::groupType()
{
  return Attribute<string>(group(), "GROUPTYPE");
}

Attribute<string> CommonAttributesFile::fileName()
{
  return Attribute<string>(group(), "FILENAME");
}

Attribute<string> CommonAttributesFile::fileDate()
{
  return Attribute<string>(group(), "FILEDATE");
}

Attribute<string> CommonAttributesFile::fileType()
{
  return Attribute<string>(group(), "FILETYPE");
}

Attribute<string> CommonAttributesFile::telescope()
{
  return Attribute<string>(group(), "TELESCOPE");
}

Attribute<string> CommonAttributesFile::observer()
{
  return Attribute<string>(group(), "OBSERVER");
}

Attribute<string> CommonAttributesFile::projectID()
{
  return Attribute<string>(group(), "PROJECT_ID");
}

Attribute<string> CommonAttributesFile::projectTitle()
{
  return Attribute<string>(group(), "PROJECT_TITLE");
}

Attribute<string> CommonAttributesFile::projectPI()
{
  return Attribute<string>(group(), "PROJECT_PI");
}

Attribute<string> CommonAttributesFile::projectCOI()
{
  return Attribute<string>(group(), "PROJECT_CO_I");
}

Attribute<string> CommonAttributesFile::projectContact()
{
  return Attribute<string>(group(), "PROJECT_CONTACT");
}

Attribute<string> CommonAttributesFile::observationID()
{
  return Attribute<string>(group(), "OBSERVATION_ID");
}

Attribute<string> CommonAttributesFile::observationStartUTC()
{
  return Attribute<string>(group(), "OBSERVATION_START_UTC");
}

Attribute<double> CommonAttributesFile::observationStartMJD()
{
  return Attribute<double>(group(), "OBSERVATION_START_MJD");
}

Attribute<string> CommonAttributesFile::observationStartTAI()
{
  return Attribute<string>(group(), "OBSERVATION_START_TAI");
}

Attribute<string> CommonAttributesFile::observationEndUTC()
{
  return Attribute<string>(group(), "OBSERVATION_END_UTC");
}

Attribute<double> CommonAttributesFile::observationEndMJD()
{
  return Attribute<double>(group(), "OBSERVATION_END_MJD");
}

Attribute<string> CommonAttributesFile::observationEndTAI()
{
  return Attribute<string>(group(), "OBSERVATION_END_TAI");
}

Attribute<unsigned> CommonAttributesFile::observationNofStations()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_STATIONS");
}

Attribute< vector<string> > CommonAttributesFile::observationStationsList()
{
  return Attribute< vector<string> >(group(), "OBSERVATION_STATIONS_LIST");
}

Attribute<double> CommonAttributesFile::observationFrequencyMax()
{
  return Attribute<double>(group(), "OBSERVATION_FREQUENCY_MAX");
}

Attribute<double> CommonAttributesFile::observationFrequencyMin()
{
  return Attribute<double>(group(), "OBSERVATION_FREQUENCY_MIN");
}

Attribute<double> CommonAttributesFile::observationFrequencyCenter()
{
  return Attribute<double>(group(), "OBSERVATION_FREQUENCY_CENTER");
}

Attribute<string> CommonAttributesFile::observationFrequencyUnit()
{
  return Attribute<string>(group(), "OBSERVATION_FREQUENCY_UNIT");
}

Attribute<unsigned> CommonAttributesFile::observationNofBitsPerSample()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> CommonAttributesFile::clockFrequency()
{
  return Attribute<double>(group(), "CLOCK_FREQUENCY");
}

Attribute<string> CommonAttributesFile::clockFrequencyUnit()
{
  return Attribute<string>(group(), "CLOCK_FREQUENCY_UNIT");
}

Attribute<string> CommonAttributesFile::antennaSet()
{
  return Attribute<string>(group(), "ANTENNA_SET");
}

Attribute<string> CommonAttributesFile::filterSelection()
{
  return Attribute<string>(group(), "FILTER_SELECTION");
}

Attribute<string> CommonAttributesFile::target()
{
  return Attribute<string>(group(), "TARGET");
}

Attribute<string> CommonAttributesFile::systemVersion()
{
  return Attribute<string>(group(), "SYSTEM_VERSION");
}

Attribute<string> CommonAttributesFile::pipelineName()
{
  return Attribute<string>(group(), "PIPELINE_NAME");
}

Attribute<string> CommonAttributesFile::pipelineVersion()
{
  return Attribute<string>(group(), "PIPELINE_VERSION");
}

Attribute<string> CommonAttributesFile::ICDNumber()
{
  return Attribute<string>(group(), "ICD_NUMBER");
}

Attribute<string> CommonAttributesFile::ICDVersion()
{
  return Attribute<string>(group(), "ICD_VERSION");
}

Attribute<string> CommonAttributesFile::notes()
{
  return Attribute<string>(group(), "NOTES");
}

}
