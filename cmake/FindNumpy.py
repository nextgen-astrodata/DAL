import numpy

try:
  print(numpy.get_include())
except AttributeError:
  # depricated, but used in old numpy versions
  print(numpy.get_numpy_include())

