# DAL example programs

# Build the C++ examples, so we can use them as tests.
macro(add_c_test _name)
  add_executable(${_name} ${_name}.cc ${ARGN})
  target_link_libraries(${_name} dal)
  add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
  set_property(TEST ${_name} APPEND PROPERTY DEPENDS make_example_symlink)
endmacro(add_c_test)

# Add a symlink from the current bin dir to examples/ so we can find input files.
# Note: The absolute CMAKE_CURRENT_SOURCE_DIR path breaks if the user moves everything (alt: copy all example data files)
add_custom_target(make_example_symlink COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/data data)

add_c_test(example-bf-recreate-dataset)
add_c_test(example-tbb-read)

if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
  add_test(py-example-bf-read       ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-bf-read.py)
  add_test(py-example-custom-write  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-custom-write.py)
  add_test(py-example-exceptions    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-exceptions.py)
  add_test(py-example-introspection ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-introspection.py)
  add_test(py-example-types         ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-types.py)

  set_property(TEST py-example-bf-read       APPEND PROPERTY DEPENDS make_example_symlink)
  set_property(TEST py-example-introspection APPEND PROPERTY DEPENDS make_example_symlink)
endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

