#ifndef __H5ATTRIBUTE__
#define __H5ATTRIBUTE__

#include <string>
#include <vector>
#include <cstdlib>
#include <hdf5.h>
#include "h5typemap.h"
#include "hid_gc.h"

inline hid_t h5scalar()
{
  return H5Screate(H5S_SCALAR);
}

inline hid_t h5array( hsize_t count )
{
  return H5Screate_simple(1, &count, NULL);
}

inline hid_t h5stringType()
{
  hid_t datatype = H5Tcopy(H5T_C_S1);

  H5Tset_size(datatype, H5T_VARIABLE);

  return datatype;
}

template<typename T> inline void writeAttribute( hid_t loc, const char *name, T value, bool create )
{
  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace");

  hid_gc_noref attr(
    create ? H5Acreate2(loc, name, h5writeType<T>(), dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(loc, name, H5P_DEFAULT)
    , H5Aclose, 
    create ? "Could not create atttribute"
           : "Could not open attribute");

  H5Awrite(attr, h5nativeType<T>(), &value);
}

template<typename T> inline T readAttribute( hid_t loc, const char *name )
{
  T value;

  hid_gc_noref attr(H5Aopen(loc, name, H5P_DEFAULT), H5Aclose, "Could not open attribute");

  H5Aread(attr, h5nativeType<T>(), &value);

  return value;
}

template<typename U> inline void writeAttributeV( hid_t loc, const char *name, const std::vector<U> &value, bool create )
{
  hid_gc_noref dataspace(h5array(value.size()), H5Sclose, "Could not create simple dataspace");

  hid_gc_noref attr(
    create ? H5Acreate2(loc, name, h5writeType<U>(), dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(loc, name, H5P_DEFAULT)
    , H5Aclose,
    create ? "Could not create atttribute"
           : "Could not open attribute");

  if (H5Awrite(attr, h5nativeType<U>(), &value[0]) < 0)
    throw HDF5Exception("Could not write to attribute");
}

inline size_t sizeAttribute( hid_t loc, const char *name )
{
  hid_gc_noref attr(H5Aopen_name(loc, name), H5Aclose, "Could not open attribute");

  hid_gc_noref dataspace(H5Aget_space(attr), H5Sclose, "Could not retrieve dataspace of atttribute");

  if (!H5Sis_simple(dataspace)) {
    // attribute is a scalar
    return 1;
  }  

  const int rank = H5Sget_simple_extent_ndims(dataspace);
  if (rank < 0)
    throw HDF5Exception("Could not obtain rank of dataspace");

  std::vector<hsize_t> dims(rank);

  if (H5Sget_simple_extent_dims(dataspace, &dims[0], NULL) < 0)
    throw HDF5Exception("Could not obtain dimensions of dataspace");

  size_t nelems = 1;

  for (int i = 0; i < rank; i++) {
    nelems *= dims[i];
  }

  return nelems;
}

template<typename U> inline std::vector<U> readAttributeV( hid_t loc, const char *name )
{
  hid_gc_noref attr(H5Aopen_name(loc, name), H5Aclose, "Could not open attribute");

  std::vector<U> value(sizeAttribute(loc, name));

  if (H5Aread(attr, h5nativeType<U>(), &value[0]) < 0)
    throw HDF5Exception("Could not read attribute");

  return value;
}

// specialisations for const char *

template<> inline void writeAttribute( hid_t loc, const char *name, char const *value, bool create )
{
  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace");
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");

  hid_gc_noref attr(
    create ? H5Acreate2(loc, name, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(loc, name, H5P_DEFAULT)
    , H5Aclose,
    create ? "Could not create atttribute"
           : "Could not open attribute");

  if (H5Awrite(attr, datatype, &value) < 0)
    throw HDF5Exception("Could not write attribute");
}

template<> inline char *readAttribute( hid_t loc, const char *name )
{
  // H5Aread will allocate memory for us (use free() to free)

  char *value;

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");
  hid_gc_noref attr(H5Aopen(loc, name, H5P_DEFAULT), H5Aclose, "Could not open attribute");

  if (H5Aread(attr, datatype, &value) < 0)
    throw HDF5Exception("Could not read attribute");

  return value;
}

// specialisations for std::string

template<> inline void writeAttribute( hid_t loc, const char *name, std::string value, bool create )
{
  writeAttribute(loc, name, value.c_str(), create);
}

template<> inline std::string readAttribute( hid_t loc, const char *name )
{
  char *buf = readAttribute<char*>(loc, name);
  std::string value = buf;

  free(buf);
  return value;
}

// specialisations for std::vector<const char *>

template<> inline void writeAttributeV( hid_t loc, const char *name, const std::vector<const char *> &value, bool create )
{
  hid_gc_noref dataspace(h5array(value.size()), H5Sclose, "Could not create scalar dataspace");
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");

  hid_gc_noref attr(
    create ? H5Acreate2(loc, name, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(loc, name, H5P_DEFAULT)
    , H5Aclose);

  H5Awrite(attr, datatype, &value[0]);
}

template<> inline std::vector<char*> readAttributeV( hid_t loc, const char *name )
{
  // H5Aread will allocate memory for us (use free() to free each element)

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");
  hid_gc_noref attr(H5Aopen_name(loc, name), H5Aclose, "Could not open attribute");

  std::vector<char *> value(sizeAttribute(loc, name));

  if (H5Aread(attr, datatype, &value[0]) < 0)
    throw HDF5Exception("Could not read attribute");

  return value;
}

// specialisations for std::vector<std::string>

template<> inline void writeAttributeV( hid_t loc, const char *name, const std::vector<std::string> &value, bool create )
{
  // convert to C-style strings
  std::vector<const char *> cstrs(value.size());
  for (unsigned i = 0; i < value.size(); i++)
    cstrs[i] = value[i].c_str();

  writeAttributeV(loc, name, cstrs, create);
}

template<> inline std::vector<std::string> readAttributeV( hid_t loc, const char *name )
{
  // convert from C-style strings
  std::vector<char *> cstrs = readAttributeV<char *>(loc, name);
  std::vector<std::string> value(cstrs.size());

  for (unsigned i = 0; i < value.size(); i++) {
    value[i] = cstrs[i];
    free(cstrs[i]);
  }

  return value;
}

#endif

