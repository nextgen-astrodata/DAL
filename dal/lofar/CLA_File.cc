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
#include "CLA_File.h"

#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>
#include <libgen.h>

#include <dal/dal_version.h>

using namespace std;

namespace DAL {

CLA_File::CLA_File() {}

CLA_File::CLA_File( const std::string &filename, enum fileMode mode )
:
  File(filename, mode, "DOC_VERSION")
{
  if (mode == CREATE) {
    telescope().create().set("LOFAR");
    fileName().create().set(getBasename(filename));
    fileDate().create().set(getFileModDate(filename)); // UTC
  } else {
    bool isCompatibleFileType = false;
    try {
      isCompatibleFileType = telescope().get() == "LOFAR"/* && enforceVersioning && getStoredFileVersion() >= VersionType(2, 0, 0)*/;
    } catch (DALException& ) {
    }
    if (!isCompatibleFileType) {
      throw DALException("Failed to open file: A LOFAR data product must have /TELESCOPE=\"LOFAR\" and /VERSION>=\"2.0.0\".\n"
                         "Older data products can be upgraded or the version check can be circumvented on opening.");
    }
    // TODO: enable the right (versions of) attributes based on file type and file version here and in sub-classes; allow circumvention and unversioned fields
  }
}

CLA_File::~CLA_File() {}

void CLA_File::open( const std::string &filename, enum fileMode mode )
{
  // As long as we have no member vars, keep open() and close() simple. See File::open().
  File::open(filename, mode, "DOC_VERSION");
}

void CLA_File::close()
{
  File::close();
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

std::string CLA_File::getBasename(const std::string& filename) const {
  char* fn = strdup(filename.c_str());
  if (fn == NULL)
    throw DALException("Failed to open file: out of memory.");
  char* bn = basename(fn); // don't use ::basename(), as basename is sometimes a macro
  string bnStr(bn); // bn may point into fn, so copy before free()
  std::free(fn);
  return bnStr;
}

/*
 * Returns last mod date/time of filename, or current time of day if stat()ing fails,
 * in "YYYY-MM-DDThh:mm:ss.s" UTC format.
 * For FILEDATE attribute.
 */
std::string CLA_File::getFileModDate(const std::string& filename) const {
	struct timeval tv;
	struct stat st;

	if (stat(filename.c_str(), &st) != 0) {
		gettimeofday(&tv, NULL); // If stat() fails, this is close enough to file mod date.
	} else {
		tv.tv_sec = st.st_mtime;
#ifdef __APPLE__
		tv.tv_usec = st.st_mtimespec.tv_nsec / 1000;
#else
		tv.tv_usec = st.st_mtim.tv_nsec / 1000;
#endif
	}

	const char output_format[] = "%Y-%m-%dT%H:%M:";
	const char output_format_secs[] = "%04.1f"; // _total_ width of 4 of "ss.s"
	const char output_format_example[] = "YYYY-MM-DDThh:mm:ss.s";
	return formatFilenameTimestamp(tv, output_format, output_format_secs, sizeof(output_format_example));
}

/*
 * The output_format is without seconds. The output_size is including the '\0'.
 * Helper for in filenames and for the FILEDATE attribute.
 */
std::string CLA_File::formatFilenameTimestamp(const struct timeval& tv, const char* output_format,
                                         const char* output_format_secs, size_t output_size) const {
	struct tm tm;
	gmtime_r(&tv.tv_sec, &tm);
	double secs = tm.tm_sec + tv.tv_usec / 1000000.0;

	vector<char> date(output_size);

	size_t nwritten = strftime(&date[0], output_size, output_format, &tm);
	if (nwritten == 0) {
		date[0] = '\0';
	}
	(void)snprintf(&date[0] + nwritten, output_size - nwritten, output_format_secs, secs);

	return string(&date[0]);
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

