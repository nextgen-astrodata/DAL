install (FILES
  HDF5Attribute.h
  HDF5DatasetBase.h
  HDF5FileBase.h
  HDF5GroupBase.h
  HDF5Node.h

  DESTINATION include/lda/hdf5
)

add_subdirectory(types)
