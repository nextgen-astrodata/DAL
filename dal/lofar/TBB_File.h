#ifndef DAL_TBB_FILE_H
#define DAL_TBB_FILE_H

#include <string>
#include <vector>
#include <complex>
#include <hdf5.h>
#include "dal/hdf5/Dataset.h"
#include "dal/hdf5/Group.h"
#include "dal/hdf5/Attribute.h"
#include "dal/lofar/CLA_File.h"

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
  /*!
   * Open `filename` for reading/writing/creation.
   */
  TBB_File( const std::string &filename, enum fileMode mode = READ, bool enforceVersioning = true );

  Attribute<std::string> operatingMode();
  Attribute<unsigned>    nofStations();

  virtual std::vector<TBB_Station> stations();
  virtual TBB_Station    station( const std::string &stationName );

  virtual TBB_Trigger    trigger();

private:
  std::string            stationGroupName( const std::string &stationName );
};

class TBB_Trigger: public Group {
public:
  TBB_Trigger( Group &parent, const std::string &name ): Group(parent, name) {}

  Attribute<std::string> triggerType();
  Attribute<int>         triggerVersion();

  Attribute<int>         paramCoincidenceChannels();
  Attribute<double>      paramCoincidenceTime();
  Attribute<std::string> paramDirectionFit();
  Attribute<double>      paramElevationMin();
  Attribute<double>      paramFitVarianceMax();
};

class TBB_Station: public Group {
public:
  TBB_Station(): Group(0) {}
  TBB_Station( Group &parent, const std::string &name ): Group(parent, name) {}

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
  std::string                           dipoleDatasetName( unsigned stationID, unsigned rspID, unsigned rcuID );
};

class TBB_DipoleDataset: public Dataset<int16_t> {
public:
  TBB_DipoleDataset(): Dataset<int16_t>(0) {}
  TBB_DipoleDataset( Group &parent, const std::string &name ): Dataset<int16_t>(parent, name) {}

  Attribute<unsigned>                   stationID();
  Attribute<unsigned>                   rspID();
  Attribute<unsigned>                   rcuID();

  Attribute<double>                     sampleFrequency();
  Attribute<std::string>                sampleFrequencyUnit();

  Attribute<unsigned>                   time();
  Attribute<unsigned>                   sampleNumber();

  Attribute<unsigned>                   samplesPerFrame();
  Attribute<unsigned long long>         dataLength();
  Attribute< std::vector<unsigned> >    flagOffsets();
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
};

}

#endif

