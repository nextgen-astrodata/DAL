%module LDA

// -------------------------------
// Documentation
// -------------------------------

// first generate signatures using SWIG's knowledge
%feature("autodoc",1);

// then append documentation using doxygen's knowledge
%include "docstrings.i"

// -------------------------------
// Exception handling
// -------------------------------

%include "exception.i"

%{
#include "hdf5core/h5exception.h"
%}

%exception {
  try {
    $action
  } catch (const LDA::HDF5Exception &e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  } catch (const std::exception& e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}

// -------------------------------
// Type marshalling - scalars
// -------------------------------

typedef long ssize_t;
typedef unsigned long size_t;

// -------------------------------
// STL/C++ templates
// -------------------------------

%include "std_complex.i"

%include "std_string.i"

%include "std_vector.i"

namespace std {
  %template(VectorSizeT)        vector<size_t>;
  %template(VectorSSizeT)       vector<ssize_t>;
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorString)       vector<string>;
};


// -------------------------------
// Type marshalling - arrays
// -------------------------------

%{
  #define SWIG_FILE_WITH_INIT
%}

%include "external/numpy.i"

%init %{
  import_array();
%}

// tell numpy which combinations of data types and index types we use
%numpy_typemaps(short, NPY_INT16, size_t)
%numpy_typemaps(float, NPY_FLOAT32, size_t)
%numpy_typemaps(std::complex<float>, NPY_COMPLEX64, size_t)

// tell SWIG how we call our dimension and array parameters
%apply (size_t DIM1, short* INPLACE_ARRAY1) {(size_t dim1, short *outbuffer1)}
%apply (size_t DIM1, size_t DIM2, short* INPLACE_ARRAY2) {(size_t dim1, size_t dim2, short *outbuffer2)}

%apply (size_t DIM1, short* IN_ARRAY1) {(size_t dim1, const short *inbuffer1)}
%apply (size_t DIM1, size_t DIM2, short* IN_ARRAY2) {(size_t dim1, size_t dim2, const short *inbuffer2)}

%apply (size_t DIM1, float* INPLACE_ARRAY1) {(size_t dim1, float *outbuffer1)}
%apply (size_t DIM1, size_t DIM2, float* INPLACE_ARRAY2) {(size_t dim1, size_t dim2, float *outbuffer2)}

%apply (size_t DIM1, float* IN_ARRAY1) {(size_t dim1, const float *inbuffer1)}
%apply (size_t DIM1, size_t DIM2, float* IN_ARRAY2) {(size_t dim1, size_t dim2, const float *inbuffer2)}

%apply (size_t DIM1, std::complex<float>* INPLACE_ARRAY1) {(size_t dim1, std::complex<float> *outbuffer1)}
%apply (size_t DIM1, size_t DIM2, std::complex<float>* INPLACE_ARRAY2) {(size_t dim1, size_t dim2, std::complex<float> *outbuffer2)}

%apply (size_t DIM1, std::complex<float>* IN_ARRAY1) {(size_t dim1, const std::complex<float> *inbuffer1)}
%apply (size_t DIM1, size_t DIM2, std::complex<float>* IN_ARRAY2) {(size_t dim1, size_t dim2, const std::complex<float> *inbuffer2)}

// -------------------------------
// LDA classes and templates
// -------------------------------

%{
  #include "BeamFormedFile.h"
  #include "TBBFile.h"

  using namespace LDA;
%}

// rename otherwise unreachable functions
%rename(get_hid_t)  operator hid_t;
%rename(get_hid_gc) operator hid_gc;

// ignore functions that contain raw pointers that
// cannot be marshalled.
%ignore *::getMatrix;
%ignore *::setMatrix;

%include HDF5Node.h
%include HDF5Attribute.h
%include HDF5FileBase.h
%include HDF5GroupBase.h
%include HDF5DatasetBase.h

namespace LDA {
  using namespace std;

  %template(AttributeBool)      Attribute<bool>;
  %template(AttributeUnsigned)  Attribute<unsigned>;
  %template(AttributeDouble)    Attribute<double>;
  %template(AttributeString)    Attribute<string>;

  %template(AttributeVUnsigned) Attribute< vector<unsigned> >;
  %template(AttributeVString)   Attribute< vector<string> >;

  %template(HDF5DatasetBaseShort)        HDF5DatasetBase<short>;
  %template(HDF5DatasetBaseFloat)        HDF5DatasetBase<float>;
  %template(HDF5DatasetBaseComplexFloat) HDF5DatasetBase< std::complex<float> >;
}

%include CommonAttributesFile.h
%include BeamFormedFile.h
%include TBBFile.h

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{
  import numpy

  # record the numpy datatypes used in the various datasets
  HDF5DatasetBaseShort.dtype = numpy.int16
  HDF5DatasetBaseFloat.dtype = numpy.float32
  HDF5DatasetBaseComplexFloat.dtype = numpy.complex64

  del numpy
%}

