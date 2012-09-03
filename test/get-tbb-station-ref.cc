// c++ -Wall get-tbb-station-ref.cc -llofardal -lhdf5
#include <iostream>
#include <dal/lofar/TBB_File.h>

using namespace std;

int main() {
	dal::TBB_File f("test-get-tbb-station-ref-cc.h5", dal::TBB_File::CREATE);

	dal::TBB_Station st(f.station("CSxxx"));

	return 0;
}

