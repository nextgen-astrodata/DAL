include(TestMacros)

if(PYTHON_BINDINGS)

  # Create symlink from the current bin dir to examples/data so we can find input files. See examples/CMakeLists.txt
  add_custom_target(utils_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/examples/data data
                    COMMENT "Creating symlink to data sets for utils programs")

  if(PYTHON_EXECUTABLE)
    add_py_test(py-util-lofar-bf-headerinfo       ${CMAKE_CURRENT_SOURCE_DIR}/lofar-bf-headerinfo.py data/L63876_SAP000_B000_S0_P000_bf.h5 )
#    add_py_test(py-util-lofar-bf-headeredit       ${CMAKE_CURRENT_SOURCE_DIR}/lofar-bf-headeredit.py data/L00000_bf.h5 )
    add_py_test(py-util-lofar-tbb-flaggeddata     ${CMAKE_CURRENT_SOURCE_DIR}/lofar-tbb-flaggeddata.py data/L59640_RS106_D20111121T130145.049Z_tbb.h5 )
  endif(PYTHON_EXECUTABLE)

  install (PROGRAMS
    lofar-bf-headerinfo.py
#    lofar-bf-headeredit.py
    lofar-tbb-flaggeddata.py

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

