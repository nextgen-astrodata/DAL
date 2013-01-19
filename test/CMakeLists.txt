# DAL test cases: unit tests, a python doc test, utilities, and example programs.
include(TestMacros)

# Create symlink from the current bin dir to examples/data so we can find input files. See examples/CMakeLists.txt
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/examples/data" test/data)

# C++ tests, each with and without valgrind
add_c_test(h5-test-create) # Doesn't use DAL. If this fails, HDF5 (or the test system) is not working.
add_c_test(instantiate-only)
add_c_test(reopen-rw)
add_c_test(constructors)
add_c_test(version-check)
add_c_test(version-check2)
add_c_test(attr-empty)
add_c_test(get-tbb-station-ref)
add_c_test(print-bf-sap-attr)
add_c_test(remove-root-exc)

# Python tests
add_py_test(py-import-only ${CMAKE_CURRENT_SOURCE_DIR}/import-only.py)
add_py_test(py-doctest ${CMAKE_BINARY_DIR}/dal/dal.py)
add_py_test(py-auto-create-bf-fields ${CMAKE_CURRENT_SOURCE_DIR}/auto-create-bf-fields.py)
add_py_test(py-get-tbb-station-ref ${CMAKE_CURRENT_SOURCE_DIR}/get-tbb-station-ref.py)
add_py_test(py-reopen-rw ${CMAKE_CURRENT_SOURCE_DIR}/reopen-rw.py)
add_py_test(py-dataset-create1D ${CMAKE_CURRENT_SOURCE_DIR}/dataset-create1D.py)

