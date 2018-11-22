/* example-tbb-read.cc
 * Author: Alexander S. van Amesfoort, ASTRON, amesfoort_at_astron.nl
 * Date: June 12th, 2012
 * Description: Example program showing how to read LOFAR TBB data
 *              from a HDF5 file using the DAL library.
 * Build command: c++ -o example-tbb-read example-tbb-read.cc -llofardal -lhdf5
 */
#include <cstddef>	// NULL
#include <iostream>

#include "dal/lofar/TBB_File.h"

#define MAX_PRINTED 64

using namespace std;

// Minimal data pointer wrapping to guarantee delete[].
template <typename T>
struct Data {
	T* data;
	size_t len;

	Data() : data(NULL), len(0) { }
	~Data() {
		delete[] data;
	}
};

static void readTBB_File(const string& filename) {
	dal::TBB_File tf(filename);

	Data<int16_t> d;
	vector<dal::TBB_Station> stations = tf.stations();
	for (size_t i = 0; i < stations.size(); i++) {
		cout << "Station " << stations[i].stationName().get() << ":" << endl;

		vector<dal::TBB_DipoleDataset> dipoleDatasets(stations[i].dipoleDataSets());
		for (size_t j = 0; j < dipoleDatasets.size(); j++) {
			cout << "\tDipole dataset " << dipoleDatasets[j].rspID().get() << " " << dipoleDatasets[j].rcuID().get() << ":" << endl;

			size_t dpDataLen = dipoleDatasets[j].dims1D();
			if (d.len < dpDataLen) {
				delete[] d.data;
				d.data = NULL; // safe delete[] in ~Data() in case new[] fails
				d.len = dpDataLen;
				d.data = new int16_t[d.len];
			}

			size_t pos = 0;
			dipoleDatasets[j].get1D(pos, d.data, d.len);

			size_t printedLen = d.len < MAX_PRINTED ? d.len : MAX_PRINTED;
			for (size_t k = 0; k < printedLen; k++) {
				cout << d.data[k] << " ";
			}
			cout << endl;
		}


		vector<dal::TBB_DipoleGroup> dipoleGroups(stations[i].dipoleGroups());
		for (size_t j = 0; j < dipoleGroups.size(); j++) {
			cout << "\tDipole group " << dipoleGroups[j].rspID().get() << " " << dipoleGroups[j].rcuID().get() << ":" << endl;

      vector<dal::TBB_SubbandDataset> subbandDatasets(dipoleGroups[j].subbandDatasets());
      for (size_t k = 0; k < subbandDatasets.size(); k++) {
        cout << "\tSubband dataset " << subbandDatasets[k].bandNumber().get() << " " << subbandDatasets[k].centralFrequency().get() << ":" << endl;
      }
		}
	}
}

static void printUsage(const char* progname) {
	cerr << "Usage: " << progname << " L12345_xxx_tbb.h5" << endl;
}

int main(int argc, char* argv[]) {
	string filepath;
	string filename1;
	string filename2;

	if (argc != 2) {
		printUsage(argv[0]);

		// Give default filenames and run anyway.
		// Normally a bad idea, but this is for regression testing: we don't have test program args atm.
		filepath = "data/";
		filename1 = "L59640_CS011_D20110719T110541.036Z_tbb.h5";
		filename2 = "L59640_RS106_D20111121T130145.049Z_tbb.h5";
	} else {
		filename1 = argv[1];
	}

	int exit_status = 1;
	try {
		readTBB_File(filepath + filename1);

		if (!filename2.empty()) {
			readTBB_File(filepath + filename2);
		}

		exit_status = 0;
	} catch (dal::HDF5Exception& exc) {
		cerr << "Error: DAL HDF5 exception: " << exc.what() << endl;
		cerr << exc.stackSummary() << endl;
	} catch (dal::DALException& exc) {
		cerr << "Error: DAL exception: " << exc.what() << endl;
	} catch (exception& exc) {
		cerr << "Error: exception: " << exc.what() << endl;
	} catch (...) {
		cerr << "Error: unknown exception" << endl;
	}

	return exit_status;
}
