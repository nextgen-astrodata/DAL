%module BeamFormedFile

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
// Type marshalling
// -------------------------------

typedef long ssize_t;
typedef unsigned long size_t;

%{
  #define SWIG_FILE_WITH_INIT
%}

%include "external/numpy.i"

%init %{
  import_array();
%}

// SWIG does not allow syntax for numpy.i supporting true
// multidimentional output arrays. So we use INPLACE_ARRAY for everything
// for consistency.
%apply (int DIM1, float* INPLACE_ARRAY1) {(int dim1, float *outbuffer1)}
%apply (int DIM1, int DIM2, float* INPLACE_ARRAY2) {(int dim1, int dim2, float *outbuffer2)}

%apply (int DIM1, float* IN_ARRAY1) {(int dim1, const float *inbuffer1)}
%apply (int DIM1, int DIM2, float* IN_ARRAY2) {(int dim1, int dim2, const float *inbuffer2)}

// -------------------------------
// STL templates
// -------------------------------

%include "std_string.i"

%include "std_vector.i"

namespace std {
  %template(VectorSizeT)        vector<size_t>;
  %template(VectorSSizeT)       vector<ssize_t>;
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorInt)          vector<int>;
  %template(VectorString)       vector<string>;
};

// -------------------------------
// LDA classes and templates
// -------------------------------

%{
  #include "BeamFormedFile.h"

  using namespace LDA;
%}

%rename(get_hid_t) operator hid_t;

%include hdf5core/h5attribute.h

namespace LDA {
  %template(AttributeBool)      Attribute<bool>;
  %template(AttributeUnsigned)  Attribute<unsigned>;
  %template(AttributeDouble)    Attribute<double>;
  %template(AttributeString)    Attribute<std::string>;

  %template(AttributeVUnsigned) Attribute< std::vector<unsigned> >;
  %template(AttributeVString)   Attribute< std::vector<std::string> >;
}

// we can't marshall the raw pointers for these.
// use a wildcard to match all subclasses of HDF5DatasetBase
// as well.
%ignore *::getMatrix;
%ignore *::setMatrix;

%include HDF5Node.h
%include HDF5FileBase.h
%include HDF5GroupBase.h
%include HDF5DatasetBase.h

namespace LDA {
  %template(HDF5DatasetBaseFloat) HDF5DatasetBase<float>;
}

%include CommonAttributesFile.h
%include BeamFormedFile.h

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{
  import numpy

  # record the numpy datatypes used in the various datasets
  HDF5DatasetBaseFloat.dtype = numpy.float32

  del numpy
%}

