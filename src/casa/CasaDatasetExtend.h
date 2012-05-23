#ifndef __CASADATASETEXTEND__
#define __CASADATASETEXTEND__

#include <casa/Arrays/Array.h>
#include "hdf5/exceptions/h5exception.h"
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
    throw HDF5Exception("Specified casacore array does not match dimensionality of dataset");

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
    throw HDF5Exception("Specified casacore array does not match dimensionality of dataset");

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
