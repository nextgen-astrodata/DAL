#!/usr/bin/env python
#
# tbb-lostframes.py
# Python script that searches for frame payload sized sequences of zeros in TBB transient data in LOFAR HDF5 files.
#
# File:         tbb-lostframes.py
# Author:       Alexander S. van Amesfoort (amesfoort_at_astron.nl)
# Date:         2012-06-11
# Last change:  2012-06-11

import sys
import numpy
import DAL

def get_lost_frame_nrs(arr, block_len):
	lost_frame_nrs = [ ]

	for frame in range(0, len(arr), block_len):
		all_zero = true
		for offset in range(frame, frame + block_len):
			if arr[offset] != 0:
				all_zeros = false
				break

		if not all_zeros:
			lost_frame_nrs.append(frame)

	return lost_frame_nrs

def print_lost_frame_nrs(filename):
	fh = DAL.TBB_File(filename)

	total_frames = 0
	total_lost = 0

	station_groups = fh.stations();
	for st in station_groups:
		dipole_datasets = st.dipoles();
		for dp in dipole_datasets:
			arr = numpy.zeros((len(dp), ), dtype=dp.dtype) # TODO: needs len to work on TBB_DipoleDataset
			#arr = numpy.array(dp, dtype=dp.dtype) # TODO: works if Python version of TBB_DipoleDataset exposes the array interface, __array__ returns an array or (nested) sequence
			total_frames += len(arr)
			block_len = dp.samplesPerFrame().value # always 1024
			lost_frame_nrs = get_lost_frame_nrs(arr, block_len)
			if lost_frame_nrs:
				print('Station', st.stationName().value, 'Dipole', str(dp.rcpId().value) + str(rcuId().value) + ':', 'zeroed frame numbers of size', block_len + ':')
				for frame_nr in lost_frame_nrs:
					print(frame_nr, '')
				total_lost += block_len # TODO: doesn't account for lost frames at the end...

	if total_lost:
		print('Data loss:', total_lost, '/', total_frames, '(' + total_lost / total_frames * 100.0 + '%)')

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
	except Exception as exc:
		sys.stderr.write('Error: ' + str(exc) + '\n')
		return 1

	return 0

if __name__ == '__main__':
	sys.exit(main())

