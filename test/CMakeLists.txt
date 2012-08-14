set(dal_cpp_test_sources
  instantiate-only.cpp
)

add_test(instantiate-only ${CMAKE_CURRENT_BINARY_DIR}/../../test/instantiate-only)

if(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)
  add_test(py-import-only ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../../test/import-only.py)
  add_test(py-doctest ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/../dal/DAL.py)
endif(PYTHON_BINDINGS AND PYTHON_EXECUTABLE)

