# DAL example programs

# Build the C++ examples, so we can use them as tests.
macro(add_c_test _name)
  add_executable(${_name} ${_name}.cc ${ARGN})
  target_link_libraries(${_name} dal)
  add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
endmacro(add_c_test)

add_c_test(example-tbb-read)

