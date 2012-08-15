/*
 * Try attribute string/vector of size 0.
 * It should store/retrieve and indicate sizes are equal to 0.
 * Build: c++ -Wall attr-empty.cc -ldal -lhdf5
 */

#include <string>
#include <vector>
#include <iostream>

#include <dal/lofar/CLA_File.h>

using namespace std;

static int exit_status;

template <typename T>
static T test(DAL::CLA_File& file, const string& attrName, const T& t0 = T()) {
	DAL::Attribute<T> attr(file, attrName);
	attr.value = t0;

	T readback = attr.get();
	size_t sz = readback.size();
	if (sz != t0.size()) {
		cerr << "failed to create and read back attribute '" << attrName << "'; size = " << sz << endl;
		exit_status = 1;
	}

	return readback;
}

int main() {
	string filename("test-attr-empty.h5");

	DAL::CLA_File file(filename, DAL::CLA_File::CREATE);

	string         s  = test<string>         (file, "ATTR_STR_EMPTY");
	vector<int>    vi = test<vector<int> >   (file, "ATTR_VEC_EMPTY");
	vector<string> vs = test<vector<string> >(file, "ATTR_VEC_STR_EMPTY");

	// set up vector of empty strings and add element size checks afterwards
	vector<string> vtval;
	vtval.push_back("");
	vtval.push_back("");
	vector<string> vt = test(file, "ATTR_VEC_STR_EMPTY_STR", vtval);
	if (vt[0].size() != 0 || vt[1].size() != 0) {
		cerr << "failed to create and read back content of attribute 'ATTR_VEC_STR_EMPTY_STR'; vt[0].size() = " << vt[0].size() << "; vt[1].size() = " << vt[1].size() << endl;
		exit_status = 1;
	}

	return exit_status;
}

