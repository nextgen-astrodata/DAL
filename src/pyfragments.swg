/*
  Redefine the error message signatures to be more user friendly
  (i.e. don't bother the Python user with C++ function signatures).
*/

#undef %argfail_fmt
#define %argfail_fmt(_type,_name,_argn)    (std::string(`_name` ": argument " `_argn` " is of the wrong type: ") + ($input->ob_type->tp_name)).c_str()

#undef %argnullref_fmt
#define %argnullref_fmt(_type,_name,_argn) `_name` ": argument " `_argn` " cannot be None"

// I could not find where to intercept the failure of dynamic dispatch, so we crudely override
// the error macro.SWIG_SetErrorMsg seems only used if the dynamic dispatch fails to find a candidate.

%header %{
#undef SWIG_SetErrorMsg
#define SWIG_SetErrorMsg(code, msg)        SWIG_Python_SetErrorMsg(PyExc_TypeError, "wrong number of arguments, or wrong type of arguments")
%}

