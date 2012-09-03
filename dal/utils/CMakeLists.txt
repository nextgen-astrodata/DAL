add_subdirectory(lib) # don't call this 'dal': it confuses when loading Python modules

if(PYTHON_BINDINGS)
  include(TestMacros)

  # Create symlink from the current bin dir to examples/data so we can find input files. See examples/CMakeLists.txt
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/examples/data" dal/utils/data)

  # Python tests
  add_py_test(py-util-lofar-bf-headerinfo       "${CMAKE_CURRENT_SOURCE_DIR}/lofar-bf-headerinfo.py" data/L63876_SAP000_B000_S0_P000_bf.h5 )
#  add_py_test(py-util-lofar-bf-headeredit       "${CMAKE_CURRENT_SOURCE_DIR}/lofar-bf-headeredit.py" data/L00000_bf.h5 )
  add_py_test(py-util-lofar-tbb-flaggeddata     "${CMAKE_CURRENT_SOURCE_DIR}/lofar-tbb-flaggeddata.py" data/L59640_RS106_D20111121T130145.049Z_tbb.h5 )

  install (PROGRAMS
    lofar-bf-headerinfo.py
#    lofar-bf-headeredit.py
    lofar-tbb-flaggeddata.py

    DESTINATION bin
    COMPONENT python
  ) 
endif(PYTHON_BINDINGS)

