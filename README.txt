The Data Access Library (DAL) - README
======================================

The DAL provides data access to radio astronomy data in HDF5 format produced by the LOFAR telescope.
It ships with the specifications describing the data formats and provides a reference implementation to access all data fields with long-term version compatibility in mind.
DAL is written in C++ and offers Python bindings to all functionality.
It is available from https://github.com/nextgen-astrodata/DAL


DAL Project Contents
--------------------

INSTALL.txt		How to retrieve and build DAL, list of dependencies.
CONTRIBUTING.txt	How to contact us and/or submit contributions.
LICENSE.txt		The license text

src/			DAL sources
CMakeLists.txt		Build configuration script
cmake/			Build configuration helper scripts
setup.py		Python bindings setup script invoked by build
examples/		Small example programs

