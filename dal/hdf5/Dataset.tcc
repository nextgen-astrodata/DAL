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
namespace DAL {

template<typename T> Dataset<T>& Dataset<T>::create( const std::vector<ssize_t> &dims,
        const std::vector<ssize_t> &maxdims, const std::string &filename, enum Endianness endianness ) {

  const size_t rank = dims.size();

  if (!maxdims.empty() && maxdims.size() != rank)
    throw DALValueError("Current and maximum dimensions vectors must have equal length to create dataset " + _name);

  // convert from ssize_t -> hsize_t
  std::vector<hsize_t> hdims(rank), hmaxdims(rank);

  for (size_t i = 0; i < rank; i++) {
    hdims[i] = dims[i];
    hmaxdims[i] = i < maxdims.size()
                    ? (maxdims[i] == -1 ? H5S_UNLIMITED : maxdims[i])
                    : dims[i];
  }

  // define the layout and the location of the data
  hid_gc_noref filespace(H5Screate_simple(rank, &hdims[0], &hmaxdims[0]), H5Sclose, "Could not create simple dataspace " + _name);

  hid_gc_noref dcpl(H5Pcreate(H5P_DATASET_CREATE), H5Pclose, "Could not create dataset creation property list to create dataset " + _name);

  // avoid HDF5 chunked storage: not faster for our dense data sets and riskier integrity-wise
  H5Pset_layout(dcpl, H5D_CONTIGUOUS);

  if (filename != "") {
    if (H5Pset_external(dcpl, filename.c_str(), 0, H5F_UNLIMITED) < 0)
      throw HDF5Exception("Could not add external file to create dataset " + _name);
  }

  // create the dataset
  _group = hid_gc(H5Dcreate2(parent, _name.c_str(), h5typemap<T>::dataType(bigEndian(endianness)),
                  filespace, H5P_DEFAULT, dcpl, H5P_DEFAULT), H5Dclose, "Could not create dataset " + _name);

  return *this;
}

template<typename T> Dataset<T>& Dataset<T>::create1D( ssize_t len, ssize_t maxlen,
        const std::string &filename, enum Endianness endianness ) {
  std::vector<ssize_t> vdims(1, len);
  std::vector<ssize_t> vmaxdims(1, maxlen);
  Dataset<T>::create(vdims, vmaxdims, filename, endianness);
  return *this;
}

template<typename T> size_t Dataset<T>::ndims()
{
  // TODO: this routine is often used for bounds checks. However, caching
  // ndims() might lead to concurrency issues. Maybe only cache if data
  // is read-only or only allow access through this API?

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not get dataspace to get number of dimenstions of dataset " + _name);

  int rank = H5Sget_simple_extent_ndims(dataspace);

  if (rank < 0)
    throw HDF5Exception("Could not get number of dimensions of dataset " + _name);

  return rank;
}

template<typename T> std::vector<ssize_t> Dataset<T>::dims()
{
  const size_t rank = ndims();
  std::vector<hsize_t> dims(rank);
  std::vector<ssize_t> result(rank);

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not get dataspace to get number of dimensions of dataset " + _name);

  if (H5Sget_simple_extent_dims(dataspace, &dims[0], NULL) < 0)
    throw HDF5Exception("Could not get number of dimensions of dataset " + _name);

  for (size_t i = 0; i < rank; i++) {
    result[i] = dims[i];
  }

  return result;
}

template<typename T> ssize_t Dataset<T>::dims1D()
{
  return Dataset<T>::dims()[0];
}

template<typename T> std::vector<ssize_t> Dataset<T>::maxdims()
{
  const size_t rank = ndims();
  std::vector<hsize_t> maxdims(rank);
  std::vector<ssize_t> result(rank);

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not get dataspace to get maximum dimensions of dataset " + _name);

  if (H5Sget_simple_extent_dims(dataspace, NULL, &maxdims[0]) < 0)
    throw HDF5Exception("Could not get maximum dimensions of dataset " + _name);

  for (size_t i = 0; i < rank; i++) {
    result[i] = maxdims[i];
  }

  return result;
}

template<typename T> ssize_t Dataset<T>::maxdims1D()
{
  return Dataset<T>::maxdims()[0];
}

template<typename T> void Dataset<T>::resize( const std::vector<ssize_t> &newdims )
{
  const size_t rank = ndims();
  std::vector<hsize_t> newdims_hsize_t(rank);

  if (newdims.size() != rank)
    throw DALValueError("Cannot resize the number of dimensions of dataset " + _name);

  for (size_t i = 0; i < rank; i++ ) {
    newdims_hsize_t[i] = newdims[i];
  }

  if (H5Dset_extent(group(), &newdims_hsize_t[0]) < 0)
    throw HDF5Exception("Could not resize dataset " + _name);
}

template<typename T> void Dataset<T>::resize1D( ssize_t newlen )
{
  std::vector<ssize_t> newdims(1, newlen);
  Dataset<T>::resize(newdims);
}

template<typename T> std::vector<std::string> Dataset<T>::externalFiles()
{
  hid_gc_noref dcpl(H5Dget_create_plist(group()), H5Pclose, "Could not open dataset creation property list to get external files of dataset " + _name);

  int numfiles = H5Pget_external_count(dcpl);

  if (numfiles < 0)
    throw HDF5Exception("Could not get number of external files for dataset " + _name);

  std::vector<std::string> files(numfiles);

  for (int i = 0; i < numfiles; i++) {
    char buf[1024];
    if (H5Pget_external(dcpl, i, sizeof buf, buf, NULL, NULL) < 0)
      throw HDF5Exception("Could not get file name of external file for dataset " + _name);

    // null-terminate in case file name is >=1024 characters long
    buf[sizeof buf - 1] = 0;

    files[i] = buf;
  }

  return files;
}

template<typename T> void Dataset<T>::getMatrix( const std::vector<size_t> &pos,
        T *buffer, const std::vector<size_t> &size )
{
  const std::vector<size_t> strides(0);

  matrixIO(pos, buffer, size, strides, true);
}

template<typename T> void Dataset<T>::setMatrix( const std::vector<size_t> &pos,
        const T *buffer, const std::vector<size_t> &size )
{
  const std::vector<size_t> strides(0);

  matrixIO(pos, const_cast<T *>(buffer), size, strides, false);
}

template<typename T> void Dataset<T>::get2D( const std::vector<size_t> &pos,
        T *outbuffer2, size_t dim1, size_t dim2, unsigned dim1index, unsigned dim2index )
{
  std::vector<size_t> size(ndims(), 1);

  if (size.size() < 2)
    throw DALValueError("Cannot get2D on fewer than 2 dimensional dataset " + _name);

  if (dim1index >= size.size())
    throw DALIndexError("Cannot get2D if first dimension index exceeds rank for dataset " + _name);

  if (dim2index >= size.size())
    throw DALIndexError("Cannot get2D if second dimension index exceeds rank for dataset " + _name);

  // we don't do transposes
  if (dim1index >= dim2index)
    throw DALValueError("Cannot get2D if dimensions are not addressed in-order for dataset " + _name);

  size[dim1index] = dim1;
  size[dim2index] = dim2;

  getMatrix(pos, outbuffer2, size);
}

template<typename T> void Dataset<T>::set2D( const std::vector<size_t> &pos,
        const T *inbuffer2, size_t dim1, size_t dim2, unsigned dim1index, unsigned dim2index )
{
  std::vector<size_t> size(ndims(), 1);

  if (size.size() < 2)
    throw DALValueError("Cannot set2D on fewer than 2 dimensional dataset " + _name);

  if (dim1index >= size.size())
    throw DALIndexError("Cannot set2D if first dimension index exceeds rank for dataset " + _name);

  if (dim2index >= size.size())
    throw DALIndexError("Cannot set2D if second dimension index exceeds rank for dataset " + _name);

  // we don't do transposes
  if (dim1index >= dim2index)
    throw DALValueError("Cannot set2D if dimensions are not addressed in-order for dataset " + _name);

  size[dim1index] = dim1;
  size[dim2index] = dim2;

  setMatrix(pos, inbuffer2, size);
}

template<typename T> void Dataset<T>::get3D( const std::vector<size_t> &pos,
        T *outbuffer3, size_t dim1, size_t dim2, size_t dim3, unsigned dim1index, unsigned dim2index, unsigned dim3index )
{
  std::vector<size_t> size(ndims(), 1);

  if (size.size() < 3)
    throw DALValueError("Cannot get3D on fewer than 3 dimensional dataset " + _name);

  if (dim1index >= size.size())
    throw DALIndexError("Cannot get3D if first dimension index exceeds rank for dataset " + _name);

  if (dim2index >= size.size())
    throw DALIndexError("Cannot get3D if second dimension index exceeds rank for dataset " + _name);

  if (dim3index >= size.size())
    throw DALIndexError("Cannot get3D if third dimension index exceeds rank for dataset " + _name);

  // we don't do transposes
  if (dim1index >= dim2index || dim2index >= dim3index)
    throw DALValueError("Cannot get3D if dimensions are not addressed in-order for dataset " + _name);

  size[dim1index] = dim1;
  size[dim2index] = dim2;
  size[dim3index] = dim3;

  getMatrix(pos, outbuffer3, size);
}

template<typename T> void Dataset<T>::set3D( const std::vector<size_t> &pos,
        const T *inbuffer3, size_t dim1, size_t dim2, size_t dim3, unsigned dim1index, unsigned dim2index, unsigned dim3index )
{
  std::vector<size_t> size(ndims(), 1);

  if (size.size() < 3)
    throw DALValueError("Cannot set3D on fewer than 3 dimensional dataset " + _name);

  if (dim1index >= size.size())
    throw DALIndexError("Cannot set3D if first dimension index exceeds rank for dataset " + _name);

  if (dim2index >= size.size())
    throw DALIndexError("Cannot set3D if second dimension index exceeds rank for dataset " + _name);

  if (dim3index >= size.size())
    throw DALIndexError("Cannot set3D if third dimension index exceeds rank for dataset " + _name);

  // we don't do transposes
  if (dim1index >= dim2index || dim2index >= dim3index)
    throw DALValueError("Cannot set3D if dimensions are not addressed in-order for dataset " + _name);

  size[dim1index] = dim1;
  size[dim2index] = dim2;
  size[dim3index] = dim3;

  setMatrix(pos, inbuffer3, size);
}

template<typename T> void Dataset<T>::get1D( size_t pos, T *outbuffer, size_t len,
        unsigned dimIndex )
{
  std::vector<size_t> size(ndims(), 1);

  if (dimIndex >= size.size())
    throw DALIndexError("Cannot get1D if dimIndex exceeds rank of dataset " + _name);

  size[dimIndex] = len;
  std::vector<size_t> vpos(1, pos);

  getMatrix(vpos, outbuffer, size);
}

template<typename T> void Dataset<T>::set1D( size_t pos, const T *inbuffer, size_t len,
        unsigned dimIndex )
{
  std::vector<size_t> size(ndims(), 1);

  if (dimIndex >= size.size())
    throw DALIndexError("Cannot set1D if dimIndex exceeds rank of dataset " + _name);

  size[dimIndex] = len;
  std::vector<size_t> vpos(1, pos);

  setMatrix(vpos, inbuffer, size);
}

template<typename T> T Dataset<T>::getScalar( const std::vector<size_t> &pos )
{
  T value;
  std::vector<size_t> size(ndims(), 1);

  getMatrix(pos, &value, size);

  return value;
}

template<typename T> T Dataset<T>::getScalar1D( size_t pos )
{
  std::vector<size_t> vpos(1, pos);
  return Dataset<T>::getScalar(vpos);
}

template<typename T> void Dataset<T>::setScalar( const std::vector<size_t> &pos,
        const T &value )
{
  std::vector<size_t> size(ndims(), 1);

  setMatrix(pos, &value, size);
}

template<typename T> void Dataset<T>::setScalar1D( size_t pos, T value )
{
  std::vector<size_t> vpos(1, pos);
  Dataset<T>::setScalar(vpos, value);
}

template<typename T> bool Dataset<T>::bigEndian( enum Endianness endianness ) const
{
  if (endianness == LITTLE)
    return false;
  else if (endianness == BIG)
    return true;
  else // NATIVE
    return BYTE_ORDER == BIG_ENDIAN;
}

template<typename T> void Dataset<T>::matrixIO( const std::vector<size_t> &pos,
        T *buffer, const std::vector<size_t> &size, const std::vector<size_t> &strides, bool read )
{
  const size_t rank = ndims();
  const bool use_strides = strides.size() == rank;

  std::vector<hsize_t> offset(rank), count(rank), stride(rank);

  if (pos.size() != rank)
    throw DALValueError("Cannot perform matrixIO if specified position does not match dimensionality of dataset " + _name);

  if (size.size() != rank)
    throw DALValueError("Cannot perform matrixIO if specified block size does not match dimensionality of dataset " + _name);

  for (size_t i = 0; i < rank; i++) {
    offset[i] = pos[i];
    count[i]  = size[i];
  }

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not retrieve dataspace " + _name);

  if (H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, &offset[0], NULL, &count[0], NULL) < 0)
    throw HDF5Exception("Could not select hyperslab to perform matrixIO on dataset " + _name);

