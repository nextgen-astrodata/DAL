#!/usr/bin/env python
#
# bfmeta.py
# Python class that retrieves header information from a BF.h5 file 
#
# File:         bfmeta.py
# Author:       Sven Duscha (duscha_at_astron.nl)
# Date:         2012-03-02
# Last change:  2012-07-18

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
    print self.fh.groupType().name(), "\t\t=", self.fh.groupType().value
    print self.fh.fileName().name(), "\t\t=", self.fh.fileName().value
    print self.fh.fileDate().name(), "\t\t=", self.fh.fileDate().value
    print self.fh.fileType().name(), "\t\t=", self.fh.fileType().value
    print self.fh.telescope().name(), "\t\t=", self.fh.telescope().value
    print self.fh.observer().name(), "\t\t=", self.fh.observer().value
    print self.fh.projectID().name(), "\t\t=", self.fh.projectID().value
    print self.fh.projectTitle().name(), "\t\t=", self.fh.projectTitle().value
    print self.fh.projectPI().name(), "\t\t=", self.fh.projectPI().value
    print self.fh.projectCOI().name(), "\t\t=", self.fh.projectCOI().value
    print self.fh.projectContact().name(), "\t=", self.fh.projectContact().value
    print self.fh.observationID().name(), "\t\t=", self.fh.observationID().value
    print self.fh.observationStartUTC().name(), "\t=", self.fh.observationStartUTC().value
    print self.fh.observationEndUTC().name(), "\t=", self.fh.observationEndUTC().value
    print self.fh.observationStartMJD().name(), "\t=%(mjd)19.12f" %{'mjd':self.fh.observationStartMJD().value}
    print self.fh.observationEndMJD().name(), "\t=%(mjd)19.12f" %{'mjd':self.fh.observationEndMJD().value}
    print self.fh.observationStartTAI().name(), "\t=", self.fh.observationStartTAI().value
    print self.fh.observationEndTAI().name(), "\t=", self.fh.observationEndTAI().value
    print self.fh.observationNofStations().name(), "=", self.fh.observationNofStations().value
    print self.fh.observationStationsList().name(), "=", self.fh.observationStationsList().value
    print self.fh.observationFrequencyMin().name(), "\t=", self.fh.observationFrequencyMin().value, self.fh.observationFrequencyUnit().value
    print self.fh.observationFrequencyCenter().name(), "\t=", self.fh.observationFrequencyCenter().value, self.fh.observationFrequencyUnit().value
    print self.fh.observationFrequencyMax().name(), "\t=", self.fh.observationFrequencyMax().value, self.fh.observationFrequencyUnit().value
    print self.fh.observationNofBitsPerSample().name(), "=", self.fh.observationNofBitsPerSample().value
    print self.fh.clockFrequency().name(), "\t=", self.fh.clockFrequency().value, self.fh.clockFrequencyUnit().value
    print self.fh.antennaSet().name(), "\t\t=", self.fh.antennaSet().value
    print self.fh.filterSelection().name(), "\t=", self.fh.filterSelection().value
    print self.fh.targets().name(), "\t\t=", self.fh.targets().value
    print self.fh.systemVersion().name(), "\t\t=", self.fh.systemVersion().value
    print self.fh.pipelineName().name(), "\t\t=", self.fh.pipelineName().value
    print self.fh.pipelineVersion().name(), "\t=", self.fh.pipelineVersion().value
    print self.fh.docName().name(), "\t\t=", self.fh.docName().value
    print self.fh.docVersion().name(), "\t\t=", self.fh.docVersion().value
    print self.fh.createOfflineOnline().name(), "\t=", self.fh.createOfflineOnline().value
    print self.fh.BFFormat().name(), "\t\t=", self.fh.BFFormat().value
    print self.fh.BFVersion().name(), "\t\t=", self.fh.BFVersion().value
    print self.fh.totalIntegrationTime().name(), " = %(ti).2f %(tiu)s" %{'ti':self.fh.totalIntegrationTime().value, 'tiu':self.fh.totalIntegrationTimeUnit().value}
    print self.fh.observationDataType().name(), "\t=", self.fh.observationDataType().value
    print self.fh.subArrayPointingDiameter().name(), " =", self.fh.subArrayPointingDiameter().value, self.fh.subArrayPointingDiameterUnit().value
    print self.fh.bandwidth().name(), "\t\t= %(bw).2f %(bwu)s" %{'bw':self.fh.bandwidth().value, 'bwu':self.fh.bandwidthUnit().value}
    print self.fh.beamDiameter().name(), "\t=", self.fh.beamDiameter().value #, self.fh.beamDiameterUnit().value
    print self.fh.weatherTemperature().name(), "\t=", self.fh.weatherTemperature().value, self.fh.weatherTemperatureUnit().value
    print self.fh.weatherHumidity().name(), "\t=", self.fh.weatherHumidity().value, self.fh.weatherHumidityUnit().value
    print self.fh.systemTemperature().name(), "\t=", self.fh.systemTemperature().value, self.fh.systemTemperatureUnit().value
    print self.fh.observationNofSubArrayPointings().name(), "=", self.fh.observationNofSubArrayPointings().value
    print self.fh.nofSubArrayPointings().name(), "=", self.fh.nofSubArrayPointings().value
    self.prefix=bcolors.ENDC      # reset printing options
  
  # Display Sub Array Pointing information for SAPs
  #
  def displaySAP(self):
    if self.sap=="all":
      for nr in range(0, self.fh.nofSubArrayPointings().value):   
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

