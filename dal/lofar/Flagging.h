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
#ifndef DAL_FLAGGING_H
#define DAL_FLAGGING_H

#include <cstddef>
#include <string>
#include "dal/hdf5/types/h5tuple.h"

namespace DAL {

/*!
 * class Range is typically used in a vector for flagging data.
 * In a range, `begin` is inclusive and `end` is exclusive.
 *
 * Note: size() (inherited) always returns 2 (number of tuple elements)
 */
struct Range : public TupleBase<unsigned long long, 2> {
  unsigned long long begin; // inclusive
  unsigned long long end;   // exclusive

  Range();

  Range(unsigned long long begin, unsigned long long end);


  //! Returns a string representation of this Range, e.g. "[0,10)".
  std::string to_string();
};

}

#endif

