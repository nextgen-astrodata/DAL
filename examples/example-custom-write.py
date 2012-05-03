import DAL

# create the file
f = DAL.HDF5FileBase("foo.h5", DAL.HDF5FileBase.CREATE)

# create an attribute
a = DAL.AttributeString(f.group(), "MY_ATTRIBUTE")
a.create()
a.set("hello world!")

# create and destroy a second attribute
b = DAL.AttributeString(f.group(), "FAULTY_ATTRIBUTE")
b.create()
b.set("hello world!")
b.remove()

# create a dataset
d = DAL.HDF5DatasetBaseComplexFloat(f.group(), "MY_DATASET")
d.create([4,4],[4,4])

# insert some data points
d.setScalar([0,0],1+2j)
d.setScalar([1,0],2+3j)
d.setScalar([0,1],3+4j)

# flushing is not needed, but can be done explicitly
f.flush()

