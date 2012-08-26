// c++ -Wall version-check.cc -ldal -lhdf5
#include <iostream>
#include <dal/dal_config.h>
#include <dal/dal_version.h>

using namespace std;

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
	string libVersion(DAL::get_lib_version());
	if (libVersion[0] != '2') { // really basic check
		cerr << "lib version should start with 2" << endl;
		err = 1;
	}

	string firstVersion(DAL::get_first_release_lib_version());
	if (firstVersion != "2.5.0") {
		cerr << "first lib version should be 2.5.0" << endl;
		err = 1;
	}

	string hdf5IncVersion(DAL::get_dal_hdf5_version());
	if (hdf5IncVersion == "") {
		cerr << "hdf5 inc version should not be an empty string" << endl;
		err = 1;
	}

	bool same = DAL::check_hdf5_versions();
	if (!same) {
		cerr << "DAL version built and test case version built should be the same" << endl;
		err = 1;
	}

	return err;
}

