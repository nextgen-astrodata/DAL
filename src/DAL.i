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

%include "std_complex.i"
%include "std_string.i"
%include "vectors.i"

// -------------------------------
// Exception handling
// -------------------------------

%include "hdf5/exceptions/exceptions.i"

// -------------------------------
// DAL classes and templates
// -------------------------------

%{
  #include "lofar/CommonTuples.h"
  #include "lofar/BF_File.h"
  #include "lofar/TBB_File.h"

  using namespace DAL;
%}

%include "hdf5/types/tuples.i"
%include "hdf5/attributes.i"

%include hdf5/HDF5FileBase.h
%include hdf5/HDF5GroupBase.h

%include "hdf5/datasets.i"

%include lofar/CommonTuples.h

%template(VectorCoordinate3DDouble)     std::vector< DAL::Coordinate3D<double> >;

namespace DAL {
  using namespace std;

  %template(Coordinate3DDouble)           Coordinate3D<double>;
  %template(AttributeCoordinate3DDouble)  Attribute< Coordinate3D<double> >;
  %template(AttributeVCoordinate3DDouble) Attribute< vector< Coordinate3D<double> > >;
}

%include lofar/CommonAttributesFile.h
%include lofar/Coordinates.h
%include lofar/BF_File.h
%include lofar/TBB_File.h

// -------------------------------
// Run doctest if module is executed
// -------------------------------

%pythoncode %{
def _test():
  import doctest
  doctest.testmod(optionflags=doctest.ELLIPSIS|doctest.IGNORE_EXCEPTION_DETAIL)

if __name__ == "__main__":
  _test()
%}

