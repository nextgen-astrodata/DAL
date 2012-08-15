// SWIG customisations for class Dataset1D

%define DATASET1DTYPE( datatype, numpytype, indextype )

%numpy_typemaps(datatype, numpytype, indextype)

%apply (indextype DIM1, datatype* INPLACE_ARRAY1) {(indextype len, datatype *outbuffer)}
%apply (indextype DIM1, datatype* IN_ARRAY1) {(indextype len, const datatype *inbuffer)}

%enddef

DATASET1DTYPE(int16_t, NPY_SHORT, size_t);


%include hdf5/Dataset1D.h

namespace DAL {
  %template(Dataset1DInt16)        Dataset1D<int16_t>;
}

%pythoncode %{
  import numpy

  Dataset1DInt16.dtype = numpy.int16

  del numpy
%}

