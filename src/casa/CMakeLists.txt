if(CASA_FOUND)
  install (FILES
    CasaDatasetExtend.h
    CasaTBBFileExtend.h

    DESTINATION include/casa
  )
endif(CASA_FOUND)

