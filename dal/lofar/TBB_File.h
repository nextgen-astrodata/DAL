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

namespace dal {

class TBB_File;
class TBB_Station;
class TBB_DipoleDataset;
class TBB_DipoleGroup;
class TBB_SubbandDataset;
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

  /*! operatingMode() returns the operatingMode in which the TBB data was recorded.
   * This can be either "transient" (since v1.0) or "spectral" (since v3.0)
   */
  Attribute<std::string> operatingMode();

  Attribute<unsigned>    nofStations();

  virtual std::vector<TBB_Station> stations();
  virtual TBB_Station    station( const std::string &stationName );

  virtual TBB_Trigger    trigger();

private:
  void                   openFile( FileMode mode );
  void                   initFileNodes();

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

  // optional parameters for version >= 3.3 "spectral" operatingMode, default to 0.
  // ICD states that non-filled-in parameters should/can be present, and should contain 0 by default.
  Attribute<double>                 triggerDispersionMeasure();
  Attribute<std::string>            triggerDispersionMeasureUnit();
  Attribute<std::vector<unsigned> > time();
  Attribute<std::vector<unsigned> > sampleNumber();
  Attribute<std::string>            fitDirectionCoordinateSystem();
  Attribute<double>                 fitDirectionAngle1();
  Attribute<double>                 fitDirectionAngle2();
  Attribute<double>                 fitDirectionDistance();
  Attribute<double>                 fitDirectionVariance();
  Attribute<double>                 referenceFrequency();
  Attribute<std::vector<double> >   observatoryCoordinates();
  Attribute<std::string>            observatoryCoordinatesCoordinateSystem();
  Attribute<std::string>            triggerId();
  Attribute<std::string>            additionalInfo();

protected:
  virtual void           initNodes();
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

  //kept for backwards compatibility. This calls dipoleDataSets();
  virtual std::vector<TBB_DipoleDataset> dipoles();
  //kept for backwards compatibility. This calls dipoleDataSet(unsigned stationID, unsigned rspID, unsigned rcuID);
  virtual TBB_DipoleDataset             dipole( unsigned stationID, unsigned rspID, unsigned rcuID );

  virtual std::vector<TBB_DipoleDataset> dipoleDataSets();
  virtual TBB_DipoleDataset             dipoleDataSet( unsigned stationID, unsigned rspID, unsigned rcuID );

  virtual std::vector<TBB_DipoleGroup>  dipoleGroups();
  virtual TBB_DipoleGroup               dipoleGroup( unsigned stationID, unsigned rspID, unsigned rcuID );


private:
  std::string                           dipoleDatasetName( unsigned stationID, unsigned rspID, unsigned rcuID );

protected:
  virtual void                          initNodes();
};



class TBB_DipoleGroup: public Group {
public:
  TBB_DipoleGroup ( Group &parent, const std::string &name );

  Attribute<unsigned>                   stationID();
  Attribute<unsigned>                   rspID();
  Attribute<unsigned>                   rcuID();

  Attribute<double>                     sampleFrequency();
  Attribute<std::string>                sampleFrequencyUnit();

  Attribute<unsigned>                   nyquistZone();

  Attribute<double>                     adc2voltage();

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

  Attribute<unsigned>                   nofSubbands();
  Attribute<std::vector<unsigned> >     subbands();
  std::vector<TBB_SubbandDataset>       subbandDatasets();
  TBB_SubbandDataset                    subband( unsigned subband_nr );

private:
  std::string                           subbandDatasetName( unsigned subband_nr );

protected:
  virtual void                          initNodes();
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
  Attribute<unsigned>                   sliceNumber();

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

protected:
  virtual void                          initNodes();
};

class TBB_SubbandDataset: public Dataset<short> {
public:
  TBB_SubbandDataset( Group &parent, const std::string &name );

  Attribute<unsigned>                   time();
  Attribute<double>                     centralFrequency();
  Attribute<std::string>                centralFrequencyUnit();
  Attribute<double>                     bandwidth();
  Attribute<std::string>                bandwidthUnit();
  Attribute<double>                     timeResolution();
  Attribute<std::string>                timeResolutionUnit();
  Attribute<unsigned>                   bandNumber();
  Attribute<unsigned>                   sliceNumber();
  Attribute<unsigned>                   samplesPerFrame();
  Attribute<unsigned long long>         dataLength();
  Attribute< std::vector<Range> >       flagOffsets();

protected:
  virtual void                          initNodes();
};

}

#endif

