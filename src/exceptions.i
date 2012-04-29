// -------------------------------
// Exception handling
// -------------------------------

%include "exception.i"

%{
#include "hdf5/exceptions/h5exception.h"
#include "hdf5/exceptions/h5errorstack.h"
#include <new>
#include <exception>
#include <stdexcept>

class IndexError: public std::exception {};
%}

%exception {
  try {
    $action

  // Catch DAL exception classes

  } catch (const DAL::HDF5Exception &e) {
    std::string msg = std::string(e.what()) + ": " + e.stackSummary();

    SWIG_exception(SWIG_RuntimeError, msg.c_str());
  } catch (const IndexError&) {
    SWIG_exception(SWIG_IndexError, "list index out of range");
  }  

  // Catch standard C++ exception classes (including std::exception)
  SWIG_CATCH_STDEXCEPT
}

%include "hdf5/exceptions/h5errorstack.h"

namespace std {
  %template(VectorStackLine)        vector<DAL::HDF5StackLine>;
}

%extend DAL::HDF5StackLine  {
  std::string __repr__() {
    return $self->longDesc();
  }

  std::string __str__() {
    return $self->shortDesc();
  }
}

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{
%}

