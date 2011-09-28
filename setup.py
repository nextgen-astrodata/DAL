#!/usr/bin/env python

"""
setup.py file from SWIG example, adjusted
"""

from distutils.core import setup, Extension

# Third-party modules - we depend on numpy for everything
import numpy

# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()


BeamFormedFile_module = Extension('_BeamFormedFile',
                           sources=['BeamFormedFile.i', 'CLAFile.cpp', 'BeamFormedFile.cpp', 'HDF5File.cpp', 'HDF5Group.cpp'],
                           include_dirs=['/data/sys/opt/cep/hdf5/include', numpy_include],
                           libraries=['hdf5'],
                           swig_opts=['-c++'],
                           language='c++',
                           )

setup (name = 'BeamFormedFile',
       version = '1.0',
       author      = "dr. Jan David Mol, ASTRON, the Netherlands",
       description = """Bindings of LDA""",
       ext_modules = [BeamFormedFile_module],
       py_modules = ["BeamFormedFile"],
       )
