add_subdirectory(casa)
add_subdirectory(hdf5core)

include_directories (
  ${LDA_SOURCE_DIR}/src
  ${LDA_BINARY_DIR}
  )

configure_file (
  "${LDA_SOURCE_DIR}/src/lda_config.h.in"
  "${LDA_BINARY_DIR}/lda_config.h"
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
  ${LDA_BINARY_DIR}/lda_config.h
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

