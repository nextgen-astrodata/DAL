#!/usr/bin/env python
import dal

# DAL throws an dal.HDF5Exception if an error is raised by the HDF5 library.
# The exception object contains a 'stack' member, which contains the back trace
# within HDF5.

try:
  f = dal.File("example-exceptions_file.h5", dal.File.READ, "DOC_VERSION")
except dal.HDF5Exception, e:
  print("Caught exception: %s" % (e,))

  print("Brief backtrace:")
  print("\n".join(["  %s" % x for x in e.stack]))

  print("Extensive backtrace:")
  print("\n".join(["  %s" % x.longDesc() for x in e.stack]))

# Common parameter errors trigger regular Python exceptions
try:
  t = dal.TupleUInt3()
  t[4] = 0
except IndexError, e:
  print("Caught exception: %s" % (e,))

# Errors raised by the C++ -> Python translation layer can unfortunately
# be a bit cryptic.
try:
  t = dal.TupleUInt3()
  t[0] = "must be an integer"
except TypeError, e:
  print("Caught exception: %s" % (e,))

print
print "Exception test succeeded"

