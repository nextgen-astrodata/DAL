// remove-root-exc.cc
// See that we properly throw on removing the file as a group
// that we don't crash on a thrown HDF5Exception.
// Build: c++ -Wall remove-root-exc.cc -llofardal -lhdf5
#include <iostream>

#include <dal/lofar/CLA_File.h>

using namespace std;

int main() {
	int exit_status;

	dal::CLA_File file("test-remove_root_exc.h5", dal::CLA_File::CREATE);
	try {
		// In DAL, a file is a group, but this must throw.
		file.remove();

		exit_status = 1;
		cerr << "remove() on the HDF5 root group incorrectly returned" << endl;
	} catch (dal::HDF5Exception& ) {
		exit_status = 0;
	}

	return exit_status;
}

