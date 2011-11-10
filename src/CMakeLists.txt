# Mandatory: HDF5 support for core library
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

include(TestHDF5)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR} # to find regular headers
  ${CMAKE_CURRENT_BINARY_DIR} # to find generated headers
  )

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/lda_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/lda_config.h"
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/lda_config.h
  lda_version.h

  DESTINATION include/lda
)

set(lda_sources
  lda_version.cc

  hdf5/HDF5FileBase.cc
  hdf5/HDF5GroupBase.cc

  lofar/BF_File.cc
  lofar/CommonAttributesFile.cc
  lofar/TBB_File.cc
)

add_library (lda 
  ${lda_sources}
)

target_link_libraries(lda ${HDF5_LIBRARIES})

install (TARGETS
  lda

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
  set_source_files_properties(LDA.i PROPERTIES CPLUSPLUS ON)
  swig_add_module(LDA python LDA.i ${lda_sources})
  add_dependencies(${SWIG_MODULE_LDA_REAL_NAME} generate_docstrings)
  swig_link_libraries(LDA ${PYTHON_LIBRARIES} ${HDF5_LIBRARIES})

  install(TARGETS
    ${SWIG_MODULE_LDA_REAL_NAME}
    DESTINATION ${PYTHON_DEST}
  )

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LDA.py
    DESTINATION ${PYTHON_DEST}
  )  
endif(PYTHON_BINDINGS)

add_subdirectory(casa)
add_subdirectory(doc)
add_subdirectory(hdf5)
add_subdirectory(lofar)

