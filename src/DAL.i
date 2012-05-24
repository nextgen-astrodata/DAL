// -------------------------------
// Documentation
// -------------------------------

%define DOCSTRING
"DAL implements a Data Access Layer for LOFAR data."
%enddef

%module(docstring=DOCSTRING) DAL

// first generate signatures using SWIG's knowledge
%feature("autodoc",1);

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

%include "hdf5/types/h5tuple.i"
%include "hdf5/Attribute.i"

%include "hdf5/Group.i"
%include "hdf5/Dataset.i"

%include hdf5/File.h

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
  import sys

  failures, tests = doctest.testmod(optionflags=doctest.ELLIPSIS | doctest.IGNORE_EXCEPTION_DETAIL | doctest.NORMALIZE_WHITESPACE)

  if failures == 0:
    sys.exit(0)
  else:  
    sys.exit(1)

if __name__ == "__main__":
  _test()
%}

