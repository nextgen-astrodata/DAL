# Optional: Casacore bindings for C++
option(CASACORE_INTERFACE "Generate casacore interface" OFF)

if(CASACORE_INTERFACE)
  find_package(Casacore REQUIRED COMPONENTS casa measures)
  include_directories(${CASACORE_INCLUDE_DIRS})

  install (FILES
    CasaDatasetExtend.h
    CasaTBBFileExtend.h

    DESTINATION include/dal/casa
    COMPONENT headers
  )
endif(CASACORE_INTERFACE)  

