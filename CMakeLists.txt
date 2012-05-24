
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

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR} # to find regular headers
  ${CMAKE_CURRENT_BINARY_DIR} # to find generated headers
  )

# Start processing the source tree

add_subdirectory(dal)
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

if(GENERATE_DOCS)
  add_subdirectory(doc)
endif(GENERATE_DOCS)

