#include "Coordinates.h"

using namespace std;

namespace LDA {

Attribute< vector<double> > CoordinatesGroup::refLocationValue()
{
  return Attribute< vector<double> >(group(), "REF_LOCATION_VALUE");
}

Attribute< vector<string> > CoordinatesGroup::refLocationUnit()
{
  return Attribute< vector<string> >(group(), "REF_LOCATION_UNIT");
}

Attribute<string> CoordinatesGroup::refLocationFrame()
{
  return Attribute<string>(group(), "REF_LOCATION_FRAME");
}

Attribute<double> CoordinatesGroup::refTimeValue()
{
  return Attribute<double>(group(), "REF_TIME_VALUE");
}

Attribute<string> CoordinatesGroup::refTimeUnit()
{
  return Attribute<string>(group(), "REF_TIME_UNIT");
}

Attribute<string> CoordinatesGroup::refTimeFrame()
{
  return Attribute<string>(group(), "REF_TIME_FRAME");
}

Attribute<unsigned> CoordinatesGroup::nofCoordinates()
{
  return Attribute<unsigned>(group(), "NOF_COORDINATES");
}

Attribute<unsigned> CoordinatesGroup::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

Attribute< vector<string> > CoordinatesGroup::coordinateTypes()
{
  return Attribute< vector<string> >(group(), "COORDINATE_TYPES");
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

Coordinate CoordinatesGroup::coordinate( unsigned nr )
{
  const string type = coordinateType(nr);
  const string name = coordinateName(nr);

  if (type == "Time")
    return TimeCoordinate(group(), name);

  if (type == "Spectral")
    return SpectralCoordinate(group(), name);

  // unknown type
  return Coordinate(group(), name);
}

Attribute<string> Coordinate::coordinateType()
{
  return Attribute<string>(group(), "COORDINATE_TYPE");
}

Attribute< vector<string> > Coordinate::storageType()
{
  return Attribute< vector<string> >(group(), "STORAGE_TYPE");
}

Attribute<unsigned> Coordinate::nofAxes()
{
  return Attribute<unsigned>(group(), "NOF_AXES");
}

Attribute< vector<string> > Coordinate::axisNames()
{
  return Attribute< vector<string> >(group(), "AXIS_NAMES");
}

Attribute< vector<string> > Coordinate::axisUnits()
{
  return Attribute< vector<string> >(group(), "AXIS_UNITS");
}

Attribute< vector<double> > Coordinate::referenceValue()
{
  return Attribute< vector<double> >(group(), "REFERENCE_VALUE");
}

Attribute< vector<double> > Coordinate::referencePixel()
{
  return Attribute< vector<double> >(group(), "REFERENCE_PIXEL");
}

Attribute< vector<double> > Coordinate::increment()
{
  return Attribute< vector<double> >(group(), "INCREMENT");
}

Attribute< vector<double> > Coordinate::pc()
{
  return Attribute< vector<double> >(group(), "PC");
}

Attribute< vector<double> > Coordinate::axisValuesPixel()
{
  return Attribute< vector<double> >(group(), "AXIS_VALUES_PIXEL");
}

Attribute< vector<double> > Coordinate::axisValuesWorld()
{
  return Attribute< vector<double> >(group(), "AXIS_VALUES_WORLD");
}

}

