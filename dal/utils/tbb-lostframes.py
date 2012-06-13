#!/usr/bin/env python
#
# tbb-lostframes.py
# Python script that searches for frame payload sized sequences of zeros in TBB transient data in LOFAR HDF5 files.
#
# File:         tbb-lostframes.py
# Author:       Alexander S. van Amesfoort (amesfoort_at_astron.nl)
# Date:         2012-06-11
# Last change:  2012-06-13

import sys
import numpy
import DAL

def get_lost_frame_nrs(data, block_len):
	lost_frame_nrs = [ ]

	for frame_nr in range((len(data) + block_len-1) / block_len):
		all_zeros = True
		# min(): avoid out of bounds access if last frame is shorter than block_len
		for offset in range(min(block_len, len(data) - frame_nr * block_len)):
			if data[offset] != 0:
				all_zeros = False
				break

		if all_zeros:
			lost_frame_nrs.append(frame_nr)

	return lost_frame_nrs

def print_lost_frame_nrs(filename):
	fh = DAL.TBB_File(filename)

	total_frames = 0
	total_lost = 0

	station_groups = fh.stations();
	for st in station_groups:
		dipole_datasets = st.dipoles();
		for dp in dipole_datasets:
			data_len = len(dp) # actual data len; should be equal to dp.dataLength().get()
			data = numpy.zeros((data_len, ), dtype=dp.dtype)
			#data = numpy.array(dp, dtype=dp.dtype) # TODO: works if Python version of TBB_DipoleDataset exposes the array interface, __array__ returns an array or (nested) sequence
			pos = (0, ) # must be a tuple, even for 1D
			#dp.get1D(pos, data_len, data)
			dp.get1D((data_len, ), data)

			block_len = 1024 #dp.samplesPerFrame().get() # always 1024
			total_frames += (data_len + block_len-1) / block_len # rounded up division
			lost_frame_nrs = get_lost_frame_nrs(data, block_len)
			if lost_frame_nrs: # does not account for missing frames at the end
				total_lost += len(lost_frame_nrs)
				print 'Station', st.stationName().value, 'rsp', str(dp.rspID().value), 'rcu', str(dp.rcuID().value) + ':', 'zeroed frame numbers of size', str(block_len) + ':'
				for frame_nr in lost_frame_nrs:
					print frame_nr,
				print

	if lost_frame_nrs:
		print
		print 'Total data loss:', total_lost, '/', total_frames, '(' + str(total_lost / total_frames * 100.0) + '%)'

def print_usage():
	print 'Usage:', sys.argv[0], 'L12345_xxx_tbb.h5 ...'

def main():
	if len(sys.argv) == 1:
		print_usage()
		return 2

	filenames = sys.argv[1 : ]
	try:
		for filename in filenames:
			print_lost_frame_nrs(filename)
	except KeyboardInterrupt as exc:
		return 1
	except Exception as exc:
		sys.stderr.write('Error: ' + str(exc) + '\n')
		return 1

	return 0

if __name__ == '__main__':
	sys.exit(main())

