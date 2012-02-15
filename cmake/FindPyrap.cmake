# - Try to find Pyrap.
# Variables used by this module:
#  PYRAP_ROOT_DIR     - Pyrap root directory
# Variables defined by this module:
#  PYRAP_FOUND        - system has Pyrap
#  PYRAP_INCLUDE_DIR  - the Pyrap include directory (cached)
#  PYRAP_INCLUDE_DIRS - the Pyrap include directories
#                       (identical to PYRAP_INCLUDE_DIR)
#  PYRAP_LIBRARY      - the Pyrap library (cached)
#  PYRAP_LIBRARIES    - the Pyrap libraries
#                       (identical to PYRAP_LIBRARY)

# Copyright (C) 2009
# ASTRON (Netherlands Institute for Radio Astronomy)
# P.O.Box 2, 7990 AA Dwingeloo, The Netherlands
#
# This file is part of the LOFAR software suite.
# The LOFAR software suite is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The LOFAR software suite is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with the LOFAR software suite. If not, see <http://www.gnu.org/licenses/>.
#
# $Id: FindPyrap.cmake 15228 2010-03-16 09:27:26Z loose $

if(NOT PYRAP_FOUND)

  find_path(PYRAP_INCLUDE_DIR pyrap/Converters.h
    HINTS ${PYRAP_ROOT_DIR} PATH_SUFFIXES include)
  find_library(PYRAP_LIBRARY pyrap
    HINTS ${PYRAP_ROOT_DIR} PATH_SUFFIXES lib)
  mark_as_advanced(PYRAP_INCLUDE_DIR PYRAP_LIBRARY)

  # Pyrap also depends on Casacore
  include(LofarFindPackage)
  lofar_find_package(Casacore REQUIRED COMPONENTS casa)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Pyrap DEFAULT_MSG 
    PYRAP_LIBRARY PYRAP_INCLUDE_DIR)

  set(PYRAP_INCLUDE_DIRS ${PYRAP_INCLUDE_DIR} ${CASACORE_INCLUDE_DIRS})
  set(PYRAP_LIBRARIES ${PYRAP_LIBRARY} ${CASACORE_LIBRARIES})

endif(NOT PYRAP_FOUND)

