#!/usr/bin/env python
import DAL

print("---- Vectors")

# initialise a vector of unsigned numbers
v = DAL.VectorUInt([1,2,3])

# A Vector behaves like a list
print("type(v) = %s" % (type(v),))
print("len(v) = %u" % (len(v),))
print("v = %s" % (v,))
print("v = (%u, %u, %u)" % (v[0], v[1], v[2]))
print("v = (%u, %u, %u)" % (v[-3], v[-2], v[-1]))
print("v = %s" % (tuple(v),))
print("v = %s" % (list(v),))
for x in v:
  print("v contains %s"% (x,))

# Vectors can also be sliced, copied, and extended
v2 = v[:]
for x in [4,5,6]:
  v2 += x

print("type(v2) = %s" % (type(v2),))
print("v2 = %s" % (v2,))
print("v = %s" % (v,))

print("---- Tuples")

# Create a tuple of unsigned numbers (1,2,3)
t = DAL.TupleUInt3()
t.set([1,2,3])

# A Tuple behaves like a tuple, but
# also allow name-based access (t.first, etc).
print("type(t) = %s" % (type(t),))
print("len(t) = %u" % (len(t),))
print("t = %s" % (t,))
print("t = (%u, %u, %u)" % (t[0], t[1], t[2]))
print("t = (%u, %u, %u)" % (t[-3], t[-2], t[-1]))
print("t = (%u, %u, %u)" % (t.first, t.second, t.third))
print("t = %s" % (t.get(),))
print("t = %s" % (tuple(t),))
print("t = %s" % (list(t),))
for x in t:
  print("t contains %s"% (x,))

# Create another tuple
t2 = DAL.TupleUInt3()
t2.first  = 4
t2.second = 5
t2.third  = 6

print("t2 = %s" % (t2,))

print("---- Vectors of tuples")

# Put two tuples in a vector
v = DAL.VectorTupleUInt3([t, t2])

# Vectors again act like lists
print("type(v) = %s" % (type(v),))
print("len(v) = %u" % (len(v),))
print("v = %s" % (v,))
for x in v:
  print("v contains %s"% (x,))
