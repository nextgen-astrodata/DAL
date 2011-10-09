include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR} # to find regular headers
  ${CMAKE_CURRENT_BINARY_DIR} # to find generated headers
  )

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/lda_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/lda_config.h"
)

set(lda_sources
  BF_File.cc
  CommonAttributesFile.cc
  HDF5FileBase.cc
  HDF5GroupBase.cc
  TBB_File.cc
)

add_library (lda 
  ${lda_sources}
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/lda_config.h
  BF_File.h
  CommonAttributesFile.h
  HDF5Attribute.h
  HDF5DatasetBase.h
  HDF5FileBase.h
  HDF5GroupBase.h
  HDF5Node.h
  TBB_File.h

  DESTINATION include
)

add_subdirectory(casa)
add_subdirectory(hdf5core)

# Doxygen documentation

if(DOXYGEN_FOUND)
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in"
    "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf"
    @ONLY
  )

  # make a html dir so that install won't fail if documentation
  # hasn't been generated
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html)

  # run "make doc" to generate doxygen documentation
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  )

  set_property (DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
    )

  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/html

    DESTINATION share/doc/lda
  )  
endif(DOXYGEN_FOUND)  

# Python bindings through SWIG

if(PYTHON_BINDINGS)
  include_directories(${PYTHON_INCLUDE_PATH})
  set_source_files_properties(LDA.i PROPERTIES CPLUSPLUS ON)
  set_source_files_properties(LDA.i PROPERTIES SWIG_FLAGS "-Wall")
  swig_add_module(LDA python LDA.i ${lda_sources})
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

