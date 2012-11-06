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

As a very brief example, the following code creates an Common LOFAR Attributes File (= a LOFAR file format), and sets its observation ID attribute, which is a string::

  [C++]
  #include <dal/lofar/CLA_File.h>

  int main {
    dal::CLA_File f("example.h5", dal::File::CREATE);
    f.observationID().value = "12345";
  }

  [Python]
  import dal

  f = dal.CLA_File("example.h5", dal.File.CREATE)
  f.observationID().value = "12345"

And the following code reads it back out::

  [C++]
  #include <dal/lofar/CLA_File.h>
  #include <iostream>

  int main {
    dal::CLA_File f("example.h5");
    cout << f.observationID().value << endl;
  }

  [Python]
  import dal

  f = dal.CLA_File("example.h5")
  print f.observationID().value

============
Installation
============

For now, please read the file INSTALL.

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

  from dal import *

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

  using namespace dal;
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

  from dal import *

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

  using namespace dal;
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

The following sections will explain basic functionality offered by the DAL to work with both HDF5 files in general, and with predefined file formats in particular. To keep the code examples short, they all assume a context in which HDF5 classes have been imported::

  [C++]
  #include <dal/hdf5/File.h>
  ... include necessary DAL headers ...
  #include <dal/hdf5/Attribute.h>
  #include <iostream>

  using namespace dal;
  using namespace std;

  int main() {
    ... insert example here ...
  }

  [Python]
  from dal import *

  ... insert example here ...

Also, most examples assume that files and variables created by previous examples are still available.

====
File
====

The File class is typically the first class to be instantiated for accessing an HDF5 file. To open a file for reading, use the following construct::

  [C++]    File f( filename, File::READ );
  [Python] f = File( filename, File.READ )

Similarly, to create a new HDF5 file, use::

  [C++]    File f( filename, File::CREATE );
  [Python] f = File( filename, File.CREATE )

The file is closed when all object references to it (by a File object or anything else) are destructed.

.. note::

  Thread safety: DAL, like the HDF5 library, is not thread safe. Please use your own locks surrounding concurrent access to the same file.

=====
Group
=====

The Group class is used to create a tree structure inside an HDF5 file. It only needs to know in which group (or file) to address the new group, and under what name. For example, to address a group ``GROUPNAME`` in a file ``f``::

  [C++]    Group g( f, "GROUPNAME" );
  [Python] g = Group( f, "GROUPNAME" )

And similarly, to address a subgroup ``SUBGROUPNAME`` in that group ``g``, do::

  [C++]    Group s( g, "SUBGROUPNAME" );
  [Python] s = Group( g, "SUBGROUPNAME" )

Note that the addressed group does not need to exist. Once we have a Group object, we can test whether it exists, and create the Group if we want to (and if the file was opened to allow writing)::

  [C++]
  if (!g.exists())
    g.create();

  [Python]
  if not g.exists():
    g.create()

If we're just reading the file, the Group will automatically be opened once we access its content. Should the Group not exist when we do access its contents, an exception will be thrown.

.. note::

  The File class is a Group, so it shares the same functionality. A File however does always exist, because the File constructor will throw an exception if the file cannot be opened.

=========
Attribute
=========

An Attribute is a simple key-value pair that can be stored anywhere in a Group. It is defined by its name and type, and the group or file which it is in. For example, to address an attribute ``MYSTRING`` in a file ``f`` of type ``string``::

  [C++]    Attribute<string> a( f, "MYSTRING" );
  [Python] a = AttributeString( f, "MYSTRING" )

Again, the file ``f`` can also be substituted for a group ``g``, if the attribute is stored below the top layer. Again, note that the attribute does not necessarily exist. Although we can test for existence using the ``exists()`` member function, the Attribute class allows us short cuts in reading and writing through the ``value`` property. Assigning a value to this property sets the attribute, creating it if needed, and reading the ``value`` property returns the value of the attribute. For example, use::

  [C++]    a.value = "hello world";
  [Python] a.value = "hello world"

to (create and) set attribute ``a``. To read it, simply do::

  [C++]    cout << a.value << endl;
  [Python] print a.value

.. note::

  In C++, an exception will be thrown if you try to read an attribute that does not exist. In Python, the special value ``None`` is returned instead.

The previous examples only addressed attributes of type ``string``/``str``. The following basic value types are supported by the DAL, along with their C++ and Python class name:

