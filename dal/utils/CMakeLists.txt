if(PYTHON_BINDINGS)
  install (PROGRAMS
    bfheaderinfo.py
    DESTINATION bin
  ) 

  install(FILES
    bfmeta.py
    DESTINATION ${PYTHON_DEST}
  )
endif(PYTHON_BINDINGS)

