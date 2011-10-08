if(CASACORE_FOUND)
  install (FILES
    CasaDatasetExtend.h
    CasaTBBFileExtend.h

    DESTINATION include/casa
  )
endif(CASACORE_FOUND)

