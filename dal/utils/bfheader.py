#!/usr/bin/env python
#
# bfheader.py
#
# Python class to view and edit BF HDF5 headers
#
# File:         bfheader.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-06-15
# Last change:  2012-06-15

import re     # regular expressions
import DAL

class bfheader:
  def __init__(self, fh=None, filename=""):
    print "__init__"                    # DEBUG
    if fh==None:                        # if no file handle given
      self.fh=DAL.BF_File(filename)     # open file    
    else:
      self.fh=fh                        # take handle

  # Analyze argument to get group(s), beam(s), attribute
  #   
  def analyzeArgument(self, arg): 
    print "analyzeArgument("+ arg + ")"   # DEBUG

    # Identify SAPs

    # Indentify BEAMs


  # Identify SAPs from argument string
  #
  def identifySAPs(self, arg):
    print "identifySAPs(" + arg + ")"   # DEBUG

    
  def identifyBEAMs(self, arg):
    print "identifySAPs(" + arg + ")"   # DEBUG

  # Create a complete HDF5 path
  #
  def createHDF5Path(self, path):
    print "createHDf5Path(" + + ")"     # DEBUG
  
  # Get a particular attribute from its HDF5 path
  #
  def getAttribute(self, path):
    print "getAttribute(" + path + ")"  # DEBUG

  # Retrieve attributes by search string (if None, all) 
  # optionally change them to value
  #
  def attributes(self, group, searchstring=None, value=None):
    print "attributes(%(group),%(searchstring),%(value))" %{'group': group, 'searchstring': searchstring, 'value': value}            # DEBUG

  def findAttributeIndex(node, substring):
    print "findAttributeIndex(" + substring + ")"   # DEBUG
    for i, s in enumerate(node.nodeNames()):
        if substring in s:
              return i
    return -1
    
  def findAttribute(node, substring):
    print "findAttribute("+ substring + ")"         # DEBUG
    indx=findAttributeIndex(node, substring)
    name=enumerate(node.nodeNames()[indx]
    node.getNode(name)