// SWIG customisations for HDF5Datasets

// -------------------------------
// Type marshalling
// -------------------------------

%{
  #define SWIG_FILE_WITH_INIT
%}

%include "external/numpy.i"

%init %{
  import_array();
%}

%define DATASETTYPE( datatype, numpytype, indextype )

// tell numpy which combinations of data types and index types we use
%numpy_typemaps(datatype, numpytype, indextype)

// tell SWIG how we call our dimension and array parameters
%apply (indextype DIM1, datatype* INPLACE_ARRAY1) {(indextype dim1, datatype *outbuffer1)}
%apply (indextype DIM1, indextype DIM2, datatype* INPLACE_ARRAY2) {(indextype dim1, indextype dim2, datatype *outbuffer2)}

%apply (indextype DIM1, datatype* IN_ARRAY1) {(indextype dim1, const datatype *inbuffer1)}
%apply (indextype DIM1, indextype DIM2, datatype* IN_ARRAY2) {(indextype dim1, indextype dim2, const datatype *inbuffer2)}

%enddef

// enumerate all the dataset types that we refer to (we use native types, so do not fix their size)
DATASETTYPE(short, NPY_SHORT, size_t);
DATASETTYPE(float, NPY_FLOAT, size_t);
DATASETTYPE(std::complex<float>, NPY_CFLOAT, size_t);

// -------------------------------
// Templates
// -------------------------------

// ignore functions that contain raw pointers that
// cannot be marshalled.
%ignore *::getMatrix;
%ignore *::setMatrix;

%include hdf5/HDF5DatasetBase.h

namespace DAL {
  %template(HDF5DatasetBaseShort)        HDF5DatasetBase<short>;
  %template(HDF5DatasetBaseFloat)        HDF5DatasetBase<float>;
  %template(HDF5DatasetBaseComplexFloat) HDF5DatasetBase< std::complex<float> >;
}

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{
  import numpy

  # record the numpy datatypes used in the various datasets
  HDF5DatasetBaseShort.dtype = numpy.short
  HDF5DatasetBaseFloat.dtype = numpy.single
  HDF5DatasetBaseComplexFloat.dtype = numpy.csingle

  del numpy
%}

