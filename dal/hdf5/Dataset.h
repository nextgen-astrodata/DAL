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
   *  NATIVE: use the endianness of the current machine
   *  LITTLE: use little-endian: x86, x86_64, ARM
   *  BIG:    use big-endian:    MIPS, POWER/PowerPC, SPARC, IA-64
   */
  void create( const std::vector<ssize_t> &dims, const std::vector<ssize_t> &maxdims = std::vector<ssize_t>(0),
               const std::string &filename = "", enum Endianness endianness = NATIVE );

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
  virtual hid_gc open( hid_t parent, const std::string &name ) const {
    return hid_gc(H5Dopen2(parent, name.c_str(), H5P_DEFAULT), H5Dclose, "Could not open dataset " + _name);
  }

  bool bigEndian( enum Endianness endianness ) const;

  // if the strides vector is empty, a continuous array is assumed
  void matrixIO( const std::vector<size_t> &pos, const std::vector<size_t> &size, const std::vector<size_t> &strides, T *buffer, bool read );

  /*!
   * Do not use this create function (without arguments) on a Dataset.
   * Use the other create function with arguments instead.
   */
  virtual void create() {
    throw HDF5Exception("create() without parameters not supported on a dataset " + _name);
  }

  // constructor default initialized sub-class obj; undesirable
  Dataset( const hid_gc &fileId ) : Group(fileId) { }
};

}

#include "Dataset.tcc"

#endif

