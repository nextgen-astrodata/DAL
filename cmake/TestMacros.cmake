macro(add_c_test _name)
  if(BUILD_TESTING)

    add_executable(${_name} ${_name}.cc ${ARGN})
    target_link_libraries(${_name} lofardal)
    add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})

    if(VALGRIND_FOUND)
      add_test("vg-${_name}" ${VALGRIND_PROGRAM} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
    endif(VALGRIND_FOUND)

  endif(BUILD_TESTING)
endmacro(add_c_test)

macro(add_py_test _name _pyfile)
  if(BUILD_TESTING AND PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

    add_test(${_name} ${PYTHON_EXECUTABLE} ${_pyfile} ${ARGN})
    set_tests_properties(${_name} PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}/dal")

  endif(BUILD_TESTING AND PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
endmacro(add_py_test)

