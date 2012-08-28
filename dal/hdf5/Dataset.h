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
#ifndef DAL_DATASET_H
#define DAL_DATASET_H

#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>	// dirname()

#include <string>
#include <vector>
#include <hdf5.h>
#include "types/h5typemap.h"
#include "exceptions/exceptions.h"
#include "Group.h"

namespace DAL {

/*!
 * \class Dataset
 *
 * Provides generic functionality for HDF5 Datasets.
 *
 * Python example:
 * \code
 *    # Create a new HDF5 file called "example.h5"
 *    >>> f = File("example.h5", File.CREATE)
 *
 *    # Create a 2 x 3 dataset of floats within the given file
 *    >>> d = DatasetFloat(f, "EXAMPLE_DATASET")
 *    >>> d.create([2,3])
 *
 *    # Retrieve some information about the dataset
 *    >>> d.dims()
 *    (2, 3)
 *    >>> d.ndims()
 *    2
 *
 *    # Query the numpy format in which the data is stored
 *    >>> d.dtype
 *    <type 'numpy.float32'>
 *
 *    # Allocate a 2 x 3 numpy array of the right type to read data into
 *    >>> import numpy
 *    >>> x = numpy.zeros((2,3), dtype=d.dtype)
 *
 *    # Read data starting from [0,0], and display it
 *    >>> d.get2D([0,0], x)
 *    >>> x
 *    array([[ 0.,  0.,  0.], [ 0.,  0.,  0.]], dtype=float32)
 *
 *    # Now, write some data: we write a block of size (1,2) to position (1,1)
 *    >>> y = numpy.ones((1,2), dtype=d.dtype)
 *    >>> d.set2D([1,1], y)
 *
 *    # Read data starting from [0,0], and display it
 *    >>> d.get2D([0,0], x)
 *    >>> x
 *    array([[ 0.,  0.,  0.], [ 0.,  1.,  1.]], dtype=float32)
 *
 *    # Clean up
 *    >>> import os
 *    >>> os.remove("example.h5")
 * \endcode
 */
template<typename T> class Dataset: public Group {
public:
  enum Endianness { NATIVE = 0, LITTLE, BIG };

  Dataset( Group &parent, const std::string &name ): Group(parent, name) {}

  /*!
   * Destruct a Dataset object.
   */
  virtual ~Dataset() {}

  /*!
   * Creates a new dataset with dimensions sized `dims'. If `maxdims' is set, the dataset can be scaled up to `maxdims'.
   * The rank of the dataset is dims.size() == maxdims.size(). A maximum of -1 represents an unbounded dimension.
   *
   * If a `filename' is given, that file will be used to store the data. The file can be provided by
   * the user, or will be created upon the first write. Note that the filename cannot be changed
   * after the dataset has been created (HDF5 1.8), so providing an absolute path will make the
   * dataset difficult to copy or move across systems. We strongly advice against absolute paths (and "../") here!
   * Note that HDF5 1.8 has a problem accessing external files outside the current working directory.
   * DAL works around this, but see Known Issue 1 for more detail.
   *
   * If no `filename' is given, dims == maxdims is required due to limitations of HDF5.
   *
   * `endianness` toggles whether the data is in big-endian format. Typically:
   *  - NATIVE: use the endianness of the current machine
   *  - LITTLE: use little-endian: x86, x86_64, ARM
   *  - BIG:    use big-endian:    MIPS, POWER/PowerPC, SPARC, IA-64
   */
  Dataset<T>& create( const std::vector<ssize_t> &dims, const std::vector<ssize_t> &maxdims = std::vector<ssize_t>(0),
                const std::string &filename = "", enum Endianness endianness = NATIVE );

  /*!
   * Create a new 1D dataset. See Dataset::create(...).
   */
  Dataset<T>& create1D( ssize_t len, ssize_t maxlen = 0, const std::string &filename = "",
                enum Endianness endianness = NATIVE );

  /*!
   * Returns the rank of the dataset.
   */
  size_t ndims();

  /*!
   * Returns the dimension sizes.
   */
  std::vector<ssize_t> dims();

  /*!
   * Returns the length of the 1D dataset.
   */
  ssize_t dims1D();

  /*!
   * Returns the maximum dimension sizes to which this dataset can grow;
   * elements of -1 represent unbounded dimensions.
   */
  std::vector<ssize_t> maxdims();

  /*!
   * Returns the maximum length to which thus dataset can grow;
   * -1 represents unbounded length.
   */
  ssize_t maxdims1D();

  /*!
   * Changes the dimensionality of the dataset. Elements of -1 represent unbounded dimensions.
   * If this dataset uses internal storage (i.e. externalFiles() is empty), dimensions
   * cannot be unbounded due to limitations of HDF5.
   *
   * For now, resizing is only supported if external files are used.
   */
  void resize( const std::vector<ssize_t> &newdims );

  /*!
   * See Dataset::resize().
   */
  void resize1D( ssize_t newlen );

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
  void getMatrix( const std::vector<size_t> &pos, T *buffer, const std::vector<size_t> &size );

  /*!
   * Stores any matrix of data of sizes `size` at position `pos`.
   *
   * Requires:
   *    pos.size() == size.size() == ndims()
   */
  void setMatrix( const std::vector<size_t> &pos, const T *buffer, const std::vector<size_t> &size );

  /*!
   * Retrieves `len` data values from a dataset starting at index `pos`.
   * `outbuffer` must point to a memory block large enough to hold `len` data values.
   * If the underlying dataset is multi-dimensional, use `dimIndex` to indicate the dimension to retrieve from.
   *
   * \param[in] pos               index of the first data value
   * \param[out] outbuffer        1D destination array
   * \param[in] len               number of data values to retrieve
   * \param[in] dimIndex          index of the dimension to query
   *
   * Requires:
   *    - pos + len <= dims()
   *    - len <= size of outbuffer
   *    - dimIndex < ndims()
   */
  void get1D( size_t pos, T *outbuffer, size_t len, unsigned dimIndex = 0 );

  /*!
   * Stores `len` data values from a dataset starting at index `pos`.
   * `inbuffer` must contain at least `len` data values.
   * If the underlying dataset is multi-dimensional, use `dimIndex` to indicate the dimension to store to.
   *
   * \param[in] pos               index of the first data value
   * \param[in] inbuffer          1D source array
   * \param[in] len               number of data values to store
   * \param[in] dimIndex          index of the dimension to query
   *
   * Requires:
   *    - pos + len <= dims()
   *    - len <= size of inbuffer
   *    - dimIndex < ndims()
   */
  void set1D( size_t pos, const T *inbuffer, size_t len, unsigned dimIndex = 0 );

  /*!
   * Retrieves a 2D matrix of data from a 2D dataset from position `pos`.
   * `buffer` must point to a memory block large enough to hold the result.
   *
   * \param[in] pos               position of the first sample
   * \param[out] outbuffer2       2D destination array
   * \param[in] dim1              size of first dimension of outbuffer2; determines the number of data values to retrieve
   * \param[in] dim2              size of second dimension of outbuffer2; determines the number of data values to retrieve
   * \param[in] dim1index         index of the first dimension to query
   * \param[in] dim2index         index of the second dimension to query
   *
   * Requires:
   *    - ndims() >= 2
   *    - pos.size() == ndims()
   *    - dim1index < dim2index < ndims()
   */
  void get2D( const std::vector<size_t> &pos, T *outbuffer2, size_t dim1, size_t dim2, unsigned dim1index = 0, unsigned dim2index = 1 );

  /*!
   * Stores a 2D matrix of data from a 2D dataset at position `pos`.
   *
   * \param[in] pos               position of the first sample
   * \param[in] inbuffer2         2D source array
   * \param[in] dim1              size of first dimension of inbuffer2; determines the number of data values to store
   * \param[in] dim2              size of second dimension of inbuffer2; determines the number of data values to store
   * \param[in] dim1index         index of the first dimension to query
   * \param[in] dim2index         index of the second dimension to query
   *
   * Requires:
   *    - ndims() >= 2
   *    - pos.size() == ndims()
   *    - dim1index < dim2index < ndims()
   */
  void set2D( const std::vector<size_t> &pos, const T *inbuffer2, size_t dim1, size_t dim2, unsigned dim1index = 0, unsigned dim2index = 1 );

  /*!
   * Retrieves a 3D matrix of data from a 3D dataset from position `pos`.
   * `buffer` must point to a memory block large enough to hold the result.
   *
   * \param[in] pos               position of the first sample
   * \param[out] outbuffer3       3D destination array
   * \param[in] dim1              size of first dimension of outbuffer3; determines the number of data values to retrieve
   * \param[in] dim2              size of second dimension of outbuffer3; determines the number of data values to retrieve
   * \param[in] dim3              size of third dimension of outbuffer3; determines the number of data values to retrieve
   * \param[in] dim1index         index of the first dimension to query
   * \param[in] dim2index         index of the second dimension to query
   * \param[in] dim3index         index of the third dimension to query
   *
   * Requires:
   *    - ndims() >= 3
   *    - pos.size() == ndims()
   *    - dim1index < dim2index < dim3index < ndims()
   */
  void get3D( const std::vector<size_t> &pos, T *outbuffer3, size_t dim1, size_t dim2, size_t dim3, unsigned dim1index = 0, unsigned dim2index = 1, unsigned dim3index = 2 );

  /*!
   * Stores a 3D matrix of data from a 3D dataset at position `pos`.
   *
   * \param[in] pos               position of the first sample
   * \param[in] inbuffer3         3D source array
   * \param[in] dim1              size of first dimension of inbuffer3; determines the number of data values to store
   * \param[in] dim2              size of second dimension of inbuffer3; determines the number of data values to store
   * \param[in] dim3              size of third dimension of inbuffer3; determines the number of data values to store
   * \param[in] dim1index         index of the first dimension to query
   * \param[in] dim2index         index of the second dimension to query
   * \param[in] dim3index         index of the third dimension to query
   *
   * Requires:
   *    - ndims() >= 2
   *    - pos.size() == ndims()
   *    - dim1index < dim2index < ndims()
   */
  void set3D( const std::vector<size_t> &pos, const T *inbuffer3, size_t dim1, size_t dim2, size_t dim3, unsigned dim1index = 0, unsigned dim2index = 1, unsigned dim3index = 2 );

  /*!
   * Retrieves a single value from the dataset at position `pos`.
   *
   * Requires:
   *    pos.size() == ndims()
   */
  T getScalar( const std::vector<size_t> &pos );

  /*!
   * See Dataset::getScalar().
   */
  T getScalar1D( size_t pos );

  /*!
   * Stores a single value into the dataset at position `pos`.
   *
   * Requires:
   *    pos.size() == ndims()
   */
  void setScalar( const std::vector<size_t> &pos, const T &value );

  /*!
   * See Dataset::setScalar().
   */
  void setScalar1D( size_t pos, T value );

protected:
  virtual hid_gc open( hid_t parent, const std::string &name ) const {
    return hid_gc(H5Dopen2(parent, name.c_str(), H5P_DEFAULT), H5Dclose, "Could not open dataset " + _name);
  }

  bool bigEndian( enum Endianness endianness ) const;

  //! If the strides vector is empty, a continuous array is assumed.
  void matrixIO( const std::vector<size_t> &pos, T *buffer, const std::vector<size_t> &size, const std::vector<size_t> &strides, bool read );


  /*!
   * Do not use this create function.
   * It always throws to catch incorrect calls to create() in Group.
   * To create a Dataset, use the create function with arguments instead.
   */
  virtual Dataset<T>& create() {
    throw HDF5Exception("create() without parameters not supported on a dataset " + _name);
  }
};

}

#include "Dataset.tcc"

#endif

