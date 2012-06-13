/* example-tbb-read.cc
 * Author: Alexander S. van Amesfoort, ASTRON, amesfoort_at_astron.nl
 * Date: June 12th, 2012
 * Description: Example program showing how to read LOFAR TBB data
 *              from a HDF5 file using the DAL library.
 * Build command: c++ -o example-tbb-read example-tbb-read.cc -ldal -lhdf5
 */
#include <iostream>

#include "dal/lofar/TBB_File.h"

#define MAX_PRINTED 64

using namespace std;

static void readTBBFile(const string& filename) {
	DAL::TBB_File tf(filename);

	const vector<size_t> pos(1, 0); // = {0}: always read starting at idx 0
	int16_t* data = NULL;
	size_t dataLen = 0;

	vector<DAL::TBB_Station> stations = tf.stations();
	for (size_t i = 0; i < stations.size(); i++) {
		cout << "Station " << stations[i].stationName().get() << ":" << endl;

		vector<DAL::TBB_DipoleDataset> dipoles = stations[i].dipoles();
		for (size_t j = 0; j < dipoles.size(); j++) {
			cout << "\tDipole " << dipoles[j].rspID().get() << " " << dipoles[j].rcuID().get() << ":" << endl;

			size_t dpDataLen = dipoles[j].dims()[0];
			if (dataLen < dpDataLen) {
				delete[] data;
				dataLen = dpDataLen;
				data = new int16_t[dataLen];
			}

			dipoles[j].get1D(pos, dataLen, data);

			size_t printedLen = dataLen < MAX_PRINTED ? dataLen : MAX_PRINTED;
			for (size_t k = 0; k < printedLen; k++) {
				cout << data[k] << " ";
			}
			cout << endl;
		}

	}

	delete[] data; // not reached if exc thrown
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
