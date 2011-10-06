#ifndef __CASADATASETBASE__
#define __CASADATASETBASE__

#include <casa/Arrays/Array.h>
#include "HDF5DatasetBase.h"

namespace LDA {

template<typename T> class CasaDatasetBase: public HDF5DatasetBase<T> {
public:
  CasaDatasetBase( const HDF5DatasetBase<T> &other ): HDF5DatasetBase<T>(other) {}

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

template<typename T> void CasaDatasetBase<T>::getMatrix( const casa::IPosition &pos, casa::Array<T> &buffer )
{
  const size_t rank = this->ndims();
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

template<typename T> void CasaDatasetBase<T>::setMatrix( const casa::IPosition &pos, const casa::Array<T> &buffer )
{
  const size_t rank = this->ndims();
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
