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
#include "Coordinates.h"

using namespace std;

namespace dal {

Attribute< vector<double> > CoordinatesGroup::refLocationValue()
{
  return Attribute< vector<double> >(*this, "REF_LOCATION_VALUE");
}

Attribute< vector<string> > CoordinatesGroup::refLocationUnit()
{
  return Attribute< vector<string> >(*this, "REF_LOCATION_UNIT");
}

Attribute<string> CoordinatesGroup::refLocationFrame()
{
  return Attribute<string>(*this, "REF_LOCATION_FRAME");
}

Attribute<double> CoordinatesGroup::refTimeValue()
{
  return Attribute<double>(*this, "REF_TIME_VALUE");
}

Attribute<string> CoordinatesGroup::refTimeUnit()
{
  return Attribute<string>(*this, "REF_TIME_UNIT");
}

Attribute<string> CoordinatesGroup::refTimeFrame()
{
  return Attribute<string>(*this, "REF_TIME_FRAME");
}

Attribute<unsigned> CoordinatesGroup::nofCoordinates()
{
  return Attribute<unsigned>(*this, "NOF_COORDINATES");
}

Attribute<unsigned> CoordinatesGroup::nofAxes()
{
  return Attribute<unsigned>(*this, "NOF_AXES");
}

Attribute< vector<string> > CoordinatesGroup::coordinateTypes()
{
  return Attribute< vector<string> >(*this, "COORDINATE_TYPES");
}

string CoordinatesGroup::coordinateName( unsigned nr )
{
  char buf[128];
  snprintf(buf, sizeof buf, "COORDINATE_%01u", nr);

  return string(buf);
}

string CoordinatesGroup::coordinateType( unsigned nr )
{
  if (!coordinateTypes().exists())
    return "";

  const vector<string> types = coordinateTypes().get();

  if (nr >= types.size())
    return "";

  return types[nr];
}

Coordinate *CoordinatesGroup::coordinate( unsigned nr )
{
  const string type = coordinateType(nr);
  const string name = coordinateName(nr);

  if (type == "Time")
    return new TimeCoordinate(*this, name);

  if (type == "Spectral")
    return new SpectralCoordinate(*this, name);

  if (type == "Direction")
    return new DirectionCoordinate(*this, name);

  if (type == "Polarization")
    return new PolarizationCoordinate(*this, name);

  // unknown type
  return new Coordinate(*this, name);
}

Attribute<string> Coordinate::coordinateType()
{
  return Attribute<string>(*this, "COORDINATE_TYPE");
}

Attribute< vector<string> > Coordinate::storageType()
{
  return Attribute< vector<string> >(*this, "STORAGE_TYPE");
}

Attribute<unsigned> Coordinate::nofAxes()
{
  return Attribute<unsigned>(*this, "NOF_AXES");
}

Attribute< vector<string> > Coordinate::axisNames()
{
  return Attribute< vector<string> >(*this, "AXIS_NAMES");
}

Attribute< vector<string> > Coordinate::axisUnits()
{
  return Attribute< vector<string> >(*this, "AXIS_UNITS");
}

Attribute<double> NumericalCoordinate::referenceValue()
{
  return Attribute<double>(*this, "REFERENCE_VALUE");
}

Attribute<double> NumericalCoordinate::referencePixel()
{
  return Attribute<double>(*this, "REFERENCE_PIXEL");
}

Attribute<double> NumericalCoordinate::increment()
{
  return Attribute<double>(*this, "INCREMENT");
}

Attribute< vector<double> > NumericalCoordinate::pc()
{
  return Attribute< vector<double> >(*this, "PC");
}

Attribute<unsigned> NumericalCoordinate::axisLength()
{
  return Attribute<unsigned>(*this, "AXIS_LENGTH");
}

Attribute< vector<unsigned> > NumericalCoordinate::axisValuesPixel()
{
  return Attribute< vector<unsigned> >(*this, "AXIS_VALUES_PIXEL");
}

Attribute< vector<double> > NumericalCoordinate::axisValuesWorld()
{
  return Attribute< vector<double> >(*this, "AXIS_VALUES_WORLD");
}


Attribute< vector<double> > DirectionCoordinate::referenceValue()
{
  return Attribute< vector<double> >(*this, "REFERENCE_VALUE");
}

Attribute< vector<double> > DirectionCoordinate::referencePixel()
{
  return Attribute< vector<double> >(*this, "REFERENCE_PIXEL");
}

Attribute< vector<double> > DirectionCoordinate::increment()
{
  return Attribute< vector<double> >(*this, "INCREMENT");
}

Attribute< vector<double> > DirectionCoordinate::pc()
{
  return Attribute< vector<double> >(*this, "PC");
}

Attribute<string> DirectionCoordinate::equinox()
{
  return Attribute<string>(*this, "EQUINOX");
}

Attribute<string> DirectionCoordinate::radecSys()
{
  return Attribute<string>(*this, "RADEC_SYS");
}

Attribute<string> DirectionCoordinate::projection()
{
  return Attribute<string>(*this, "PROJECTION");
}

Attribute< vector<double> > DirectionCoordinate::projectionParam()
{
  return Attribute< vector<double> >(*this, "PROJECTION_PARAM");
}

Attribute<double> DirectionCoordinate::lonPole()
{
  return Attribute<double>(*this, "LONPOLE");
}

Attribute<double> DirectionCoordinate::latPole()
{
  return Attribute<double>(*this, "LATPOLE");
}

Attribute<unsigned> StringCoordinate::axisLength()
{
  return Attribute<unsigned>(*this, "AXIS_LENGTH");
}

Attribute< vector<unsigned> > StringCoordinate::axisValuesPixel()
{
  return Attribute< vector<unsigned> >(*this, "AXIS_VALUES_PIXEL");
}

Attribute< vector<string> > StringCoordinate::axisValuesWorld()
{
  return Attribute< vector<string> >(*this, "AXIS_VALUES_WORLD");
}

Attribute<string> TimeCoordinate::referenceFrame()
{
  return Attribute<string>(*this, "REFERENCE_FRAME");
}

Attribute<string> SpectralCoordinate::referenceFrame()
{
  return Attribute<string>(*this, "REFERENCE_FRAME");
}

Attribute<double> SpectralCoordinate::restFrequency()
{
  return Attribute<double>(*this, "REST_FREQUENCY");
}

Attribute<string> SpectralCoordinate::restFrequencyUnit()
{
  return Attribute<string>(*this, "REST_FREQUENCY_UNIT");
}

Attribute<double> SpectralCoordinate::restWavelength()
{
  return Attribute<double>(*this, "REST_WAVELENGTH");
}

Attribute<string> SpectralCoordinate::restWavelengthUnit()
{
  return Attribute<string>(*this, "REST_WAVELENGTH_UNIT");
}

}

