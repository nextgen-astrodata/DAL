#ifndef DAL_STATION_H
#define DAL_STATION_H

#include <string>
#include "dal/hdf5/exceptions/exceptions.h"

namespace DAL {

/*!
 * Array of C strings with all LOFAR station names.
 *
 * The number of station names is:
 *   ( sizeof(DAL::stationNames) / sizeof(DAL::stationNames[0]) )
 */
extern const char stationNames[][6];

/*!
 * Returns the LOFAR station name (e.g. "CS011") corresponding to stationID.
 * Returns "ST<stationID>" (always 5 characters) if stationID is unknown.
 */
std::string stationIDToName(unsigned stationID);

/*!
 * Returns LOFAR station ID corresponding to stationName (e.g. "CS011").
 * May throw DAL::DALValueError if stationName is not in the stationNames array above.
 * Does not throw on a valid stationName with a suffix (e.g. a field name like "CS011HBA0").
 */
unsigned stationNameToID(const std::string& stationName);

}

#endif

