#!/usr/bin/env python
#
# bfheader.py
#
# Python class to view and edit BF HDF5 headers
#
# File:         bfheader.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-06-15
# Last change:  2012-06-25

import re     # regular expressions
import dal

class bfheader:
  def __init__(self, fh=None, filename="", options=None, args=[]):
    self.debug=options.debug
    self.add=options.add                # turn on adding of attributes
    if self.debug:
      print "__init__"                  # DEBUG
    if fh==None:                        # if no file handle given
      self.fh=dal.BF_File(filename)     # open file    
    else:
      self.fh=fh                        # take handle
    
    #self.args=args
    self.paths=[]                       # list of HDF5 paths to search for
    self.attributePaths=[]              # paths to attributes matching search pattern
    
  # Analyze argument to get group(s), beam(s), attribute
  #   
  def analyzeArgument(self, arg): 
    if self.debug:
      print "analyzeArgument("+ arg + ")"   # DEBUG

    # Identify ROOT
    if re.match('/ROOT', arg, re.IGNORECASE) or re.match('/', arg, re.IGNORECASE):
      root="/"
  
    # Identify SAPs
    SAPNr="all"
    match=re.search('SAP[0-9]{0,3}', arg, re.IGNORECASE)
    if match:
      if len(match.group())==3:
        SAPNr="all"
      else:
        SAPNr = int(match.group()[3:])
      if self.debug:
        print "SAPNr = ", SAPNr
    match=re.search('SAP_[0-9]{0,3}', arg, re.IGNORECASE)
    if match:
      if len(match.group())==3:
        SAPNr="all"
      else:
        SAPNr = int(match.group()[3:])
      if self.debug:
        print "SAPNr = ", SAPNr
    match=re.search('SUB_ARRAY_POINTING[0-9]{0,3}', arg, re.IGNORECASE)
    if match:
      if len(match.group())==18:
        SAPNr="all"
        #SAPNr = []    # empty list, such that we can handle a number or "all", too
      else:
        SAPNr = int(match.group()[18:])
      if self.debug:
        print "SAPNr = ", SAPNr

    # Indentify BEAMs
    match=re.search('/BEAM[0-9]{0,3}', arg, re.IGNORECASE)
    BeamNr=None
    if match:
      #BeamNr=[]     # empty list, such that we can handle a number or "all", too
      if len(match.group())==4:
        BeamNr="all"
      else:
        BeamNr = int(match.group()[5:])
      if self.debug:
        print "BeamNr = ", BeamNr

    # Identify Stokes by number
    match=re.search('/Stokes[0-9]{0,1}', arg, re.IGNORECASE)
    StokesNr=None
    if match:
      if len(match.group())==6:
        StokesNr="all"
      else:
        StokesNr = int(match.group()[7:])
        print "StokesNr = ", StokesNr
        
    # Identify attribute and value
    match=re.search(':\w*', arg, re.IGNORECASE)
    attribute=""
    if match:
      attribute=match.group()[1:]
      if self.debug:
        print "attribute = ", attribute     

    # Identify value
    match=re.search('=\w*', arg, re.IGNORECASE)
    if match:
      value=match.group()[1:]
      if self.debug:
        print "value = ", value
    
    # If --add flag has been specified
    
    # Now create valid HDF5Path
    print "SAPNr = ", SAPNr
    self.createHDF5Path(SAPNr, BeamNr, StokesNr, attribute)
    
  # Create a complete HDF5 path
  #
  def createHDF5Path(self, sapNr=None, beamNr=None, stokesNr=None, attribute=None):
    if self.debug:
      print "createHDf5Path(" + str(sapNr) + "," + str(beamNr) + "," + str(stokesNr) + str(attribute) + ")"     # DEBUG
      print "createHDF5Path() sapNr = ", sapNr
      print "createHDF5Path() beamNr = ", beamNr  
      print "createHDF5Path() stokesNr = ", stokesNr
      print "createHDF5Path() attribute = ", attribute
  
    path="/"
    if sapNr!=None and sapNr!="all":
      #if self.SubArrayPointing(sapNr).exists():
      path += "SUB_ARRAY_POINTING_%(sapNr)03d" %{'sapNr': sapNr}
    else:
      for sap in range(0, self.fh.nofSubArrayPointings().value):    # all SAPS
        #print "sap =", sap         # DEBUG
        if self.fh.subArrayPointing(sap).exists():
          path += "SUB_ARRAY_POINTING_%(sap)03d" %{'sap': sap}
        if beamNr!=None and beamNr!="all":                          # BEAM
          if self.fh.subArrayPointing(sap).beam(beamNr).exists:
            path += "/BEAM_%(beamNr)03d" %{'beamNr': beamNr}
            self.paths.append(path)
          if stokesNr!=None and stokesNr!="all":                    # STOKES
            if self.fh.subArrayPointing(sap).beam(beamNr).stokes(stokesNr).exists():
              path += "/STOKES_%(stokesNr)1d" %{'stokesNr': stokesNr}
              self.paths.append(path)
          else:
            for s in range(0, self.fh.subArrayPointing(sap).beam(beamNr).nofStokes().value):
              #print "s = ", s       # DEBUG
              if self.fh.subArrayPointing(sap).beam(beamNr).stokes(s).exists():
                path += "/STOKES_%(s)01d" %{'s': s}
                path=path.upper()             # convert path to upper case
                self.paths.append(path)
        else:
          for b in range(0, self.fh.observationNofBeams().value):      # use here then nofObservedBeams()
            #print "b = ", b         # DEBUG           # check if BeamNr exists in this hdf5
            if fh.subArrayPointing(sap).beam(b).exists():
              path += "/BEAM_%(beam)03d" %{'beam': b}
              if stokesNr!=None and stokesNr!="all":
                if fh.SubArrayPointing().beam(b).stokes(stokesNr).exists():
                  path += "/STOKES_%(stokesNr)1d" %{'stokesNr': stokesNr}
                  self.paths.append(path)
              else:
                for s in range(0, self.fh.subArrayPointing(sap).beam(b).nofStokes().value):
                  #print "s = ", s       # DEBUG
                  if self.fh.SubArrayPointing().beam(b).stokes(s).exists():
                    path += "/STOKES_%(s)01d" %{'s': s}
                    path=path.upper()             # convert path to upper case
                    self.paths.append(path)

    if self.debug:
      print "createHDF5Path() path = " + path

  # Create attribute paths
  #
  def attributePaths(self, attribute, path=None):
    if self.debug:
      print "attributePaths(" + path + ")"  # DEBUG

    if path==None:     # If no particular was given
      for path in self.paths:
        path += "/%(att)" %{'att': attribute}
    else:
      path += "/%s" %attribute
 
  # Get attribute paths that match search string
  #
  def attributeSearchPaths(self, searchString, path=None):
    if self.debug:
      print "attributeSearchPaths(" + searchString + "," + path + ")"   # DEBUG
 
    # If path is None, then search in all subgroups
    
    # Otherwise start with group path
 
    # get all nodes recursively from this group on
    
      # get the names of the attributes

      # search for searchstring  within attribute name
 
      # if present at to paths
 
  # Get the value part of the argument, if present
  #
  def getValue(self, path):
    print "getValue(" + path + ")"       # DEBUG
  
  def setValue(self, path):
    print "setValue(" + path + ")"       # DEBUG
    # Check if file is writable!

  # DEBUG Show attribute paths
  def showPaths(self):
    print "HDF5 paths with attributes:"
    for path in self.paths:
      print path
  
  # Get a particular attribute from its HDF5 path
  #

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
    
#  def findAttribute(node, substring):
#    print "findAttribute("+ substring + ")"         # DEBUG
#    indx=findAttributeIndex(node, substring)
#    name=enumerate(node.nodeNames()[indx]
#    node.getNode(name)

