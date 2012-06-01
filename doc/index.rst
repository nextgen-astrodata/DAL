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

The DAL was created for two reasons:

* You do not want to deal with the HDF5 library directly. While the HDF5 library is very powerful, its use is also quite technical.
* To wrap standardised HDF5 file formats, and to provide higher-level functionality on top of them.

============
Installation
============

For now, please read INSTALL.txt.

=====
Usage
=====

To work with the DAL, a (very) basic understanding of HDF5 is required. An HDF5 file encodes an hierarchical structure consisting of a set of *groups*. Each group has a name, and can have sub groups, as well as a set of key-value pairs called *attributes*. Finally, a *dataset* is a specialised group which has a large array of data associated with it. An HDF5 file itself starts with a so-called *root group*, named ``/``. All of these elements in a file are typically represented by a tree.

The rest of this section will provide an example of how you can read and write such structures using the DAL. Subsequent sections will cover the used functionality in more detail.

Example HDF5 structure
----------------------

Consider the following example structure of groups, attributes and datasets, annotated with their respective data type::

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

Creating the structure using the DAL
------------------------------------

The following code creates the above structure in Python in a file called ``foo.h5``::

  from DAL import *

  f = File("foo.h5", File.CREATE)

  # create the attributes in the root group
  numelements = AttributeInt(f, "NUMELEMENTS")
  numelements.value = 42

  datetime = AttributeString(f, "DATETIME")
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

Or, in C++, producing the same HDF5 file::

  #include "dal/hdf5/File.h"
  #include "dal/hdf5/Group.h"
  #include "dal/hdf5/Dataset.h"
  #include "dal/hdf5/Attribute.h"
  #include <string>
  #include <complex>
  #include <vector>

  using namespace DAL;
  using namespace std;

  int main() {
    File f("foo.h5", File::CREATE);

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
    vector<ssize_t> dims(2);
    dims[0] = 10;
    dims[1] = 20;
    dataset.create(dims);
  }

Reading the structure using HDF5 tools
--------------------------------------

Although we'll later learn how to read back data using the DAL, the ``h5dump`` inspection tool (part of the HDF5 toolset) allows easy inspection of any HDF5 file. Running ``h5dump -A foo.h5`` yields::

  HDF5 "foo.h5" {
  GROUP "/" {
     ATTRIBUTE "DATETIME" {
        DATATYPE  H5T_STRING {
              STRSIZE H5T_VARIABLE;
              STRPAD H5T_STR_NULLTERM;
              CSET H5T_CSET_ASCII;
              CTYPE H5T_C_S1;
           }
        DATASPACE  SCALAR
        DATA {
        (0): "2012-05-24 15:03:52"
        }
     }
     ATTRIBUTE "NUMELEMENTS" {
        DATATYPE  H5T_STD_I32LE
        DATASPACE  SCALAR
        DATA {
        (0): 42
        }
     }
     DATASET "DATASET" {
        DATATYPE  H5T_IEEE_F32LE
        DATASPACE  SIMPLE { ( 10, 20 ) / ( 10, 20 ) }
     }
     GROUP "GROUP_1" {
        ATTRIBUTE "PHASE" {
           DATATYPE  H5T_COMPOUND {
              H5T_IEEE_F32LE "real";
              H5T_IEEE_F32LE "imag";
           }
           DATASPACE  SCALAR
           DATA {
           (0): {
                 1.5,
                 0.5
              }
           }
        }
        GROUP "SUBGROUP_1" {
           ATTRIBUTE "STATIONS" {
              DATATYPE  H5T_STRING {
                    STRSIZE H5T_VARIABLE;
                    STRPAD H5T_STR_NULLTERM;
                    CSET H5T_CSET_ASCII;
                    CTYPE H5T_C_S1;
                 }
              DATASPACE  SIMPLE { ( 3 ) / ( 3 ) }
              DATA {
              (0): "CS001", "CS002", "CS003"
              }
           }
        }
     }
     GROUP "GROUP_2" {
        GROUP "SUBGROUP_2" {
        }
     }
  }
  }

which, albeit verbose, shows the entire structure as our program defined it. 

