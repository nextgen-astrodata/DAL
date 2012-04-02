#!/usr/bin/env python
#
# bfmeta.py
# Python class that retrieves header information from a BF.h5 file 
#
# File:         bfmeta.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-03-02
# Last change:  2012-04-02


import sys
import DAL

class bfmeta:
  def __init__(self, fh=0, filename="", tabs=True, color=False, sap="all", beam="all", stokes="all", verbose=False):
    if fh==0:                       # if no file handle given
      self.fh=DAL.BF_File(filename)      # open file    
    else:
      self.fh=fh                        # take handle
      
    # Display attributes
    self.useTabs=tabs
    self.useColor=color
    self.prefix=""
    # Selection of SAP, Beam and Stokes to show
    self.sap=sap  
    self.beam=beam
    self.stokes=stokes
    self.verbose=verbose
    
    self.displayInfo()

  # High-level function to display all info, calling display ftns for classes
  #  
  def displayInfo(self):
    self.displayFileInfo()
    self.displaySAP()
  
  # Display information about BF_File
  #
  def displayFileInfo(self):
    #print "displayFileInfo()"       # DEBUG
    if self.fh.telescope().exists():
      print "Telescope              = ", self.fh.telescope().get()
    if self.fh.observer().exists():
      print "Observer               = ", self.fh.observer().get()
    if self.fh.target().exists():
      print "Target                 = ", self.fh.target().get()
    if self.fh.filterSelection().exists():
      print "Backend                = ", self.fh.filterSelection().get()
    if self.fh.projectID().exists():
      print "Project ID             = ", self.fh.projectID().get()
    if self.fh.observationStartUTC().exists():
      print "UTC start time         = ", self.fh.observationStartUTC().get()
    if self.fh.observationEndUTC().exists():
      print "UTC end time           = ", self.fh.observationEndUTC().get()
    if self.fh.observationStartMJD().exists():
      print "MJD start time         = ", self.fh.observationStartMJD().get()  
    if self.fh.observationEndMJD().exists():
      print "MJD end time           = ", self.fh.observationEndMJD().get() 
    if self.fh.observationStartTAI().exists():
      print "TAI start time         = ", self.fh.observationStartTAI().get()
    if self.fh.observationEndTAI().exists():
      print "TAI end time           = ", self.fh.observationEndTAI().get()
    if self.fh.totalIntegrationTime().exists():
      print "Total integration time = ", self.fh.totalIntegrationTime().get()
    if self.fh.observationDatatype().exists():
      print "Observation datatype   = ", self.fh.observationDatatype().get()
    if self.fh.subArrayPointingDiameter().exists():
      print "Subarray pointing diameter = ", self.fh.subArrayPointingDiameter().get()
    if self.fh.bandwidth().exists():
      print "Bandwidth              = ", self.fh.bandwidth().get()
    if self.fh.beamDiameter().exists():
      print "Beam diameter          = ", self.fh.beamDiameter().get()
    if self.fh.nofSubArrayPointings().exists():
      print "No. of SAP             = ", self.fh.nofSubArrayPointings().get()
    self.prefix=bcolors.ENDC      # reset printing options
  
  # Display Sub Array Pointing information for SAPs
  #
  def displaySAP(self):
    if self.sap=="all":
      for nr in range(0, self.fh.nofSubArrayPointings().get()):   
        self.displaySAPInfo(nr)
    else:
      if isinstance(self.sap, list):
        for nr in self.sap:
          self.displaySAPInfo(nr)
      else:   # single SAP nr (int)
        self.displaySAPInfo(int(self.sap))
  
  # SAP attributes of individual SAP Nr.
  #
  def displaySAPInfo(self, nr):
    if self.useTabs:
      self.prefix=""    # SAP is high-level doesn't have a tab
    if self.useColor:
      self.prefix=self.prefix + bcolors.SAP

    if self.fh.subArrayPointing(nr).exists():
      if str(nr) in self.sap or self.sap=="all":
        sap=self.fh.subArrayPointing(nr)
        print self.prefix + "------------------------------------"
        print self.prefix + "SubArrayPointing Nr    = ", nr
      else:
        print "SubArrayPointing Nr", nr, "doesn't exist."        
        return
    else:
      print "SubArrayPointing Nr", nr, "doesn't exist."
      return    

    if sap.nofStations().exists():   
      print self.prefix + "No. of stations        = ", sap.nofStations().get()
    if sap.stationsList().exists():
      print self.prefix + "Stationlist            = ", sap.stationsList().get()
    if sap.pointRA().exists():
      print self.prefix + "pointing RA            = ", sap.pointRA().get()
    if sap.pointDEC().exists():
      print self.prefix + "pointing DEC           = ", sap.pointDEC().get()
    if sap.clockRate().exists() and sap.clockRateUnit().exists()==False:
      #sys.stdout.write(self.prefix + "Clock rate             = "+str(sap.clockRate().get()))
      print self.prefix + "Clock rate             = ", sap.clockRate().get()
    if sap.clockRate().exists() and sap.clockRateUnit().exists():
      print self.prefix + "Clock rate             = ", sap.clockRate().get(), sap.clockRateUnit().get()
    if sap.nofSamples().exists():
      print self.prefix + "No. of samples         = ", sap.nofSamples().get()
    if sap.samplingRate().exists() and sap.samplingRateUnit().exists()==False:
      print self.prefix + "Sampling rate          = ", sap.samplingRate().get()      
    if sap.samplingRate().exists() and sap.samplingRateUnit().exists():
      print self.prefix + "Sampling rate          = ", sap.samplingRate().get(), sap.samplingRateUnit().get()      
    if sap.channelsPerSubband().exists() and sap.subbandWidth().exists()==False:
      print self.prefix + "Channels per subband   = ", sap.channelsPerSubband().get()
    if sap.channelsPerSubband().exists() and sap.subbandWidth().exists()==False:
      print self.prefix + "Channels per subband   = ", sap.channelsPerSubband().get(), sap.subbandWidth().get()
    if sap.channelsPerSubband().exists() and sap.subbandWidthUnit().exists():
      print self.prefix + "Subband width unit     = ", sap.subbandWidthUnit().get()      
    if sap.channelWidth().exists()  and sap.channelWidthUnit().exists()==False:
      print self.prefix + "Channel width          = ", sap.channelWidth().get()
    if sap.channelWidth().exists() and sap.channelWidthUnit().exists():
      print self.prefix + "Channel width          = ", sap.channelWidth().get(), sap.channelWidthUnit().get()
    if sap.nofBeams().exists():
      print self.prefix + "No. of beams           = ", sap.nofBeams().get()      

    # Beams within this SAP
    self.displayBeam(sap)
    self.prefix=bcolors.ENDC
    print self.prefix

  # Display Sub Array Pointing information for Beams
  #  
  def displayBeam(self, sap):
    #print "displayBeam()"               # DEBUG
  
    if self.beam=="all":
      for n in range(0, sap.nofBeams().get()):   
          self.displayBeamInfo(sap, int(n))
    elif isinstance(self.beam, list):
      for b in self.beam:
        self.displayBeamInfo(sap, int(b))
    else:   # single beam integer
      self.displayBeamInfo(sap, int(self.beam))

  # Display Beam information
  #  
  def displayBeamInfo(self, sap, nr):
    #print "displayBeamInfo()"

    if self.useTabs:
      self.prefix="\t"
    if self.useColor:
      self.prefix=self.prefix + bcolors.BEAM

    # Check if this beam exists in this SAP
    if sap.beam(nr).exists():
      beam=sap.beam(nr)
    else:
      print self.prefix + "Beam No. ", str(nr), " doesn't exist in file." 
      return

    # only display beam if it is in the list to be shown
    print "str(nr) = ", str(nr), " self.beam = ",self.beam    # DEBUG

    if str(nr) not in self.beam and self.beam!="all":    
      return

    print self.prefix + "------------------------------------"
    print self.prefix + "Beam Nr                = ", nr
        

    # Only beams with selected Stokes components
    if self.stokes not in beam.stokesComponents().get() and self.stokes!="all":
      return

    if beam.nofStations().exists():
      print self.prefix + "No of stations         = ", beam.nofStations().get()
    if beam.stationsList().exists():
      print self.prefix + "Stations               = ", beam.stationsList().get()
    if beam.pointRA().exists():
      print self.prefix + "pointing RA            = ", beam.pointRA().get()
    if beam.pointDEC().exists():
      print self.prefix + "pointing DEC           = ", beam.pointDEC().get()
    if beam.pointOffsetRA().exists():
      print self.prefix + "pointing offset RA     = ", beam.pointOffsetRA().get()
    if beam.pointOffsetDEC().exists():
      print self.prefix + "pointing offset DEC    = ", beam.pointOffsetDEC().get()
    if beam.beamDiameterRA().exists():
      print self.prefix + "beam diameter RA       = ", beam.beamDiameterRA().get()
    if beam.beamDiameterDEC().exists():
      print self.prefix + "beam diameter DEC      = ", beam.beamDiameterDEC().get()      
    if beam.beamFrequencyCenter().exists() and beam.beamFrequencyCenterUnit().exists()==False:
      print self.prefix + "beam freq. barycenter  = ", beam.beamFrequencyCenter().get()
    if beam.beamFrequencyCenter().exists() and beam.beamFrequencyCenterUnit().exists():
      print self.prefix + "beam freq. barycenter  = ", beam.beamFrequencyCenter().get(), beam.beamFrequencyCenterUnit().get()
