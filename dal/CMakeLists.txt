include(TestSizeT)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/size_types.i.in"
  "${CMAKE_CURRENT_BINARY_DIR}/size_types.i"
)

install (FILES
  ${CMAKE_CURRENT_BINARY_DIR}/dal_config.h
  dal_version.h

  DESTINATION include/dal
)

set(dal_sources
  dal_version.cc

  hdf5/File.cc
  hdf5/Group.cc
  hdf5/Node.cc
  hdf5/exceptions/exceptions.cc
  hdf5/exceptions/errorstack.cc
  hdf5/types/versiontype.cc

  lofar/Station.cc
  lofar/BF_File.cc
  lofar/CLA_File.cc
  lofar/Coordinates.cc
  lofar/TBB_File.cc
)

set(dal_headers
  dal_version.h

  hdf5/Attribute.h
  hdf5/Attribute.tcc
  hdf5/exceptions/errorstack.h
  hdf5/exceptions/exceptions.h
  hdf5/File.h
  hdf5/Dataset.h
  hdf5/Dataset.tcc
  hdf5/Group.h
  hdf5/types/h5complex.h
  hdf5/types/issame.h
  hdf5/types/implicitdowncast.h
  hdf5/types/h5typemap.h
  hdf5/types/h5tuple.h
  hdf5/types/isderivedfrom.h
  hdf5/types/versiontype.h
  hdf5/types/hid_gc.h
  hdf5/Node.h

  lofar/Station.h
  lofar/Coordinates.h
  lofar/TBB_File.h
  lofar/CommonTuples.h
  lofar/CLA_File.h
  lofar/BF_File.h

  casa/CasaTBBFileExtend.h
  casa/CasaDatasetExtend.h
)

set(swig_sources
  DAL.i
  vectors.i
  external/numpy.i

  hdf5/Attribute.i
  hdf5/Group.i
  hdf5/exceptions/exceptions.i
  hdf5/Node.i
  hdf5/Dataset.i
  hdf5/types/h5tuple.i
  hdf5/types/versiontype.i

  lofar/TBB_File.i
  lofar/CommonTuples.i
)  

add_library (dal
  ${dal_sources}
)


if(CMAKE_COMPILER_IS_GNUCXX)
  set_target_properties(dal PROPERTIES COMPILE_FLAGS "-g3 -Wall -Wextra -Wno-unused-function -Wno-long-long -ansi -pedantic")
endif(CMAKE_COMPILER_IS_GNUCXX)

target_link_libraries(dal ${HDF5_LIBRARIES})

install (TARGETS
  dal

  DESTINATION lib
)

# Python bindings through SWIG

# Optional: Python bindings through SWIG
option(PYTHON_BINDINGS "Generate python bindings" ON)

if(PYTHON_BINDINGS)
  find_package(SWIG REQUIRED)
  include(${SWIG_USE_FILE})

  find_package(PythonLibs REQUIRED)
  include_directories(${PYTHON_INCLUDE_DIRS})

  find_package(Numpy REQUIRED)
  include_directories(${NUMPY_INCLUDE_DIRS})

  find_package(PythonInterp)

  if(PYTHON_EXECUTABLE)
    # Obtain location of 'site-packages' directory (doesn't work when cross-compiling)
    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
  else(PYTHON_EXECUTABLE)
    # A default value -- X.X should be replaced with the target python version
    set(PYTHON_SITE_PACKAGES ${CMAKE_INSTALL_PREFIX}/lib/pythonX.X/dist-packages)
  endif(PYTHON_EXECUTABLE)

  set(PYTHON_DEST ${PYTHON_SITE_PACKAGES} CACHE PATH "Target directory for python bindings")

  list(APPEND CMAKE_SWIG_FLAGS -Wall -Wextra)
  set_source_files_properties(DAL.i PROPERTIES CPLUSPLUS ON)
  set_source_files_properties(DAL.i PROPERTIES SWIG_FLAGS -modern -oldrepr -keyword -castmode -modernargs)
  set(SWIG_MODULE_DAL_EXTRA_DEPS swig_docstrings dal ${swig_sources} ${dal_headers})
  swig_add_module(DAL python DAL.i ${dal_sources})
  swig_link_libraries(DAL ${PYTHON_LIBRARIES} ${HDF5_LIBRARIES})

  install(TARGETS
    ${SWIG_MODULE_DAL_REAL_NAME}
    DESTINATION ${PYTHON_DEST}
  )

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/DAL.py
    DESTINATION ${PYTHON_DEST}
  )
endif(PYTHON_BINDINGS)

add_subdirectory(casa)
add_subdirectory(doc)
add_subdirectory(hdf5)
add_subdirectory(lofar)
add_subdirectory(utils)

# Generate the configuration file at the end, once all options are known
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/dal_config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/dal_config.h"
)

