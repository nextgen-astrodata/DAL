// h5-test-create.cc
// Build: cc -Wall -o h5-test-create h5-test-create.cc -lhdf5

#include <stdio.h>
#include <hdf5.h>

int main() {
	char filename[] = "test-h5-test-create.h5";

	hid_t prop_hid = H5Pcreate(H5P_FILE_ACCESS);
	if (prop_hid < 0) {
		fprintf(stderr, "H5Pcreate() failed\n");
		return 1;
	}

	hid_t file_hid = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, prop_hid);
	if (file_hid < 0) {
		fprintf(stderr, "H5Fcreate() failed\n");
		return 1;
	}

	printf("file %s was created\n", filename);
	return 0;
}

