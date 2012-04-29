// SWIG customisations for the TupleBase classes

%{
  #include <sstream>
  #include <vector>
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

    if (index >= $self->size())
      throw IndexError();

    return $self->operator[](index);
  }

  void __setitem__(ssize_t index, const T& value) {
    if (index < 0)
      index += $self->size();

    if (index >= $self->size())
      throw IndexError();

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
}

namespace DAL {
  %template()     TupleBase<unsigned,2>;
  %template()     TupleBase<unsigned,3>;
  %template()     TupleBase<unsigned,4>;
  %template()     TupleBase<float,2>;
  %template()     TupleBase<float,3>;
  %template()     TupleBase<float,4>;
  %template()     TupleBase<double,2>;
  %template()     TupleBase<double,3>;
  %template()     TupleBase<double,4>;

  %template(TupleUnsigned2)     Tuple<unsigned,2>;
  %template(TupleUnsigned3)     Tuple<unsigned,3>;
  %template(TupleUnsigned4)     Tuple<unsigned,4>;
  %template(TupleDouble2)       Tuple<double,2>;
  %template(TupleDouble3)       Tuple<double,3>;
  %template(TupleDouble4)       Tuple<double,4>;

  %template(Coordinate3DDouble) Coordinate3D<double>;
  %template(Coordinate3DFloat)  Coordinate3D<float>;
}

// std::vector variants
namespace std {
  %template(VectorTupleUnsigned2)     vector< DAL::Tuple<unsigned,2> >;
  %template(VectorTupleUnsigned3)     vector< DAL::Tuple<unsigned,3> >;
  %template(VectorTupleUnsigned4)     vector< DAL::Tuple<unsigned,4> >;
  %template(VectorTupleDouble2)       vector< DAL::Tuple<double,2> >;
  %template(VectorTupleDouble3)       vector< DAL::Tuple<double,3> >;
  %template(VectorTupleDouble4)       vector< DAL::Tuple<double,4> >;

  %template(VectorCoordinate3DDouble) vector< DAL::Coordinate3D<double> >;
  %template(VectorCoordinate3DFloat)  vector< DAL::Coordinate3D<float> >;
}

