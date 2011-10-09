
## Name of the project
project (LDA)

## Project release version
set (LDA_VERSION_MAJOR 0)
set (LDA_VERSION_MINOR 1)
set (LDA_VERSION_PATCH 7)
set (LDA_VERSION "${LDA_VERSION_MAJOR}.${LDA_VERSION_MINOR}.${LDA_VERSION_PATCH}")

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

#include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Mandatory: HDF5 support for core library

find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Optional: Casacore bindings for C++
option(CASACORE_INTERFACE "Generate casacore interface" OFF)

if(CASACORE_INTERFACE)
  find_package(Casacore REQUIRED COMPONENTS casa measures)
  include_directories(${CASACORE_INCLUDES})
endif(CASACORE_INTERFACE)

# Optional: Doxygen generation (including python docstrings generation)

find_package(Doxygen)

# Optional: Python bindings through SWIG
option(PYTHON_BINDINGS "Generate python bindings" ON)

if(PYTHON_BINDINGS)
  find_package(SWIG REQUIRED)
  include(${SWIG_USE_FILE})

  # For now, we assume python bindings only
  find_package(PythonLibs REQUIRED)

  set(PYTHON_DEST "lib/python${PYTHON_VERSION}/site-packages")
endif(PYTHON_BINDINGS)  

# Start processing the source tree

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

