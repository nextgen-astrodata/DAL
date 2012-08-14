## Name of the project
project (DAL)

## Project release version
set (DAL_VERSION_MAJOR 2)
set (DAL_VERSION_MINOR 0)
set (DAL_VERSION_PATCH 0)
set (DAL_VERSION "${DAL_VERSION_MAJOR}.${DAL_VERSION_MINOR}.${DAL_VERSION_PATCH}")

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

include(CTest)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(BUILD_SHARED_LIBS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR} # to find regular headers
  ${CMAKE_CURRENT_BINARY_DIR} # to find generated headers
  )

## Mandatory: HDF5 support for core library
find_package(HDF5_DAL)
include_directories(${HDF5_INCLUDES})

include(TestHDF5)

## Python bindings
option(PYTHON_BINDINGS "Generate python bindings" ON)

if(PYTHON_BINDINGS)
  find_package(SWIG REQUIRED)
  include(${SWIG_USE_FILE})

  find_package(PythonLibs REQUIRED)
  include_directories(${PYTHON_INCLUDE_DIRS})

  find_package(Numpy REQUIRED)
  include_directories(${NUMPY_INCLUDE_DIRS})

  if(NOT CMAKE_CROSSCOMPILING)
    find_package(PythonInterp)
  endif(NOT CMAKE_CROSSCOMPILING)

  # Backwards compatibility
  if(PYTHON_DEST)
    set(PYTHON_SITE_PACKAGES ${PYTHON_DEST})
  endif(PYTHON_DEST)  

  # Obtain location of 'site-packages' directory (doesn't work when cross-compiling)
  if(NOT PYTHON_SITE_PACKAGES)
    if(PYTHON_EXECUTABLE)
      execute_process(
        COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib(plat_specific=True, prefix=''))"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif(PYTHON_EXECUTABLE)
  endif(NOT PYTHON_SITE_PACKAGES)

  # Obtain version info
  if(NOT PYTHON_VERSION)
    include(PythonVersion)
  endif(NOT PYTHON_VERSION)

  set(PYTHON_SITE_PACKAGES ${PYTHON_SITE_PACKAGES} CACHE PATH "Target directory for python bindings")
  set(PYTHON_VERSION       ${PYTHON_VERSION}       CACHE STRING "Python version to compile bindings against")
endif(PYTHON_BINDINGS)

## Start processing the source tree

add_subdirectory(dal)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(package)

if(GENERATE_DOCS)
  add_subdirectory(doc)
endif(GENERATE_DOCS)

MESSAGE("------------------------------------------------------")
MESSAGE("[${CMAKE_PROJECT_NAME} ${DAL_VERSION}] configuration summary")
MESSAGE("------------------------------------------------------")
MESSAGE("CMAKE_VERSION        = ${CMAKE_VERSION}")
MESSAGE("HDF5_VERSION         = ${HDF5_VERSION}")
MESSAGE("HDF5_INCLUDES        = ${HDF5_INCLUDES}")
MESSAGE("HDF5_LIBRARIES       = ${HDF5_LIBRARIES}")
MESSAGE("PYTHON_BINDINGS      = ${PYTHON_BINDINGS}")
if(PYTHON_BINDINGS)
  MESSAGE("PYTHON_VERSION       = ${PYTHON_VERSION}")
  MESSAGE("PYTHON_EXECUTABLE    = ${PYTHON_EXECUTABLE}")
  MESSAGE("PYTHON_INCLUDE_DIRS  = ${PYTHON_INCLUDE_DIRS}")
  MESSAGE("PYTHON_SITE_PACKAGES = ${PYTHON_SITE_PACKAGES}")
  MESSAGE("NUMPY_INCLUDE_DIRS   = ${NUMPY_INCLUDE_DIRS}")
endif(PYTHON_BINDINGS)
MESSAGE("GENERATE_DOCS        = ${GENERATE_DOCS}")
if(GENERATE_DOCS)
  MESSAGE("SPHINX_EXECUTABLE    = ${SPHINX_EXECUTABLE}")
endif(GENERATE_DOCS)
MESSAGE("------------------------------------------------------")

