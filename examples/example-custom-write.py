#!/usr/bin/env python
import dal

# create the file
f = dal.File("example-custom-write_file.h5", dal.File.CREATE, "DOC_VERSION")

# create an attribute
a = dal.AttributeString(f, "MY_ATTRIBUTE")
a.value = "hello world!"

# create and destroy a second attribute
b = dal.AttributeString(f, "FAULTY_ATTRIBUTE")
assert b.value is None

b.value = "foo"
assert b.value == "foo"

del b.value
assert b.value is None

# create a dataset
d = dal.DatasetComplexFloat(f, "MY_DATASET")
d.create([4,4])

# insert some data points
d.setScalar([0,0],1+2j)
d.setScalar([1,0],2+3j)
d.setScalar([0,1],3+4j)

# flushing is not needed, but can be done explicitly
f.flush()

