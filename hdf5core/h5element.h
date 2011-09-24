#ifndef __H5ELEMENT__
#define __H5ELEMENT__

#include <hdf5.h>
#include "h5attribute.h"

/*
 * Represents an element inside a group.
 *
 * The Element classes provide meta-functionality,
 * such as get/set/exists/remove.
 */
class Element {
public:
  std::string name() const { return _name; }

  bool exists() const { return H5Aexists(container, _name.c_str()) > 0; }

  // useful for porting, repairing, or otherwise modifying files on a structural level
  void remove() const { if (H5Adelete(container, _name.c_str()) < 0) throw HDF5Exception("Could not delete atttribute"); }

protected:
  Element( const hid_gc &container, const std::string &name ): container(container), _name(name) {}

  const hid_gc container;
  const std::string _name;
};

/*
 * Represents an attribute containing a scalar or a string.
 */
template<typename T> class Attribute: public Element {
public:
  Attribute( const hid_gc &container, const std::string &name ): Element(container, name) {}

  T get() const                    { return readAttribute<T>(container, _name.c_str()); }
  void set( const T &value ) const { writeAttribute<T>(container, _name.c_str(), value, !exists()); }
};

/*
 * Represents an attribute containing a vector.
 */
template<typename T> class AttributeV: public Element {
public:
  AttributeV( const hid_gc &container, const std::string &name ): Element(container, name) {}

  std::vector<T> get() const                    { return readAttributeV<T>(container, _name.c_str()); }
  void set( const std::vector<T> &value ) const { writeAttributeV<T>(container, _name.c_str(), value, !exists()); }
};

#endif

