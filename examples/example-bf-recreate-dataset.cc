/*
 * example-bf-recreate-dataset.cc
 * Build: c++ -Wall example-bf-recreate-dataset.cc -ldal -lhdf5
 */
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <dal/lofar/BF_File.h>

using namespace std;

static void printData2D(const float* data, size_t dim1, size_t dim2) {
	for (size_t i = 0; i < dim1; i++) {
		for (size_t j = 0; j < dim2; j++) {
			cout << data[i * dim2 + j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[]) {
	bool doprint = false;
	if (argc >= 2 && string(argv[1]) == "--print") {
		doprint = true;
	}

	string filedir("data/");
	string filename("L63876_SAP000_B000_S0_P000_bf.h5");
	string filenameRaw(filename.substr(0, filename.size()-3).append(".raw")); // assumes filename.size() > 3

	DAL::BF_File f(filedir + filename);
	vector<size_t> pos0(2, 0); // start at (0, 0)
	size_t sliceLen;

	// Vars that make up (part of) the stokes dataset
	float* data0;
	vector<ssize_t> dims;
	vector<ssize_t> maxdims;

	string groupType;
	string dataType;
	string stokesComponent;
	vector<unsigned> nofChannels;
	unsigned nofSubbands;
	unsigned nofSamples;


{ // new scope, so we can close all attributes at scope exit (better do this in a function)
	DAL::BF_SubArrayPointing sap(f.subArrayPointing(0));
	DAL::BF_BeamGroup beam(sap.beam(0));
	DAL::BF_StokesDataset stokes(beam.stokes(0));

	if (stokes.ndims() != 2) {
		cerr << "stokes ndims must be 2" << endl;
		return 1;
	}
	dims = stokes.dims();
	maxdims = stokes.maxdims();

	// take a slice of (at most) 8 x 3904 at the beginning
	sliceLen = dims[0] < 8 ? dims[0] : 8;
	data0 = new float[sliceLen * dims[1]];

	stokes.get2D(pos0, data0, sliceLen, dims[1]);
	if (doprint) {
		cout << "stokes data dims=" << dims[0] << " x " << dims[1] << endl; // for the opened file, 3576 x 3904(=244*16, stride-1 dim)
		printData2D(data0, sliceLen, (size_t)dims[1]);
	}

	// grab all attributes in the stokes dataset
	groupType = stokes.groupType().get();
	dataType = stokes.dataType().get();
	stokesComponent = stokes.stokesComponent().get();
	nofChannels = stokes.nofChannels().get();
	nofSubbands = stokes.nofSubbands().get();
	nofSamples = 8; //stokes.nofSamples().get();

	if (doprint) {
		cout << "stokes attribs: groupType=" << groupType << " dataType=" << dataType << " stokesComponent=" << stokesComponent << endl;
		for (size_t i = 0; i < nofChannels.size(); i++) {
			cout << nofChannels[i] << " ";
		}
		cout << endl;
		cout << "nofSubbands=" << nofSubbands << " nofSamples=" << nofSamples << endl;
	}

// close all attribute refs at scope exit and then the file
}
	f.close();


	// Create another file to copy the stokes dataset into.
	filename = "example-bf-recreate-dataset.h5";
	filenameRaw = "example-bf-recreate-dataset.raw";
	f.open(filedir + filename, DAL::File::CREATE);
	DAL::BF_SubArrayPointing sap(f.subArrayPointing(0));
	sap.create();
	DAL::BF_BeamGroup beam(sap.beam(0));
	beam.create();
	DAL::BF_StokesDataset stokes(beam.stokes(0));

	stokes.create(dims, maxdims, filenameRaw, DAL::BF_StokesDataset::BIG);
	stokes.groupType().create().set(groupType);
	stokes.dataType().create().set(dataType);
	stokes.stokesComponent().create().set(stokesComponent);
	stokes.nofChannels().create(nofChannels.size()).set(nofChannels); // size() trick is optional, but show/test that too
	stokes.nofSubbands().create().set(nofSubbands);
	stokes.nofSamples().create().set(nofSamples);

	stokes.set2D(pos0, data0, sliceLen, dims[1]);


	// Try to remove the stokes dataset again (both files stay)
	stokes.remove();


	delete[] data0;
	return 0;
}

