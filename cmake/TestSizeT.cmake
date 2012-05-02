# - Find what size_t and other types resolve to
# Variables defined by this module:
#  TYPEOF_size_t      - the integer type corresponing to size_t (unsigned int, unsigned long, etc)
#  TYPEOF_ssize_t     - the integer type corresponing to ssize_t (int, long, etc)

# Resolve all the types we need
foreach(SRC_TYPE size_t ssize_t)
  if(NOT TYPEOF_${SRC_TYPE})
    # First do a trial run to see if TestIsSame is sane
    try_compile(TEST_COMPILE
            ${CMAKE_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/cmake/TestIsSame.cc
            CMAKE_FLAGS
              "-DCOMPILE_DEFINITIONS:STRING=-DSRC_TYPE='${SRC_TYPE}' -DDEST_TYPE='${SRC_TYPE}'"
            OUTPUT_VARIABLE TEST_COMPILE_OUTPUT
            )

    if(NOT TEST_COMPILE)
      message(FATAL_ERROR "Failed to compile cmake/TestIsSame.cc: ${TEST_COMPILE_OUTPUT}")
    endif(NOT TEST_COMPILE)

    # Try to match any of these types. Note that adding types here required additional code
    # in src/DAL.i and src/size_types.i as well to marshall the types to SWIG and Python.
    foreach(DEST_TYPE
      "unsigned int" "unsigned long"
      "int" "long"
    )

      # Try to compile TestIsSame.cc given the SRC_TYPE and DEST_TYPE. The compilation will
      # only succeed if SRC_TYPE and DEST_TYPE are considered to be the same by the compiler.
      # We just compile, and don't run anything, to allow DAL to be cross compiled.
      try_compile(TEST_COMPILE
              ${CMAKE_BINARY_DIR}
              ${PROJECT_SOURCE_DIR}/cmake/TestIsSame.cc
              CMAKE_FLAGS
                "-DCOMPILE_DEFINITIONS:STRING=-DSRC_TYPE='${SRC_TYPE}' -DDEST_TYPE='${DEST_TYPE}'"
              OUTPUT_VARIABLE TEST_COMPILE_OUTPUT
              )

      if(TEST_COMPILE)
        message(STATUS "${SRC_TYPE} == ${DEST_TYPE}")
 
        set(TYPEOF_${SRC_TYPE} ${DEST_TYPE} CACHE INTERNAL "Basic type (int, long, etc) of ${SRC_TYPE}")

        break()  
      endif(TEST_COMPILE)
    endforeach(DEST_TYPE)

  endif(NOT TYPEOF_${SRC_TYPE})

  if(NOT TYPEOF_${SRC_TYPE})
    message(FATAL_ERROR "Could not determine the basic type of ${SRC_TYPE}")
  endif(NOT TYPEOF_${SRC_TYPE})
endforeach(SRC_TYPE)
