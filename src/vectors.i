%{
#define SWIG_PYTHON_EXTRA_NATIVE_CONTAINERS 
%}

%include "std_vector.i"

%extend std::vector {
  %pythoncode {
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
  }
}

%define AddVector( PythonName, CPPName )
  // create the Python class VectorXXX
  %template(Vector ## PythonName) std::vector< CPPName >;

  // register it in our Vectors dict
  %pythoncode {
    Vectors[#CPPName] = Vector ## PythonName;
  }
%enddef

%pythoncode {
  # std::vector templates can be registered here
  Vectors = {}
}

AddVector(Unsigned,     unsigned int)
AddVector(UnsignedLong, unsigned long)
AddVector(Int,          int)
AddVector(Long,         long)
AddVector(Double,       double)
AddVector(String,       std::string)

// Define Vector aliases for python for size_t and ssize_t
%pythoncode %{
  VectorSizeT    = Vectors[typeof_size_t];
  VectorSSizeT   = Vectors[typeof_ssize_t];
  VectorPtrDiffT = Vectors[typeof_ptrdiff_t];
%}

