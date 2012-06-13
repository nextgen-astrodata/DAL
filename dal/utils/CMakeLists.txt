if(PYTHON_BINDINGS)
  install (PROGRAMS
    bfheaderinfo.py
    tbb-lostframes.py
    DESTINATION bin
  ) 

  install(FILES
    bfmeta.py
    DESTINATION ${PYTHON_DEST}
  )
endif(PYTHON_BINDINGS)

