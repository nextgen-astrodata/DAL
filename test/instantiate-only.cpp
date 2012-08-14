// instantiate-only.cpp
// Build: c++ -Wall -o instantiate-only instantiate-only.cpp -ldal -lhdf5

#include <dal/lofar/BF_File.h>
#include <dal/lofar/TBB_File.h>

int main() {
	DAL::BF_File  bfFile ("h5tmp/bf.h5",  DAL::File::CREATE);
	DAL::TBB_File tbbFile("h5tmp/tbb.h5", DAL::File::CREATE);

	return 0;
}

