#include "hdf5/HDF5Attribute.h"
#include "hdf5/types/h5typemap.h"
#include <cstdlib>
#include <hdf5.h>

namespace DAL {

inline bool AttributeBase::exists() const
{
  return H5Aexists(parent, _name.c_str()) > 0;
}

inline bool AttributeBase::valid() const
{
  return exists();
}

inline void AttributeBase::remove() const {
  if (H5Adelete(parent, _name.c_str()) < 0)
    throw HDF5Exception("Could not delete attribute " + _name);
}

inline size_t AttributeBase::size() const
{
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  hid_gc_noref dataspace(H5Aget_space(attr), H5Sclose, "Could not retrieve dataspace for attribute " + _name);

  if (!H5Sis_simple(dataspace)) {
    // attribute is a scalar
    return 1;
  }  

  const int rank = H5Sget_simple_extent_ndims(dataspace);
  if (rank < 0)
    throw HDF5Exception("Could not obtain rank of dataspace for attribute " + _name);

  std::vector<hsize_t> dims(rank);

  if (H5Sget_simple_extent_dims(dataspace, &dims[0], NULL) < 0)
    throw HDF5Exception("Could not obtain dimensions of dataspace for attribute " + _name);

  size_t nelems = 1;

  for (int i = 0; i < rank; i++) {
    nelems *= dims[i];
  }

  return nelems;
}

template<typename T> AttributeValue<T>& AttributeValue<T>::operator=( const T& value )
{
  if (!attr.exists())
    attr.create();

  attr.set(value);

  return *this;
}

template<typename T> AttributeValue<T>& AttributeValue<T>::operator=( const AttributeValue<T>& value )
{
  if (this == &value)
    return *this;

  return *this = static_cast<T>(value);
}

template<typename T> AttributeValue<T>::operator T() const
{
  // We can't gracefully return if the attribute does not exist,
  // because there is no safe default value for T. Note that in
  // Python, we return None in that case.
  return attr.get();
}

template<typename T> void AttributeValue<T>::del() const
{
  if (attr.exists())
    attr.remove();
}

template<typename T> std::ostream& operator<<(std::ostream &out, const AttributeValue<T> &val)
{
  return out << static_cast<T>(val);
}

static inline hid_t h5scalar()
{
  return H5Screate(H5S_SCALAR);
}

static inline hid_t h5array( hsize_t count )
{
  return H5Screate_simple(1, &count, NULL);
}

static inline hid_t h5stringType()
{
  const hid_t datatype = H5Tcopy(H5T_C_S1);

  H5Tset_size(datatype, H5T_VARIABLE);

  return datatype;
}

// generic versions
template<typename T> inline Attribute<T>& Attribute<T>::create()
{
  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace for attribute " + _name);

  hid_gc_noref attr(H5Acreate2(parent, _name.c_str(), h5typemap<T>::attributeType(), dataspace, H5P_DEFAULT, H5P_DEFAULT), H5Aclose, "Could not create attribute " + _name);

  return *this;
}

template<typename T> inline void Attribute<T>::set( const T &value )
{
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  if (H5Awrite(attr, h5typemap<T>::memoryType(), &value) < 0)
    throw HDF5Exception("Could not write attribute " + _name);
}

template<typename T> inline T Attribute<T>::get() const
{
  T value;

  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  if (H5Aread(attr, h5typemap<T>::memoryType(), &value) < 0)
    throw HDF5Exception("Could not read attribute" + _name);

  return value;
}

template<typename T> inline bool Attribute<T>::valid() const
{
  if (!exists())
    return false;

  try {
    (void)get();
  } catch (HDF5Exception &e) {
    return false;
  }

  return true;
}

template<typename T> inline Attribute< std::vector<T> >& Attribute< std::vector<T> >::create( size_t length )
{
  if (length == 0)
    throw DALValueError("Cannot store empty arrays for attribute " + _name);

  hid_gc_noref dataspace(h5array(length), H5Sclose, "Could not create simple dataspace for attribute " + _name);

  hid_gc_noref attr(H5Acreate2(parent, _name.c_str(), h5typemap<T>::attributeType(), dataspace, H5P_DEFAULT, H5P_DEFAULT), H5Aclose, "Could not create attribute " + _name);

  return *this;
}

template<typename T> inline void Attribute< std::vector<T> >::set( const std::vector<T> &value )
{
  if (value.empty())
    throw DALValueError("Cannot store empty arrays for attribute " + _name);

  if (size() != value.size()) {
    // recreate the attribute to change the vector length on disk
    remove();
    create(value.size());
  }
    
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  if (H5Awrite(attr, h5typemap<T>::memoryType(), &value[0]) < 0)
    throw HDF5Exception("Could not write to attribute " + _name);
}

template<typename T> inline std::vector<T> Attribute< std::vector<T> >::get() const
{
  hid_gc_noref attr(H5Aopen_name(parent, _name.c_str()), H5Aclose, "Could not open attribute " + _name);

  std::vector<T> value(size());

  if (H5Aread(attr, h5typemap<T>::memoryType(), &value[0]) < 0)
    throw HDF5Exception("Could not read attribute " + _name);

  return value;
}

template<typename T> inline bool Attribute< std::vector<T> >::valid() const
{
  if (!exists())
    return false;

  try {
    (void)get();
  } catch (HDF5Exception &e) {
    return false;
  }

  return true;
}

// specialisations for std::string

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template<> inline Attribute<std::string>& Attribute<std::string>::create()
{
  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace for attribute " + _name);
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);

