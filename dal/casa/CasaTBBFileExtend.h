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
#ifndef DAL_CASATBBFILEEXTEND_H
#define DAL_CASATBBFILEEXTEND_H

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
      throw HDF5Exception("Cannot get position with a values vector that is not of length 3");

    MPosition::Types type;

    if (!MPosition::getType(type, frame))
      throw HDF5Exception("Cannot get position with invalid position type");

    switch (type) {
      case MPosition::ITRF:
        return MPosition(MVPosition(values[0], values[1], values[2]), type);

      case MPosition::WGS84:
        return MPosition(MVPosition(Quantity(values[0], String(unit)),
                                    Quantity(values[1], String(unit)),
                                    Quantity(values[2], String(unit))), type);

      default:
        throw HDF5Exception("Cannot get position with an unsupported position type");
    }
  }
};

}

#endif
