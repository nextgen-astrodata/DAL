if(PYTHON_BINDINGS)
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in"
    "${CMAKE_CURRENT_BINARY_DIR}/setup.py"
  )
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/setup.py"
    DESTINATION "${PYTHON_SITE_PACKAGES}/dal"
    COMPONENT python
  )

  include(TestMacros)
  install_python_module_files(
    __init__.py
    bfmeta.py
    bfheader.py
  )
endif(PYTHON_BINDINGS)

