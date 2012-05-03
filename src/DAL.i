// -------------------------------
// Documentation
// -------------------------------

%define DOCSTRING
"DAL implements a Data Access Layer for LOFAR data."
%enddef

%module(docstring=DOCSTRING) DAL

// first generate signatures using SWIG's knowledge
%feature("autodoc",1);

// then append documentation using doxygen's knowledge
%include "doc/docstrings.i"

// -------------------------------
// Type marshalling - scalars
// -------------------------------

%include "size_types.i"

// -------------------------------
// STL/C++ templates
// -------------------------------

%{
#define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS 
%}

%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"

namespace std {
  %template(VectorUnsigned)     vector<unsigned>;
  %template(VectorUnsignedLong) vector<unsigned long>;
  %template(VectorInt)          vector<int>;
  %template(VectorLong)         vector<long>;
  %template(VectorDouble)       vector<double>;
  %template(VectorString)       vector<string>;
};

// Define Vector aliases for python for size_t and ssize_t
%pythoncode %{
  if typeof_size_t == "unsigned int":
    VectorSizeT = VectorUnsigned
  elif typeof_size_t == "unsigned long":
    VectorSizeT = VectorUnsignedLong

  if typeof_ssize_t == "int":
    VectorSSizeT = VectorInt
  elif typeof_size_t == "long":
    VectorSSizeT = VectorLong
%}

// -------------------------------
// Exception handling
// -------------------------------

%include "exceptions.i"

// -------------------------------
// DAL classes and templates
// -------------------------------

%{
  #include "lofar/BF_File.h"
  #include "lofar/TBB_File.h"

  using namespace DAL;
%}

// rename otherwise unreachable functions
%rename(get_hid_t)  operator hid_t;
%rename(get_hid_gc) operator hid_gc;

%include hdf5/HDF5Node.h
%include hdf5/HDF5Attribute.h
%include hdf5/HDF5FileBase.h
%include hdf5/HDF5GroupBase.h

%include "tuples.i"
%include "datasets.i"

namespace DAL {
  using namespace std;

  %template(AttributeBool)      Attribute<bool>;
  %template(AttributeUnsigned)  Attribute<unsigned>;
  %template(AttributeDouble)    Attribute<double>;
  %template(AttributeString)    Attribute<string>;

  %template(AttributeVUnsigned) Attribute< vector<unsigned> >;
  %template(AttributeVDouble)   Attribute< vector<double> >;
  %template(AttributeVString)   Attribute< vector<string> >;

  %template(AttributeUnsigned3)     Attribute< Tuple<unsigned,3> >;
  %template(AttributeDouble3)       Attribute< Tuple<double,3> >;
  %template(AttributeCoordinate3D)  Attribute< Coordinate3D<double> >;

  %template(AttributeVUnsigned3)    Attribute< vector< Tuple<unsigned,3> > >;
  %template(AttributeVDouble3)      Attribute< vector< Tuple<double,3> > >;
  %template(AttributeVCoordinate3D) Attribute< vector< Coordinate3D<double> > >;
}

%include lofar/CommonAttributesFile.h
%include lofar/Coordinates.h
%include lofar/BF_File.h
%include lofar/TBB_File.h

// -------------------------------
// Class extensions for bindings
// -------------------------------

%pythoncode %{

# Add special functions to all vectors

class PythonicVector:
  def __repr__(self):
    return "(" + ", ".join([x.__repr__() for x in self]) + ")"

  def __add__(self, other):
    result = self[:]
    result.append(other)
    return result

  def __radd__(self, other):
    result = self[:]
    result.insert(result.__iter__(), other)
    return result

  def __iadd__(self, other):
    self.append(other)
    return self

  def __mul__(self, value):
    result = self.__class__()
    result.reserve(len(self) * value)

    for x in xrange(len(self)):
      result.extend(self)

    return result

  def __imul__(self, value):
    if value == 0:
      self.clear()

    if value <= 1:
      return self

    origlist = self[:]
    self.reserve(len(self) * value)

    for x in xrange(value - 1):
      self.extend(origlist)

    return self

  def count(self, value):
    n = 0

    for x in self:
      if x == value:
        n += 1

    return n

  def extend(self, l):
    for x in l:
      self.append(x)

  def index(self, value, *args):
    # slow because list(self) copies, but list.index has some extensive behaviour
    return list(self).index(value, *args)

  def sort(self, *args, **kwargs):
    # a future implementation could use std::sort in C++ for the default case
    raise NotImplementedError

for vector in [x for x in locals().keys() if x.startswith("Vector") and type(locals()[x]) == type]:
  # SWIG generates __repr__ members for all classes, so we need to explicitly override them all
  locals()[vector].__repr__ = PythonicVector.__repr__

  # provide all other members at once through inheritance
  if PythonicVector not in locals()[vector].__bases__: # some Vector classes are aliases to others
    locals()[vector].__bases__ += (PythonicVector,)

class PythonicAttribute:
  @property
  def value(self):
    if not self.exists():
      return None

    return self.get()

  @value.setter
  def value(self, val):
    if not self.exists():
      self.create()

    try:
      self.set(val)
    except TypeError:
      raise TypeError("'%s' cannot be assigned values of type '%s'" % (self.__class__.__name__, type(val).__name__,))

  @value.deleter
  def value(self):
    if self.exists():
      self.remove()

for attr in [x for x in locals().keys() if x.startswith("Attribute") and type(locals()[x]) == type]:
  # provide all other members at once through inheritance
  if PythonicAttribute not in locals()[attr].__bases__: # some Attribute classes are aliases to others
    locals()[attr].__bases__ += (PythonicAttribute,)

%}

