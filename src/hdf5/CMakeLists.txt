install (FILES
  HDF5Attribute.h
  HDF5Attribute.tcc
  HDF5DatasetBase.h
  HDF5DatasetBase.tcc
  HDF5FileBase.h
  HDF5GroupBase.h
  HDF5Node.h

  DESTINATION include/dal/hdf5
)

add_subdirectory(types)

