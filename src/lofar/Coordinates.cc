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

Coordinate *CoordinatesGroup::coordinate( unsigned nr )
{
  const string type = coordinateType(nr);
  const string name = coordinateName(nr);

  if (type == "Time")
    return new TimeCoordinate(group(), name);

  if (type == "Spectral")
    return new SpectralCoordinate(group(), name);

  if (type == "Direction")
    return new DirectionCoordinate(group(), name);

  if (type == "Polarization")
    return new PolarizationCoordinate(group(), name);

  /* TODO:
    type == "FaradayDepth" ??
  */  

  // unknown type
  return new Coordinate(group(), name);
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

Attribute<double> NumericalCoordinate::referenceValue()
{
  return Attribute<double>(group(), "REFERENCE_VALUE");
}

Attribute<double> NumericalCoordinate::referencePixel()
{
  return Attribute<double>(group(), "REFERENCE_PIXEL");
}

Attribute<double> NumericalCoordinate::increment()
{
  return Attribute<double>(group(), "INCREMENT");
}

Attribute<unsigned> NumericalCoordinate::axisLength()
{
  return Attribute<unsigned>(group(), "AXIS_LENGTH");
}

Attribute< vector<unsigned> > NumericalCoordinate::axisValuesPixel()
{
  return Attribute< vector<unsigned> >(group(), "AXIS_VALUES_PIXEL");
}

Attribute< vector<double> > NumericalCoordinate::axisValuesWorld()
{
  return Attribute< vector<double> >(group(), "AXIS_VALUES_WORLD");
}


Attribute< vector<double> > DirectionCoordinate::referenceValue()
{
  return Attribute< vector<double> >(group(), "REFERENCE_VALUE");
}

Attribute< vector<double> > DirectionCoordinate::referencePixel()
{
  return Attribute< vector<double> >(group(), "REFERENCE_PIXEL");
}

Attribute< vector<double> > DirectionCoordinate::increment()
{
  return Attribute< vector<double> >(group(), "INCREMENT");
}

Attribute< vector<double> > DirectionCoordinate::pc()
{
  return Attribute< vector<double> >(group(), "PC");
}

Attribute<string> DirectionCoordinate::equinox()
{
  return Attribute<string>(group(), "EQUINOX");
}

Attribute<string> DirectionCoordinate::radecSys()
{
  return Attribute<string>(group(), "RADEC_SYS");
}

Attribute<string> DirectionCoordinate::projection()
{
  return Attribute<string>(group(), "PROJECTION");
}

Attribute< vector<double> > DirectionCoordinate::projectionParam()
{
  return Attribute< vector<double> >(group(), "PROJECTION_PARAM");
}

Attribute<double> DirectionCoordinate::lonPole()
{
  return Attribute<double>(group(), "LONPOLE");
}

Attribute<double> DirectionCoordinate::latPole()
{
  return Attribute<double>(group(), "LATPOLE");
}

Attribute<unsigned> StringCoordinate::axisLength()
{
  return Attribute<unsigned>(group(), "AXIS_LENGTH");
}

Attribute< vector<unsigned> > StringCoordinate::axisValuesPixel()
{
  return Attribute< vector<unsigned> >(group(), "AXIS_VALUES_PIXEL");
}

Attribute< vector<string> > StringCoordinate::axisValuesWorld()
{
  return Attribute< vector<string> >(group(), "AXIS_VALUES_WORLD");
}

Attribute<string> TimeCoordinate::referenceFrame()
{
  return Attribute<string>(group(), "REFERENCE_FRAME");
}

Attribute<string> SpectralCoordinate::referenceFrame()
{
  return Attribute<string>(group(), "REFERENCE_FRAME");
}

Attribute<double> SpectralCoordinate::restFrequency()
{
  return Attribute<double>(group(), "REST_FREQUENCY");
}

Attribute<string> SpectralCoordinate::restFrequencyUnit()
{
  return Attribute<string>(group(), "REST_FREQUENCY_UNIT");
}

Attribute<double> SpectralCoordinate::restWavelength()
{
  return Attribute<double>(group(), "REST_WAVELENGTH");
}

Attribute<string> SpectralCoordinate::restWavelengthUnit()
{
  return Attribute<string>(group(), "REST_WAVELENGTH_UNIT");
}

}

