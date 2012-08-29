// instantiate-only.cc
// Build: c++ -Wall -o instantiate-only instantiate-only.cc -llofardal -lhdf5

#include <dal/lofar/BF_File.h>
#include <dal/lofar/TBB_File.h>

int main() {
	DAL::BF_File  bfFile ("test-instantiate-only_bf.h5",  DAL::File::CREATE);
	DAL::TBB_File tbbFile("test-instantiate-only_tbb.h5", DAL::File::CREATE);

	return 0;
}

