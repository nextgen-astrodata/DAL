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
#ifndef DAL_BF_FILE_H
#define DAL_BF_FILE_H

#include <string>
#include <vector>
#include <hdf5.h>
#include "CLA_File.h"
#include "Coordinates.h"
#include "../hdf5/Dataset.h"

namespace DAL {

class BF_File;
class BF_SysLog;
class BF_ProcessingHistory;
class BF_SubArrayPointing;
class BF_BeamGroup;
class BF_StokesDataset;

/*!
 * Interface for Beam-formed Data.
 */
class BF_File: public CLA_File {
public:
  BF_File();

  /*!
   * Open `filename` for reading/writing/creation.
   */
  BF_File( const std::string &filename, FileMode mode = READ );

  virtual ~BF_File();

  virtual void open( const std::string &filename, FileMode mode = READ );
  virtual void close();

  Attribute<std::string>  createOfflineOnline();
  Attribute<std::string>  BFFormat();
  Attribute<std::string>  BFVersion();

  Attribute<double>       totalIntegrationTime();
  Attribute<std::string>  totalIntegrationTimeUnit();
  
  Attribute<std::string>  observationDatatype();

  Attribute<double>       subArrayPointingDiameter();
  Attribute<std::string>  subArrayPointingDiameterUnit();
  Attribute<double>       bandwidth();
  Attribute<std::string>  bandwidthUnit();
  Attribute<double>       beamDiameter();
  Attribute<std::string>  beamDiameterUnit();

  Attribute<unsigned>     observationNofSubArrayPointings();
  Attribute<unsigned>     nofSubArrayPointings();
  virtual BF_SubArrayPointing subArrayPointing( unsigned nr );

  BF_SysLog               sysLog();

protected:
  std::string             subArrayPointingName( unsigned nr );

private:
  void                    openFile( FileMode mode );
  void                    initFileNodes();
};

class BF_SysLog: public Group {
public:
  BF_SysLog( Group &parent, const std::string &name ): Group(parent, name) {}
};

class BF_ProcessingHistory: public Group {
public:
  BF_ProcessingHistory( Group &parent, const std::string &name ): Group(parent, name) {}
};

class BF_SubArrayPointing: public Group {
public:
  BF_SubArrayPointing( Group &parent, const std::string &name );

  Attribute<std::string>  expTimeStartUTC();
  Attribute<std::string>  expTimeEndUTC();

  Attribute<double>       expTimeStartMJD();
  Attribute<double>       expTimeEndMJD();

  Attribute<double>       totalIntegrationTime();
  Attribute<std::string>  totalIntegrationTimeUnit();

  Attribute<double>       pointRA();
  Attribute<std::string>  pointRAUnit();  
  Attribute<double>       pointDEC();
  Attribute<std::string>  pointDECUnit();  

  Attribute< std::vector<double> >       pointAltitude();
  Attribute< std::vector<std::string> >  pointAltitudeUnit();  
  Attribute< std::vector<double> >       pointAzimuth();
  Attribute< std::vector<std::string> >  pointAzimuthUnit();  

  Attribute<unsigned>     observationNofBeams();
  Attribute<unsigned>     nofBeams();

  virtual BF_ProcessingHistory processHistory();

  virtual BF_BeamGroup    beam( unsigned nr );

protected:
  std::string             beamName( unsigned nr );

  virtual void            initNodes();
};

class BF_BeamGroup: public Group {
public:
  BF_BeamGroup( Group &parent, const std::string &name );

  Attribute< std::vector<std::string> >  targets();

  Attribute<unsigned>     nofStations();

  Attribute< std::vector<std::string> > stationsList();

  Attribute<unsigned>     nofSamples();
  Attribute<double>       samplingRate();
  Attribute<std::string>  samplingRateUnit();
  Attribute<double>       samplingTime();
  Attribute<std::string>  samplingTimeUnit();

  Attribute<unsigned>     channelsPerSubband();
  Attribute<double>       subbandWidth();
  Attribute<std::string>  subbandWidthUnit();

  Attribute<double>       channelWidth();
  Attribute<std::string>  channelWidthUnit();

  Attribute<std::string>  tracking();

  Attribute<double>       pointRA();
  Attribute<std::string>  pointRAUnit();    
  Attribute<double>       pointDEC();
  Attribute<std::string>  pointDECUnit();  
  
  Attribute<double>       pointOffsetRA();
  Attribute<std::string>  pointOffsetRAUnit();  
  Attribute<double>       pointOffsetDEC();
  Attribute<std::string>  pointOffsetDECUnit();  

  Attribute<double>       beamDiameterRA();
  Attribute<std::string>  beamDiameterRAUnit();
  Attribute<double>       beamDiameterDEC();
  Attribute<std::string>  beamDiameterDECUnit();
  Attribute<double>       beamFrequencyCenter();
  Attribute<std::string>  beamFrequencyCenterUnit();

  Attribute<bool>         foldedData();
  Attribute<double>       foldPeriod();
  Attribute<std::string>  foldPeriodUnit();

  Attribute<std::string>  dedispersion();
  Attribute<double>       dispersionMeasure();
  Attribute<std::string>  dispersionMeasureUnit();

  Attribute<bool>         barycentered();

  Attribute<unsigned>     observationNofStokes();
  Attribute<unsigned>     nofStokes();
  Attribute< std::vector<std::string> > stokesComponents();
  Attribute<bool>         complexVoltage();
  Attribute<std::string>  signalSum();

  virtual BF_ProcessingHistory processHistory();

  virtual CoordinatesGroup coordinates();

  virtual BF_StokesDataset stokes( unsigned nr );

protected:
  std::string             stokesName( unsigned nr );
  std::string             coordinatesName();

  virtual void            initNodes();
};

class BF_StokesDataset: public Dataset<float> {
public:
  BF_StokesDataset( Group &parent, const std::string &name );

  Attribute<std::string>  dataType();

  Attribute<std::string>  stokesComponent();
  Attribute< std::vector<unsigned> >    nofChannels();
  Attribute<unsigned>     nofSubbands();
  Attribute<unsigned>     nofSamples();

protected:
  virtual void            initNodes();
};

}

#endif

