import BeamFormedFile
import numpy
from itertools import count

# open the file for reading
f = BeamFormedFile.BeamFormedFile("test.h5")

# functions like f.observationID() return attribute objects, which support the following
# methods:
#       get()    retrieve the attribute (but bail if it does not exist)
#       set(x)   set the attribute to value x (creating the attribute if needed)
#       exists() check for the existence of the attribute
#       remove() delete the attribute from the group
#       name()   the name of the attribute in the HDF5 file (f.e. "OBSERVATION_ID")
print "Observation %s ran from %s UTC to %s UTC" % (f.observationID().get(), f.observationStartUTC().get(), f.observationEndUTC().get())

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

  print "SAP %u points to (%.2f, %.2f)" % (sapnr, sap.pointRA().get(), sap.pointDEC().get())

  for beamnr in count():
    beam = sap.beam(beamnr)

    if not beam.exists():
      break

    print "    Beam %u points to (%.2f, %.2f)" % (beamnr, beam.pointRA().get(), beam.pointDEC().get())

    for stokesnr in [0,1,2,3]:
      # any stokes [0..3] can exist

      stokes = beam.stokes(stokesnr)

      if not stokes.exists():
        continue

      print "        Stokes %s has %u subbands and %u samples" % (stokes.stokesComponent().get(), stokes.nofSubbands().get(), stokes.nofSamples().get())

      # data sets can get and set slices of data in the form of numpy arrays.
      # The dimensions of the provided numpy arrays determine the amount of data
      # that has to be read or written. The dimensionality must be the same as of
      # the dataset. Care must be taken that the numpy array
      # is of the correct type (numpy.float32 in this case).
      x = numpy.array([[0,0],[0,0]], dtype=numpy.float32)

      # get2D(pos,array) reads `array` at position `pos`.
      stokes.get2D([0,0],x);

      print "            First two samples of the first two channels are:\n%s" % (x,)

