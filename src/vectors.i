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

