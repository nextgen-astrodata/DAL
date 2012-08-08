/* Copyright 2011-2012  ASTRON, Netherlands Institute for Radio Astronomy
 * This file is part of the Data Access Library (DAL).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
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

