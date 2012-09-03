if(PYTHON_BINDINGS)
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in"
    "${CMAKE_CURRENT_BINARY_DIR}/setup.py"
  )

  install(FILES
    __init__.py
    ${CMAKE_CURRENT_BINARY_DIR}/setup.py

    DESTINATION ${PYTHON_SITE_PACKAGES}/dal
    COMPONENT python
  )
endif(PYTHON_BINDINGS)