#      sys.stdout.write(beam.beamFrequencyCenterUnit().get())
    if beam.foldedData().exists():
      print self.prefix + "folded data            = ", beam.foldedData().get()
    if beam.foldPeriod().exists() and beam.foldPeriodUnit().exists()==False:
      sys.stdout.write(self.prefix + "folded period          = " + str(beam.foldPeriod().get()))
    if beam.foldPeriodUnit().exists():
      print " ", beam.foldPeriodUnit().get()
    if beam.dedispersion().exists():
      print self.prefix + "dedispersion           = ", beam.dedispersion().get()
    if beam.dedispersionMeasure().exists():
      sys.stdout.write(self.prefix + "dedispersion Measure   = " + str(beam.dedispersionMeasure().get()))
    if beam.dedispersionMeasureUnit().exists():
      print " " + beam.dedispersionMeasureUnit().get()
    if beam.barycentered().exists():
      print self.prefix + "barycentered           = ", beam.barycentered().get()
    if beam.nofStokes().exists():
      print self.prefix + "No of Stokes           = ", beam.nofStokes().get()
    if beam.stokesComponents().exists():
      print self.prefix + "Stokes components      = ", beam.stokesComponents().get()
    if beam.complexVoltages().exists():
      print self.prefix + "Complex voltages       = ", beam.complexVoltages().get()
    if beam.signalSum().exists():
      print self.prefix + "Signal sum             = ", beam.signalSum().get()

    # Display Stokes datasets
    for d in range(0, beam.nofStokes().get()):
      self.displayStokesDatasetInfo(beam, d)
   
    self.displayCoordinates(beam)

    self.prefix=bcolors.ENDC          # reset printing options
    print self.prefix
    
  # Display info of Stokes dataset
  #
  def displayStokesDataset(self, beam, nr="all"):
    if nr=="all":
      for n in range(0, beam.nofStokes().get()):
        self.displayStokesDatasetInfo(n)
    else:
      self.displayStokesDatasetInfo(nr)

  def displayStokesDatasetInfo(self, beam, nr):
    if self.useTabs==True:
      self.prefix="\t\t\t"
    if self.useColor==True:
      self.prefix=self.prefix + bcolors.DATASET

    if beam.stokes(nr).exists():
      stokes=beam.stokes(nr)
    else:
      print bcolors.FAIL + "Stokes dataset ", nr, " doesn't exist."
      self.prefix=bcolors.ENDC
      print self.prefix
      return

    if stokes.stokesComponent().exists():
      print self.prefix + "Stokes             = ", stokes.stokesComponent().get()    
    if stokes.nofChannels().exists():
      print self.prefix + "No. of channels    = ", stokes.nofChannels().get()    
    if stokes.nofSubbands().exists():
      print self.prefix + "No. of subbands    = ", stokes.nofSubbands().get()    
    if stokes.nofSamples().exists():
      print self.prefix + "No. of samples     = ", stokes.nofSamples().get()    
     
    self.prefix=bcolors.ENDC        # reset printing options     
    print self.prefix

  # Display coordinategroup info (only in verbose mode)
  #
  def displayCoordinates(self, beam):
    if self.useTabs==True:
      self.prefix="\t\t\t"
    if self.useColor==True:
      self.prefix=self.prefix + bcolors.COORD

    # Show coordinate infos only in verbose mode
    if not self.verbose:
      self.prefix=bcolors.ENDC            # reset printing options
      print self.prefix
      return

    print self.prefix + "----------------------------------"
    print self.prefix + "Coordinates"
    if beam.coordinates().exists()==False:
      return
    else:
      coords=beam.coordinates()

      # This is buggy in the Swig bindings
      #if coords.refLocationValue().exists():
      #  print "refLocationValue     = ", coords.refLocationValue().get()
      if coords.refLocationUnit().exists():
        print self.prefix + "refLocationUnit    = ", coords.refLocationUnit().get()
      if coords.refLocationFrame().exists():
        print self.prefix + "refLocationFrame   = ", coords.refLocationFrame().get()
      if coords.refTimeValue().exists():
        print self.prefix + "refTimeValue       = ", coords.refTimeValue().get()
      if coords.refTimeUnit().exists():
        print self.prefix + "refTimeUnit        = ", coords.refTimeUnit().get()
      if coords.refTimeFrame().exists():
        print self.prefix + "refTimeFrame       = ", coords.refTimeFrame().get()
      if coords.nofCoordinates().exists():
        print self.prefix + "No. of Coordinates = ", coords.nofCoordinates().get()
      if coords.nofAxes().exists():
        print self.prefix + "No. of Axes        = ", coords.nofAxes().get()
      if coords.coordinateTypes().exists():
        print self.prefix + "Coordinate types   = ", coords.coordinateTypes().get()

      for c in range(0, coords.nofCoordinates().get()):
        self.displayCoordinate(coords, c)

      self.prefix=bcolors.ENDC
      print self.prefix

  # Display a particular coordinate
  #
  def displayCoordinate(self, coords, nr):
    print self.prefix + "--------------------------------"
    print self.prefix + "Coordinate Nr      = ", nr
    if coords.coordinate(nr).exists()==False:
      print bcolors.FAIL + "Coordinate Nr ", str(nr), " does not exist."
      self.prefix=bcolors.ENDC
      return
    else:
      coord=coords.coordinate(nr)         # pick coordinate
      if coord.coordinateType().exists():
        print self.prefix + "Coordinate type    = ", coord.coordinateType().get()
      if coord.storageType().exists():
        print self.prefix + "Storage type       = ", coord.storageType().get()
      if coord.nofAxes().exists():
        print self.prefix + "No. of axes        = ", coord.nofAxes().get()
      if coord.axisNames().exists():
        print self.prefix + "Axis names         = ", coord.axisNames().get()
      if coord.axisUnits().exists():
        print self.prefix + "Axis units         = ", coord.axisUnits().get()

      #if coord.coordinateType().exists():
      #  if coord.coordinateType().get() == "Time":
      #    print "coord.coordinateType().get() = ", coord.coordinateType().get()
      #    #self.displayTimeCoordinate(coord)
      #  else:
      #    print "coord.coordinateType().get()", coord.coordinateType().get()
      #    self.displaySpectralCoordinate(coord)
          
  # Time coordinate information
  #
  def displayTimeCoordinate(self, coord):
    if coord.referenceFrame().exists():
      print self.prefix + "Reference frame    = ", coord.referenceFrame().get()

  # Spectral coordinate information
  #
  def displaySpectralCoordinate(self, coord):
    if coord.referenceFrame().exists():
      print self.prefix + "Reference frame    = ", coord.referenceFrame().get()
    if coord.restFrequency().exists():
      print self.prefix + "Rest frequency     = ", coord.restFrequency().get()
    if coord.restFrequencyUnit().exists():
      print self.prefix + "Rest frequency unit = ", coord.restFrequencyUnit().get()
    if coord.restWavelength().exists():
      print self.prefix + "Rest wavelength    = ", coord.restWavelength().get()
    if coord.restWavelengthUnit().exists():
      print self.prefix + "Rest wavelength unit = ", coord.restWavelengthUnit().get()


  def handleArg(self, arg):
    print "handleArg()"

    if "[" in arg and "]" in arg:    
      handleList(arg)
    else:
      return(int(arg))  # treat as integer

  # Handle command line options supplied as list
  #
  def handleList(self, list):
    print "handleList()"
    
    # strip off [ and ]
    # separate on ,
    # Detect ~ for ranges

  # Handle command line options supplied as a range
  #
  def handleRange(self, range):
    print "handleList()"
  

