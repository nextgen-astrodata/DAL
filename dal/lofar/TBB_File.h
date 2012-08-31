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
#ifndef DAL_TBB_FILE_H
#define DAL_TBB_FILE_H

#include <string>
#include <vector>
#include <complex>
#include <hdf5.h>
#include "CLA_File.h"
#include "Flagging.h"
#include "../hdf5/Dataset.h"

namespace DAL {

class TBB_File;
class TBB_Station;
class TBB_DipoleDataset;
class TBB_Trigger;

/*!
 * Interface for TBB Time-Series Data.
 */
class TBB_File: public CLA_File {
public:
  TBB_File();

  /*!
   * Open `filename` for reading/writing/creation.
   */
  TBB_File( const std::string &filename, FileMode mode = READ );

  virtual ~TBB_File();

  virtual void open( const std::string &filename, FileMode mode = READ );
  virtual void close();

  Attribute<std::string> operatingMode();
  Attribute<unsigned>    nofStations();

  virtual std::vector<TBB_Station> stations();
  virtual TBB_Station    station( const std::string &stationName );

  virtual TBB_Trigger    trigger();

private:
  void                   openFile( FileMode mode );
  void                   initNodes();

  std::string            stationGroupName( const std::string &stationName );
};

class TBB_Trigger: public Group {
public:
  TBB_Trigger( Group &parent, const std::string &name );

  Attribute<std::string> triggerType();
  Attribute<int>         triggerVersion();

  Attribute<int>         paramCoincidenceChannels();
  Attribute<double>      paramCoincidenceTime();
  Attribute<std::string> paramDirectionFit();
  Attribute<double>      paramElevationMin();
  Attribute<double>      paramFitVarianceMax();

private:
  void                   initNodes();
};

class TBB_Station: public Group {
public:
  TBB_Station( Group &parent, const std::string &name );

  Attribute<std::string>                stationName();

  Attribute< std::vector<double> >      stationPosition();
  Attribute<std::string>                stationPositionUnit();
  Attribute<std::string>                stationPositionFrame();

  Attribute< std::vector<double> >      beamDirection();
  Attribute<std::string>                beamDirectionUnit();
  Attribute<std::string>                beamDirectionFrame();

  Attribute<double>                     clockOffset();
  Attribute<std::string>                clockOffsetUnit();

  Attribute<unsigned>                   nofDipoles();

  virtual std::vector<TBB_DipoleDataset> dipoles();
  virtual TBB_DipoleDataset             dipole( unsigned stationID, unsigned rspID, unsigned rcuID );

private:
  void                                  initNodes();
  std::string                           dipoleDatasetName( unsigned stationID, unsigned rspID, unsigned rcuID );
};

class TBB_DipoleDataset: public Dataset<short> {
public:
  TBB_DipoleDataset( Group &parent, const std::string &name );

  Attribute<unsigned>                   stationID();
  Attribute<unsigned>                   rspID();
  Attribute<unsigned>                   rcuID();

  Attribute<double>                     sampleFrequency();
  Attribute<std::string>                sampleFrequencyUnit();

  Attribute<unsigned>                   time();
  Attribute<unsigned>                   sampleNumber();

  Attribute<unsigned>                   samplesPerFrame();
  Attribute<unsigned long long>         dataLength();
  Attribute< std::vector<Range> >       flagOffsets();
  Attribute<unsigned>                   nyquistZone();

  Attribute<double>                     cableDelay();
  Attribute<std::string>                cableDelayUnit();

  Attribute<double>                     dipoleCalibrationDelay();
  Attribute<std::string>                dipoleCalibrationDelayUnit();
  Attribute< std::vector<std::complex<double> > > dipoleCalibrationGainCurve();

  Attribute< std::vector<double> >      antennaPosition();
  Attribute<std::string>                antennaPositionUnit();
  Attribute<std::string>                antennaPositionFrame();
  Attribute< std::vector<double> >      antennaNormalVector();
  Attribute< std::vector<double> >      antennaRotationMatrix(); // 3 x 3, row-minor

  Attribute< std::vector<double> >      tileBeam();
  Attribute<std::string>                tileBeamUnit();
  Attribute<std::string>                tileBeamFrame();

  Attribute<double>                     dispersionMeasure();
  Attribute<std::string>                dispersionMeasureUnit();

private:
  void                                  initNodes();
};

}

#endif

