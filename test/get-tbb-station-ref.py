#!/usr/bin/env python
import DAL
f = DAL.TBB_File('test-get-tbb-station-ref-py.h5', DAL.File.CREATE)

st = f.station('CSxxx')

