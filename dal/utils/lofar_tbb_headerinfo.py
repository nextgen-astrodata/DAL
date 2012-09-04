#!/usr/bin/env python
#
# lofar_tbb_headerinfo.py
# Python script that displays header information from a TBB .h5 file 
#
# File:         lofar_tbb_headerinfo.py
# Author:       Alexander S. van Amesfoort (amesfoort_at_astron.nl)
# Date:         2012-09-04
# Last change:  2012-09-04

import sys
import dal

def print_cla(fh):
	print fh.groupType().name(), "\t\t\t=", fh.groupType().value
	print fh.fileName().name(), "\t\t\t=", fh.fileName().value
	print fh.fileDate().name(), "\t\t\t=", fh.fileDate().value
	print fh.fileType().name(), "\t\t\t=", fh.fileType().value
	print fh.telescope().name(), "\t\t\t=", fh.telescope().value
	print fh.projectID().name(), "\t\t\t=", fh.projectID().value
	print fh.projectTitle().name(), "\t\t\t=", fh.projectTitle().value
	print fh.projectPI().name(), "\t\t\t=", fh.projectPI().value
	print fh.projectCOI().name(), "\t\t\t=", fh.projectCOI().value
	print fh.projectContact().name(), "\t\t=", fh.projectContact().value
	print fh.observationID().name(), "\t\t\t=", fh.observationID().value
	print fh.observationStartUTC().name(), "\t\t=", fh.observationStartUTC().value
	print fh.observationEndUTC().name(), "\t\t=", fh.observationEndUTC().value

	observationStartMJDVal = fh.observationStartMJD().value
	if observationStartMJDVal is None:
		observationStartMJDVal = '-'
	print fh.observationStartMJD().name(), "\t\t=%(mjd)19.12f" %{'mjd':observationStartMJDVal}

	observationEndMJDVal = fh.observationEndMJD().value
	if observationEndMJDVal is None:
		observationEndMJDVal = '-'
	print fh.observationEndMJD().name(), "\t\t=%(mjd)19.12f" %{'mjd':observationEndMJDVal}

	print fh.observationNofStations().name(), "\t=", fh.observationNofStations().value
	print fh.observationStationsList().name(), "\t=", fh.observationStationsList().value
	print fh.observationFrequencyMin().name(), "\t=", fh.observationFrequencyMin().value, fh.observationFrequencyUnit().value
	print fh.observationFrequencyCenter().name(), "\t=", fh.observationFrequencyCenter().value, fh.observationFrequencyUnit().value
	print fh.observationFrequencyMax().name(), "\t=", fh.observationFrequencyMax().value, fh.observationFrequencyUnit().value
	print fh.observationNofBitsPerSample().name(), "=", fh.observationNofBitsPerSample().value
	print fh.clockFrequency().name(), "\t\t=", fh.clockFrequency().value, fh.clockFrequencyUnit().value
	print fh.antennaSet().name(), "\t\t\t=", fh.antennaSet().value
	print fh.filterSelection().name(), "\t\t=", fh.filterSelection().value
	print fh.targets().name(), "\t\t\t=", fh.targets().value
	print fh.systemVersion().name(), "\t\t\t=", fh.systemVersion().value

	pipelineNameVal = fh.pipelineName().value
	if pipelineNameVal is None:
		pipelineNameVal = '-'
	print fh.pipelineName().name(), "\t\t\t=", pipelineNameVal

	pipelineVersionVal = fh.pipelineVersion().value
	if pipelineVersionVal is None:
		pipelineVersionVal = '-'
	print fh.pipelineVersion().name(), "\t\t=", pipelineVersionVal

	print fh.docName().name(), "\t\t\t=", fh.docName().value
	print fh.docVersion().name(), "\t\t\t=", fh.docVersion().value

def print_tbb_root(fh):
	print fh.operatingMode().name(), '\t\t\t=', fh.operatingMode().value
	print fh.nofStations().name(), '\t\t\t=', fh.nofStations().value

def print_trigger_info(trgp):
	print trgp.groupType().name(), '\t\t\t=', trgp.groupType().value
	print trgp.triggerType().name(), '\t\t\t=', trgp.triggerType().value
	print trgp.triggerVersion().name(), '\t\t=', trgp.triggerVersion().value
	print trgp.paramCoincidenceChannels().name(), '\t=', trgp.paramCoincidenceChannels().value
	print trgp.paramCoincidenceTime().name(), '\t\t=', trgp.paramCoincidenceTime().value
	print trgp.paramDirectionFit().name(), '\t\t=', trgp.paramDirectionFit().value
	print trgp.paramElevationMin().name(), '\t\t=', trgp.paramElevationMin().value
	print trgp.paramFitVarianceMax().name(), '\t\t=', trgp.paramFitVarianceMax().value

def print_basic_station_dipole_info(stationList):
	for st in stationList:
		print_basic_station_info(st)
	print

	# Print some dipole info once that is likely to be the same for all.
	if stationList:
		dp = stationList[0].dipoles()[0]
		print_basic_dipole_info(dp)

def print_basic_station_info(st):
	# Don't print everything. We may get this up to 48x and users already know.
	print st.groupType().name(), '\t\t\t=', st.groupType().value
	print st.stationName().name(), '\t\t\t=', st.stationName().value
	print st.nofDipoles().name(), '\t\t\t=', st.nofDipoles().value

def print_basic_dipole_info(dp):
	print 'Basic dipole info from the first dipole found:'
	print dp.groupType().name(), '\t\t\t=', dp.groupType().value

	# try dal.stationIDToName() translation (we already have the station name, but ok)
	stID = dp.stationID().value
	if stID is not None:
		stName = dal.stationIDToName(stID)
	else:
		stName = '-'
	print 'Station name,', dp.rspID().name() + ',', dp.rcuID().name(), '\t=', stName + ',', str(dp.rspID().value) + ',', dp.rcuID().value

	print dp.sampleFrequency().name(), '\t\t=', dp.sampleFrequency().value, dp.sampleFrequencyUnit().value
	datalen = dp.dataLength().value
	print dp.dataLength().name(), '\t\t\t=', datalen

	nflaggedSamp = 0 # i.e. for this dipole
	for flrange in dp.flagOffsets().value:
		nflaggedSamp += flrange.end - flrange.begin
	print dp.flagOffsets().name(), 'summary\t\t=', nflaggedSamp, '(' + str(100.0 * nflaggedSamp // datalen) + '%)' # don't bother with proper rounding

	print dp.nyquistZone().name(), '\t\t\t=', dp.nyquistZone().value
	print dp.dispersionMeasure().name(), '\t\t=', dp.dispersionMeasure().value, dp.dispersionMeasureUnit().value

def print_tbb_header(filename):
	fh = dal.TBB_File(filename)
	print_cla(fh)
	print_tbb_root(fh)
	print
	trgp = fh.trigger()
	print_trigger_info(trgp)
	print
	stationList = fh.stations();
	print_basic_station_dipole_info(stationList)

def print_usage():
	print 'Print basic info about a LOFAR TBB HDF5 file.'
	print 'Usage:', sys.argv[0], 'L12345_xxx_tbb.h5 ...'

def main():
	if len(sys.argv) == 1:
		print_usage()
		return 2

	filenames = sys.argv[1 : ]
	try:
		for filename in filenames:
			print_tbb_header(filename)
			print '--------------------------------------------------------'
	except KeyboardInterrupt as exc:
		return 1
	except Exception as exc:
		sys.stderr.write('Error: ' + str(exc) + '\n')
		return 1

	return 0

if __name__ == '__main__':
	sys.exit(main())

