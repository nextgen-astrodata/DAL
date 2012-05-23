install (FILES
  Attribute.h
  Attribute.tcc
  Dataset.h
  Dataset.tcc
  File.h
  Group.h
  Node.h

  DESTINATION include/dal/hdf5
)

add_subdirectory(types)
add_subdirectory(exceptions)

