#!/usr/bin/env python
import DAL
import numpy
from itertools import count

filedir = 'data'
filenames = \
[ 'L30042_SAP000_B000_S0_P000_bf.h5'
, 'L63876_SAP000_B000_S0_P000_bf.h5'
]

def printData(bffile):
  # functions like f.observationID() return attribute objects, which has a `value' property
  # that can be get, set, or deleted:
  #
  # a = f.observationID()
  # a.value = "12345"   # setter
  # print a.value       # getter
  # del a.value         # removes the attribute from the HDF5 file
  #
  # more low-level functionality is offered by the following methods:
  #       get()    retrieve the attribute (but bail if it does not exist)
  #       set(x)   set the attribute to value x (creating the attribute if needed)
  #       exists() check for the existence of the attribute
  #       remove() delete the attribute from the group
  #       name()   the name of the attribute in the HDF5 file (f.e. "OBSERVATION_ID")
  print "Observation %s ran from %s UTC to %s UTC" % (f.observationID().value, f.observationStartUTC().value, f.observationEndUTC().value)

  for sapnr in count():
    # functions like f.subArrayPointing(x) return group objects, which have their own attributes.
    # A group is only really opened only if its attributes/datasets/subgroups are accessed, which
    # allows the following functionality first:
    #
    #     create()         create the group
    #     exists()         check for the existence of the group

    sap = f.subArrayPointing(sapnr)

    if not sap.exists():
      break

    print "SAP %u points to (%.2f, %.2f)" % (sapnr, sap.pointRA().value, sap.pointDEC().value)

    for beamnr in count():
      beam = sap.beam(beamnr)

      if not beam.exists():
        break

      print "    Beam %u points to (%.2f, %.2f)" % (beamnr, beam.pointRA().value, beam.pointDEC().value)

      for stokesnr in [0,1,2,3]:
        # any stokes [0..3] can exist

        stokes = beam.stokes(stokesnr)

        if not stokes.exists():
          continue

        print "        Stokes %s has %u subbands and %u samples" % (stokes.stokesComponent().value, stokes.nofSubbands().value, stokes.nofSamples().value)

        # data sets can get and set slices of data in the form of numpy arrays.
        # The dimensions of the provided numpy arrays determine the amount of data
        # that has to be read or written. The dimensionality must be the same as of
        # the dataset. Care must be taken that the numpy array
        # is of the correct type (stokes.dtype == numpy.float32 in this case).
        x = numpy.array([[0,0],[0,0]], dtype=stokes.dtype)

        # get2D(pos,array) reads `array` at position `pos`.
        stokes.get2D([0,0], x);

        print "            First two samples of the first two channels are:\n%s" % (x,)


# open the file for reading
for filename in filenames:
  f = DAL.BF_File(filedir + '/' + filename)
  printData(f)
  print "--------------------------------------------------------------------------------"

