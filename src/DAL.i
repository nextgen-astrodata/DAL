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

%include "size_types.i"

// -------------------------------
// STL/C++ templates
// -------------------------------

%{
#define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS 
%}

%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"

namespace std {
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorUnsignedLong) vector<unsigned long>;
  %template(VectorInt)          vector<int>;
  %template(VectorLong)         vector<long>;
  %template(VectorDouble)       vector<double>;
  %template(VectorString)       vector<string>;
};

// Define Vector aliases for python for size_t and ssize_t
%pythoncode %{
  if typeof_size_t == "unsigned int":
    VectorSizeT = VectorUnsigned
  elif typeof_size_t == "unsigned long":
    VectorSizeT = VectorUnsignedLong

  if typeof_ssize_t == "int":
    VectorSSizeT = VectorInt
  elif typeof_size_t == "long":
    VectorSSizeT = VectorLong
%}

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

# Add __repr__ functions to all vectors

def vector_repr(self):
  return "(" + ", ".join([x.__repr__() for x in self]) + ")"

for vector in [x for x in locals().keys() if x.startswith("Vector") and type(locals()[x]) == type]:
  locals()[vector].__repr__ = vector_repr

%}

