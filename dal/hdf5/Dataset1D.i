// SWIG customisations for class Dataset1D

#include "Dataset.i"


%include hdf5/Dataset1D.h

namespace DAL {
  %template(Dataset1DInt16)        Dataset1D<int16_t>;
}

%pythoncode %{
  import numpy

  # record the numpy datatypes used in the various datasets
  DatasetInt16.dtype = numpy.int16

  del numpy
%}

