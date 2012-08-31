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
#ifndef DAL_H5COMPLEX_H
#define DAL_H5COMPLEX_H

#include <complex>
#include <hdf5.h>
#include "hid_gc.h"
#include "../exceptions/exceptions.h"

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

