// constructors.cc
// Build: c++ -Wall -o constructors constructors.cc -llofardal -lhdf5

#include <dal/lofar/BF_File.h>
#include <dal/lofar/TBB_File.h>

struct Files {
	dal::BF_File bfFile;
	dal::TBB_File tbbFile;
};


static void bf(dal::BF_File& file) {
	file.open("test-instantiate-only_bf.h5", dal::File::CREATE);
	file.close(); // to reopen with different mode, use close(), or drop obj and create a new one.
	file.open("test-instantiate-only_bf.h5");
}

static void tbb(dal::TBB_File& file) {
	file.open("test-instantiate-only_tbb.h5", dal::File::CREATE);
	file.close();
	file.open("test-instantiate-only_tbb.h5");
	file.close(); // see if this also properly destructs
}

int main() {
	Files files;

	bf(files.bfFile);
	tbb(files.tbbFile);

	return 0;
}

