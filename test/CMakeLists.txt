if(PYTHON_BINDINGS)
  add_test("DAL.py-doctest" python ${CMAKE_CURRENT_BINARY_DIR}/../src/DAL.py)
endif(PYTHON_BINDINGS)

