#!/usr/bin/env python
import DAL

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


print("---- Ranges")

r = DAL.Range() # sets begin=0, end=0
print "r =", r

r.begin = 1
r.end = 5
print "r =", r
# note that a Range's size is always 2, because it is a tuple with 2 members
print "Range size =", r.size(), "(2 by definition)"
# to determine its span, use
print "span size =", r.end - r.begin

r2 = DAL.Range(10, 100)
print("begin = %lu, end = %lu" % (r2.begin, r2.end))

# For flagging, a list of DAL.Range objects is received / must be passed
flags = [ ] # valid
print "flags =", flags
flags.append(r)
flags.append(r2)
print "flags =", flags

