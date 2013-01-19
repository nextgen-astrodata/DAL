// c++ -Wall -o version-check2 version-check2.cc -llofardal -lhdf5
#include <string>
#include <iostream>

#include <dal/lofar/BF_File.h>

using namespace std;

int main() {
	const string filename("test-version-check2.h5");
	dal::BF_File newfile(filename, dal::File::CREATE);

	// Check reading (in-memory) version from existing file with non-default initialized (0.0.0) version attribute.
	dal::CLA_File f(filename);
	dal::VersionType docVersion(f.docVersion().get()); // CLA_File
	cout << "DOC_VERSION (docVersion()) = " << docVersion << endl;
	dal::VersionType fversion(f.version().get()); // File
	cout << "DOC_VERSION (version()) = " << fversion << endl;
	const dal::VersionType firstRelease(2, 5, 0);
	bool looksFine = docVersion >= firstRelease && fversion >= firstRelease;

	// Same but indicated version attribute does not exist: must throw.
	bool thrown = false;
	try {
		dal::File f2(filename, dal::File::READ, "DOC_VERSION_NONEXISTANT");
		cout << "Incorrectly opened file for READ specifying non-existing attribute: should have thrown" << endl;
	} catch (dal::HDF5Exception& ) {
		thrown = true;
	}

	return looksFine && thrown ? 0 : 1;
}

