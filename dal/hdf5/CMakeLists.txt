install (FILES
  Attribute.h
  Attribute.tcc
  Dataset.h
  Dataset.tcc
  Dataset1D.h
  Dataset1D.tcc
  File.h
  Group.h
  Node.h

  DESTINATION include/dal/hdf5
  COMPONENT headers
)

add_subdirectory(types)
add_subdirectory(exceptions)

