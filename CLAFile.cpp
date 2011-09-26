#include "CLAFile.h"

using namespace std;

CLAFile::CLAFile( const string &filename, enum HDF5File::fileMode mode )
:
  HDF5File(filename, mode)
{
}

Attribute<string> CLAFile::groupType()
{
  return Attribute<string>(group(), "GROUPTYPE");
}

Attribute<string> CLAFile::fileName()
{
  return Attribute<string>(group(), "FILENAME");
}

Attribute<string> CLAFile::fileDate()
{
  return Attribute<string>(group(), "FILEDATE");
}

Attribute<string> CLAFile::fileType()
{
  return Attribute<string>(group(), "FILETYPE");
}

Attribute<string> CLAFile::telescope()
{
  return Attribute<string>(group(), "TELESCOPE");
}

Attribute<string> CLAFile::observer()
{
  return Attribute<string>(group(), "OBSERVER");
}

Attribute<string> CLAFile::projectID()
{
  return Attribute<string>(group(), "PROJECT_ID");
}

Attribute<string> CLAFile::projectTitle()
{
  return Attribute<string>(group(), "PROJECT_TITLE");
}

Attribute<string> CLAFile::projectPI()
{
  return Attribute<string>(group(), "PROJECT_PI");
}

Attribute<string> CLAFile::projectCOI()
{
  return Attribute<string>(group(), "PROJECT_CO_I");
}

Attribute<string> CLAFile::projectContact()
{
  return Attribute<string>(group(), "PROJECT_CONTACT");
}

Attribute<string> CLAFile::observationID()
{
  return Attribute<string>(group(), "OBSERVATION_ID");
}

Attribute<string> CLAFile::observationStartUTC()
{
  return Attribute<string>(group(), "OBSERVATION_START_UTC");
}

Attribute<double> CLAFile::observationStartMJD()
{
  return Attribute<double>(group(), "OBSERVATION_START_MJD");
}

Attribute<string> CLAFile::observationStartTAI()
{
  return Attribute<string>(group(), "OBSERVATION_START_TAI");
}

Attribute<string> CLAFile::observationEndUTC()
{
  return Attribute<string>(group(), "OBSERVATION_END_UTC");
}

Attribute<double> CLAFile::observationEndMJD()
{
  return Attribute<double>(group(), "OBSERVATION_END_MJD");
}

Attribute<string> CLAFile::observationEndTAI()
{
  return Attribute<string>(group(), "OBSERVATION_END_TAI");
}

Attribute<unsigned> CLAFile::observationNofStations()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_STATIONS");
}

AttributeV<string> CLAFile::observationStationsList()
{
  return AttributeV<string>(group(), "OBSERVATION_STATIONS_LIST");
}

Attribute<unsigned> CLAFile::observationNofBitsPerSample()
{
  return Attribute<unsigned>(group(), "OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> CLAFile::clockFrequency()
{
  return Attribute<double>(group(), "CLOCK_FREQUENCY");
}

Attribute<string> CLAFile::clockFrequencyUnit()
{
  return Attribute<string>(group(), "CLOCK_FREQUENCY_UNIT");
}

Attribute<string> CLAFile::antennaSet()
{
  return Attribute<string>(group(), "ANTENNA_SET");
}

Attribute<string> CLAFile::filterSelection()
{
  return Attribute<string>(group(), "FILTER_SELECTION");
}

Attribute<string> CLAFile::target()
{
  return Attribute<string>(group(), "TARGET");
}

Attribute<string> CLAFile::systemVersion()
{
  return Attribute<string>(group(), "SYSTEM_VERSION");
}

Attribute<string> CLAFile::pipelineName()
{
  return Attribute<string>(group(), "PIPELINE_NAME");
}

Attribute<string> CLAFile::pipelineVersion()
{
  return Attribute<string>(group(), "PIPELINE_VERSION");
}

Attribute<string> CLAFile::ICDNumber()
{
  return Attribute<string>(group(), "ICD_NUMBER");
}

Attribute<string> CLAFile::ICDVersion()
{
  return Attribute<string>(group(), "ICD_VERSION");
}

Attribute<string> CLAFile::notes()
{
  return Attribute<string>(group(), "NOTES");
}
