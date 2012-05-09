#ifndef __H5ATTRIBUTE__
#define __H5ATTRIBUTE__

#include <string>
#include <vector>
#include <ostream>
#include "hdf5/types/hid_gc.h"
#include "hdf5/HDF5Node.h"

/*
 * NOTE: Setting attributes is not thread-safe if the same attribute is modified by multiple
 * threads in parallel!
 */

namespace DAL {

/*!
 * Represents core functionality for an attribute inside a group.
 */
class AttributeBase: public HDF5Node {
public:
  /*!
   * Create a generic Attribute object, providing meta functionality.
   */
  AttributeBase( HDF5NodeSet &parent, const std::string &name ): HDF5Node(parent.group(), name) {}

  /*!
   * Returns whether this attribute exists in the HDF5 file.
   */
  virtual bool exists() const;

  /*!
   * Removes this element from the HDF5 file. Useful for porting, 
   * repairing, or otherwise modifying files on a structural level.
   */
  void remove() const;

  /*!
   * Returns the number of data points in this element (1 for a scalar, >= 0 for a vector)
   */
  size_t size() const;
};

#ifndef SWIG

template<typename T> class Attribute;

/*!
 * Interface class for Attribute<T>::value, providing Python-property-like functionality:
 *
 * Attribute<int> attr(...);
 *
 * attr.value = 42;    // set the value
 * int i = attr.value; // get the value
 * attr.del();         // remove the attribute
 *
 * where attr.value is of type AttributeValue<int>.
 *
 * The setter will create the attribute if it does not exist.
 * The getter will throw an exception if the attribute does not exist.
 * The deleter will not throw an exception if the attribute dos not exist.
 */
template<typename T> class AttributeValue {
public:
  /*!
   * Setter: allows x.value = (T)y.
   */
  AttributeValue<T>& operator=( const T& value );

  /*!
   * Allow x.value = y.value
   */
  AttributeValue<T>& operator=( const AttributeValue<T>& value );

  /*!
   * Getter: allows T y = x.value.
   */
  operator T() const;

  /*!
   * Crudely mimic Python's "del attr.value" (the property's deleter)
   */
  void del() const;

private:
  // Do'not allow copying, as attr of the copy might get out of scope
  AttributeValue( const AttributeValue& );

  AttributeValue( const Attribute<T> &attr ): attr(attr) {}

  const Attribute<T> &attr;

  // Only Attribute<T> can create instances
  friend class Attribute<T>;
};

template<typename T> std::ostream& operator<<(std::ostream &out, const AttributeValue<T> &val);

#endif /* !SWIG */

/*!
 * Represents an attribute containing a scalar or a string.
 *
 * Python example:
 * \code
 *     # Create a new HDF5 file with some string attribute
 *     >>> f = HDF5FileBase("example.h5", HDF5FileBase.CREATE)
 *     >>> a = AttributeString(f, "EXAMPLE_STRING")
 *
 *     # Because we are creating the file, the attribute does initially not exist
 *     >>> a.value is None
 *     True
 *
 *     # Once we set the value, the attribute exists and can be read
 *     >>> a.value = "hello world!"
 *     >>> a.value
 *     'hello world!'
 *
 *     # The attribute can also be removed
 *     >>> del a.value
 *     >>> a.value is None
 *     True
 *
 *     # Low-level functions allow finer control ...
 *     >>> a.exists()
 *     False
 *     >>> a.create() # returns a
 *     <...>
 *     >>> a.exists()
 *     True
 *     >>> a.set("hello world!")
 *     >>> a.get()
 *     'hello world!'
 *     >>> a.remove()
 *
 *     # ... but raise errors if used incorrectly
 *     >>> a.exists()
 *     False
 *     >>> a.set("hello world!")
 *     Traceback (most recent call last):
 *     HDF5Exception: Could not open attribute
 *     >>> a.get()
 *     Traceback (most recent call last):
 *     HDF5Exception: Could not open attribute
 *     >>> a.remove()
 *     Traceback (most recent call last):
 *     HDF5Exception: Could not delete element
 *
 *     # Clean up:
 *     >>> import os
 *     >>> os.remove("example.h5")
 * \endcode
 */
template<typename T> class Attribute: public AttributeBase {
public:
  /*!
   * Represent an attribute called `name' within group `parent'.
   */
  Attribute( HDF5NodeSet &parent, const std::string &name ): AttributeBase(parent, name), value(*this) {}

  Attribute( const Attribute &other ): AttributeBase(other), value(*this) {}

  /*!
   * Creates this attribute.
   */
  Attribute<T>& create();

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not exist.
   */
  T get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. An exception is thrown
   * if the attribute does not exist.
   */
  void set( const T &value );

  AttributeValue<T> value;
};

/*!
 * Represents an attribute containing a vector of scalars or strings.
 */
template<typename T> class Attribute< std::vector<T> >: public AttributeBase {
public:
  /*!
   * Represent an attribute called `name' within group `parent'.
   */
  Attribute( HDF5NodeSet &parent, const std::string &name ): AttributeBase(parent, name), value(*this) {}

  Attribute( const Attribute &other ): AttributeBase(other), value(*this) {}

  /*!
   * Creates this attribute, reserving a certain length. Note that HDF5 does not support
   * arrays of size 0, so length >= 1.
   */
  Attribute< std::vector<T> > &create( size_t length = 1 );

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not already exist.
   */
  std::vector<T> get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. An exception is thrown
   * if the attribute does not exist.
   */
  void set( const std::vector<T> &value );

#ifndef SWIG
  AttributeValue< std::vector<T> > value;
#endif
};

}

#include "hdf5/HDF5Attribute.tcc"

#endif

