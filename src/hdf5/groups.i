// member functions that return *this are problematic,
// because SWIG generates a new wrapper object and does not
// know how to do the memory management right between
// both wrapper objects. So we write our own further below.
%rename(_create) DAL::HDF5GroupBase::create;

%include hdf5/HDF5GroupBase.h

%extend DAL::HDF5GroupBase {
  %pythoncode {
    def create(self):
      self._create()
      return self
}

