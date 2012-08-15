// c++ -Wall -o reopen-rw reopen-rw.cpp -ldal -lhdf5
#include <dal/lofar/CLA_File.h>
#include <iostream>

using namespace std;

static void createTest() {
	DAL::CLA_File f("test-reopen-rw-cla-cpp.h5", DAL::CLA_File::CREATE);

	f.clockFrequency().value = 160.0;
}

static void reopenrwTest() {
	DAL::CLA_File f("test-reopen-rw-cla-cpp.h5", DAL::CLA_File::READWRITE);

	f.clockFrequencyUnit().value = "MHz";
}

static int checkTest() {
	int err = 0;

	DAL::CLA_File f("test-reopen-rw-cla-cpp.h5");

	if (f.clockFrequency().get() != 160.0) {
		err = 1;
		cout << "Written clock freq val could not be read back" << endl;
	}
	if (f.clockFrequencyUnit().get() != "MHz") {
		err = 1;
		cout << "Written clock freq unit val could not be read back" << endl;
	}

	//DAL::CLA_File f2("test-reopen-rw-cla-cpp.h5", DAL::CLA_File::READWRITE); // throws: HDF5 cannot reopen while already open

	return err;
}

int main() {
	createTest();
	reopenrwTest();

	return checkTest();
}

