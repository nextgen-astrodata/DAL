import BeamFormedFile
from itertools import count

f = BeamFormedFile.BeamFormedFile("test.h5")

print "Observation %s ran from %s UTC to %s UTC" % (f.observationID().get(), f.observationStartUTC().get(), f.observationEndUTC().get())

for sapnr in count():
  if not f.sap(sapnr).exists():
    break

  sap = f.sap(sapnr)

  print "SAP %u points to (%.2f, %.2f)" % (sapnr, sap.pointRA().get(), sap.pointDEC().get())

  for beamnr in count():
    if not sap.beam(beamnr).exists():
      break

    beam = sap.beam(beamnr)

    print "    Beam %u points to (%.2f, %.2f)" % (beamnr, beam.pointRA().get(), beam.pointDEC().get())

    for stokesnr in count():
      if not beam.stokes(stokesnr).exists():
        break

      stokes = beam.stokes(stokesnr)

      print "        Stokes %s has %u subbands and %u samples" % (stokes.stokesComponent().get(), stokes.nofSubbands().get(), stokes.nofSamples().get())

      x = BeamFormedFile.ArrayFloat(4)
      stokes.getMatrix([0,0],[4,1],x);

      print "            First few samples of the first channel are %s" % ([x[i] for i in range(4)],)


