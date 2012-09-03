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

  } catch (const dal::HDF5Exception &e) {
    const std::string msg = std::string(e.what()) + ": " + e.stackSummary();

#ifdef SWIGPYTHON
    PyErr_SetString(pHDF5Exception, const_cast<char*>(msg.c_str()));
    return NULL;
#else
    SWIG_exception(SWIG_RuntimeError, msg.c_str());
#endif

  } catch (const dal::DALIndexError &e) {
    SWIG_exception(SWIG_IndexError, e.what());
  } catch (const dal::DALValueError &e) {
    SWIG_exception(SWIG_ValueError, e.what());
  } catch (const dal::DALException &e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }  

  // Catch standard C++ exception classes (including std::exception)
  SWIG_CATCH_STDEXCEPT
}


/*
 * Marshall and extend HDF5 error stack classes.
 */
vector_typemap( dal::HDF5StackLine );

%include "hdf5/exceptions/errorstack.h"

%extend dal::HDF5StackLine {
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
 * Create a custom HDF5Exception in Python.
 */
#ifdef SWIGPYTHON

%{
  static PyObject* pHDF5Exception;
%}

%init %{
  pHDF5Exception = PyErr_NewException(const_cast<char*>("_dal.HDF5Exception"), PyExc_RuntimeError, NULL);
  Py_INCREF(pHDF5Exception);
  PyModule_AddObject(m, "HDF5Exception", pHDF5Exception); // 'm' is the name of the module object in SWIG
%}

%pythoncode {
  # marshall from shadow module
  HDF5Exception = _dal.HDF5Exception
}

/*
 * Extend  HDF5Exception.__init__ to provide an error stack.
 */
%pythoncode {
  HDF5Exception.__old_init = HDF5Exception.__init__

  def newinit(self, *args, **kwargs):
    self.__old_init(*args, **kwargs)

    self.stack = HDF5ErrorStack().stack()

  HDF5Exception.__init__ = newinit
  del newinit
}

#endif  

