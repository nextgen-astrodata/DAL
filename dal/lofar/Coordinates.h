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
#ifndef DAL_COORDINATES_H
#define DAL_COORDINATES_H

#include <string>
#include <hdf5.h>
#include "../hdf5/Attribute.h"
#include "../hdf5/Group.h"

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

namespace dal {

class Coordinate;

/*!
 * Interface for coordinate groups.
 */
class CoordinatesGroup: public Group {
public:
  CoordinatesGroup( Group &parent, const std::string &name ): Group(parent, name) {}

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

class Coordinate: public Group {
public:
  Coordinate( Group &parent, const std::string &name ): Group(parent, name) {}

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
  NumericalCoordinate( Group &parent, const std::string &name ): Coordinate(parent, name) {}

  // linear coordinates use these attributes
  Attribute<double>                     referenceValue();
  Attribute<double>                     referencePixel();
  Attribute<double>                     increment();
  Attribute< std::vector<double> >      pc();

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
  DirectionCoordinate( Group &parent, const std::string &name ): Coordinate(parent, name) {}

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
  StringCoordinate( Group &parent, const std::string &name ): Coordinate(parent, name) {}

  Attribute<unsigned>                   axisLength();
  Attribute< std::vector<unsigned> >    axisValuesPixel();
  Attribute< std::vector<std::string> > axisValuesWorld();
};

class TimeCoordinate: public NumericalCoordinate {
public:
  TimeCoordinate( Group &parent, const std::string &name ): NumericalCoordinate(parent, name) {}

  Attribute<std::string>                referenceFrame();
};

class SpectralCoordinate: public NumericalCoordinate {
public:
  SpectralCoordinate( Group &parent, const std::string &name ): NumericalCoordinate(parent, name) {}

  Attribute<std::string>                referenceFrame();

  Attribute<double>                     restFrequency();
  Attribute<std::string>                restFrequencyUnit();

  Attribute<double>                     restWavelength();
  Attribute<std::string>                restWavelengthUnit();
};

class PolarizationCoordinate: public StringCoordinate {
public:
  PolarizationCoordinate( Group &parent, const std::string &name ): StringCoordinate(parent, name) {}
};

}

#endif

