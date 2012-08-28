#!/usr/bin/env python
import DAL

f = DAL.TBB_File('test-dataset-create_tbb.h5', DAL.TBB_File.CREATE)
st = f.station('CS001')
st.create()
dp = st.dipole(1, 5, 7)

dp.create1D(100)

