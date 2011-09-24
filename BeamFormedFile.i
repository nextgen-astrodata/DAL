%module BeamFormedFile
%feature("autodoc", "1");

typedef long ssize_t;
typedef unsigned long size_t;

%include "exception.i"

%{
#include "sys/h5exception.h"
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
%include "carrays.i"
%array_class(float,ArrayFloat);

%include "std_string.i"

%include "std_vector.i"
namespace std {
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorInt)          vector<int>;
  %template(VectorUnsignedLong) vector<unsigned long>;
  %template(VectorLong)         vector<long>;
  %template(VectorString)       vector<string>;
};

%{
#include "BeamFormedFile.h"
%}

%rename(get_hid_t) operator hid_t;

%include h5element.h

%template(AttributeBool)      Attribute<bool>;
%template(AttributeUnsigned)  Attribute<unsigned>;
%template(AttributeDouble)    Attribute<double>;
%template(AttributeString)    Attribute<std::string>;

%template(AttributeVUnsigned) AttributeV<unsigned>;
%template(AttributeVString)   AttributeV<std::string>;

%include HDF5Group.h
%include HDF5File.h
%include HDF5SubGroup.h
%include HDF5Dataset.h

%template(HDF5DatasetFloat)   HDF5Dataset<float>;

%include BeamFormedFile.h

