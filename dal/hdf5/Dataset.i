// SWIG customisations for class Dataset

// member functions that return *this are problematic,
// because SWIG generates a new wrapper object and does not
// know how to do the memory management right between
// both wrapper objects. So we write our own further below.
%rename(_create)   DAL::Dataset::create;
%rename(_create1D) DAL::Dataset::create1D;

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

// Tell SWIG how we call our dimension and array parameters.
// The C++ arg order *and* identifiers in {(...)} must match exactly, but may be a sub-set of the args in the C++ code.
// get1D/set1D
%apply (datatype* INPLACE_ARRAY1, indextype DIM1) {(datatype *outbuffer,      indextype len)}
%apply (datatype* IN_ARRAY1,      indextype DIM1) {(const datatype *inbuffer, indextype len)}

// get2D/set2D
%apply (datatype* INPLACE_ARRAY2, indextype DIM1, indextype DIM2) {(datatype *outbuffer2,      indextype dim1, indextype dim2)}
%apply (datatype* IN_ARRAY2,      indextype DIM1, indextype DIM2) {(const datatype *inbuffer2, indextype dim1, indextype dim2)}

// get3D/set3D
%apply (datatype* INPLACE_ARRAY3, indextype DIM1, indextype DIM2, indextype DIM3) {(datatype *outbuffer3,      indextype dim1, indextype dim2, indextype dim3)}
%apply (datatype* IN_ARRAY3,      indextype DIM1, indextype DIM2, indextype DIM3) {(const datatype *inbuffer3, indextype dim1, indextype dim2, indextype dim3)}

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

%include hdf5/Dataset.h

// -------------------------------
// Class extensions for bindings
// -------------------------------

%extend DAL::Dataset {
  %pythoncode {
    def create(self, *args, **kwargs):
      self._create(*args, **kwargs)
      return self

    def create1D(self, *args, **kwargs):
      self._create1D(*args, **kwargs)
      return self

    def __len__(self):
      import operator
      return reduce(operator.mul, self.dims())
  }    
}

namespace DAL {
  %template(DatasetShort)        Dataset<short>;
  %template(DatasetFloat)        Dataset<float>;
  %template(DatasetComplexFloat) Dataset< std::complex<float> >;
}

%pythoncode %{
  import numpy

  # record the numpy datatypes used in the various datasets
  DatasetShort.dtype = numpy.short
  DatasetFloat.dtype = numpy.single
  DatasetComplexFloat.dtype = numpy.csingle

  del numpy
%}

