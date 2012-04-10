install (FILES
  bfheaderinfo.py

  DESTINATION $LOFARSOFT/release/bin
)

if(PYTHON_BINDINGS)
  install(FILES
    bfmeta.py
    DESTINATION ${PYTHON_DEST}
  )
endif(PYTHON_BINDINGS)