+------------------------+-----------------------------------+------------------+----------------------------+
| C++ data type          | C++ Attribute class               | Python data type | Python Attribute class     |
+========================+===================================+==================+============================+
| ``int``                | ``Attribute<int>``                | ``int``          | ``AttributeInt``           |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``unsigned``           | ``Attribute<unsigned>``           | ``int``          | ``AttributeUInt``          |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``long``               | ``Attribute<long>``               | ``int``          | ``AttributeLong``          |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``unsigned long``      | ``Attribute<unsigned long>``      | ``int``          | ``AttributeULong``         |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``long long``          | ``Attribute<long long>``          | ``int``          | ``AttributeLongLong``      |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``unsigned long long`` | ``Attribute<unsigned long long>`` | ``int``          | ``AttributeULongLong``     |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``float``              | ``Attribute<float>``              | ``float``        | ``AttributeFloat``         |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``double``             | ``Attribute<double>``             | ``float``        | ``AttributeDouble``        |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``complex<float>``     | ``Attribute< complex<float> >``   | ``complex``      | ``AttributeComplexFloat``  |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``complex<double>``    | ``Attribute< complex<double> >``  | ``complex``      | ``AttributeComplexDouble`` |
+------------------------+-----------------------------------+------------------+----------------------------+
| ``string``             | ``Attribute<string>``             | ``str``          | ``AttributeString``        |
+------------------------+-----------------------------------+------------------+----------------------------+

An attribute can also encode a list of values of one of the data types in the previous table. Even though the corresponding Python type is always ``list``, the DAL will require and supply only lists with values that can be converted to the corresponding C++ data type:

+-----------------------+---------------------------------+------------------+------------------------+
| C++ data type         | C++ Attribute class             | Python data type | Python Attribute class |
+=======================+=================================+==================+========================+
| ``vector<int>``       | ``Attribute< vector<int> >``    | ``list``         | ``AttributeVInt``      |
+-----------------------+---------------------------------+------------------+------------------------+
| ``vector<string>``    | ``Attribute< vector<string> >`` | ``list``         | ``AttributeVString``   |
+-----------------------+---------------------------------+------------------+------------------------+
| ...                   | ...                             | ...              | ...                    |
+-----------------------+---------------------------------+------------------+------------------------+
| ``vector<XXX>``       | ``Attribute< vector<XXX> >``    | ``list``         | ``AttributrVXXX``      |
+-----------------------+---------------------------------+------------------+------------------------+

For example, to create an attribute containing a list of strings::

  [C++]
  Attribute< vector<string> > a( f, "MYSTRINGLIST" );
  vector<string> values(2);
  values[0] = "one";
  values[1] = "two";
  a.value = values;

  [Python]
  a = AttributeVString( f, "MYSTRINGLIST" )
  a.value = ["one", "two"]

.. note::

  User-defined attribute types, such as tuples, can be added by extending DAL in C++ (see ``hdf5/types/h5tuple.h``, ``lofar/CommonTuples.h``, as well as the accompanying ``.i`` files which marshall the tuples from C++ to Python).

=======
Dataset
=======

A Dataset is a special Group that has a (multidimensional) data set attached. The data set can have any number of dimensions, and be of any size. All of its elements have to be of the same type, however. Also, because a Dataset is a Group, a data set can have its own attributes and sub groups attached. The data type stored in the data set has to be known from the start. For example, to address a data set called ``DATASET`` of type ``float`` stored directly in File ``f``, use::

  [C++]    Dataset<float> d( f, "DATASET" );
  [Python] d = DatasetFloat( f, "DATASET" )

Again, we can test using the ``exists()`` method whether the data set exists. The following code creates a 10x20 data set::

  [C++]
  if (!d.exists()) {
    vector<ssize_t> dimensions(2);
    dimensions[0] = 10;
    dimensions[1] = 20;
    d.create( dimensions );
  }  

  [Python]
  if not d.exists():
    d.create( [10, 20] )

The DAL provides several functions to query the dimensionality of an existing data set::

  [C++]
  const size_t rank = d.ndims();
  const vector<ssize_t> dims = d.dims();

  for (size_t i = 0; i < rank; i++)
    cout << "Dimension " << i << " has size " << dims[i] << endl;

  [Python]
  rank = d.ndims()
  dims = d.dims()

  for i in range(rank):
    print "Dimension %u has size %u" % (i, dims[i])

Individual elements can be set using the ``getScalar`` and ``setScalar`` methods. For example, to read and write the element at [1,2]::

  [C++]
  const vector<size_t> pos(2);
  pos[0] = 1;
  pos[1] = 2;

  cout << "Element at [1,2] = " << d.getScalar(pos) << endl;
  d.setScalar(pos, 42.0);
  cout << "Element at [1,2] = " << d.getScalar(pos) << endl;

  [Python]
  pos = [1,2]

  print "Element at [1,2] = %.2f" % d.getScalar(pos)
  d.setScalar(pos, 42.0)
  print "Element at [1,2] = %.2f" % d.getScalar(pos)

