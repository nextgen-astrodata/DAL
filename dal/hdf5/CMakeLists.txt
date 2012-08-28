install (FILES
  Attribute.h
  Attribute.tcc
  Dataset.h
  Dataset.tcc
  File.h
  Group.h
  Node.h

  DESTINATION include/dal/hdf5
  COMPONENT headers
)

add_subdirectory(types)
add_subdirectory(exceptions)

