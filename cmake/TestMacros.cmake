macro(add_c_test _name)
  if(BUILD_TESTING)

    add_executable("${_name}" "${_name}.cc" ${ARGN})
    target_link_libraries("${_name}" lofardal)
    add_test("${_name}" "${CMAKE_CURRENT_BINARY_DIR}/${_name}")

    if(VALGRIND_FOUND)
      add_test("vg-${_name}" "${VALGRIND_PROGRAM}" "${CMAKE_CURRENT_BINARY_DIR}/${_name}")
    endif(VALGRIND_FOUND)

  endif(BUILD_TESTING)
endmacro(add_c_test)

macro(add_py_test _name _pyfile)
  if(BUILD_TESTING AND PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

    # Set PYTHONPATH to find (the symlinks to) our modules. Once installed, our Python programs also find our modules that way.
    add_test("${_name}" "${PYTHON_EXECUTABLE}" "${_pyfile}" ${ARGN})
    set_tests_properties("${_name}" PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_BINARY_DIR}")

  endif(BUILD_TESTING AND PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
endmacro(add_py_test)


# this should perhaps be in or done by PythonInstall.cmake (else remove that one)
macro(install_python_module_files)
  if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

    install(FILES
      ${ARGN}
      DESTINATION "${PYTHON_SITE_PACKAGES}/dal"
      COMPONENT python
    )

    # Python program sources, modules sources, and generated sources end up in different dirs.
    # To make sure that the test suite uses the source files instead of depending on already
    # installed files, the build dir needs to symlink to all non-generated .py files.
    if(BUILD_TESTING)

      foreach(_py ${ARGN})
        execute_process(COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/${_py}" "dal/${_py}")
      endforeach(_py ${ARGN})

    endif(BUILD_TESTING)
  endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
endmacro(install_python_module_files)

