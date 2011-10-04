#ifndef __HDF5DATASET__
#define __HDF5DATASET__

// Enable for casa array support in getMatrix and setMatrix
//#define HAVE_CASA

#include <string>
#include <vector>
#include <hdf5.h>
#include "HDF5GroupBase.h"
#include "hdf5core/hid_gc.h"
#include "hdf5core/h5typemap.h"

#ifdef HAVE_CASA
#include <casa/Arrays/Array.h>
#endif

namespace LDA {

/*!
 * \class HDF5DatasetBase
 *
 * Provides generic functionality for HDF5 Datasets.
 */
template<typename T> class HDF5DatasetBase: public HDF5GroupBase {
public:
  enum Endianness { NATIVE = 0, LITTLE, BIG };

  HDF5DatasetBase( const hid_gc &parent, const std::string &name ): HDF5GroupBase(parent, name) {}

  /*!
   * Creates a new dataset with dimensions sized `dims` and can be scaled up to `maxdims`. The
   * rank of the dataset is dims.size() == maxdims.size(). A maximum of -1 represents an unbounded dimension.
   *
   * If a `filename` is given, that file will be used to store the data. The file can be provided by
   * the user, or will be created upon the first write. Note that the filename cannot be changed
   * after the dataset has been created (HDF5 1.8.7), so providing absolute paths will make the
   * dataset difficult to copy or move across systems.
   *
   * If no `filename' is given, dims == maxdims is required due to limitations of HDF5.
   *
   * `endianness` toggles whether the data is in big-endian format. Typically:
   *  NATIVE: use the endianness of the current machine
   *  LITTLE: use little-endian: ARM, x86, x86_64
   *  BIG:    use big-endian:    MIPS, POWER, PowerPC, SPARC
   */
  void create( const std::vector<ssize_t> &dims, const std::vector<ssize_t> &maxdims, const std::string &filename = "", enum Endianness endianness = NATIVE );
  virtual void create() const { throw HDF5Exception("create() not supported on a dataset"); }

  /*!
   * Returns the rank of the dataset.
   */
  size_t ndims();

  /*!
   * Returns the dimension sizes.
   */
  std::vector<ssize_t> dims();

  /*!
   * Returns the maximum dimension sizes to which this dataset can grow;
   * elements of -1 represent unbounded dimensions.
   */
  std::vector<ssize_t> maxdims();

  /*!
   * Changes the dimensionality of the dataset. Elements of -1 represent unbounded dimensions.
   * If this dataset uses internal storage (i.e. externalFiles() is empty), dimensions
   * cannot be unbounded due to limitations of HDF5.
   *
   * For now, resizing is only supported if external files are used.
   */
  void resize( const std::vector<ssize_t> &newdims );

  /*!
   * Returns a list of the external files containing data for this dataset.
   */
  std::vector<std::string> externalFiles();

  /*!
   * Retrieves any matrix of data of sizes `size` from position `pos`.
   * `buffer` must point to a memory block large enough to hold the result.
   *
   * Requires:
   *    pos.size() == size.size() == ndims()
   */
  void getMatrix( const std::vector<size_t> &pos, const std::vector<size_t> &size, T *buffer );

  /*!
   * Stores any matrix of data of sizes `size` at position `pos`.
   *
   * Requires:
   *    pos.size() == size.size() == ndims()
   */
  void setMatrix( const std::vector<size_t> &pos, const std::vector<size_t> &size, const T *buffer );

#ifdef HAVE_CASA
  /*!
   * Retrieves any matrix from position `pos`.
   *
   * Requires:
   *    buffer.ndim() == ndims()
   */
  void getMatrix( const std::vector<size_t> &pos, casa::Array<T> &buffer );

  /*!
   * Stores any matrix of data of sizes `size` at position `pos`.
   *
   * Requires:
   *    pos.size() == size.size() == ndims()
   */
  void setMatrix( const std::vector<size_t> &pos, const casa::Array<T> &buffer );

#endif

  /*!
   * Retrieves a 2D matrix of data from a 2D dataset from position `pos`.
   * `buffer` must point to a memory block large enough to hold the result.
   *
   * pos:                       position of the first sample
   * dim1, dim2, outbuffer2:    2D array, the size of which determines the amount of data to retrieve
   * dim1index, dim2index:      indices of the dimensions to query
   *
   * Requires:
   *    ndims() >= 2
   *    pos.size() == ndims()
   *    dim1index < dim2index < ndims()
   */
  void get2D( const std::vector<size_t> &pos, size_t dim1, size_t dim2, T *outbuffer2, unsigned dim1index = 0, unsigned dim2index = 1 );

  /*!
   * Stores a 2D matrix of data from a 2D dataset at position `pos`.
   *
   * pos:                       position of the first sample
   * dim1, dim2, outbuffer2:    2D array, the size of which determines the amount of data to write
   * dim1index, dim2index:      indices of the dimensions to query
   *
   * Requires:
   *    ndims() >= 2
   *    pos.size() == ndims()
   *    dim1index < dim2index < ndims()
   */
  void set2D( const std::vector<size_t> &pos, size_t dim1, size_t dim2, const T *inbuffer2, unsigned dim1index = 0, unsigned dim2index = 1 );

  /*!
   * Retrieves a 1D matrix of data from a 1D dataset from position `pos`.
   * `buffer` must point to a memory block large enough to hold the result.
   *
   * pos:                       position of the first sample
   * dim1, outbuffer1:          1D array, the size of which determines the amount of data to write
   * dim1index:                 index of the dimension to query
   *
   * Requires:
   *    ndims() >= 1
   *    pos.size() == ndims()
   *    dim1index < ndims()
   */
  void get1D( const std::vector<size_t> &pos, size_t dim1, T *outbuffer1, unsigned dim1index = 0 );

  /*!
   * Stores a 1D matrix of data from a 1D dataset at position `pos`.
   *
   * pos:                       position of the first sample
   * dim1, outbuffer1:          1D array, the size of which determines the amount of data to write
   * dim1index:                 index of the dimension to query
   *
   * Requires:
   *    ndims() >= 1
   *    pos.size() == ndims()
   *    dim1index < ndims()
   */
  void set1D( const std::vector<size_t> &pos, size_t dim1, const T *inbuffer1, unsigned dim1index = 0 );

  /*!
   * Retrieves a single value from the dataset from position `pos`.
   *
   * Requires:
   *    pos.size() == ndims()
   */
  T getScalar( const std::vector<size_t> &pos );

  /*!
   * Stores a single value into the dataset at position `pos`.
   *
   * Requires:
   *    pos.size() == ndims()
   */
  void setScalar( const std::vector<size_t> &pos, const T &value );

protected:
  virtual hid_gc *open( hid_t parent, const std::string &name ) const {
    return new hid_gc(H5Dopen2(parent, name.c_str(), H5P_DEFAULT), H5Dclose, "Could not open dataset");
  }

private:
  bool bigEndian( enum Endianness endianness ) const;

  // if the strides vector is empty, a continuous array is assumed
  void matrixIO( const std::vector<size_t> &pos, const std::vector<size_t> &size, const std::vector<size_t> &strides, T *buffer, bool read );
};

template<typename T> void HDF5DatasetBase<T>::create( const std::vector<ssize_t> &dims, const std::vector<ssize_t> &maxdims, const std::string &filename, enum Endianness endianness ) {

  const size_t rank = dims.size();

  if (maxdims.size() != rank)
    throw HDF5Exception("Current and maximum dimensions vectors must have equal length");

  // convert from ssize_t -> hsize_t
  std::vector<hsize_t> hdims(rank), hmaxdims(rank);

  for (size_t i = 0; i < rank; i++) {
    hdims[i] = dims[i];
    hmaxdims[i] = i < maxdims.size()
                    ? (maxdims[i] == -1 ? H5S_UNLIMITED : maxdims[i])
                    : dims[i];
  }

  // define the layout and the location of the data
  hid_gc_noref filespace(H5Screate_simple(rank, &hdims[0], &hmaxdims[0]), H5Sclose, "Could not create simple dataspace");

  hid_gc_noref dcpl(H5Pcreate(H5P_DATASET_CREATE), H5Pclose, "Could not create dataset creation property list (dcpl)");
  H5Pset_layout(dcpl, H5D_CONTIGUOUS);
  if (filename != "") {
    if (H5Pset_external(dcpl, filename.c_str(), 0, H5F_UNLIMITED) < 0)
      throw HDF5Exception("Could not add external file to dataset");
  }

  // create the dataset
  delete _group; _group = 0;
  _group = new hid_gc(H5Dcreate2(parent, _name.c_str(), h5typemap<T>::dataType(bigEndian(endianness)), filespace, H5P_DEFAULT, dcpl, H5P_DEFAULT), H5Dclose, "Could not create dataset");
}

template<typename T> size_t HDF5DatasetBase<T>::ndims()
{
  // TODO: this routine is often used for bounds checks. However, caching
  // ndims() might lead to concurrency issues. Maybe only cache if data
  // is read-only or only allow access through this API?

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not obtain dataspace of dataset");

  int rank = H5Sget_simple_extent_ndims(dataspace);

  if (rank < 0)
    throw HDF5Exception("Could not obtain rank of dataspace");

  return rank;
}

template<typename T> std::vector<ssize_t> HDF5DatasetBase<T>::dims()
{
  const size_t rank = ndims();
  std::vector<hsize_t> dims(rank);
  std::vector<ssize_t> result(rank);

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not obtain dataspace of dataset");

  if (H5Sget_simple_extent_dims(dataspace, &dims[0], NULL) < 0)
    throw HDF5Exception("Could not obtain dimensions of dataspace");

  for (size_t i = 0; i < rank; i++) {
    result[i] = dims[i];
  }

  return result;
}

template<typename T> std::vector<ssize_t> HDF5DatasetBase<T>::maxdims()
{
  const size_t rank = ndims();
  std::vector<hsize_t> maxdims(rank);
  std::vector<ssize_t> result(rank);

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not obtain dataspace of dataset");

  if (H5Sget_simple_extent_dims(dataspace, &maxdims[0], NULL) < 0)
    throw HDF5Exception("Could not obtain maximum dimensions of dataspace");

  for (size_t i = 0; i < rank; i++) {
    result[i] = maxdims[i];
  }

  return result;
}

template<typename T> void HDF5DatasetBase<T>::resize( const std::vector<ssize_t> &newdims )
{
  const size_t rank = ndims();
  std::vector<hsize_t> newdims_hsize_t(rank);

  if (newdims.size() != rank)
    throw HDF5Exception("resize() cannot change the number of dimensions");

  for (size_t i = 0; i < rank; i++ ) {
    newdims_hsize_t[i] = newdims[i];
  }

  if (H5Dset_extent(group(), &newdims_hsize_t[0]) < 0)
    throw HDF5Exception("Could not resize dataset");
}

template<typename T> std::vector<std::string> HDF5DatasetBase<T>::externalFiles()
{
  hid_gc_noref dcpl(H5Dget_create_plist(group()), H5Pclose, "Could not open dataset creation property list (dcpl)");

  int numfiles = H5Pget_external_count(dcpl);

  if (numfiles < 0)
    throw HDF5Exception("Could not obtain number of external files");

  std::vector<std::string> files(numfiles);

  for (int i = 0; i < numfiles; i++) {
    char buf[1024];
    if (H5Pget_external(dcpl, i, sizeof buf, buf, NULL, NULL) < 0)
      throw HDF5Exception("Could not obtain file name of external file");

    // null-terminate in case file name is >=1024 characters long
    buf[sizeof buf - 1] = 0;

    files[i] = buf;
  }

  return files;
}

template<typename T> void HDF5DatasetBase<T>::getMatrix( const std::vector<size_t> &pos, const std::vector<size_t> &size, T *buffer )
{
  const std::vector<size_t> strides(0);

  matrixIO(pos, size, strides, buffer, true);
}

template<typename T> void HDF5DatasetBase<T>::setMatrix( const std::vector<size_t> &pos, const std::vector<size_t> &size, const T *buffer )
{
  const std::vector<size_t> strides(0);

  matrixIO(pos, size, strides, const_cast<T *>(buffer), false);
}

#ifdef HAVE_CASA
template<typename T> void HDF5DatasetBase<T>::getMatrix( const std::vector<size_t> &pos, casa::Array<T> &buffer )
{
  const size_t rank = ndims();
  std::vector<size_t> size(rank), strides(rank);

  const casa::IPosition &shape = buffer.shape();
  const casa::IPosition &steps = buffer.steps();

  if (shape.size() != rank)
    throw HDF5Exception("Specified casacore array does not match dimensionality of dataset");

  for (size_t i = 0; i < rank; i++) {
    size[i] = shape[i];
    strides[i] = steps[i];
  }

  matrixIO(pos, size, strides, buffer.data(), true);
}

template<typename T> void HDF5DatasetBase<T>::setMatrix( const std::vector<size_t> &pos, const casa::Array<T> &buffer )
{
  const size_t rank = ndims();
  std::vector<size_t> size(rank), strides(rank);

  const casa::IPosition &shape = buffer.shape();
  const casa::IPosition &steps = buffer.steps();

  if (shape.size() != rank)
    throw HDF5Exception("Specified casacore array does not match dimensionality of dataset");

  for (size_t i = 0; i < rank; i++) {
    size[i] = shape[i];
    strides[i] = steps[i];
  }

  matrixIO(pos, size, strides, const_cast<T *>(buffer.data()), false);
}
#endif

template<typename T> void HDF5DatasetBase<T>::get2D( const std::vector<size_t> &pos, size_t dim1, size_t dim2, T *outbuffer2, unsigned dim1index, unsigned dim2index )
{
  std::vector<size_t> size(ndims(),1);

  if (size.size() < 2)
    throw HDF5Exception("get2D requires a dataset of at least 2 dimensions");

  if (dim1index >= size.size())
    throw HDF5Exception("First dimension index exceeds the dataset rank");

  if (dim2index >= size.size())
    throw HDF5Exception("Second dimension index exceeds the dataset rank");

  // we don't do transposes
  if (dim1index >= dim2index)
    throw HDF5Exception("Dimensions must be addressed in-order");

  size[dim1index] = dim1;
  size[dim2index] = dim2;

  getMatrix(pos, size, outbuffer2);
}

template<typename T> void HDF5DatasetBase<T>::set2D( const std::vector<size_t> &pos, size_t dim1, size_t dim2, const T *inbuffer2, unsigned dim1index, unsigned dim2index )
{
  std::vector<size_t> size(ndims(),1);

  if (size.size() < 2)
    throw HDF5Exception("set2D requires a dataset of at least 2 dimensions");

  if (dim1index >= size.size())
    throw HDF5Exception("First dimension index exceeds the dataset rank");

  if (dim2index >= size.size())
    throw HDF5Exception("Second dimension index exceeds the dataset rank");

  // we don't do transposes
  if (dim1index >= dim2index)
    throw HDF5Exception("Dimensions must be addressed in-order");

  size[dim1index] = dim1;
  size[dim2index] = dim2;

  setMatrix(pos, size, inbuffer2);
}

template<typename T> void HDF5DatasetBase<T>::get1D( const std::vector<size_t> &pos, size_t dim1, T *outbuffer1, unsigned dim1index )
{
  std::vector<size_t> size(ndims(),1);

  if (dim1index >= size.size())
    throw HDF5Exception("Dimension index exceeds the dataset rank");

  size[dim1index] = dim1;

  getMatrix(pos, size, outbuffer1);
}

template<typename T> void HDF5DatasetBase<T>::set1D( const std::vector<size_t> &pos, size_t dim1, const T *inbuffer1, unsigned dim1index )
{
  std::vector<size_t> size(ndims(),1);

  if (dim1index >= size.size())
    throw HDF5Exception("Dimension index exceeds the dataset rank");

  size[dim1index] = dim1;

  setMatrix(pos, size, inbuffer1);
}

template<typename T> T HDF5DatasetBase<T>::getScalar( const std::vector<size_t> &pos )
{
  T value;
  std::vector<size_t> size(ndims(),1);

  getMatrix(pos, size, &value);

  return value;
}

template<typename T> void HDF5DatasetBase<T>::setScalar( const std::vector<size_t> &pos, const T &value )
{
  std::vector<size_t> size(ndims(),1);

  setMatrix(pos, size, &value);
}

template<typename T>  bool HDF5DatasetBase<T>::bigEndian( enum Endianness endianness ) const
{
  switch (endianness) {
    union {
      char c[sizeof (unsigned)];
      unsigned i;
    } checker;

    case LITTLE:
      return false;

    case BIG:
      return true;

    default:
      // we don't actually know sizeof unsigned, so check for little-endianness
      checker.i = 1;
      return checker.c[0] != 1;
  };
}

template<typename T> void HDF5DatasetBase<T>::matrixIO( const std::vector<size_t> &pos, const std::vector<size_t> &size, const std::vector<size_t> &strides, T *buffer, bool read )
{
  const size_t rank = ndims();
  const bool use_strides = strides.size() == rank;

  std::vector<hsize_t> offset(rank), count(rank), stride(rank);

  if (pos.size() != rank)
    throw HDF5Exception("Specified position does not match dimensionality of dataset");

  if (size.size() != rank)
    throw HDF5Exception("Specified block size does not match dimensionality of dataset");

  for (size_t i = 0; i < rank; i++) {
    offset[i] = pos[i];
    count[i]  = size[i];
  }

  hid_gc_noref dataspace(H5Dget_space(group()), H5Sclose, "Could not retrieve dataspace of group");

  if (H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, &offset[0], NULL, &count[0], NULL) < 0)
    throw HDF5Exception("Could not select hyperslab in dataspace");

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
        count[i] = strides[i+1] / strides[i];
      }  
    }
  } else {
    for (size_t i = 0; i < rank; i++) {
      count[i]  = size[i];
    }
  }

  hid_gc_noref memspace(H5Screate_simple(rank, &count[0], NULL), H5Sclose, "Could not create simple dataspace");

  for (size_t i = 0; i < rank; i++) {
    offset[i] = 0;
    count[i]  = size[i];
  }

  if (H5Sselect_hyperslab(memspace, H5S_SELECT_SET, &offset[0], NULL, &count[0], NULL) < 0)
    throw HDF5Exception("Could not select hyperslab in dataspace");


  if (read) {
    if (H5Dread(group(), h5typemap<T>::memoryType(), memspace, dataspace, H5P_DEFAULT, buffer) < 0)
      throw HDF5Exception("Could not read data from dataset");
  } else {
    if (H5Dwrite(group(), h5typemap<T>::memoryType(), memspace, dataspace, H5P_DEFAULT, buffer) < 0)
      throw HDF5Exception("Could not write data to dataset");
  }    
}

}

#endif

