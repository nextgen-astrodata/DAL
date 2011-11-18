#ifndef __COORDINATES__
#define __COORDINATES__

#include <string>
#include <hdf5.h>
#include "hdf5/HDF5Attribute.h"
#include "hdf5/HDF5GroupBase.h"

namespace LDA {

class Coordinate;
class TimeCoordinate;
class SpectralCoordinate;

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

  virtual Coordinate      coordinate( unsigned nr );

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

  Attribute< std::vector<double> >      referenceValue();
  Attribute< std::vector<double> >      referencePixel();
  Attribute< std::vector<double> >      increment();
  Attribute< std::vector<double> >      pc();
  Attribute< std::vector<double> >      axisValuesPixel();
  Attribute< std::vector<double> >      axisValuesWorld();
};

class TimeCoordinate: public Coordinate {
public:
  TimeCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}
};

class SpectralCoordinate: public Coordinate {
public:
  SpectralCoordinate( const hid_gc &parent, const std::string &name ): Coordinate(parent, name) {}
};

}

#endif
