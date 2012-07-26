// -------------------------------
// Exception handling
// -------------------------------

%include "exception.i"

/*
 * Catch and marshall all C++ exceptions. Define the exception handler first,
 * to ensure that all calls will be wrapped.
 */
%exception {
  try {
    $action

  // Catch DAL exception classes

  } catch (const DAL::HDF5Exception &e) {
    const std::string msg = std::string(e.what()) + ": " + e.stackSummary();

#ifdef SWIGPYTHON
    PyErr_SetString(pHDF5Exception, const_cast<char*>(msg.c_str()));
    return NULL;
#else
    SWIG_exception(SWIG_RuntimeError, msg.c_str());
#endif

  } catch (const DAL::DALIndexError &e) {
    SWIG_exception(SWIG_IndexError, e.what());
  } catch (const DAL::DALValueError &e) {
    SWIG_exception(SWIG_ValueError, e.what());
  } catch (const DAL::DALException &e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }  

  // Catch standard C++ exception classes (including std::exception)
  SWIG_CATCH_STDEXCEPT
}


/*
 * Marshall and extend HDF5 error stack classes.
 */
vector_typemap( DAL::HDF5StackLine );

%include "hdf5/exceptions/errorstack.h"

%extend DAL::HDF5StackLine {
  %pythoncode {
    __repr__ = longDesc
    __str__  = shortDesc  
  }
}

/*
 * Marshall our custom exceptions.
 */

// Tell SWIG about std::runtime_error and to ignore it
%ignore std::runtime_error;

namespace std {
  class runtime_error {
  };
}

%include "hdf5/exceptions/exceptions.h"

/*
 * Extend  HDF5Exception.__init__ to provide an error stack.
 * We need to modify DAL._DAL.HDF5Exception, because that is what
 * will be thrown(not DAL.HDF5Exception).
 */
%pythoncode {
  _DAL.HDF5Exception.__old_init = _DAL.HDF5Exception.__init__

  def newinit(self, *args, **kwargs):
    self.__old_init(*args, **kwargs)

    self.stack = HDF5ErrorStack().stack()

  _DAL.HDF5Exception.__init__ = newinit
  del newinit
}

/*
 * Create a custom HDF5Exception in Python.
 */
#ifdef SWIGPYTHON

%{
  static PyObject* pHDF5Exception;
%}

%init %{
  pHDF5Exception = PyErr_NewException(const_cast<char*>("_DAL.HDF5Exception"), PyExc_RuntimeError, NULL);
  Py_INCREF(pHDF5Exception);
  PyModule_AddObject(m, "HDF5Exception", pHDF5Exception); // 'm' is the name of the module object in SWIG
%}

%pythoncode {
  # marshall from shadow module
  HDF5Exception = _DAL.HDF5Exception
}

#endif  

