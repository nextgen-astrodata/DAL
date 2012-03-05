#!/usr/bin/env python
#
# bf_header.py
# Python script that displays header information from a BF.h5 file 
#
# File:         bfheaderinfo.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-03-01
# Last change:  2012-03-05

import sys
import os
import numpy
from optparse import OptionParser         # command line argument parsing
import DAL
import bfmeta

"""
# Display usage information
#
def usage(progname):
  print "usage: ", progname, " <filename.h5> <options>"
  print "Displays HDF5 meta information of a BF h5 file."
  print "Currently this only extends to the same attributes"
  print "that readfile displays for FITS files."
  print "Options:"
  print "-s <sapNr>   info for this sap nr only"
  print "-b <beamNr>    info for this beam nr only"
  print "-s             show SAP names and beam numbers"
  print "-t             use tabs for display"
  print "-c             use color for display"
  print "-h             show this help info"
"""

def main():
  basename=os.path.basename(sys.argv[0])

  parser = OptionParser()
  parser.add_option("-t", "--tabs", dest="tabs",
                    action="store_true", help="use tabs for display")
  parser.add_option("-c", "--color", dest="color", default=False,
                    action="store_true", help="use color for display")
  parser.add_option("-p", "--sap", dest="sap", default="all",
                    action="store", type="string", help="display this sap")
  parser.add_option("-b", "--beam", dest="beam", default="all",
                    action="store", type="string", help="display this beam")
  parser.add_option("-s", "--stokes", dest="stokes", default="all",
                    action="store", type="string", help="display these stokes")
  parser.add_option("-v", "--verbose", dest="verbose", default=False,
                    action="store_true", help="display verbose info")
  (options, args) = parser.parse_args()
  
  if len(sys.argv)==1:
    usage(basename)
    sys.exit()
  else:
    filename=sys.argv[1]
    fh=DAL.BF_File(filename)      # open file

    bfmeta.bfmeta(fh, tabs=options.tabs, color=options.color, sap=options.sap, beam=options.beam, stokes=options.stokes, verbose=options.verbose)

#    displayInfo(sys.argv[1], tabs=False)


# Entry point on call
#  
if __name__ == "__main__":
  main()