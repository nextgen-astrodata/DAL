#!/usr/bin/env python
import dal
f = dal.TBB_File('test-get-tbb-station-ref-py.h5', dal.File.CREATE)

st = f.station('CSxxx')

