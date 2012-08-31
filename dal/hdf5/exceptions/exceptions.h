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
#ifndef DAL_EXCEPTIONS_H
#define DAL_EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include "errorstack.h"

namespace DAL {

class DALException: public std::runtime_error
{
public:
  DALException(const std::string &msg): std::runtime_error(msg) {}
};

class DALValueError: public DALException
{
public:
  DALValueError(const std::string &msg): DALException(msg) {}
};

class DALIndexError: public DALValueError
{
public:
  DALIndexError(const std::string &msg): DALValueError(msg) {}
};

class HDF5Exception: public DALException
{
public:
  HDF5Exception(const std::string &msg, const HDF5ErrorStack &stack = HDF5ErrorStack());
  virtual ~HDF5Exception() throw();

  HDF5ErrorStack stack;

  std::string stackSummary() const;
};

}

#endif