#    if sap.nofStations().exists():   
#      print self.prefix + "No. of stations        = ", sap.nofStations().value
#    if sap.stationsList().exists():
#      print self.prefix + "Stationlist            = ", sap.stationsList().value
    if sap.pointRA().exists():
      print self.prefix + "pointing RA            =  %(pra)3.10f %(prau)s" %{ 'pra': sap.pointRA().value, 'prau': sap.pointRAUnit().value}
    if sap.pointDEC().exists():
      print self.prefix + "pointing DEC           =  %(decra)4.10f %(decrau)s" %{'decra': sap.pointDEC().value, 'decrau': sap.pointDECUnit().value}
#    if sap.clockRate().exists() and sap.clockRateUnit().exists()==False:
#      print self.prefix + "Clock rate             = ", sap.clockRate().value
    if sap.clockRate().exists() and sap.clockRateUnit().exists():
      print self.prefix + "Clock rate             = ", sap.clockRate().value, sap.clockRateUnit().value
    if sap.nofSamples().exists():
      print self.prefix + "No. of samples         = ", sap.nofSamples().value
    if sap.samplingRate().exists() and sap.samplingRateUnit().exists()==False:
      print self.prefix + "Sampling rate          = ", sap.samplingRate().value      
    if sap.samplingRate().exists() and sap.samplingRateUnit().exists():
      print self.prefix + "Sampling rate          = ", sap.samplingRate().value, sap.samplingRateUnit().value      
    if sap.channelsPerSubband().exists() and sap.subbandWidth().exists()==False:
      print self.prefix + "Channels per subband   = ", sap.channelsPerSubband().value
    if sap.channelsPerSubband().exists() and sap.subbandWidth().exists()==False:
      print self.prefix + "Channels per subband   = ", sap.channelsPerSubband().value, sap.subbandWidth().value
    if sap.channelsPerSubband().exists() and sap.subbandWidthUnit().exists():
      print self.prefix + "Subband width unit     = ", sap.subbandWidthUnit().value      
    if sap.channelWidth().exists()  and sap.channelWidthUnit().exists()==False:
      print self.prefix + "Channel width          = ", sap.channelWidth().value
    if sap.channelWidth().exists() and sap.channelWidthUnit().exists():
      print self.prefix + "Channel width          = ", sap.channelWidth().value, sap.channelWidthUnit().value
    if sap.nofBeams().exists():
      print self.prefix + "No. of beams           = ", sap.nofBeams().value      

    # Beams within this SAP
    self.displayBeam(sap)
    self.prefix=bcolors.ENDC
    print self.prefix

  # Display Sub Array Pointing information for Beams
  #  
  def displayBeam(self, sap):
    #print "displayBeam()"               # DEBUG
  
    if self.beam=="all":
      for n in range(0, sap.nofBeams().value):   
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
    #print "str(nr) = ", str(nr), " self.beam = ",self.beam    # DEBUG

    if str(nr) not in self.beam and self.beam!="all":    
      return

    print self.prefix + "------------------------------------"
    print self.prefix + "Beam Nr                = ", nr

    # Only beams with selected Stokes components
    if self.stokes not in beam.stokesComponents().value and self.stokes!="all":
      print self.prefix + "Stokes component " + str(self.stokes) + " doesn't exist in beam Nr. " + str(nr)
      return

    if beam.nofStations().exists():
      print self.prefix + "No of stations         = ", beam.nofStations().value
    if beam.stationsList().exists():
      print self.prefix + "Stations               = ", beam.stationsList().value
    if beam.pointRA().exists():
      print self.prefix + "pointing RA            = ", beam.pointRA().value
    if beam.pointDEC().exists():
      print self.prefix + "pointing DEC           = ", beam.pointDEC().value
    if beam.pointOffsetRA().exists():
      print self.prefix + "pointing offset RA     = ", beam.pointOffsetRA().value
    if beam.pointOffsetDEC().exists():
      print self.prefix + "pointing offset DEC    = ", beam.pointOffsetDEC().value
    if beam.beamDiameterRA().exists():
      print self.prefix + "beam diameter RA       = ", beam.beamDiameterRA().value
    if beam.beamDiameterDEC().exists():
      print self.prefix + "beam diameter DEC      = ", beam.beamDiameterDEC().value      
    if beam.beamFrequencyCenter().exists() and beam.beamFrequencyCenterUnit().exists()==False:
      print self.prefix + "beam freq. barycenter  = ", beam.beamFrequencyCenter().value
    if beam.beamFrequencyCenter().exists() and beam.beamFrequencyCenterUnit().exists():
      print self.prefix + "beam freq. barycenter  = ", beam.beamFrequencyCenter().value, beam.beamFrequencyCenterUnit().value
    if beam.foldedData().exists():
      print self.prefix + "folded data            = ", beam.foldedData().value
    if beam.foldPeriod().exists() and beam.foldPeriodUnit().exists()==False:
      sys.stdout.write(self.prefix + "folded period          = " + str(beam.foldPeriod().value))
    if beam.foldPeriodUnit().exists():
      print " ", beam.foldPeriodUnit().value
    if beam.dedispersion().exists():
      print self.prefix + "dedispersion           = ", beam.dedispersion().value
    if beam.dedispersionMeasure().exists():
      print self.prefix + "dedispersion Measure   =  %(dm) %(dmu)" %{'dm': beam.dedispersionMeasure().value, 'dmu': beam.dedispersionMeasureUnit().value}
    if beam.barycentered().exists():
      print self.prefix + "barycentered           = ", beam.barycentered().value
    if beam.nofStokes().exists():
      print self.prefix + "No of Stokes           = ", beam.nofStokes().value
    if beam.stokesComponents().exists():
      print self.prefix + "Stokes components      = ", beam.stokesComponents().value
    if beam.complexVoltages().exists():
      print self.prefix + "Complex voltages       = ", beam.complexVoltages().value
    if beam.signalSum().exists():
      print self.prefix + "Signal sum             = ", beam.signalSum().value

    # Display Stokes datasets
    for d in range(0, beam.nofStokes().value):
      self.displayStokesDatasetInfo(beam, d)
   
    self.displayCoordinates(beam)

    self.prefix=bcolors.ENDC          # reset printing options
    print self.prefix
    
  # Display info of Stokes dataset
  #
  def displayStokesDataset(self, beam, nr="all"):
    if nr=="all":
      for n in range(0, beam.nofStokes().value):
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
    print self.prefix + "-----------------------------------"
    if stokes.stokesComponent().exists():
      print self.prefix + "Stokes             = ", stokes.stokesComponent().value    
    if stokes.nofChannels().exists():
      print self.prefix + "No. of channels    = ", stokes.nofChannels().value    
    if stokes.nofSubbands().exists():
      print self.prefix + "No. of subbands    = ", stokes.nofSubbands().value    
    if stokes.nofSamples().exists():
      print self.prefix + "No. of samples     = ", stokes.nofSamples().value    
     
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
      #  print "refLocationValue     = ", coords.refLocationValue().value
      if coords.refLocationUnit().exists():
        print self.prefix + "refLocationUnit    = ", coords.refLocationUnit().value
      if coords.refLocationFrame().exists():
        print self.prefix + "refLocationFrame   = ", coords.refLocationFrame().value
      if coords.refTimeValue().exists():
        print self.prefix + "refTimeValue       = ", coords.refTimeValue().value
      if coords.refTimeUnit().exists():
        print self.prefix + "refTimeUnit        = ", coords.refTimeUnit().value
      if coords.refTimeFrame().exists():
        print self.prefix + "refTimeFrame       = ", coords.refTimeFrame().value
      if coords.nofCoordinates().exists():
        print self.prefix + "No. of Coordinates = ", coords.nofCoordinates().value
      if coords.nofAxes().exists():
        print self.prefix + "No. of Axes        = ", coords.nofAxes().value
      if coords.coordinateTypes().exists():
        print self.prefix + "Coordinate types   = ", coords.coordinateTypes().value

      for c in range(0, coords.nofCoordinates().value):
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
        print self.prefix + "Coordinate type    = ", coord.coordinateType().value
      if coord.storageType().exists():
        print self.prefix + "Storage type       = ", coord.storageType().value
      if coord.nofAxes().exists():
        print self.prefix + "No. of axes        = ", coord.nofAxes().value
      if coord.axisNames().exists():
        print self.prefix + "Axis names         = ", coord.axisNames().value
      if coord.axisUnits().exists():
        print self.prefix + "Axis units         = ", coord.axisUnits().value

      #if coord.coordinateType().exists():
      #  if coord.coordinateType().value == "Time":
      #    print "coord.coordinateType().value = ", coord.coordinateType().value
      #    #self.displayTimeCoordinate(coord)
      #  else:
      #    print "coord.coordinateType().value", coord.coordinateType().value
      #    self.displaySpectralCoordinate(coord)
          
  # Time coordinate information
  #
  def displayTimeCoordinate(self, coord):
    if coord.referenceFrame().exists():
      print self.prefix + "Reference frame    = ", coord.referenceFrame().value

  # Spectral coordinate information
  #
  def displaySpectralCoordinate(self, coord):
    if coord.referenceFrame().exists():
      print self.prefix + "Reference frame    = ", coord.referenceFrame().value
    if coord.restFrequency().exists():
      print self.prefix + "Rest frequency     = ", coord.restFrequency().value
    if coord.restFrequencyUnit().exists():
      print self.prefix + "Rest frequency unit = ", coord.restFrequencyUnit().value
    if coord.restWavelength().exists():
      print self.prefix + "Rest wavelength    = ", coord.restWavelength().value
    if coord.restWavelengthUnit().exists():
      print self.prefix + "Rest wavelength unit = ", coord.restWavelengthUnit().value


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