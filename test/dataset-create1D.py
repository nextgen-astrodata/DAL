#!/usr/bin/env python
import sys
import dal

f = dal.TBB_File('test-dataset-create_tbb.h5', dal.TBB_File.CREATE)
st = f.station('CS001')
st.create()
dp0 = st.dipole(1, 5, 7)
dp0.create1D(100, 100)
# for now, resizing is only supported if external data sets are used
#dp0.resize1D(50)
#excSeen0 = False
#try:
#  dp0.resize1D(101)
#except dal.HDF5Exception, e:
#  excSeen0 = True

#if not excSeen0:
#  print "resizeing beyond maxsize did not throw (1)"


dp1 = st.dipole(2, 7, 9)
# if maxdim > dim (and for now, to do any resize), you must provide an external filename
dp1.create1D(100, 120, 'test-dataset-create_tbb.raw') #, dal.TBB_DipoleDataset.LITTLE)
dp1.resize1D(120)
dp1.resize1D(50)

excSeen1 = False
try:
  dp1.resize1D(200)
except dal.HDF5Exception, e:
  excSeen1 = True

if not excSeen1:
  print "resizing beyond maxsize did not throw (2)"


if not excSeen1:
  sys.exit(1)

