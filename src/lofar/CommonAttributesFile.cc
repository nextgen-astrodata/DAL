#include "CommonAttributesFile.h"

using namespace std;

namespace DAL {

CommonAttributesFile::CommonAttributesFile( const std::string &filename, enum HDF5FileBase::fileMode mode )
:
  HDF5FileBase(filename, mode)
{
}

Attribute<string> CommonAttributesFile::groupType()
{
  return Attribute<string>(*this, "GROUPTYPE");
}

Attribute<string> CommonAttributesFile::fileName()
{
  return Attribute<string>(*this, "FILENAME");
}

Attribute<string> CommonAttributesFile::fileDate()
{
  return Attribute<string>(*this, "FILEDATE");
}

Attribute<string> CommonAttributesFile::fileType()
{
  return Attribute<string>(*this, "FILETYPE");
}

Attribute<string> CommonAttributesFile::telescope()
{
  return Attribute<string>(*this, "TELESCOPE");
}

Attribute<string> CommonAttributesFile::observer()
{
  return Attribute<string>(*this, "OBSERVER");
}

Attribute<string> CommonAttributesFile::projectID()
{
  return Attribute<string>(*this, "PROJECT_ID");
}

Attribute<string> CommonAttributesFile::projectTitle()
{
  return Attribute<string>(*this, "PROJECT_TITLE");
}

Attribute<string> CommonAttributesFile::projectPI()
{
  return Attribute<string>(*this, "PROJECT_PI");
}

Attribute<string> CommonAttributesFile::projectCOI()
{
  return Attribute<string>(*this, "PROJECT_CO_I");
}

Attribute<string> CommonAttributesFile::projectContact()
{
  return Attribute<string>(*this, "PROJECT_CONTACT");
}

Attribute<string> CommonAttributesFile::observationID()
{
  return Attribute<string>(*this, "OBSERVATION_ID");
}

Attribute<string> CommonAttributesFile::observationStartUTC()
{
  return Attribute<string>(*this, "OBSERVATION_START_UTC");
}

Attribute<double> CommonAttributesFile::observationStartMJD()
{
  return Attribute<double>(*this, "OBSERVATION_START_MJD");
}

Attribute<string> CommonAttributesFile::observationStartTAI()
{
  return Attribute<string>(*this, "OBSERVATION_START_TAI");
}

Attribute<string> CommonAttributesFile::observationEndUTC()
{
  return Attribute<string>(*this, "OBSERVATION_END_UTC");
}

Attribute<double> CommonAttributesFile::observationEndMJD()
{
  return Attribute<double>(*this, "OBSERVATION_END_MJD");
}

Attribute<string> CommonAttributesFile::observationEndTAI()
{
  return Attribute<string>(*this, "OBSERVATION_END_TAI");
}

Attribute<unsigned> CommonAttributesFile::observationNofStations()
{
  return Attribute<unsigned>(*this, "OBSERVATION_NOF_STATIONS");
}

Attribute< vector<string> > CommonAttributesFile::observationStationsList()
{
  return Attribute< vector<string> >(*this, "OBSERVATION_STATIONS_LIST");
}

Attribute<double> CommonAttributesFile::observationFrequencyMax()
{
  return Attribute<double>(*this, "OBSERVATION_FREQUENCY_MAX");
}

Attribute<double> CommonAttributesFile::observationFrequencyMin()
{
  return Attribute<double>(*this, "OBSERVATION_FREQUENCY_MIN");
}

Attribute<double> CommonAttributesFile::observationFrequencyCenter()
{
  return Attribute<double>(*this, "OBSERVATION_FREQUENCY_CENTER");
}

Attribute<string> CommonAttributesFile::observationFrequencyUnit()
{
  return Attribute<string>(*this, "OBSERVATION_FREQUENCY_UNIT");
}

Attribute<unsigned> CommonAttributesFile::observationNofBitsPerSample()
{
  return Attribute<unsigned>(*this, "OBSERVATION_NOF_BITS_PER_SAMPLE");
}

Attribute<double> CommonAttributesFile::clockFrequency()
{
  return Attribute<double>(*this, "CLOCK_FREQUENCY");
}

Attribute<string> CommonAttributesFile::clockFrequencyUnit()
{
  return Attribute<string>(*this, "CLOCK_FREQUENCY_UNIT");
}

Attribute<string> CommonAttributesFile::antennaSet()
{
  return Attribute<string>(*this, "ANTENNA_SET");
}

Attribute<string> CommonAttributesFile::filterSelection()
{
  return Attribute<string>(*this, "FILTER_SELECTION");
}

Attribute<string> CommonAttributesFile::target()
{
  return Attribute<string>(*this, "TARGET");
}

Attribute<string> CommonAttributesFile::systemVersion()
{
  return Attribute<string>(*this, "SYSTEM_VERSION");
}

Attribute<string> CommonAttributesFile::pipelineName()
{
  return Attribute<string>(*this, "PIPELINE_NAME");
}

Attribute<string> CommonAttributesFile::pipelineVersion()
{
  return Attribute<string>(*this, "PIPELINE_VERSION");
}

Attribute<string> CommonAttributesFile::ICDNumber()
{
  return Attribute<string>(*this, "ICD_NUMBER");
}

Attribute<string> CommonAttributesFile::ICDVersion()
{
  return Attribute<string>(*this, "ICD_VERSION");
}

Attribute<string> CommonAttributesFile::notes()
{
  return Attribute<string>(*this, "NOTES");
}

}

