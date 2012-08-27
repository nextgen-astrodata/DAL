/* A dummy vector class to register it in SWIG */
namespace std {
  template <typename T> class vector {
  };
}

/* input and output typemaps for types that
   have native Python counterparts.
*/
%define vector_native_typemap( T )

%typemap(in) const std::vector< T > & (std::vector< T > result)
{
  if (!PySequence_Check($input))
    SWIG_exception(SWIG_TypeError, "input is not a sequence (list, tuple, etc)");

  const size_t size = PySequence_Size($input);
  result.reserve(size);

  for( size_t i = 0; i < size; i++ ) {
    PyObject *py_obj = PySequence_ITEM($input, i);
    T cpp_obj;

    int res = SWIG_AsVal(T)(py_obj, &cpp_obj);

    if (!SWIG_IsOK(res))
      SWIG_exception(SWIG_TypeError, "cannot convert value in sequence");

    result.push_back(cpp_obj);
  }

  $1 = &result;
}

%typemap(out) std::vector< T >, std::vector< T > const {
 const size_t size = $1.size();

 $result = PyList_New(size);

 for( size_t i = 0; i < size; i++ ) {
   PyObject *py_obj = SWIG_From(T)($1.operator[](i));

   PyList_SET_ITEM($result, i, py_obj);
 }
}

%enddef

/* input and output typemaps for types that need
   to be wrapped by SWIG
*/
%define vector_typemap( T )

%typemap(in) const std::vector< T > & (std::vector< T > result)
{
  if (!PySequence_Check($input))
    SWIG_exception(SWIG_TypeError, "input is not a sequence (list, tuple, etc)");

  const size_t size = PySequence_Size($input);
  result.reserve(size);

  for( size_t i = 0; i < size; i++ ) {
    PyObject *py_obj = PySequence_ITEM($input, i);
    T *cpp_obj;

    int res = SWIG_ConvertPtr(py_obj, reinterpret_cast<void**>(&cpp_obj), $descriptor( T* ), 0);

    if (!SWIG_IsOK(res))
      SWIG_exception(SWIG_TypeError, "cannot convert value in sequence");

    result.push_back(*cpp_obj);
  }

  $1 = &result;
}

%typemap(out) std::vector< T >, std::vector< T > const {
 const size_t size = $1.size();

 $result = PyList_New(size);

 for( size_t i = 0; i < size; i++ ) {
   T *cpp_obj = new T($1.operator[](i));
   PyObject *py_obj = SWIG_NewPointerObj(cpp_obj, $descriptor( T* ), 1);

   PyList_SET_ITEM($result, i, py_obj);
 }
}

%enddef

/*
 * Make sure that the basic vectors are defined.
 */

vector_native_typemap( int );
vector_native_typemap( unsigned int );
vector_native_typemap( float );
vector_native_typemap( double );
vector_native_typemap( size_t );
vector_native_typemap( std::complex<float> );
vector_native_typemap( std::complex<double> );

/*
 * ssize_t and std::string can be converted to native types as well,
 * but we'll need to tell SWIG how.
 */

%wrapper %{

int SWIG_AsVal_ssize_t(PyObject *o, ssize_t *v) {
  long l;
  int ret = SWIG_AsVal_long(o, &l);

  if(SWIG_IsOK(ret))
    *v = l;

  return ret;
}

PyObject *SWIG_From_ssize_t(ssize_t v) {
  return PyInt_FromLong(v);
}

int SWIG_AsVal_std_string(PyObject* o, std::string *s) {
  if (!PyString_Check(o))
    return SWIG_ERROR;

  *s = std::string(PyString_AsString(o));

  return SWIG_OK;
}

%}

vector_native_typemap( ssize_t );
vector_native_typemap( std::string );

