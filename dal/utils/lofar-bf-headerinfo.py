#!/usr/bin/env python
#
# bf_header.py
# Python script that displays header information from a BF.h5 file 
#
# File:         bfheaderinfo.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-03-01
# Last change:  2012-07-26

import sys
import os
import numpy
from optparse import OptionParser         # command line argument parsing
import dal
import bfmeta


def main():
  basename=os.path.basename(sys.argv[0])

  parser = OptionParser("filename")
  parser.add_option("-t", "--tabs", dest="tabs",
                    action="store_true", help="use tabs for display")
  parser.add_option("-c", "--color", dest="color", default=False,
                    action="store_true", help="use color for display")
  parser.add_option("-l", "--level", dest="level", default="6",
                    action="store", type="int", help="level of HDF5 structure to display l=0..6 (default=6)")
  parser.add_option("-p", "--sap", dest="sap", default="all",
                    action="store", type="string", help="display this sap, one out of [0->NSAP] or 'all'")
  parser.add_option("-b", "--beam", dest="beam", default="all",
                    action="store", type="string", help="display this beam, one out of  [0->NBeam] or 'all'")
  parser.add_option("-s", "--stokes", dest="stokes", default="all",
                    action="store", type="string", help="display these stokes one out of [IQUV], [Xr,Xi,Yr,Yi], or 'all'")
  #parser.add_option("-v", "--verbose", dest="verbose", default=False,
  #                  action="store_true", help="display verbose output")
  (options, args) = parser.parse_args()
  
  if len(sys.argv)==1:
    parser.print_help()
    sys.exit()
  else:
    filename=args[0]
    fh=dal.BF_File(filename)      # open file

    bfmeta.bfmeta(fh, tabs=options.tabs, color=options.color, sap=options.sap, beam=options.beam, stokes=options.stokes, level=options.level) #verbose=options.verbose)

# Entry point on call
#  
if __name__ == "__main__":
  main()

