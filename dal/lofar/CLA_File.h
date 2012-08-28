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
#ifndef DAL_CLA_FILE_H
#define DAL_CLA_FILE_H

#include <cstddef>
#include <sys/time.h>

#include <string>
#include <vector>
#include <hdf5.h>
#include "dal/hdf5/Attribute.h"
#include "dal/hdf5/File.h"

namespace DAL {

/*!
 * Wraps an HDF5 file implementing the Common LOFAR Attributes.
 */
class CLA_File: public File {
public:
  CLA_File();
  CLA_File( const std::string &filename, enum fileMode mode = READ );

  virtual ~CLA_File();

  virtual void open( const std::string &filename, enum fileMode mode = READ );
  virtual void close();

  Attribute<std::string> fileName();
  Attribute<std::string> fileDate();
  Attribute<std::string> fileType();

  Attribute<std::string>  telescope();
  Attribute<std::string>  observer();

  Attribute<std::string>  projectID();
  Attribute<std::string>  projectTitle();
  Attribute<std::string>  projectPI();
  Attribute<std::string>  projectCOI();
  Attribute<std::string>  projectContact();

  Attribute<std::string>  observationID();

  Attribute<std::string>  observationStartUTC();
  Attribute<double>       observationStartMJD();
  Attribute<std::string>  observationStartTAI();

  Attribute<std::string>  observationEndUTC();
  Attribute<double>       observationEndMJD();
  Attribute<std::string>  observationEndTAI();

  Attribute<unsigned>     observationNofStations();
  Attribute< std::vector<std::string> > observationStationsList();

  Attribute<double>       observationFrequencyMax();
  Attribute<double>       observationFrequencyMin();
  Attribute<double>       observationFrequencyCenter();
  Attribute<std::string>  observationFrequencyUnit();

  Attribute<unsigned>     observationNofBitsPerSample();
  Attribute<double>       clockFrequency();
  Attribute<std::string>  clockFrequencyUnit();
  Attribute<std::string>  antennaSet();
  Attribute<std::string>  filterSelection();
  Attribute< std::vector<std::string> >  targets();

  Attribute<std::string>  systemVersion();
  Attribute<std::string>  pipelineName();
  Attribute<std::string>  pipelineVersion();
  Attribute<std::string>  docName();
  Attribute<std::string>  docVersion();
  Attribute<std::string>  notes();

protected:
  virtual void            initNodes();

  std::string             getBasename(const std::string& filename) const;
  std::string             getFileModDate(const std::string& filename) const;
  std::string             formatFilenameTimestamp(const struct timeval& tv, const char* output_format,
                                                  const char* output_format_secs, size_t output_size) const;
};

}

#endif

