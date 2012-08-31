macro(add_c_test _name)
  add_executable(${_name} ${_name}.cc ${ARGN})
  target_link_libraries(${_name} lofardal)
  add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})

  if(VALGRIND_FOUND)
    add_test("vg-${_name}" ${VALGRIND_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
  endif(VALGRIND_FOUND)
endmacro(add_c_test)

if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
  macro(add_py_test _name _pyfile)
    add_test(${_name} ${PYTHON_EXECUTABLE} ${_pyfile} ${ARGN})
    set_tests_properties(${_name} PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/dal")
  endmacro(add_py_test)
endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

