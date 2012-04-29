# Mandatory: HDF5 support for core library
find_package(HDF5_DAL)
include_directories(${HDF5_INCLUDES})

include(TestHDF5)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR} # to find regular headers
  ${CMAKE_CURRENT_BINARY_DIR} # to find generated headers
  )

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/dal_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/dal_config.h"
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/dal_config.h
  dal_version.h

  DESTINATION include/dal
)

set(dal_sources
  dal_version.cc

  hdf5/HDF5FileBase.cc
  hdf5/HDF5GroupBase.cc
  hdf5/exceptions/h5errorhandling.cc

  lofar/BF_File.cc
  lofar/CommonAttributesFile.cc
  lofar/Coordinates.cc
  lofar/TBB_File.cc
)

add_library (dal
  ${dal_sources}
)

target_link_libraries(dal ${HDF5_LIBRARIES})

install (TARGETS
  dal

  DESTINATION lib
)

# Python bindings through SWIG

# Optional: Python bindings through SWIG
option(PYTHON_BINDINGS "Generate python bindings" ON)

if(PYTHON_BINDINGS)
  find_package(SWIG REQUIRED)
  include(${SWIG_USE_FILE})

  find_package(PythonLibs REQUIRED)
  include_directories(${PYTHON_INCLUDE_DIRS})

  find_package(Numpy REQUIRED)
  include_directories(${NUMPY_INCLUDE_DIRS})

  # Obtain location of 'site-packages' directory (doesn't work when cross-compiling)
  execute_process(COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(PYTHON_DEST ${PYTHON_SITE_PACKAGES} CACHE PATH "Target directory for python bindings")

  list(APPEND CMAKE_SWIG_FLAGS -Wall)
  set_source_files_properties(DAL.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(DAL python DAL.i ${dal_sources})
  add_dependencies(${SWIG_MODULE_DAL_REAL_NAME} docstrings_i)
  swig_link_libraries(DAL ${PYTHON_LIBRARIES} ${HDF5_LIBRARIES})

  install(TARGETS
    ${SWIG_MODULE_DAL_REAL_NAME}
    DESTINATION ${PYTHON_DEST}
  )

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/DAL.py
    DESTINATION ${PYTHON_DEST}
  )  
endif(PYTHON_BINDINGS)

add_subdirectory(casa)
add_subdirectory(doc)
add_subdirectory(hdf5)
add_subdirectory(lofar)
add_subdirectory(utils)
