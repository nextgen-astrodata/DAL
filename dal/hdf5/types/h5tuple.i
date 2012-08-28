// SWIG customisations for the TupleBase classes

%{
  #include <sstream>
%}

// make DAL::TupleBase more pythonic
%ignore DAL::TupleBase::operator[];
%ignore DAL::TupleBase::begin;
%ignore DAL::TupleBase::end;
%ignore DAL::TupleUntemplated;

%include hdf5/types/h5tuple.h

// make DAL::TupleBase more pythonic
%extend DAL::TupleBase {
  T __getitem__(ssize_t index) {
    if (index < 0)
      index += $self->size();

    if (index < 0 || index >= $self->size())
      throw DAL::DALIndexError("list index out of range");

    return $self->operator[](index);
  }

  void __setitem__(ssize_t index, const T& value) {
    if (index < 0)
      index += $self->size();

    if (index < 0 || index >= $self->size())
      throw DAL::DALIndexError("list index out of range");

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
%extend DAL::Tuple {
  %pythoncode {
    __repr__ = __str__
  }
}

%define AddTuple( PythonName, CPPName )
  // instantiate the template
  %template(PythonName) CPPName;
%enddef

namespace DAL {
  // TupleBases need to be instantiated to force that they will be %extended
  %template(_TupleBaseUnsigned2)     TupleBase<unsigned,2>;
  %template(_TupleBaseUnsigned3)     TupleBase<unsigned,3>;
  %template(_TupleBaseUnsigned4)     TupleBase<unsigned,4>;
  %template(_TupleBaseFloat2)        TupleBase<float,2>;
  %template(_TupleBaseFloat3)        TupleBase<float,3>;
  %template(_TupleBaseFloat4)        TupleBase<float,4>;
  %template(_TupleBaseDouble2)       TupleBase<double,2>;
  %template(_TupleBaseDouble3)       TupleBase<double,3>;
  %template(_TupleBaseDouble4)       TupleBase<double,4>;
}

AddTuple( TupleUnsigned2, %arg(DAL::Tuple<unsigned,2>) )
AddTuple( TupleUnsigned3, %arg(DAL::Tuple<unsigned,3>) )
AddTuple( TupleUnsigned4, %arg(DAL::Tuple<unsigned,4>) )
AddTuple( TupleFloat2, %arg(DAL::Tuple<float,2>) )
AddTuple( TupleFloat3, %arg(DAL::Tuple<float,3>) )
AddTuple( TupleFloat4, %arg(DAL::Tuple<float,4>) )
AddTuple( TupleDouble2, %arg(DAL::Tuple<double,2>) )
AddTuple( TupleDouble3, %arg(DAL::Tuple<double,3>) )
AddTuple( TupleDouble4, %arg(DAL::Tuple<double,4>) )

