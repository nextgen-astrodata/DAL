// SWIG customisations for the TupleBase classes

%{
  #include <sstream>
%}

// make dal::TupleBase more pythonic
%ignore dal::TupleBase::operator[];
%ignore dal::TupleBase::begin;
%ignore dal::TupleBase::end;
%ignore dal::TupleUntemplated;

%include hdf5/types/h5tuple.h

// make dal::TupleBase more pythonic
%extend dal::TupleBase {
  T __getitem__(ssize_t index) {
    if (index < 0)
      index += $self->size();

    if (index < 0 || index >= $self->size())
      throw dal::DALIndexError("list index out of range");

    return $self->operator[](index);
  }

  void __setitem__(ssize_t index, const T& value) {
    if (index < 0)
      index += $self->size();

    if (index < 0 || index >= $self->size())
      throw dal::DALIndexError("list index out of range");

    $self->operator[](index) = value;
  }

  size_t __len__() {
    return $self->size();
  }

  std::string __str__() {
    std::ostringstream oss(std::ostringstream::out);

    oss << "(";

    for (size_t i = 0; i < $self->size(); i++) {
      oss << $self->operator[](i);

      if (i != $self->size() - 1)
        oss << ", ";
    }

    oss << ")";

    return oss.str();
  }

  %pythoncode {
    __repr__ = __str__
  }
}

// SWIG sets __repr__ for all classes, so we need to replace them for
// all classes too.
%extend dal::Tuple {
  %pythoncode {
    __repr__ = __str__
  }
}

%define AddTuple( PythonName, CPPName )
  // instantiate the template
  %template(PythonName) CPPName;
%enddef

namespace dal {
  // TupleBases need to be instantiated to force that they will be %extended
  %template(_TupleBaseUInt2)         TupleBase<unsigned int,2>;
  %template(_TupleBaseUInt3)         TupleBase<unsigned int,3>;
  %template(_TupleBaseUInt4)         TupleBase<unsigned int,4>;
  %template(_TupleBaseULongLong2)    TupleBase<unsigned long long,2>;
  %template(_TupleBaseULongLong3)    TupleBase<unsigned long long,3>;
  %template(_TupleBaseULongLong4)    TupleBase<unsigned long long,4>;
  %template(_TupleBaseFloat2)        TupleBase<float,2>;
  %template(_TupleBaseFloat3)        TupleBase<float,3>;
  %template(_TupleBaseFloat4)        TupleBase<float,4>;
  %template(_TupleBaseDouble2)       TupleBase<double,2>;
  %template(_TupleBaseDouble3)       TupleBase<double,3>;
  %template(_TupleBaseDouble4)       TupleBase<double,4>;
}

AddTuple( TupleUInt2, %arg(dal::Tuple<unsigned int,2>) )
AddTuple( TupleUInt3, %arg(dal::Tuple<unsigned int,3>) )
AddTuple( TupleUInt4, %arg(dal::Tuple<unsigned int,4>) )
AddTuple( TupleULongLong2, %arg(dal::Tuple<unsigned long long,2>) )
AddTuple( TupleULongLong3, %arg(dal::Tuple<unsigned long long,3>) )
AddTuple( TupleULongLong4, %arg(dal::Tuple<unsigned long long,4>) )
AddTuple( TupleFloat2, %arg(dal::Tuple<float,2>) )
AddTuple( TupleFloat3, %arg(dal::Tuple<float,3>) )
AddTuple( TupleFloat4, %arg(dal::Tuple<float,4>) )
AddTuple( TupleDouble2, %arg(dal::Tuple<double,2>) )
AddTuple( TupleDouble3, %arg(dal::Tuple<double,3>) )
AddTuple( TupleDouble4, %arg(dal::Tuple<double,4>) )

