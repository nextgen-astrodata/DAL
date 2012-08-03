#include "Station.h"
#include <cstdlib>
#include <cstdio>

using namespace std;

namespace DAL {

// from the LOFAR repos in MAC/Deployment/data/StaticMetaData/StationInfo.dat
const char stationNames[][6] = {
"CS001", "CS002", "CS003", "CS004", "CS005", "CS006", "CS007", "CS008",
"CS009", "CS010", "CS011", "CS012", "CS013", "CS014", "CS015", "CS016",
"CS017", "CS018", "CS019", "CS020", "CS021", "CS022", "CS023", "CS024",
"CS025", "CS026", "CS027", "CS028", "CS029", "CS030", "CS031", "CS032",

"CS101", "CS102", "CS103", "RS104", "RS105", "RS106", "RS107", "RS108",
"RS109", "CS201", "RS202", "RS203", "RS204", "RS205", "RS206", "RS207",
"RS208", "RS209", "RS210", "CS301", "CS302", "RS303", "RS304", "RS305",
"RS306", "RS307", "RS308", "RS309", "RS310", "CS401", "RS402", "RS403",
"RS404", "RS405", "RS406", "RS407", "RS408", "RS409", "RS410", "RS411",
"RS412", "RS413", "CS501", "RS502", "RS503", "RS504", "RS505", "RS506",
"RS507", "RS508", "RS509",

"DE601", "DE602", "DE603", "DE604", "DE605", "FR606", "SE607", "UK608",
"FI609"
};

string stationIDToName(unsigned stationID) {
	string name;

	switch (stationID) {
		case   1: name = "CS001"; break;
		case   2: name = "CS002"; break;
		case   3: name = "CS003"; break;
		case   4: name = "CS004"; break;
		case   5: name = "CS005"; break;
		case   6: name = "CS006"; break;
		case   7: name = "CS007"; break;
		case   8: name = "CS008"; break;
		case   9: name = "CS009"; break;
		case  10: name = "CS010"; break;
		case  11: name = "CS011"; break;
		case  12: name = "CS012"; break;
		case  13: name = "CS013"; break;
		case  14: name = "CS014"; break;
		case  15: name = "CS015"; break;
		case  16: name = "CS016"; break;
		case  17: name = "CS017"; break;
		case  18: name = "CS018"; break;
		case  19: name = "CS019"; break;
		case  20: name = "CS020"; break;
		case  21: name = "CS021"; break;
		case  22: name = "CS022"; break;
		case  23: name = "CS023"; break;
		case  24: name = "CS024"; break;
		case  25: name = "CS025"; break;
		case  26: name = "CS026"; break;
		case  27: name = "CS027"; break;
		case  28: name = "CS028"; break;
		case  29: name = "CS029"; break;
		case  30: name = "CS030"; break;
		case  31: name = "CS031"; break;
		case  32: name = "CS032"; break;

		case 101: name = "CS101"; break;
		case 102: name = "CS102"; break;
		case 103: name = "CS103"; break;

		case 104: name = "RS104"; break;
		case 105: name = "RS105"; break;
		case 106: name = "RS106"; break;
		case 107: name = "RS107"; break;
		case 108: name = "RS108"; break;
		case 109: name = "RS109"; break;

		case 121: name = "CS201"; break;

		case 122: name = "RS202"; break;
		case 123: name = "RS203"; break;
		case 124: name = "RS204"; break;
		case 125: name = "RS205"; break;
		case 126: name = "RS206"; break;
		case 127: name = "RS207"; break;
		case 128: name = "RS208"; break;
		case 129: name = "RS209"; break;
		case 130: name = "RS210"; break;

		case 141: name = "CS301"; break;
		case 142: name = "CS302"; break;

		case 143: name = "RS303"; break;
		case 144: name = "RS304"; break;
		case 145: name = "RS305"; break;
		case 146: name = "RS306"; break;
		case 147: name = "RS307"; break;
		case 148: name = "RS308"; break;
		case 149: name = "RS309"; break;
		case 150: name = "RS310"; break;

		case 161: name = "CS401"; break;

		case 162: name = "RS402"; break;
		case 163: name = "RS403"; break;
		case 164: name = "RS404"; break;
		case 165: name = "RS405"; break;
		case 166: name = "RS406"; break;
		case 167: name = "RS407"; break;
		case 168: name = "RS408"; break;
		case 169: name = "RS409"; break;
		case 170: name = "RS410"; break;
		case 171: name = "RS411"; break;
		case 172: name = "RS412"; break;
		case 173: name = "RS413"; break;

		case 181: name = "CS501"; break;

		case 182: name = "RS502"; break;
		case 183: name = "RS503"; break;
		case 184: name = "RS504"; break;
		case 185: name = "RS505"; break;
		case 186: name = "RS506"; break;
		case 187: name = "RS507"; break;
		case 188: name = "RS508"; break;
		case 189: name = "RS509"; break;

		case 201: name = "DE601"; break;
		case 202: name = "DE602"; break;
		case 203: name = "DE603"; break;
		case 204: name = "DE604"; break;
		case 205: name = "DE605"; break;
		case 206: name = "FR606"; break;
		case 207: name = "SE607"; break;
		case 208: name = "UK608"; break;
		case 209: name = "FI609"; break;

		// Unknown station number. Return "ST<stationID>".
		default:
		{
			char stName[6]; // 2 letters, 3 digits and the '\0'
			snprintf(stName, sizeof stName, "ST%03u", stationID);
			name = stName;
		}
	}

	return name;
}

unsigned stationNameToID(const string& stationName) {
	if (stationName.size() < 5) {
		throw DALValueError("stationNameToID(): station name must be at least 5 characters (e.g. \"CS031\")");
	}

	unsigned id = (unsigned)atoi(&stationName.c_str()[2]);
	if (id > 999) { // Don't bother checking the first 2 chars and don't error on unknown 3 digit IDs incl from conv err.
		throw DALValueError("stationNameToID(): number in station name must have 3 digits");
	}

	if (id > 200) {
		unsigned sub = (id - 101) / 100;
		id = id - sub * 80;
	}
	return id;
}

}

