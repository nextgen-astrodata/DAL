# - Generate script to configure and run the code documentation tool Doxygen.

# $Id: LofarDoxygen.cmake 17084 2011-01-14 12:55:56Z loose $
#
# Copyright (C) 2010
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

include(LofarMacros)

# Only process this file when we're ate the top-level source directory.
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")

  if(BUILD_DOCUMENTATION)
    # Locate the doxygen programs.
    find_package(Doxygen REQUIRED)

    # Document all source code, unless BUILD_PACKAGES is defined.
    if(NOT DEFINED BUILD_PACKAGES)
      set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
    else(NOT DEFINED BUILD_PACKAGES)
      # We need the list of package source directories.
      include(LofarPackageList)
      set(DOXYGEN_INPUT)
      foreach(_pkg ${BUILD_PACKAGES})
        list(APPEND DOXYGEN_INPUT ${${_pkg}_SOURCE_DIR})
      endforeach(_pkg ${BUILD_PACKAGES})
      lofar_join_arguments(DOXYGEN_INPUT)
    endif(NOT DEFINED BUILD_PACKAGES)

    # Set Doxygen HTML output directory, if not yet defined; and create it.
    if(NOT DOXYGEN_HTML_OUTPUT)
      set(DOXYGEN_HTML_OUTPUT "${CMAKE_BINARY_DIR}/doc/html" CACHE PATH
        "Directory where Doxygen will write the generated documentation")
    endif(NOT DOXYGEN_HTML_OUTPUT)
    file(MAKE_DIRECTORY "${DOXYGEN_HTML_OUTPUT}")

    # Set system- and build-dependent predefinitions for Doxygen, in order to
    # make sure that the generated documentation will match with the code.
    get_directory_property(_defs COMPILE_DEFINITIONS)
    set(DOXYGEN_PREDEFINED ${_defs})
    get_directory_property(_cache_vars CACHE_VARIABLES)
    foreach(_cv ${_cache_vars})
      if(_cv MATCHES "^HAVE_")
        list(APPEND DOXYGEN_PREDEFINED ${_cv})
      endif(_cv MATCHES "^HAVE_")
    endforeach(_cv ${_cache_vars})
    lofar_join_arguments(DOXYGEN_PREDEFINED)

    # Generate the Doxygen configuration file, used by Doxygen.
    configure_file(
      "${CMAKE_SOURCE_DIR}/CMake/docscripts/doxygen.cfg.in"
      "${CMAKE_BINARY_DIR}/doxygen.cfg" @ONLY)

    # Generate the CMake script that will be invoked by 'make doc'.
    configure_file(
      "${CMAKE_SOURCE_DIR}/CMake/docscripts/MakeDoxyDoc.cmake.in"
      "${CMAKE_BINARY_DIR}/MakeDoxyDoc.cmake" @ONLY)

    # Define custom target 'doc'. The reason for using an external script
    # MakeDoxyDoc.cmake, instead of defining the custom target directly, is
    # that we want to be able to redirect stdout and stderr, which can only be
    # done using execute_process().
    add_custom_target(doc
      COMMAND "${CMAKE_COMMAND}" 
      -D DOXYGEN_CONFIG_FILE="${CMAKE_BINARY_DIR}/doxygen.cfg"
      -D DOXYGEN_OUTPUT_LOG_FILE="${CMAKE_BINARY_DIR}/doxygen.log"
      -P "${CMAKE_BINARY_DIR}/MakeDoxyDoc.cmake"
      COMMENT "Generating code documentation. Please be patient ...")

    # Add the Doxygen Quick Guide, if present.
    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/doc/doxygen")
      add_subdirectory("${CMAKE_SOURCE_DIR}/doc/doxygen")
      add_dependencies(doc doxygen_quick_guide)
    endif(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/doc/doxygen")

    # Install the generated code documentation
    install(DIRECTORY "${DOXYGEN_HTML_OUTPUT}"
      DESTINATION share/doc/html)

  endif(BUILD_DOCUMENTATION)

endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")

