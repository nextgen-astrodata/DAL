# Optional: Doxygen generation (including python SWIG docstrings generation)

find_package(Doxygen)

# Doxygen documentation
option(GENERATE_DOCS "Generate documentation and regenerate docstrings using Doxygen" ${DOXYGEN_FOUND})

if(GENERATE_DOCS)
  find_package(PythonInterp REQUIRED)

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in"
    "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf"
    @ONLY
  )

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf
    COMMENT "Generating doxygen documentation"
  )

  set_property(DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
  )

  set_property(DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/xml
  )

  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/html

    DESTINATION share/doc/dal
    COMPONENT documentation
  )

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docstrings.i
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/external/doxy2swig.py ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml ${CMAKE_CURRENT_BINARY_DIR}/docstrings.i
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml
    COMMENT "Generating SWIG docstrings"
  )

else(GENERATE_DOCS)
  # generate an empty docstrings.i
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docstrings.i
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/docstrings.i
    COMMENT "Generating empty docstrings"
  )
endif(GENERATE_DOCS)

add_custom_target(swig_docstrings
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docstrings.i
)

