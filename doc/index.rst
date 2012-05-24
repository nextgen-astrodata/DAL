.. DAL documentation master file, created by
   sphinx-quickstart on Fri May 18 09:36:20 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to DAL's documentation!
===============================

Contents:

.. toctree::
   :maxdepth: 2


************
Introduction
************

The DAL, or Data Access Library, is a library to read and write HDF5 files, and is tuned to process astronomical data sets. More specifically, the DAL provides an interface in both C++ and Python to access various astronomical file formats that use HDF5, but also allows you to define your custom HDF5 structure on the fly.

============
Installation
============

For now, please read INSTALL.txt.

=====
Usage
=====

To work with the DAL, a (very) basic understanding of HDF5 is required. An HDF5 file encodes an hierarchical structure consisting of a set of *groups*. Each group has a name, and can have sub groups, as well as a set of key-value pairs called *attributes*. Finally, a *dataset* is a specialised group which has a large array of data associated with it. An HDF5 file itself starts with a so-called *root group*, named ``/``.

An hierarchical structure is typically represented by a tree. For example, consider the following example structure of groups, attributes and datasets, annotated with their respective data type::

  /
  +-- NUMELEMENTS (int)
  +-- DATETIME    (string)
  |
  +-- GROUP_1
  |   +-- PHASE (complex float)
  |   +-- SUBGROUP_1
  |       +-- STATIONS (list of strings)
  |
  +-- GROUP_2
  |   +-- SUBGROUP_2
  |
  +-- DATASET (array[10][20] of float)
      +-- DESCRIPTION (string)

The above structure consists of a root group ``/``, which contains two sub groups (``GROUP_1`` and ``GROUP_2``), one dataset (``DATASET``), and two attributes (``NUMELEMENTS``, an integer, and ``DATETIME``, a string). These groups as well as the dataset have their own attributes and sub groups.

The following code creates the above structure in Python in a file called ``foo.h5``::

  from DAL import *

  f = File("foo.h5", File.CREATE)

  # create the attributes in the root group
  numelements = AttributeInt(f, "NUMELEMENTS")
  numelements.value = 42

  datetime = AttributeInt(f, "DATETIME")
  datetime.value = "2012-05-24 15:03:52"

  # create GROUP_1 and its contents
  group1 = Group(f, "GROUP_1")
  group1.create()

  phase = AttributeComplexFloat(group1, "PHASE")
  phase.value = 1.5 + 0.5i

  subgroup1 = Group(group1, "SUBGROUP_1")
  subgroup1.create()

  stations = AttributeVString(subgroup1, "STATIONS")
  stations.value = ["CS001", "CS002", "CS003"]

  # create GROUP_2 and its contents
  group2  = Group(f, "GROUP_2")
  group2.create()

  subgroup2 = Group(group2, "SUBGROUP_2")
  subgroup2.create()

  # create DATASET and its contents
  dataset   = DatasetFloat(f, "DATASET")
  dataset.create([10,20])

Or, in C++::

  #include "dal/hdf5/File.h"
  #include "dal/hdf5/Group.h"
  #include "dal/hdf5/Attribute.h"
  #include <string>
  #include <complex>
  #include <vector>

  using namespace DAL;
  using namespace std;

  int main() {
    File f("foo.h5", File.CREATE);

    Attribute<int> numelements(f, "NUMELEMENTS");
    numelements.value = 42;

    Attribute<string> datetime(f, "DATETIME");
    datetime.value = "2012-05-24 15:03:52";

    // create GROUP_1 and its contents
    Group group1(f, "GROUP_1");
    group1.create();

    Attribute< complex<float> > phase(group1, "PHASE");
    phase.value = complex<float>(1.5, 0.5); // 1.5 + 0.5i

    Group subgroup1(group1, "SUBGROUP_1");
    subgroup1.create();

    Attribute< vector<string> > stations(subgroup1, "STATIONS");
    vector<string> v(3);
    v[0] = "CS001";
    v[1] = "CS002";
    v[2] = "CS003";
    stations.value = v;

    // create GROUP_2 and its contents
    Group group2(f, "GROUP_2");
    group2.create();

    Group subgroup2(group2, "SUBGROUP_2");
    subgroup2.create();

    // create DATASET and its contents
    Dataset<float> dataset(f, "DATASET");
    vector<size_t> dims(2);
    dims[0] = 10;
    dims[1] = 20;
    dataset.create(dims);
  }

Both the Python and C++ codes produce the same HDF5 file. Although we'll later learn how to read back data using the DAL, the ``h5dump`` inspection tool (part of the HDF5 toolset) allows easy inspection of any HDF5 file. Running ``h5dump -A foo.h5`` yields::

  (TODO)

***********************
Predefined file formats
***********************

==========
Versioning
==========

=============
Introspection
=============


*italic* **bold** ``code``

* list
* list

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

