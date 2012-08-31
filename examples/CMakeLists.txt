# DAL example programs
include(TestMacros)

# Create symlink from the current bin dir to examples/data so we can find input files. The create_symlink cmd only works on UNIX systems.
# Note: Also done for test/ and dal/utils. The absolute CMAKE_CURRENT_SOURCE_DIR path breaks if the user moves everything (alt: copy all example data files)
add_custom_target(example_symlink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data data
                  COMMENT "Creating symlink to data sets for example programs")

# C++ tests, each with and without valgrind
add_c_test(example-bf-recreate-dataset)
add_c_test(example-tbb-read)

# Python tests
add_py_test(py-example-bf-read       ${CMAKE_CURRENT_SOURCE_DIR}/example-bf-read.py)
add_py_test(py-example-custom-write  ${CMAKE_CURRENT_SOURCE_DIR}/example-custom-write.py)
add_py_test(py-example-exceptions    ${CMAKE_CURRENT_SOURCE_DIR}/example-exceptions.py)
add_py_test(py-example-introspection ${CMAKE_CURRENT_SOURCE_DIR}/example-introspection.py)
add_py_test(py-example-types         ${CMAKE_CURRENT_SOURCE_DIR}/example-types.py)

