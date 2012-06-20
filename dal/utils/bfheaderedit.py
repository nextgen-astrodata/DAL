#!/usr/bin/env python
#
# bfheaderedit.py
# Python script that allows to header information in a BF.h5 file 
#
# File:         bfheaderedit.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-06-05
# Last change:  2012-06-15

import sys
import os
import numpy
from optparse import OptionParser         # command line argument parsing
import DAL
import bfmeta


def main():
  basename=os.path.basename(sys.argv[0]) 
  if len(sys.argv)==1:
    parser.print_usage()
    sys.exit()
  else:

    parser = OptionParser(usage="usage: %prog [options] filename", )
    parser.add_option("-v", "--verbose", dest="verbose",
                      action="store_true", help="verbose display")
    parser.add_option("-e", "--edit", dest="edit", default=False,
                      action="store_true", help="allow editing of attributes")
    parser.add_option("-c", "--clobber", dest="clobber", default=False,
                      action="store_true", help="apply editing changes to file")
    parser.add_option("-o", "--overwrite", dest="overwrite", default=False,
                      action="store_true", help="write output to temporary file first")
    parser.add_option("-g", "--group", dest="group", action="store", type="string",
                      help="change attributes in this group; supports multiple numbers")
    parser.add_option("-a", "--attribute", dest="attribute", action="store", type="string",
                      help="attribute (wildcard) to view/edit") 
    parser.add_option("-f", "--file", dest="filename", action="store", type="string",
                      help="filename of BF HDF5 file")  
    (options, args) = parser.parse_args()
  
    print "args: ", args
  
    if options.filename==None:
      filename=args[0]
    else:
      filename=options.filename
    
    #print "filename: ", filename         # DEBUG
    if options.clobber:
      fh=DAL.BF_File(options.filename, DAL.File.READWRITE)  # open file read/write
    elif options.overwrite:
      # make copy first
      print "Copying", filename,"to "
    else:
      fh=DAL.BF_File(options.filename, DAL.File.READ)  # open file readonly
    args.remove(filename)                 # remove filename from args list

#    bfmeta.bfmeta(fh, tabs=options.tabs, color=options.color, sap=options.sap, beam=options.beam, stokes=options.stokes, verbose=options.verbose)
    bfheader=befheader.bfheader(fh)


    for arg in args:
      bfheader.analyzeArg(arg)

# Entry point on call
#  
if __name__ == "__main__":
  main()