  hid_gc_noref attr(H5Acreate2(parent, _name.c_str(), datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT), H5Aclose, "Could not create attribute " + _name);

  return *this;
}

template<> inline void Attribute<std::string>::set( const std::string &value )
{
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);

  const char *cstr = value.c_str();
  if (H5Awrite(attr, datatype, &cstr) < 0)
    throw HDF5Exception("Could not write attribute " + _name);
}

template<> inline std::string Attribute<std::string>::get() const
{
  // H5Aread will allocate memory for us (use free() to free)

  char *buf;

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  if (H5Aread(attr, datatype, &buf) < 0)
    throw HDF5Exception("Could not read attribute " + _name);

  std::string value = buf;

  free(buf);
  return value;
}

// specialisations for std::vector<std::string>

template<> inline Attribute< std::vector<std::string> >& Attribute< std::vector<std::string> >::create( size_t length )
{
  if (length == 0)
    throw DALValueError("Cannot store empty arrays for attribute " + _name);

  hid_gc_noref dataspace(h5array(length), H5Sclose, "Could not create simple dataspace for attribute " + _name);
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);

  hid_gc_noref attr(H5Acreate2(parent, _name.c_str(), datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT), H5Aclose, "Could not create attribute " + _name);

  return *this;
}

template<> inline void Attribute< std::vector<std::string> >::set( const std::vector<std::string> &value )
{
  if (value.empty())
    throw DALValueError("Cannot store empty arrays for attribute " + _name);

  if (size() != value.size()) {
    // recreate the attribute to change the vector length on disk
    remove();
    create(value.size());
  }

  // convert to C-style strings
  std::vector<const char *> c_strs(value.size());
  for (unsigned i = 0; i < value.size(); i++) {
    c_strs[i] = value[i].c_str();
  }

  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);

  if (H5Awrite(attr, datatype, &c_strs[0]) < 0)
    throw HDF5Exception("Could not write attribute " + _name);
}

template<> inline std::vector<std::string> Attribute< std::vector<std::string> >::get() const
{
  // H5Aread will allocate memory for us (use free() to free each element)
  std::vector<char *> c_strs(size());

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype for attribute " + _name);
  hid_gc_noref attr(H5Aopen(parent, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute " + _name);

  if (H5Aread(attr, datatype, &c_strs[0]) < 0)
    throw HDF5Exception("Could not read attribute " + _name);

  // convert from C-style strings
  std::vector<std::string> value(c_strs.size());
  for (unsigned i = 0; i < value.size(); i++) {
    value[i] = c_strs[i];
    free(c_strs[i]);
  }

  return value;
}

#endif

}