Reading the structure using the DAL
-----------------------------------

The individual data can also be read using the DAL, of course. For example, the following programs extract the values of a few attributes, as well as a few scalars from the dataset from ``foo.h5``. In Python::

  from DAL import *

  f = File("foo.h5", File.READ)

  # reference the attributes in the root group
  numelements = AttributeInt(f, "NUMELEMENTS")
  print "numelements =", numelements.value

  datetime = AttributeString(f, "DATETIME")
  print "datetime =", datetime.value

  # reference GROUP_1 and its contents
  group1 = Group(f, "GROUP_1")

  phase = AttributeComplexFloat(group1, "PHASE")
  print "group1.phase =", phase.value

  subgroup1 = Group(group1, "SUBGROUP_1")

  stations = AttributeVString(subgroup1, "STATIONS")
  print "group1.subgroup1.stations =", stations.value

  # reference DATASET and its contents
  dataset   = DatasetFloat(f, "DATASET")
  print "dataset has", dataset.ndims(), "dimensions"
  print "dataset[0][0] =", dataset.getScalar([0,0])

Yielding::

  numelements = 42
  datetime = 2012-05-24 15:03:52
  group1.phase = (1.5+0.5j)
  group1.subgroup1.stations = ('CS001', 'CS002', 'CS003')
  dataset has 2 dimensions
  dataset[0][0] = 0.0

In C++::

  #include "dal/hdf5/File.h"
  #include "dal/hdf5/Group.h"
  #include "dal/hdf5/Dataset.h"
  #include "dal/hdf5/Attribute.h"
  #include <string>
  #include <complex>
  #include <vector>
  #include <iostream>

  using namespace DAL;
  using namespace std;

  int main() {
    File f("foo.h5", File::READ);

    Attribute<int> numelements(f, "NUMELEMENTS");
    cout << "numelements = " << numelements.value << endl;

    Attribute<string> datetime(f, "DATETIME");
    cout << "datetime = " << datetime.value << endl;

    // reference GROUP_1 and its contents
    Group group1(f, "GROUP_1");

    Attribute< complex<float> > phase(group1, "PHASE");
    cout << "group1.phase = " << phase.value << endl;

    Group subgroup1(group1, "SUBGROUP_1");

    Attribute< vector<string> > stations(subgroup1, "STATIONS");
    vector<string> stations_val = stations.value;
    cout << "group1.subgroup1.stations = (";
    for (size_t i = 0; i < stations_val.size(); i++) {
      if (i > 0) cout << ", ";
      cout << "'" << stations_val[i] << "'";
    }
    cout << ")" << endl;

    // create DATASET and its contents
    Dataset<float> dataset(f, "DATASET");
    cout << "dataset has " << dataset.ndims() << " dimensions" << endl;
    vector<size_t> pos(2);
    pos[0] = 0;
    pos[1] = 0;
    cout << "dataset[0][0] = " << dataset.getScalar(pos) << endl;
  }

Yielding::

  numelements = 42
  datetime = 2012-05-24 15:03:52
  group1.phase = (1.5,0.5)
  group1.subgroup1.stations = ('CS001', 'CS002', 'CS003')
  dataset has 2 dimensions
  dataset[0][0] = 0

*********
Basic API
*********

====
File
====

The File class is typically the first class to be instantiated for accessing an HDF5 file. To open a file for reading, use the following construct::

  [C++]    File f( filename, File::READ );
  [Python] f = File( filename, File.READ )

Similarly, to create a new HDF5 file, use:

  [C++]    File f( filename, File::CREATE );
  [Python] f = File( filename, File.CREATE )


.. class:: File

   .. attribute:: READ
                  READWRITE
                  CREATE

   Various file modes to be used in the constructor.

   .. method:: [C++] File( const std::string &filename, enum fileMode mode )
               [Python] __init__( filename, mode )

   Opens or creates an HDF5 file. 

   .. method:: [C++] void flush()
               [Python] flush()

   Commits any changes to disk.

   blablabla

=====
Group
=====

.. autoclass:: DAL.Group
   :members:

=======
Dataset
=======

=========
Attribute
=========

**********
Exceptions
**********

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

