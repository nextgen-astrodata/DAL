// SWIG customisations for class Dataset1D

%define DATASET1DTYPE( datatype, numpytype, indextype )

%numpy_typemaps(datatype, numpytype, indextype)

%apply (indextype DIM1, datatype* INPLACE_ARRAY1) {(indextype len, datatype *outbuffer)}
%apply (indextype DIM1, datatype* IN_ARRAY1) {(indextype len, const datatype *inbuffer)}

%enddef

DATASET1DTYPE(short, NPY_SHORT, size_t);


%include hdf5/Dataset1D.h

namespace DAL {
  %template(Dataset1DShort)        Dataset1D<short>;
}

%pythoncode %{
  import numpy

  Dataset1DShort.dtype = numpy.short

  del numpy
%}

