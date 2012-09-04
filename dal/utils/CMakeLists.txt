add_subdirectory(lib) # don't call this 'dal': it confuses when loading Python modules

if(PYTHON_BINDINGS)
  include(TestMacros)

  # Create symlink from the current bin dir to examples/data so we can find input files. See examples/CMakeLists.txt
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/examples/data" dal/utils/data)

  # Python tests
  add_py_test(py-util-lofar_headerinfo          "${CMAKE_CURRENT_SOURCE_DIR}/lofar_headerinfo.py" data/L63876_SAP000_B000_S0_P000_bf.h5 )
  add_py_test(py-util-lofar_bf_headerinfo       "${CMAKE_CURRENT_SOURCE_DIR}/lofar_bf_headerinfo.py" data/L63876_SAP000_B000_S0_P000_bf.h5 )
#  add_py_test(py-util-lofar_bf_headeredit       "${CMAKE_CURRENT_SOURCE_DIR}/lofar_bf_headeredit.py" data/L00000_bf.h5 )
  add_py_test(py-util-lofar_tbb_headerinfo      "${CMAKE_CURRENT_SOURCE_DIR}/lofar_tbb_headerinfo.py" data/L59640_CS011_D20110719T110541.036Z_tbb.h5 )
  add_py_test(py-util-lofar_tbb_flaggeddata     "${CMAKE_CURRENT_SOURCE_DIR}/lofar_tbb_flaggeddata.py" data/L59640_RS106_D20111121T130145.049Z_tbb.h5 )

  install (PROGRAMS
    lofar_headerinfo.py
    lofar_bf_headerinfo.py
#    lofar_bf_headeredit.py
    lofar_tbb_headerinfo.py
    lofar_tbb_flaggeddata.py

    DESTINATION bin
    COMPONENT python
  ) 
endif(PYTHON_BINDINGS)

