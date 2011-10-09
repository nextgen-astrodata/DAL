
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
if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
  #list(APPEND lda_link_libraries ${HDF5_LIBRARIES})
endif(HDF5_FOUND)

# Optional: Casacore bindings for C++

find_package(Casacore COMPONENTS casa measures)
if(CASACORE_FOUND)
  include_directories(${CASACORE_INCLUDES})
  #list(APPEND lda_link_libraries ${CASACORE_LIBRARIES})
endif(CASACORE_FOUND)

# Optional: Python bindings through SWIG

find_package(SWIG)
if(SWIG_FOUND)
  include(${SWIG_USE_FILE})

  # For now, we assume python bindings only
  find_package(PythonLibs REQUIRED)

  set(PYTHON_DEST "lib/python${PYTHON_VERSION}/site-packages")

  set(PYTHON_BINDINGS TRUE)
endif(SWIG_FOUND)

# Start processing the source tree

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

