#ifndef __CASATBBFILEEXTEND__
#define __CASATBBFILEEXTEND__

#include <casa/Measures/MPosition.h>
#include "dal/hdf5/exceptions/exceptions.h"
#include "TBB_File.h"
#include "CasaDatasetExtend.h"
#include "Attribute.h"

namespace DAL {

/*!
 * Adds casacore functionality to an Dataset<T> class or any of its derivatives.
 */
class CasaTBBDipoleDatasetExtend: public CasaDatasetExtend<short, TBB_DipoleDataset> {
public:
  CasaTBBDipoleDatasetExtend( const TBB_DipoleDataset &other ): CasaDatasetExtend<short, TBB_DipoleDataset>(other) {}

  casa::MPosition antennaPosition() {
    return getPosition( this->antennaPositionValue().get(),
                        this->antennaPositionUnit().get(),
                        this->antennaPositionFrame().get() );
  }

  void setAntennaPosition( const casa::MPosition &pos ) {
    std::string unit = pos.getUnit().getName();
    std::string frame = pos.getRefString();
    std::vector<double> values(3);

    for (unsigned i = 0; i < 3; i++) {
      values[i] = pos.getValue()(i);
    }

    this->antennaPositionValue().set(value);
    this->antennaPositionUnit().set(unit);
    this->antennaPositionFrame().set(frame);
  }

protected:
  casa::MPosition getPosition( const std::vector<double> &values, const std::string &unit, const std::string &frame ) {
    using namespace casa;

    if (values.size() != 3)
      throw HDF5Exception("Values must be an array of length 3");

    MPosition::Types type;

    if (!MPosition::getType(type, frame))
      throw HDF5Exception("Invalid position type");

    switch (type) {
      case MPosition::ITRF:
        return MPosition(MVPosition(values[0], values[1], values[2]), type);

      case MPosition::WGS84:
        return MPosition(MVPosition(Quantity(values[0], String(unit)),
                                    Quantity(values[1], String(unit)),
                                    Quantity(values[2], String(unit))), type);

      default:
        throw HDF5Exception("Cannot convert position type");
    }
  }
};

}

#endif
