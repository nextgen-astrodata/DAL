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
#ifndef DAL_CASADATASETEXTEND_H
#define DAL_CASADATASETEXTEND_H

#include <casa/Arrays/Array.h>
#include "dal/hdf5/exceptions/exceptions.h"
#include "Dataset.h"

namespace DAL {

/*!
 * Adds casacore functionality to an Dataset<T> class or any of its derivatives.
 */
template<typename T, typename BASE = Dataset<T> > class CasaDatasetExtend: public BASE {
public:
  CasaDatasetExtend( const BASE &other ): BASE(other) {}

  /*!
   * Retrieves any matrix from position `pos`.
   *
   * Note that casa objects use FORTRAN dimension ordering, as opposed
   * to the C dimension ordering used throughout the rest of this
   * library.
   *
   * Requires:
   *    buffer.ndim() == ndims()
   */
  void getMatrix( const casa::IPosition &pos, casa::Array<T> &buffer );

  /*!
   * Stores any matrix of data of sizes `size` at position `pos`.
   *
   * Note that casa objects use FORTRAN dimension ordering, as opposed
   * to the C dimension ordering used throughout the rest of this
   * library.
   *
   * Requires:
   *    pos.size() == size.size() == ndims()
   */
  void setMatrix( const casa::IPosition &pos, const casa::Array<T> &buffer );
};

template<typename T, typename BASE> void CasaDatasetExtend<T,BASE>::getMatrix( const casa::IPosition &pos, casa::Array<T> &buffer )
{
  const size_t rank = BASE::ndims();
  std::vector<size_t> dpos(rank), dsize(rank), dstrides(rank);

  const casa::IPosition &shape = buffer.shape();
  const casa::IPosition &steps = buffer.steps();

  if (shape.size() != rank)
    throw HDF5Exception("Cannot get matrix as the shape of the casacore array to write into does not match the dimensionality of the dataset");

  for (size_t i = 0; i < rank; i++) {
    // casacore uses FORTRAN indexation, so swap the order of the dimensions
    dpos[i]  = pos[rank-1 -i];
    dsize[i] = shape[rank-1 -i];
    dstrides[i] = steps[rank-1 -i];
  }

  matrixIO(dpos, dsize, dstrides, buffer.data(), true);
}

template<typename T, typename BASE> void CasaDatasetExtend<T,BASE>::setMatrix( const casa::IPosition &pos, const casa::Array<T> &buffer )
{
  const size_t rank = BASE::ndims();
  std::vector<size_t> dpos(rank), dsize(rank), dstrides(rank);

  const casa::IPosition &shape = buffer.shape();
  const casa::IPosition &steps = buffer.steps();

  if (shape.size() != rank)
    throw HDF5Exception("Cannot set matrix as the shape of the casacore array to read from does not match the dimensionality of the dataset");

  for (size_t i = 0; i < rank; i++) {
    // casacore uses FORTRAN indexation, so swap the order of the dimensions
    dpos[i]  = pos[rank-1 -i];
    dsize[i] = shape[rank-1 -i];
    dstrides[i] = steps[rank-1 -i];
  }

  matrixIO(dpos, dsize, dstrides, const_cast<T *>(buffer.data()), false);
}

}

#endif
