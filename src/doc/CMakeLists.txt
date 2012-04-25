# Optional: Doxygen generation (including python SWIG docstrings generation)

find_package(Doxygen)

# Doxygen documentation
option(GENERATE_DOCS "Generate documentation and regenerate docstrings using Doxygen" ${DOXYGEN_FOUND})

if(GENERATE_DOCS)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in"
    "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf"
    @ONLY
  )

  # run "make doc" to generate doxygen documentation
  add_custom_target(doc# ALL
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf
    COMMENT "Generating doxygen documentation"
  )

  set_property(DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
  )

  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION share/doc/dal
  )  

  add_custom_target(swig_docstrings
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/external/doxy2swig.py xml/index.xml docstrings.i
    COMMENT "Generating SWIG docstrings"
  )
  
  add_dependencies(swig_docstrings doc)

else(GENERATE_DOCS)
  # generate an empty docstrings.i
  add_custom_target(swig_docstrings
    COMMAND ${CMAKE_COMMAND} -E touch docstrings.i
    COMMENT "Creating empty SWIG docstrings.i file"
  )
endif(GENERATE_DOCS)

