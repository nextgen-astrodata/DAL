option(QUIET_HDF5_ERRORS "Prevent HDF5 from printing error information directly on stderr" ON)

install (FILES
  errorstack.h
  exceptions.h

  DESTINATION include/dal/hdf5/exceptions
)

