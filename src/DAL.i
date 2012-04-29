// -------------------------------
// Documentation
// -------------------------------

%define DOCSTRING
"DAL implements a Data Access Layer for LOFAR data."
%enddef

%module(docstring=DOCSTRING) DAL

// first generate signatures using SWIG's knowledge
%feature("autodoc",1);

// then append documentation using doxygen's knowledge
%include "doc/docstrings.i"

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
  %template(VectorDouble)       vector<double>;
  %template(VectorString)       vector<string>;
};

// -------------------------------
// Exception handling
// -------------------------------

%include "exceptions.i"

// -------------------------------
// DAL classes and templates
// -------------------------------

%{
  #include "lofar/BF_File.h"
  #include "lofar/TBB_File.h"

  using namespace DAL;
%}

// rename otherwise unreachable functions
%rename(get_hid_t)  operator hid_t;
%rename(get_hid_gc) operator hid_gc;

%include hdf5/HDF5Node.h
%include hdf5/HDF5Attribute.h
%include hdf5/HDF5FileBase.h
%include hdf5/HDF5GroupBase.h

%include "tuples.i"
%include "datasets.i"

namespace DAL {
  using namespace std;

  %template(AttributeBool)      Attribute<bool>;
  %template(AttributeUnsigned)  Attribute<unsigned>;
  %template(AttributeDouble)    Attribute<double>;
  %template(AttributeString)    Attribute<string>;

  %template(AttributeVUnsigned) Attribute< vector<unsigned> >;
  %template(AttributeVDouble)   Attribute< vector<double> >;
  %template(AttributeVString)   Attribute< vector<string> >;

  %template(AttributeUnsigned3)     Attribute< Tuple<unsigned,3> >;
  %template(AttributeDouble3)       Attribute< Tuple<double,3> >;
  %template(AttributeCoordinate3D)  Attribute< Coordinate3D<double> >;

  %template(AttributeVUnsigned3)    Attribute< vector< Tuple<unsigned,3> > >;
  %template(AttributeVDouble3)      Attribute< vector< Tuple<double,3> > >;
  %template(AttributeVCoordinate3D) Attribute< vector< Coordinate3D<double> > >;
}

%include lofar/CommonAttributesFile.h
%include lofar/Coordinates.h
%include lofar/BF_File.h
%include lofar/TBB_File.h

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{
%}

