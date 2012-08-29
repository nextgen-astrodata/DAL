# DAL example programs

# Build the C++ examples, so we can use them as tests.
macro(add_c_test _name)
  add_executable(${_name} ${_name}.cc ${ARGN})
  target_link_libraries(${_name} dal)
  add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
endmacro(add_c_test)

# Create symlink from the current bin dir to examples/data so we can find input files. The create_symlink cmd only works on UNIX systems.
# Note: Also done for test/ and dal/utils. The absolute CMAKE_CURRENT_SOURCE_DIR path breaks if the user moves everything (alt: copy all example data files)
add_custom_target(example_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data data
                  COMMENT "Creating symlink to data sets for example programs")

add_c_test(example-bf-recreate-dataset)
add_c_test(example-tbb-read)

if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
  add_test(py-example-bf-read       ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-bf-read.py)
  add_test(py-example-custom-write  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-custom-write.py)
  add_test(py-example-exceptions    ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-exceptions.py)
  add_test(py-example-introspection ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-introspection.py)
  add_test(py-example-types         ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/example-types.py)
endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

