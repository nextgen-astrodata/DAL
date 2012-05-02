foreach(SRC_TYPE size_t ssize_t)
  if(NOT TYPEOF_${SRC_TYPE})

    foreach(DEST_TYPE
      "unsigned int" "unsigned long"
      "int" "long"
    )

      try_compile(TEST_COMPILE
              ${CMAKE_BINARY_DIR}
              ${PROJECT_SOURCE_DIR}/cmake/TestIsSame.cc
              CMAKE_FLAGS
                "-DINCLUDE_DIRECTORIES:STRING=${PROJECT_SOURCE_DIR}/src"
                "-DCOMPILE_DEFINITIONS:STRING=-DSRC_TYPE='${SRC_TYPE}' -DDEST_TYPE='${DEST_TYPE}'"
              OUTPUT_VARIABLE TEST_COMPILE_OUTPUT
              )

      if(TEST_COMPILE)
        message(STATUS "${SRC_TYPE} is the same type as ${DEST_TYPE}")
 
        set(TYPEOF_${SRC_TYPE} ${DEST_TYPE} CACHE INTERNAL "Actual type of size_t")

        break()  
      endif(TEST_COMPILE)
    endforeach(DEST_TYPE)

  endif(NOT TYPEOF_${SRC_TYPE})

  if(NOT TYPEOF_${SRC_TYPE})
    message(FATAL_ERROR "Could not determine real type of ${SRC_TYPE}")
  endif(NOT TYPEOF_${SRC_TYPE})
endforeach(SRC_TYPE)
