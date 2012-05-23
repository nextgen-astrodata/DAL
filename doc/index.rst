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

The DAL, or Data Access Library, is a library to read and write astronomical data sets. More specifically, the DAL provides an interface in both C++ and Python to access various astronomical file formats that use HDF5, but also allows you to define your custom HDF5 structure on the fly.

====
HDF5
====

To work with the DAL, a (very) basic understanding of HDF5 is required. An HDF5 file encodes an hierarchical structure of groups, attributes, and datasets.

Groups
------

At the core of the HDF5 file format is the *group*, which is a generic container of sub structures. The HDF5 file itself represents a so-called *root group*, which can contain any number of sub groups. Each group in turn can contain its own sub groups, allowing a nearly infinite nesting. Each group has a name (the root group is called ``/``).

For example, if we have an HDF5 file that contains two groups, each of which contains one sub group, we can represent such a structure as follows::

  /
  +-- GROUP_1
  |   +-- SUBGROUP_1
  |
  +-- GROUP_2
      +-- SUBGROUP_2

The code to create a file ``foo.h5`` with such a structure is (in Python)::

  from DAL import *

  f = File("foo.h5", File.CREATE)

  group1    = Group(f,      "GROUP_1").create()
  subgroup1 = Group(group1, "SUBGROUP_1").create()

  group2    = Group(f,      "GROUP_2").create()
  subgroup2 = Group(group2, "SUBGROUP_2").create()

and in C++::

  #include "dal/hdf5/File.h"
  #include "dal/hdf5/Group.h"

  using namespace DAL;

  int main() {
    File f("foo.h5", File.CREATE);

    Group group1    = Group(f,      "GROUP_1"),create();
    Group subgroup1 = Group(group1, "SUBGROUP_1").create();

    Group group2    = Group(f,      "GROUP_2"),create();
    Group subgroup2 = Group(group2, "SUBGROUP_2").create();
  }

The HDF5 tool ``h5dump`` is ideal to quickly inspect any HDF5 file, and will reveal that ``foo.h5`` indeed contains the described structure::

  $ h5dump foo.h5
  HDF5 "foo.h5" {
  GROUP "/" {
     GROUP "GROUP_1" {
        GROUP "SUBGROUP_1" {
        }
     }
     GROUP "GROUP_2" {
        GROUP "SUBGROUP_2" {
        }
     }
  }
  }

Attributes
----------

Each group, including the root group, can contain *attributes*, which represent (small) data values, such as ints, floats, strings, lists, tuples, etc. The DAL allows the user to define their own types as well. For example, we can alter the previous group structure as follows::

  /
  +-- MY_INTEGER (int = 42)
  +-- MY_STRING  (string = "hello world")
  |
  +-- GROUP_1
      +-- MY_COMPLEXNUMBER (complex float = 1 + 2i)
      +-- SUBGROUP_1
          +-- MY_STRINGLIST (list of strings = ["foo","bar"])

The code to create a file ``foo.h5`` with such a structure is (in Python)::

  from DAL import *

  f = File("foo.h5", File.CREATE)

  my_integer = AttributeInt(f, "MY_INTEGER")
  my_integer.value = 42

  my_string  = AttributeString(f, "MY_STRING")
  my_string.value = "hello world"

  group1    = Group(f,      "GROUP_1").create()
  my_complexnumber = AttributeComplexFloat(group1, "MY_COMPLEXNUMBER")
  my_complexnumber.value = 1 + 2i

  subgroup1 = Group(group1, "SUBGROUP_1").create()
  my_stringlist = AttributeVString(subgroup1, "MY_STRINGLIST")
  my_stringlist.value = ["foo", "bar"]

and in C++::

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

    Attribute<int> my_integer(f, "MY_INTEGER");
    f.value = 42;

    Attribute<string> my_string(f, "MY_STRING");
    f.value = "hello world";

    Group group1 = Group(f, "GROUP_1"),create();
    Attribute< complex<float> > my_complexnumber(group1, "MY_COMPLEXNUMBER");
    my_complexnumber.value = complex<float>(1, 2); // 1 + 2i

    Group subgroup1 = Group(group1, "SUBGROUP_1").create();
    Attribute< vector<string> > my_stringlist(subgroup1, "MY_STRINGLIST");
    vector<string> v(2);
    v[0] = "foo";
    v[1] = "bar";
    my_stringlist.value = v;
  }

The HDF5 tool ``h5dump`` is ideal to quickly inspect any HDF5 file, and will reveal that ``foo.h5`` indeed contains the described structure::

  $ h5dump foo.h5
  (TODO)

Datasets
--------

Finally, HDF5 has special groups called *datasets*. A dataset is a group accompanied by a (large) array of data values. The array can have any number of dimensions and any size. Because a dataset is a group, it can contain its own attributes as well as sub groups. For example, if we extend the group structure with a dataset, we get::

  /
  +-- MY_INTEGER (int)
  +-- MY_STRING  (string)
  |
  +-- GROUP_1
  |   +-- MY_COMPLEXNUMBER (complex float)
  |   +-- SUBGROUP_1
  |       +-- MY_STRINGLIST (list of strings)
  |
  +-- GROUP_2
  |   +-- SUBGROUP_2
  |
  +-- DATASET (array[10][20] of float)

*italic* **bold** ``code``

* list
* list

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

