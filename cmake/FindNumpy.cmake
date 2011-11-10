# - Try to find Numpy.
# Variables defined by this module:
#  NUMPY_FOUND        - system has Numpy
#  NUMPY_INCLUDE_DIR  - the Numpy include directory

# Copyright (C) 2011
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
# $Id: FindNumpy.cmake 15228 2010-03-16 09:27:26Z loose $

# Search for the Python interpreter.
find_package(PythonInterp)

if(NOT NUMPY_FOUND)
  if(PYTHON_EXECUTABLE)
    execute_process(
      COMMAND "${PYTHON_EXECUTABLE}" "${PROJECT_SOURCE_DIR}/cmake/FindNumpy.py"
      OUTPUT_VARIABLE _numpydir
      ERROR_VARIABLE _pyerr
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(_pyerr)
      message(FATAL_ERROR "Numpy: Python command failed:\n${_pyerr}")
    endif(_pyerr)
    set(NUMPY_INCLUDE_DIR "${_numpydir}")
    set(NUMPY_FOUND TRUE)
  endif(PYTHON_EXECUTABLE)

  set(NUMPY_INCLUDE_DIRS ${NUMPY_INCLUDE_DIR})
endif(NOT NUMPY_FOUND)

