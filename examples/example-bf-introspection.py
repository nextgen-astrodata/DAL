#!/usr/bin/env python
import DAL

f = DAL.BF_File("L30042_SAP000_B000_S0_P000_bf.h5")

print "file %s reports to be version %s" % (f.filename, f.docVersion())
print

print "supp   = whether this attribute is supported by the version as reported by the file"
print "exists = whether this attribute exists in the file"
print "valid  = whether this attribute can be read (exists and is of the correct type)"
print

print "%40s %6s %6s %6s %s" % ("HDF5 Node name", "supp", "exists", "valid", "value")

for n in f.nodeNames():
  node = f.getNode(n)

  if node.exists():
    print "%40s %6s %6s %6s %s" % (n, node.supported(), node.exists(), node.valid(), node.value)
  else:  
    print "%40s %6s %6s %6s %s" % (n, node.supported(), node.exists(), "", "")

