%module BeamFormedFile
%feature("autodoc", "1");

typedef long ssize_t;
typedef unsigned long size_t;

%include "exception.i"

%{
#include "hdf5core/h5exception.h"
%}

%exception {
  try {
    $action
  } catch (const HDF5Exception &e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  } catch (const std::exception& e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}

// use carrays for arrays for now. primitive, but better than nothing.
// (use if numpy is not available)
//%include "carrays.i"
//%array_class(float,ArrayFloat);

%{
  #define SWIG_FILE_WITH_INIT
  #include "BeamFormedFile.h"
%}

%include "numpy.i"

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

%include "std_string.i"

%include "std_vector.i"
namespace std {
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorInt)          vector<int>;
  %template(VectorUnsignedLong) vector<unsigned long>;
  %template(VectorLong)         vector<long>;
  %template(VectorString)       vector<string>;
};

%rename(get_hid_t) operator hid_t;

%include hdf5core/h5attribute.h

%template(AttributeBool)      Attribute<bool>;
%template(AttributeUnsigned)  Attribute<unsigned>;
%template(AttributeDouble)    Attribute<double>;
%template(AttributeString)    Attribute<std::string>;

%template(AttributeVUnsigned) AttributeV<unsigned>;
%template(AttributeVString)   AttributeV<std::string>;

%include HDF5Node.h
%include HDF5File.h
%include HDF5Group.h
%include HDF5Dataset.h

%template(HDF5DatasetFloat)   HDF5Dataset<float>;

%include CLAFile.h
%include BeamFormedFile.h

