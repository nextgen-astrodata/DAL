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
import bfheader

def main():
  basename=os.path.basename(sys.argv[0]) 
  if len(sys.argv)==1:
    parser.print_usage()
    sys.exit()
  else:

    parser = OptionParser(usage="usage: %prog [options] filename", )
    parser.add_option("-v", "--view", dest="view",
                      action="store_true", help="view header attribute")
    parser.add_option("-o", "--overwrite", dest="overwrite", default=False,
                      action="store_true", help="write output to temporary file first")
    parser.add_option("-e", "--edit", dest="edit", default=False,
                      action="store_true", help="allow editing of attributes")
    parser.add_option("-c", "--clobber", dest="clobber", default=False,
                      action="store_true", help="apply editing changes to file")
    parser.add_option("-d", "--debug", dest="debug", default=False,
                      action="store_true", help="turn on debug messages")
    parser.add_option("-a", "--add", dest="add", default=False, action="store_true",
                      help="add an attribute to a group")
    (options, args) = parser.parse_args()
  
    #print "args: ", args  # DEBUG
 
    filename=args[0]
    if options.debug:
      print "filename: ", filename         # DEBUG
    if options.clobber:
      fh=DAL.BF_File(filename, DAL.File.READWRITE)  # open file read/write
    elif options.overwrite:
       # make copy first
      print "Copying", filename,"to "
    else:
      fh=DAL.BF_File(filename, DAL.File.READ)  # open file readonly
    
    if filename in args:
      args.remove(filename)                 # remove filename from args list

    header=bfheader.bfheader(fh=fh, args=args, options=options)

    for arg in args:
      header.analyzeArgument(arg)

    header.showPaths()   # DEBUG

# Entry point on call
#  
if __name__ == "__main__":
  main()

