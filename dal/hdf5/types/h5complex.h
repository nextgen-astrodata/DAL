#ifndef DAL_H5COMPLEX_H
#define DAL_H5COMPLEX_H

#include <complex>
#include <hdf5.h>
#include "hid_gc.h"
#include "dal/hdf5/exceptions/exceptions.h"

namespace DAL {

inline hid_gc h5complexType( hid_t halftype )
{
  // assume complex type is packed
  const size_t halfsize = H5Tget_size(halftype);

  hid_gc complex_id(H5Tcreate(H5T_COMPOUND, 2 * halfsize), H5Tclose, "Could not create compound datatype for complex datatype");
  
  if (H5Tinsert(complex_id, "real", 0, halftype) < 0)
    throw HDF5Exception("Could not create real part of complex datatype");

  if (H5Tinsert(complex_id, "imag", halfsize, halftype) < 0)
    throw HDF5Exception("Could not create imaginary part of complex datatype");

  return complex_id;
}

}

#endif