The data set can also be sliced to access blocks of elements in a single call, which is a lot faster than accessing each element individually. In C++, data is referred to using raw pointers and providing the sizes of the slice. In Python, the numpy library is used to represent raw data. The example below extracts a 2D slice of data from our data set using the ``get2D`` and ``set2D`` methods. It reads and writes a block of size 3x3 starting at location [1,2] in the data set::

  [C++]
  const vector<size_t> pos(2);
  pos[0] = 1;
  pos[1] = 2;

  cout << "Element [1,2] = " << d.getScalar(pos) << endl;

  // a pointer to any data set will do, for instance, these all work:
  //
  // data type:                         pointer to first element:
  // -----------------------------------------------------
  // float data[3][3]                   &data[0][0]
  // float data[3 * 3]                  &data[0]
  // vector<float> data(3 * 3)          &data[0]
  // float *data = new float[3 * 3]     data
  float data[3][3];

  d.get2D( pos, &data[0][0], 3, 3 );
  data[0][0] = 1.0;
  d.set2D( pos, &data[0][0], 3, 3 );

  cout << "Element [1,2] = " << d.getScalar(pos) << endl;

  [Python]
  pos = [1,2]

  print "Element at [1,2] = %.2f" % d.getScalar(pos)

  # we need a numpy array for data storage; the dataset provides
  # us with the numpy data type that we need to use

  import numpy
  data = numpy.zeros((3, 3), dtype=d.dtype)

  d.get2D(pos, data)

  data[1][1] = 1.0
  d.set2D(pos, data)

  print "Element at [1,2] = %.2f" % d.getScalar(pos)

**********
Exceptions
**********

Almost all of the DAL functions can throw an exception in case of an error. The following exceptions can be thrown:

+-------------------+-----------------------+-------------------------+
| C++ exception     | Python exception      | Meaning                 |
+===================+=======================+=========================+
| ``DALException``  | ``RuntimeError``      | Something went wrong    |
+-------------------+-----------------------+-------------------------+
| ``HDF5Exception`` | ``dal.HDF5Exception`` | HDF5 threw an error     |
+-------------------+-----------------------+-------------------------+
| ``DALValueError`` | ``ValueError``        | Invalid parameter value |
+-------------------+-----------------------+-------------------------+
| ``DALIndexError`` | ``IndexError``        | Out-of-bounds access    |
+-------------------+-----------------------+-------------------------+

The above classes adhere to the following class hierarchy in C++::

  DALException
  +-- HDF5Exception
  +-- DALValueError
      +-- DALIndexError

All exceptions carry an error message (``e.what()`` in C++ and ``str(e)`` in Python) explaining what went wrong.

=========================
HDF5Exception error stack
=========================

The HDF5Exception indicates an error generated by the HDF5 library used by DAL. It carries a copy of the error stack inside the HDF5 library, which provides a more detailed explanation of what was attempted and why it failed. The error stack of an HDF5Exception can be accessed as follows::

  [C++]
  try {
    File f("non_existing_file.h5");
  } catch( HDF5Exception &e ) {
    // print the error message
    cout << e.what() << endl;

    // print a summary
    cout << e.stackSummary() << endl;

    // inspect each stack line individually -- each line has both a shortDesc() and a longDesc()
    for( vector<HDF5StackLine>::const_iterator i = e.stack.stack.begin(); i != e.stack.stack.end(); i++ )
      cout << (*i).shortDesc() << endl;
  }

  [Python]
  try:
    f = File("non_existing_file.h5")
  except HDF5Exception, e:
    # print the error message
    print e

    # print a summary

    # inspect each stack line individually -- each line has both a shortDesc() and a longDesc()
    for i in e.stack:
      print i.shortDesc()


***********************
Predefined file formats
***********************

The DAL allows wrapping *predefined file formats*, of which the group structure and attribute names and types are known. For example, DAL defines the Common LOFAR Attributes File format, which is accessed through the ``CLA_File`` class. This file format is simple, as it happens to only define attributes in the root group, for example the observation ID. The following example creates a CLA File and sets the observationID::

  [C++]
  CLA_File f("example.h5", File::CREATE);
  f.observationID().value = "12345";

  [Python]
  f = CLA_File("example.h5", File.CREATE)
  f.observationID().value = "12345"

The way this works is that ``CLA_File.observationID`` actually wraps the appropriate Attribute class for us. It indirectly returns::

  Attribute<string>(f, "OBSERVATION_ID")

without requiring the user to know the actual key name and type (or allowing the user to make a mistake in supplying them). The same construct is used to create groups and datasets as defined in a file format, allowing robust and reliable access to files adhering to a specified standard.

A predefined file formats class can be extended to maintain more meta data than just the element names and types. The next sections will talk about how multiple versions of the same file format can be handled properly, and how attribute introspection can be done to aid writing file format validators.

