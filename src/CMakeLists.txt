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

target_link_libraries(lda ${HDF5_LIBRARIES})

install (TARGETS
  lda

  DESTINATION lib
)

# Python bindings through SWIG

if(PYTHON_BINDINGS)
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

add_subdirectory(hdf5core)
add_subdirectory(doc)

if(CASACORE_INTERFACE)
  add_subdirectory(casa)
  target_link_libraries(lda ${CASACORE_LIBRARIES})
endif(CASACORE_INTERFACE)
