if(PYTHON_BINDINGS)
  install (PROGRAMS
    bfheaderinfo.py
    bfheaderedit.py
    tbb-lostframes.py
    DESTINATION bin
  ) 

  install(FILES
    bfmeta.py
    bfheader.py
    DESTINATION ${PYTHON_SITE_PACKAGES}/DAL
  )
endif(PYTHON_BINDINGS)

