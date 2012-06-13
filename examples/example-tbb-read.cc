/* example-tbb-read.cc
 * Author: Alexander S. van Amesfoort, ASTRON, amesfoort_at_astron.nl
 * Date: June 12th, 2012
 * Description: Example program showing how to read LOFAR TBB data
 *              from a HDF5 file using the DAL library.
 * Build command: c++ -o example-tbb-read example-tbb-read.cc -ldal -lhdf5
 */
#include <iostream>

#include "dal/lofar/TBB_File.h"

using namespace std;

static void readTBBFile(const string& filename) {
	DAL::TBB_File tf(filename);

	vector<DAL::TBB_Station> stations = tf.stations();

	for (size_t i = 0; i < stations.size(); i++) {
		cout << "Station: " << stations[i].stationName().get() << endl;
	}
}

static void printUsage(const char* progname) {
	cerr << "Usage: " << progname << " L12345_xxx_tbb.h5" << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printUsage(argv[0]);
		return 2;
	}

	int exit_status = 1;
	try {
		const string filename = argv[1];
		readTBBFile(filename);
		exit_status = 0;
	} catch (DAL::HDF5Exception& exc) {
		cerr << "Error: DAL HDF5 exception: " << exc.what() << endl;
		cerr << exc.stackSummary() << endl;
	} catch (DAL::DALException& exc) {
		cerr << "Error: DAL exception: " << exc.what() << endl;
	} catch (exception& exc) {
		cerr << "Error: exception: " << exc.what() << endl;
	} catch (...) {
		cerr << "Error: unknown exception" << endl;
	}

	return exit_status;
}
