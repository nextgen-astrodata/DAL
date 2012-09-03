// c++ -Wall version-check.cc -llofardal -lhdf5
#include <iostream>
#include <dal/dal_config.h>
#include <dal/dal_version.h>

using namespace std;
using namespace dal;

int main() {
	int err = 0;

	// Test if dal_config version defines are correctly propagated by cmake.
	// This is needed to work around version-specific bugs or API changes (hope we don't).
#if DAL_VERSION_MAJOR == 2
#endif

#if DAL_VERSION_MINOR == 5
#endif

#if DAL_VERSION_RELEASE == 0
#endif

// This doesn't work; use the numerical symbols above for pre-processor comparisons.
//#if DAL_VERSION_STRING == "2.5.0"
//#endif
	// DAL_VERSION_STRING is for runtime use.
	string dalVersionString(DAL_VERSION_STRING);

	// Test if dal_version functions exist and do anything remotely reasonable.
	VersionType libVersion(version());
	if (libVersion.major != 2) { // really basic check
		cerr << "lib version should start with 2" << endl;
		err = 1;
	}

	VersionType firstVersion(version_first_release());
	if (firstVersion != VersionType(2, 5, 0)) {
		cerr << "first lib version should be 2.5.0" << endl;
		err = 1;
	}

	VersionType hdf5IncVersion1(version_hdf5_headers_dal());
	if (hdf5IncVersion1 == VersionType(0, 0, 0)) {
		cerr << "version_hdf5_headers_dal should be set" << endl;
		err = 1;
	}

	VersionType hdf5IncVersion2(version_hdf5_headers_current());
	if (hdf5IncVersion2 == VersionType(0, 0, 0)) {
		cerr << "version_hdf5_headers_current should be set" << endl;
		err = 1;
	}

	bool same = check_hdf5_versions();
	if (!same) {
		cerr << "DAL version built and test case version built should be the same" << endl;
		cerr << "DAL version:                   " << version() << endl;
		cerr << "HDF5 lib version:              " << version_hdf5() << endl;
		cerr << "HDF5 header version (DAL):     " << version_hdf5_headers_dal() << endl;
		cerr << "HDF5 header version (current): " << version_hdf5_headers_current() << endl;
		err = 1;
	}

	return err;
}

