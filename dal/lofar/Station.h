#ifndef DAL_STATION_H
#define DAL_STATION_H

#include <string>
#include "dal/hdf5/exceptions/exceptions.h"

namespace DAL {

/*!
 * Returns the LOFAR station name (e.g. "CS011") corresponding to stationID.
 * Returns "ST<stationID>" (always 5 characters) if stationID is unknown.
 */
std::string stationIDToName(unsigned stationID);

/*!
 * Returns LOFAR station ID corresponding to stationName (e.g. "CS011" or "CS011HBA0", same result).
 * Throws DAL::DALValueError if stationName contains an invalid number.
 */
unsigned stationNameToID(const std::string& stationName);

}

#endif

