import DAL

# DAL throws an DAL.HDF5Exception if an error is raised by the HDF5 library.
# The exception object contains a 'stack' member, which contains the back trace
# within HDF5.

try:
  f = DAL.File("does_not_exist.h5", DAL.File.READ)
except DAL.HDF5Exception, e:
  print("Caught exception: %s" % (e,))

  print("Brief backtrace:")
  print("\n".join(["  %s" % x for x in e.stack]))

  print("Extensive backtrace:")
  print("\n".join(["  %s" % x.longDesc() for x in e.stack]))

# Common parameter errors trigger regular Python exceptions
try:
  t = DAL.TupleUnsigned3()
  t[4] = 0
except IndexError, e:
  print("Caught exception: %s" % (e,))

# Errors raised by the C++ -> Python translation layer can unfortunately
# be a bit cryptic.
try:
  t = DAL.TupleUnsigned3()
  t[0] = "must be an integer"
except TypeError, e:
  print("Caught exception: %s" % (e,))

