#!/usr/bin/env python
#
# lofar_headerinfo.py
# Python script that displays header information from a LOFAR .h5 file 
#
# File:         lofar_headerinfo.py
# Author:       Alexander S. van Amesfoort (amesfoort_at_astron.nl)
# Date:         2012-09-04
# Last change:  2012-09-04

import sys
import dal
import lofar_tbb_headerinfo

def dispatch_to_headerinfo_util(filename):
	# (try to) open as CLA to see what LOFAR data product type it is
	fh = dal.CLA_File(filename)
	ftype = fh.fileType().value

	if ftype == 'tbb':
		lofar_tbb_headerinfo.print_tbb_header(filename)
	elif ftype == 'bf' or ftype == 'dynspec':
		dal.bfmeta(0, filename=filename)
	elif ftype is None:
		print 'The file', filename, 'does not appear to be a LOFAR data product, or it just lacks the FILETYPE attribute.'
	else:
		lofar_tbb_headerinfo.print_cla(fh)

def print_usage():
	print 'Print basic info about a LOFAR HDF5 file.'
	print 'Usage:', sys.argv[0], 'L12345_xxx.h5 ...'

def main():
	if len(sys.argv) == 1:
		print_usage()
		return 2

	exit_status = 0
	filenames = sys.argv[1 : ]
	try:
		for filename in filenames:
			retval = dispatch_to_headerinfo_util(filename)
			if retval != 0:
				exit_status = retval
			print '--------------------------------------------------------'
	except KeyboardInterrupt as exc:
		exit_status = 1
	except Exception as exc:
		sys.stderr.write('Error: ' + str(exc) + '\n')
		exit_status = 1

	return exit_status


if __name__ == '__main__':
	sys.exit(main())

