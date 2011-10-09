# Optional: Doxygen generation (including python docstrings generation)

find_package(Doxygen)

# Doxygen documentation
option(GENERATE_DOCS "Generate documentation and regenerate docstrings using Doxygen" ${DOXYGEN_FOUND})

if(GENERATE_DOCS)
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in"
    "${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf"
    @ONLY
  )

  # run "make doc" to generate doxygen documentation
  add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.conf
  )

  set_property (DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
    )

  install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/html

    DESTINATION share/doc/lda
  )  

  # generate SWIG docstrings from Doxygen output
  add_custom_command(
    OUTPUT docstrings.i
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/external/doxy2swig.py xml/index.xml docstrings.i
    DEPENDS doc
  )
else(GENERATE_DOCS)
  # generate an empty docstrings.i
  add_custom_command(
    OUTPUT docstrings.i
    COMMAND touch docstrings.i
  )
endif(GENERATE_DOCS)

add_custom_target(
  generate_docstrings
  DEPENDS docstrings.i
)

