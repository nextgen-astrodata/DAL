#ifndef __CLAFILE__
#define __CLAFILE__

#include <string>
#include <vector>
#include <hdf5.h>
#include "hdf5/Attribute.h"
#include "hdf5/File.h"

namespace DAL {

/*!
 * Wraps an HDF5 file implementing the Common LOFAR Attributes.
 */
class CommonAttributesFile: public File {
public:
  CommonAttributesFile( const std::string &filename, enum fileMode mode = READ );

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
  Attribute<std::string>  target();

  Attribute<std::string>  systemVersion();
  Attribute<std::string>  pipelineName();
  Attribute<std::string>  pipelineVersion();
  Attribute<std::string>  ICDNumber();
  Attribute<std::string>  ICDVersion();
  Attribute<std::string>  notes();

protected:
  virtual void            initNodes();
};

}

#endif

