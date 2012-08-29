# DAL test cases: unit tests, a python doc test, utilities, and example programs.

macro(add_c_test _name)
  add_executable(${_name} ${_name}.cc ${ARGN})
  target_link_libraries(${_name} dal)
  add_test(${_name} ${CMAKE_CURRENT_BINARY_DIR}/${_name})
endmacro(add_c_test)

# Create symlink from the current bin dir to examples/data so we can find input files. See examples/CMakeLists.txt
add_custom_target(test_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/../examples/data data
                  COMMENT "Creating symlink to data sets for test programs")

add_c_test(h5-test-create) # Doesn't use DAL. If this fails, HDF5 (or the test system) is not working.
add_c_test(instantiate-only)
add_c_test(reopen-rw)
add_c_test(constructors)
add_c_test(version-check)
add_c_test(attr-empty)
add_c_test(get-tbb-station-ref)
add_c_test(remove-root-exc)

if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
  add_test(py-import-only ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/import-only.py)
  add_test(py-doctest ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../dal/DAL.py)
  add_test(py-auto-create-bf-fields ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/auto-create-bf-fields.py)
  add_test(py-get-tbb-station-ref ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/get-tbb-station-ref.py)
  add_test(py-reopen-rw ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/reopen-rw.py)
  add_test(py-dataset-create1D ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/dataset-create1D.py)
endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

