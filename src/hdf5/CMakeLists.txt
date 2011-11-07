# Mandatory: HDF5 support for core library
find_package(HDF5 REQUIRED)
include_directories(${HDF5_INCLUDE_DIR})

include(TestHDF5)

install (FILES
  HDF5Attribute.h
  HDF5DatasetBase.h
  HDF5FileBase.h
  HDF5GroupBase.h
  HDF5Node.h

  DESTINATION include/lda/hdf5
)

add_subdirectory(types)