  if (use_strides) {
    // HDF5 doesn't support strides directly (*), so we present it with a larger continuous array which matches
    // the strides. By subsequently only requesting to read a small portion of the array, everything works out.
    
    // (*) The strides in H5Sselect_hyperslab actually indicate how many elements to skip in each dimension,
    //     /not/ the distance between neighbouring elements in memory.
    for (size_t i = 0; i < rank; i++) {
      if (i == rank - 1) {
        // no need to extend the last dimension
        count[i] = size[i];
      } else {  
        count[i] = strides[i] / strides[i+1];
      }
    }
  } else {
    for (size_t i = 0; i < rank; i++) {
      count[i]  = size[i];
    }
  }

  hid_gc_noref memspace(H5Screate_simple(rank, &count[0], NULL), H5Sclose, "Could not create simple dataspace to perform matrixIO on dataset " + _name);

  for (size_t i = 0; i < rank; i++) {
    offset[i] = 0;
    count[i]  = size[i];
  }

  if (H5Sselect_hyperslab(memspace, H5S_SELECT_SET, &offset[0], NULL, &count[0], NULL) < 0)
    throw HDF5Exception("Could not select hyperslab (2) to perform matrixIO on dataset " + _name);


  if (read) {
    if (H5Dread(group(), h5typemap<T>::memoryType(), memspace, dataspace, H5P_DEFAULT, buffer) < 0)
      throw HDF5Exception("Could not perform matrixIO to read data from dataset " + _name);
  } else {
    if (H5Dwrite(group(), h5typemap<T>::memoryType(), memspace, dataspace, H5P_DEFAULT, buffer) < 0)
      throw HDF5Exception("Could not perform matrixIO to write data to dataset " + _name);
  }    
}

}

