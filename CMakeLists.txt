
## Name of the project
project (LDA)

## Project release version
set (LDA_VERSION_MAJOR 1)
set (LDA_VERSION_MINOR 0)
set (LDA_VERSION_PATCH 0)
set (LDA_VERSION "${LDA_VERSION_MAJOR}.${LDA_VERSION_MINOR}.${LDA_VERSION_PATCH}")

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

#include(CTest)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Start processing the source tree

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)
