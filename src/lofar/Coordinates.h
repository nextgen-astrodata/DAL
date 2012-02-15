#ifndef __COORDINATES__
#define __COORDINATES__

#include <string>
#include <hdf5.h>
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5GroupBase.h"

/*
 * The coordinate system is described in ICD002, to closely match the FITS WCS (World Coordinate System) specification.
 *
 * Several types of coordinates exist:
 *      - Time
 *      - Spectral
 *      - Polarization
 *      - Direction
 *      - FaradayDepth
 * as well as any user-defined types, typically:
 *      - Direction
 *      - Linear
 *      - Tabular<P,W> (P = pixel type (unsigned/int/double), W = world type (double/string))
 */

namespace DAL {

class Coordinate;

/*!
 * Coordinate groups as defined in ICD002.
 */
class CoordinatesGroup: public HDF5GroupBase {
public:
  CoordinatesGroup( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute< std::vector<double> >      refLocationValue();
  Attribute< std::vector<std::string> > refLocationUnit();
  Attribute<std::string>  refLocationFrame();

  Attribute<double>       refTimeValue();
  Attribute<std::string>  refTimeUnit();
  Attribute<std::string>  refTimeFrame();

  Attribute<unsigned>     nofCoordinates();
  Attribute<unsigned>     nofAxes();
  Attribute< std::vector<std::string> > coordinateTypes();

  virtual Coordinate *    coordinate( unsigned nr );

protected:
  std::string             coordinateType( unsigned nr );
  std::string             coordinateName( unsigned nr );
};

class Coordinate: public HDF5GroupBase {
public:
  Coordinate( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  Attribute<std::string>  coordinateType();
  Attribute< std::vector<std::string> > storageType();

  Attribute<unsigned>     nofAxes();
  Attribute< std::vector<std::string> > axisNames();
  Attribute< std::vector<std::string> > axisUnits();
};

/*!
 * A coordinate which translates unsigned (pixel) <--> double (world). Defines 1 axis, which
 * can be linear or tabular.
 */
class NumericalCoordinate: public Coordinate {
public:
  NumericalCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}

  // linear coordinates use these attributes
  Attribute<double>                     referenceValue();
  Attribute<double>                     referencePixel();
  Attribute<double>                     increment();

  // tabular coordinates use these attributes
  Attribute<unsigned>                   axisLength();
  Attribute< std::vector<unsigned> >    axisValuesPixel();
  Attribute< std::vector<double> >      axisValuesWorld();
};

/*!
 * A coordinate which translates unsigned (pixel) <--> double (world) through a non-linear
 * transformation. Defines 2 (or more) linear axes.
 */
class DirectionCoordinate: public Coordinate {
public:
  DirectionCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}

  Attribute< std::vector<double> >      referenceValue();
  Attribute< std::vector<double> >      referencePixel();
  Attribute< std::vector<double> >      increment();
  Attribute< std::vector<double> >      pc();

  Attribute<std::string>                equinox();
  Attribute<std::string>                radecSys();
  Attribute<std::string>                projection();
  Attribute< std::vector<double> >      projectionParam();
  Attribute<double>                     lonPole();
  Attribute<double>                     latPole();
};

/*!
 * A coordinate which translates unsigned (pixel) <--> string (world). Defines 1 tabular axis.
 */
class StringCoordinate: public Coordinate {
public:
  StringCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}

  Attribute<unsigned>                   axisLength();
  Attribute< std::vector<unsigned> >    axisValuesPixel();
  Attribute< std::vector<std::string> > axisValuesWorld();
};

class TimeCoordinate: public NumericalCoordinate {
public:
  TimeCoordinate( const hid_gc &parent, const std::string &name ): NumericalCoordinate(parent, name) {}

  Attribute<std::string>                referenceFrame();
};

class SpectralCoordinate: public NumericalCoordinate {
public:
  SpectralCoordinate( const hid_gc &parent, const std::string &name ): NumericalCoordinate(parent, name) {}

  Attribute<std::string>                referenceFrame();

  Attribute<double>                     restFrequency();
  Attribute<std::string>                restFrequencyUnit();

  Attribute<double>                     restWavelength();
  Attribute<std::string>                restWavelengthUnit();
};

class PolarizationCoordinate: public StringCoordinate {
public:
  PolarizationCoordinate( const hid_gc &parent, const std::string &name ): StringCoordinate(parent, name) {}
};

}

#endif