#############################################
#
# Helper class for color terminal printing
#
#############################################

        
class bcolors:
    BACKGROUND="dark"       # background scheme of terminal (dark or bright)
    HEADER = '\033[95m'
    SAP = '\033[94m'        # blue
    BEAM = '\033[92m'       # green
    #DATASET = '\033[93m'    # yellow
    DATASET= '\033[91m'     # red
    COORD = '\033[0m'       # fat white
    FAIL = '\033[91m'
    ENDC = '\033[0m'

    def switch(self):
      if self.BACKGROUND=="dark": # switch to bright background scheme
        BACKGROUND="bright"     # background scheme of terminal (dark or bright)
        HEADER = '\033[95m'
        SAP = '\033[94m'        # blue
        BEAM = '\033[92m'       # green
        DATASET = '\033[93m'    # yellow
        COORD = '\033[0m'       # fat white
        FAIL = '\033[91m'
        ENDC = '\033[0m'
      else:                     # switch to dark background scheme
        BACKGROUND="dark"
        HEADER = '\033[95m'
        SAP = '\033[94m'        # blue
        BEAM = '\033[92m'       # green
        DATASET = '\033[93m'    # yellow
        COORD = '\033[0m'       # fat white
        FAIL = '\033[91m'
        ENDC = '\033[0m'

    def disable(self):
        self.HEADER = ''
        self.SAP = ''
        self.BEAM = ''
        self.DATASET = ''
        self.FAIL = ''
        self.ENDC = ''      