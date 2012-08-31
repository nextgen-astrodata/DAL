#!/usr/bin/env python
import DAL

filedir = 'data'
filenames = \
[ 'L59640_CS011_D20110719T110541.036Z_tbb.h5'
, 'L59640_RS106_D20111121T130145.049Z_tbb.h5'
, 'L30042_SAP000_B000_S0_P000_bf.h5'
, 'L63876_SAP000_B000_S0_P000_bf.h5'
] 

def printNodesInfo(h5file):
  print "file %s reports to be version %s" % (h5file.filename, h5file.docVersion())
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


for filename in filenames:
  fullpath = '%s/%s' % (filedir, filename)

  f = DAL.CLA_File(fullpath)
  ftype = f.fileType().get()

  if ftype == 'tbb':
    f = DAL.TBB_File(fullpath)
  elif ftype == 'bf' or ftype == 'dynspec':
    f = DAL.BF_File(fullpath)
  else:
    None # leave it opened as a CLA_File, so we can access the Common LOFAR Attributes

  printNodesInfo(f)
  print "--------------------------------------------------------------------------------"

