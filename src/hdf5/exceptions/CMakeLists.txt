option(QUIET_HDF5_ERRORS "Prevent HDF5 from printing error information directly on stderr" ON)

install (FILES
  h5errorhandling.h
  h5exception.h

  DESTINATION include/dal/hdf5/exceptions
)

