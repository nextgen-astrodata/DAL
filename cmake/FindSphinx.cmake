# - Try to find Sphinx.
# Variables defined by this module:
#  SPHINX_FOUND        - system has Sphinx

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
# $Id: FindSphinx.cmake 15228 2010-03-16 09:27:26Z loose $

if(NOT SPHINX_FOUND)
  find_program(SPHINX_EXECUTABLE NAMES sphinx-build
    HINTS
    $ENV{SPHINX_DIR}
    PATH_SUFFIXES bin
    DOC "Sphinx documentation generator"
  )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(SPHINX DEFAULT_MSG SPHINX_EXECUTABLE)
endif(NOT SPHINX_FOUND)

