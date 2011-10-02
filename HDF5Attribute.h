#ifndef __H5ATTRIBUTE__
#define __H5ATTRIBUTE__

#include <string>
#include <vector>
#include <cstdlib>
#include <hdf5.h>
#include "HDF5Node.h"
#include "hdf5core/h5typemap.h"
#include "hdf5core/hid_gc.h"

namespace LDA {

/*!
 * Represents core functionality for an attribute inside a group.
 */
class AttributeBase: public HDF5Node {
public:
  /*!
   * Returns whether this attribute exists in the HDF5 file.
   */
  bool exists() const { return H5Aexists(container, _name.c_str()) > 0; }

  /*!
   * Removes this element from the HDF5 file. Useful for porting, 
   * repairing, or otherwise modifying files on a structural level.
   */
  void remove() const { if (H5Adelete(container, _name.c_str()) < 0) throw HDF5Exception("Could not delete element"); }

protected:
  AttributeBase( const hid_gc &container, const std::string &name ): HDF5Node(name), container(container) {}

  /*!
   * Returns the number of data points in this element (1 for a scalar, >= 0 for a vector)
   */
  size_t size() const;

  const hid_gc container;
};

/*!
 * Represents an attribute containing a scalar or a string.
 */
template<typename T> class Attribute: public AttributeBase {
public:
  Attribute( const hid_gc &container, const std::string &name ): AttributeBase(container, name) {}

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not already exist.
   */
  T get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. The attribute is created
   * if it does not already exist.
   */
  void set( const T &value ) const;
};

/*!
 * Represents an attribute containing a vector of scalars or strings.
 */
template<typename T> class Attribute< std::vector<T> >: public AttributeBase {
public:
  Attribute( const hid_gc &container, const std::string &name ): AttributeBase(container, name) {}

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not already exist.
   */
  std::vector<T> get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. The attribute is created
   * if it does not already exist.
   */
  void set( const std::vector<T> &value ) const;
};

inline size_t AttributeBase::size() const
{
  hid_gc_noref attr(H5Aopen_name(container, _name.c_str()), H5Aclose, "Could not open attribute");

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
  const hid_t datatype = H5Tcopy(H5T_C_S1);

  H5Tset_size(datatype, H5T_VARIABLE);

  return datatype;
}

// generic versions

template<typename T> inline void Attribute<T>::set( const T &value ) const
{
  const bool create = !exists();

  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace");

  hid_gc_noref attr(
    create ? H5Acreate2(container, _name.c_str(), h5writeType<T>(), dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(container, _name.c_str(), H5P_DEFAULT)
    , H5Aclose, 
    create ? "Could not create atttribute"
           : "Could not open attribute");

  if (H5Awrite(attr, h5nativeType<T>(), &value) < 0)
    throw HDF5Exception("Could not write attribute");
}

template<typename T> inline T Attribute<T>::get() const
{
  T value;

  hid_gc_noref attr(H5Aopen(container, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute");

  if (H5Aread(attr, h5nativeType<T>(), &value) < 0)
    throw HDF5Exception("Could not read attribute");

  return value;
}

template<typename T> inline void Attribute< std::vector<T> >::set( const std::vector<T> &value ) const
{
  const bool create = !exists();

  hid_gc_noref dataspace(h5array(value.size()), H5Sclose, "Could not create simple dataspace");

  hid_gc_noref attr(
    create ? H5Acreate2(container, _name.c_str(), h5writeType<T>(), dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(container, _name.c_str(), H5P_DEFAULT)
    , H5Aclose,
    create ? "Could not create atttribute"
           : "Could not open attribute");

  if (H5Awrite(attr, h5nativeType<T>(), &value[0]) < 0)
    throw HDF5Exception("Could not write to attribute");
}

template<typename T> inline std::vector<T> Attribute< std::vector<T> >::get() const
{
  hid_gc_noref attr(H5Aopen_name(container, _name.c_str()), H5Aclose, "Could not open attribute");

  std::vector<T> value(size());

  if (H5Aread(attr, h5nativeType<T>(), &value[0]) < 0)
    throw HDF5Exception("Could not read attribute");

  return value;
}

// specialisations for std::string

#ifndef DOXYGEN_SHOULD_SKIP_THIS

template<> inline void Attribute<std::string>::set( const std::string &value ) const
{
  const bool create = !exists();

  hid_gc_noref dataspace(h5scalar(), H5Sclose, "Could not create scalar dataspace");
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");

  hid_gc_noref attr(
    create ? H5Acreate2(container, _name.c_str(), datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(container, _name.c_str(), H5P_DEFAULT)
    , H5Aclose,
    create ? "Could not create atttribute"
           : "Could not open attribute");

  const char *cstr = value.c_str();
  if (H5Awrite(attr, datatype, &cstr) < 0)
    throw HDF5Exception("Could not write attribute");
}

template<> inline std::string Attribute<std::string>::get() const
{
  // H5Aread will allocate memory for us (use free() to free)

  char *buf;

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");
  hid_gc_noref attr(H5Aopen(container, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute");

  if (H5Aread(attr, datatype, &buf) < 0)
    throw HDF5Exception("Could not read attribute");

  std::string value = buf;

  free(buf);
  return value;
}

// specialisations for std::vector<std::string>

template<> inline void Attribute< std::vector<std::string> >::set( const std::vector<std::string> &value ) const
{
  const bool create = !exists();

  // convert to C-style strings
  std::vector<const char *> c_strs(value.size());
  for (unsigned i = 0; i < value.size(); i++) {
    c_strs[i] = value[i].c_str();
  }  

  hid_gc_noref dataspace(h5array(c_strs.size()), H5Sclose, "Could not create scalar dataspace");
  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");

  hid_gc_noref attr(
    create ? H5Acreate2(container, _name.c_str(), datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT)
           : H5Aopen(container, _name.c_str(), H5P_DEFAULT)
    , H5Aclose);

  if (H5Awrite(attr, datatype, &c_strs[0]) < 0)
    throw HDF5Exception("Could not write attribute");
}

template<> inline std::vector<std::string> Attribute< std::vector<std::string> >::get() const
{
  // H5Aread will allocate memory for us (use free() to free each element)
  std::vector<char *> c_strs(size());

  hid_gc_noref datatype(h5stringType(), H5Tclose, "Could not create string datatype");
  hid_gc_noref attr(H5Aopen(container, _name.c_str(), H5P_DEFAULT), H5Aclose, "Could not open attribute");

  if (H5Aread(attr, datatype, &c_strs[0]) < 0)
    throw HDF5Exception("Could not read attribute");

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

#endif

