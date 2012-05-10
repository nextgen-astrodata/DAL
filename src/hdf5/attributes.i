
%include hdf5/types/versiontype.h

%extend DAL::VersionType {
  %pythoncode {
    def __repr__(self):
      return "%s('%s')" % (self.__class__.__name__,self.toString())

    __str__ = toString
  }
}

// prevent SWIG from requiring a default constructor for AttributeBase
namespace DAL {
  %valuewrapper AttributeBase;
  class AttributeBase;
};

%{
#include <typeinfo>
%}

// To replace HDF5NodeSet.getNode, SWIG requires us to first
// %extend it, and then %ignore the original, both before
// loading the actual class.
%extend DAL::HDF5NodeSet {
  /*
   * When registering objects in an HDF5NodeSet, they are collected
   * in a generic map<string, HDF5Node*>. In C++, we can use dynamic_cast
   * to downcast each registered node to its original type. This is how
   * HDF5NodeSet.getNode(name) is implemented: the user gets a reference
   * to the requested node, which can be downcast to the desired type.
   *
   * However, SWIG behaves a lot better when it can handle objects
   * instead of references or pointers to objects. A straight-forward
   * implementation of HDF5NodeSet.getNode(name) would return a
   * regular HDF5NodeSet object, slicing the requested node. We can't
   * downcast a sliced object afterwards, since it's only a (wrapped) copy.
   *
   * Much nicer behaviour is obtained by letting Python return
   * objects of the same class as the requested node really is. Such
   * behaviour is obtained using the following approach. First, all Attribute
   * wrapper classes (AttributeXXXX) register themselves under their
   * internal C++ ABI type name. Second, any call to getNode first obtains
   * the type of object (the internal C++ ABI type name) that needs to
   * be returned. Finally, the class of the correct wrapper object
   * is requested to return our node, forcably downcast to the correct
   * C++ type of Attribute.
   *
   * 1) AttributeXXXX._typeName()
   *      returns the internal C++ ABI type name of the wrapped Attribute<T> class.
   * 2) Attributes
   *      is a dict resolving C++ ABI type names to AttributeXXXX classes.
   * 3) HDF5NodeSet._getNodeTypeName(name)
   *      returns the internal C++ ABI type name of a node
   * 4) AttributeXXXX._downCast(nodeSet, name)
   *      returns nodeSet.getNode(name) forcably upcast to AttributeXXXX.
   * 5) HDF5Node.getNode(name) (Python implementation to allow weakly typed return values)
   *      returns a node, forcably downcast to the AttributeXXXX class
   *      registered to the internal C++ ABI name of the node.
   *
   * In short, HDF5Node.getNode(name) will return an object of the proper
   * AttributeXXXX type. If the type of the node is not registered, a generic
   * HDF5Node object is returned instead.
   */

  // A generic getNode replacement that always returns an HDF5Node
  HDF5Node _getNode( const std::string &name ) {
    return $self->getNode(name);
  }

  // The C++ ABI name of a specific node
  std::string _getNodeTypeName( const std::string &name ) {
    const HDF5Node &obj = $self->getNode(name);
    return typeid(obj).name();
  }

  %pythoncode {
    def getNode(self, name):
      """
        Returns a registered node `name'.
        
        If the attribute type is present in DAL.Attributes.values(),
        the returned object will have the correct type. Otherwise,
        a generic HDF5Node object is returned.

        Python example:

             # Create a new HDF5 file with a predefined format
             >>> f = BF_File("example.h5", HDF5FileBase.CREATE)

             # Set one of the attributes
             >>> f.observationID().value = '12345'

             # Check the HDF5 name of the observationID attribute
             >>> f.observationID().name()
             'OBSERVATION_ID'

             # The observationID attribute is registered by BF_File
             >>> 'OBSERVATION_ID' in f.nodeNames()
             True

             # Retrieve the attribute through introspection
             >>> a = f.getNode('OBSERVATION_ID')
             >>> a.value
             '12345'
        
             # Clean up:
             >>> import os
             >>> os.remove("example.h5")
      """
      typename = self._getNodeTypeName(name)

      if typename in Attributes:
        # attribute type is registered, so cast to it
        return Attributes[typename]._downCast(self, name)
      else:
        # cast to the lowest common denominator
        return self._getNode(name)
  }
}

// ignore the original getNode routine, which cannot be exported
// because it returns a fancy ImplicitDowncast<HDF5Node>.
%ignore DAL::HDF5NodeSet::getNode;

%extend DAL::Attribute {
  // The C++ ABI name for this Attribute class
  static std::string _typeName() {
    hid_gc dummy_hid;
    Attribute< T > dummy(dummy_hid, "");

    return typeid(Attribute< T >(dummy)).name();
  }

  // Force node `name' in nodeset `nodeSet' to be of our type
  static Attribute< T > _downCast( HDF5NodeSet &nodeSet, const std::string &name ) {
    return nodeSet.getNode(name);
  }
}  

// member functions that return *this are problematic,
// because SWIG generates a new wrapper object and does not
// know how to do the memory management right between
// both wrapper objects. So we write our own further below.
%rename(_create) DAL::Attribute::create;

// We will provide an Attribute.value implementation in Python
%ignore DAL::Attribute::value;

// rename otherwise unreachable functions
%rename(get_hid_t)  operator hid_t;
%rename(get_hid_gc) operator hid_gc;

%include hdf5/HDF5Node.h
%include hdf5/HDF5Attribute.h

%extend DAL::Attribute {
  %pythoncode {
    def create(self):
      self._create()
      return self

    @property
    def value(self):
      if not self.exists():
        return None

      return self.get()

    @value.setter
    def value(self, val):
      if not self.exists():
        self.create()

      try:
        self.set(val)
      except TypeError:
        raise TypeError("'%s' cannot be assigned values of type '%s'" % (self.__class__.__name__, type(val).__name__,))

    @value.deleter
    def value(self):
      if self.exists():
        self.remove()
  }
}

%define AddAttribute( PythonName, CPPName )
  // create the Python class VectorXXX
  %template(Attribute ## PythonName) DAL::Attribute< CPPName >;

  // register it in our Attributes dict
  %pythoncode {
    typeName = Attribute ## PythonName ._typeName();
    Attributes[typeName] = Attribute ## PythonName;
  }
%enddef

%pythoncode {
  # DAL::Attribute templates can be registered here
  Attributes = {}
}

AddAttribute( Bool,       bool );

AddAttribute( Unsigned,   unsigned );
AddAttribute( VUnsigned,  std::vector<unsigned> );

AddAttribute( Double,     double );
AddAttribute( VDouble,    std::vector<double> );

AddAttribute( String,     std::string );
AddAttribute( VString,    std::vector<std::string> );

AddAttribute( Unsigned3,  %arg(Tuple<unsigned,3>) );
AddAttribute( VUnsigned3, %arg(std::vector< Tuple<unsigned,3> >) );

AddAttribute( Double3,    %arg(Tuple<double,3>) );
AddAttribute( VDouble3,   %arg(std::vector< Tuple<double,3> >) );

