if(PYTHON_BINDINGS)
  install (PROGRAMS
    bfheaderinfo.py
    bfheaderedit.py
    tbb-lostframes.py

    DESTINATION bin
    COMPONENT python
  ) 

  install(FILES
    bfmeta.py
    bfheader.py

    DESTINATION ${PYTHON_SITE_PACKAGES}/DAL
    COMPONENT python
  )
endif(PYTHON_BINDINGS)

