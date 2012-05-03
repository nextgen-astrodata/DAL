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
   * Returns whether this attribute exists in the HDF5 file.
   */
  bool exists() const;

  /*!
   * Removes this element from the HDF5 file. Useful for porting, 
   * repairing, or otherwise modifying files on a structural level.
   */
  void remove() const;

  /*!
   * Returns the number of data points in this element (1 for a scalar, >= 0 for a vector)
   */
  size_t size() const;

protected:
  AttributeBase( const hid_gc &container, const std::string &name ): HDF5Node(name), container(container) {}

  const hid_gc container;
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
 * where attr.value is of type AttributeValueType<int>.
 *
 * The setter will create the attribute if it does not exist.
 * The getter will throw an exception if the attribute does not exist.
 * The deleter will not throw an exception if the attribute dos not exist.
 */
template<typename T> class AttributeValueType {
public:
  /*!
   * Setter.
   */
  AttributeValueType<T>& operator=( const T& value ) {
    if (!attr.exists())
      attr.create();

    attr.set(value);

    return *this;
  }

  /*!
   * Allow x.value = y.value
   */
  AttributeValueType<T>& operator=( const AttributeValueType<T>& value ) {
    if (this == &value)
      return *this;

    return *this = static_cast<T>(value);
  }

  /*!
   * Getter.
   */
  operator T() const {
    // We can't gracefully return if the attribute does not exist,
    // because there is no safe default value for T. Note that in
    // Python, we return None in that case.
    return attr.get();
  }

  /*!
   * Crudely mimic Python's "del attr.value" (the property's deleter)
   */
  void del() const {
    if (attr.exists())
      attr.remove();
  }

private:
  // Do'not allow copying, as attr of the copy might get out of scope
  AttributeValueType( const AttributeValueType& );

  AttributeValueType( const Attribute<T> &attr ): attr(attr) {}

  const Attribute<T> &attr;

  // Only Attribute<T> can create instances
  friend class Attribute<T>;
};

template<typename T> std::ostream& operator<<(std::ostream &out, const AttributeValueType<T> &val)
{
  return out << static_cast<T>(val);
}
#endif


/*!
 * Represents an attribute containing a scalar or a string.
 */
template<typename T> class Attribute: public AttributeBase {
public:
  /*!
   * Represent an attribute called `name' within group `container'.
   */
  Attribute( const hid_gc &container, const std::string &name ): AttributeBase(container, name), value(*this) {}

  Attribute( const Attribute &other ): AttributeBase(other), value(*this) {}

  /*!
   * Creates this attribute.
   */
  void create() const;

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not exist.
   */
  T get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. An exception is thrown
   * if the attribute does not exist.
   */
  void set( const T &value ) const;

#ifndef SWIG
  AttributeValueType<T> value;
#endif
};

/*!
 * Represents an attribute containing a vector of scalars or strings.
 */
template<typename T> class Attribute< std::vector<T> >: public AttributeBase {
public:
  /*!
   * Represent an attribute called `name' within group `container'.
   */
  Attribute( const hid_gc &container, const std::string &name ): AttributeBase(container, name), value(*this) {}

  Attribute( const Attribute &other ): AttributeBase(other), value(*this) {}

  /*!
   * Creates this attribute, reserving a certain length. Note that HDF5 does not support
   * arrays of size 0, so length >= 1.
   */
  void create( size_t length = 1 ) const;

  /*!
   * Returns the value of this attribute, retrieved from the HDF5 file. An exception
   * is thrown if the attribute does not already exist.
   */
  std::vector<T> get() const;

  /*!
   * Stores the value of this attribute in the HDF5 file. An exception is thrown
   * if the attribute does not exist.
   */
  void set( const std::vector<T> &value ) const;

#ifndef SWIG
  AttributeValueType< std::vector<T> > value;
#endif
};

}

#include "hdf5/HDF5Attribute.tcc"

#endif

