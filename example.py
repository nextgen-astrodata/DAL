import BeamFormedFile
from itertools import count

f = BeamFormedFile.BeamFormedFile("test.h5")

print "Observation %s ran from %s UTC to %s UTC" % (f.observationID().get(), f.observationStartUTC().get(), f.observationEndUTC().get())

for sapnr in count():
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

      # ArrayFloat has no bounds check, nor does it act
      # like a list! So be careful to only use valid
      # and nonnegative indices
      x = BeamFormedFile.ArrayFloat(4)
      stokes.getMatrix([0,0],[4,1],x);

      print "            First few samples of the first channel are %s" % ([x[i] for i in range(4)],)