==========
Versioning
==========

File formats evolve, and typically have a version number attached to document its evolution. The DAL provides the basic tools to store and retrieve version information. First, each file can have a version associated with it. The following code creates a new HDF5 file, and sets its version number to 1.0.0::

  [C++]
  File f("example.h5", File::CREATE);
  f.setFileVersion(VersionType("1.0.0"));

  [Python]
  f = File("example.h5", File.CREATE)
  f.setFileVersion(VersionType("1.0.0"))

.. note::

  The version number is stored in a string attribute called ``VERSION`` in the root group.

Once the version number is set, it can be retrieved through the ``fileVersion`` call, which is actually available through any attribute, group, and dataset object::

  [C++]
  File f("example.h5", File::READWRITE);
  cout << f.fileVersion() << endl;

  Group g(f, "MYGROUP");
  g.create();
  cout << g.fileVersion() << endl;

  [Python]
  f = File("example.h5", File.READWRITE)
  print f.fileVersion()

  g = Group(f, "MYGROUP")
  g.create()
  print g.fileVersion()

.. note::

  See the class documentation on ``VersionType`` for the interface VersionType allows to compare versions and to retrieve the individual version components (major, minor, release).

The version number is primarily used to document the specification version that was used to generate the file. However, the DAL also allows any attribute, group, or dataset to be annotated with a minimal required version::

  [C++]
  File f("example.h5", File::READ);
  Group g(f, "MYGROUP");

  g.minVersion = VersionType("2.0.0");

  [Python]
  f = File("example.h5", File.READ)
  g = Group(f, "MYGROUP")

  g.minVersion = VersionType("2.0.0")

In the above code, we read a file with a version that was previously set to 1.0.0, and refer to a group for which we set the minimally required version to 2.0.0 (note that whether the group actually exists is not relevant for this example). Once the above configuration is set up, we can query whether group ``g`` is actually supported by the file we've just opened. The following relations will hold::

  [C++]
  g.supported() == false
  g.minVersion <= g.fileVersion()

  [Python]
  g.supported() == False
  g.minVersion <= g.fileVersion()

In a predefined file format implemented through the DAL, one can thus annotate each attribute/group/dataset with the minimal version required for that element. Doing so allows anyone working with the documents to verify what elements should and should not be present in the file, based on the file's version.

.. note::

  Versioning information is currently not enforced. It is thus possible to, for example, create an element defined in version 2.0.0 inside a file that is set up as version 1.0.0.

=============
Introspection
=============

Classes that wrap predefined file formats can be written such that each group maintains a list of all of the attributes that should be present in files conforming to the file format. This list of *registered* attributes can be introspected, in order to iteratively process all required attributes. The ``nodeNames()`` method present in each Group provides a list of attribute names that the class knows about. The ``getNode()`` method subsequently returns a requested attribute as the appropriate type::

  [C++]
  CLA_File f("example.h5");

  cout << setw(40) << "HDF5 Node name" << "   supp" << " exists" << "  valid" << endl;

  const vector<string> nodeNames = f.nodeNames();

  for (vector<string>::const_iterator i = nodeNames.begin(); i != nodeNames.end(); i++) {
    string name = *i;

    // cast to a common base class
    AttributeBase &node = f.getNode(name);

    // whether the attribute is supported by the version of this file.
    // i.e. node.minVersion <= node.fileVersion()
    bool supported = node.supported();

    // whether the node exists in the file
    bool exists = node.exists();

    // whether the node is valid (exists and is (or can be converted to) the correct type)
    bool valid = node.valid();

    // due to C++'s static typing, we can't retrieve the value if we don't know the attribute type
    // ??? value = node.value;

    cout << setw(40) << name << setw(7) << supported << setw(7) << exists << setw(7) << valid << endl;

    print "%40s %6s %6s %6s %s" % (n, supported, exists, valid, node.value)
  }

  [Python]
  f = CLA_File("example.h5")

  print "%40s %6s %6s %6s %s" % ("HDF5 Node name", "supp", "exists", "valid", "value")

  for name in f.nodeNames():
    node = f.getNode(name)

    # whether the attribute is supported by the version of this file.
    # i.e. node.minVersion <= node.fileVersion()
    supported = node.supported()

    # whether the node exists in the file
    exists = node.exists()

    # whether the node is valid (exists and is (or can be converted to) the correct type)
    valid = node.valid()

    # the value of this node (None if the attribute does not exist)
    value = node.value

    print "%40s %6s %6s %6s %s" % (n, supported, exists, valid, node.value)


===============================
Supporting your own file format
===============================

TODO for now, but do look at ``lofar/BF_File.h`` and ``lofar/TBB_File.h`` for example implementations.

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

