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

add_library (lda 
  BF_File.cc
  CommonAttributesFile.cc
  HDF5FileBase.cc
  HDF5GroupBase.cc
  TBB_File.cc
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

