// c++ -Wall print-bf-sap-attr.cc -llofardal -lhdf5
#include <iostream>

#include "dal/lofar/BF_File.h"

using namespace std;

int main() {
	dal::BF_File bfFile("data/L63876_SAP000_B000_S0_P000_bf.h5");
	dal::BF_SubArrayPointing sap(bfFile.subArrayPointing(0)); // assume it exists

	cout << "EXPTIME_START_UTC = " << sap.expTimeStartUTC().get() << endl;

	return 0;
}

