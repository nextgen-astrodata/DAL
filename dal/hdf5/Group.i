// member functions that return *this are problematic,
// because SWIG generates a new wrapper object and does not
// know how to do the memory management right between
// both wrapper objects. So we write our own further below.
%rename(_create) DAL::Group::create;

%{
#include <typeinfo>
%}

// To replace Group.getNode, SWIG requires us to first
// %extend it, and then %ignore the original, both before
// loading the actual class.
%extend DAL::Group {
  /*
   * Each Group allows nodes to be registered in a generic
   * map<string, Node*> using the addNode method. The getNode method
   * is used for node lookup in that map. Nodes in the map are typically
   * subclasses of Node. In C++, we can use dynamic_cast to cast
   * the received object to its proper type.
   *
   * In SWIG however, we prefer to pass around regular objects instead
   * of references and pointers, to prevent crashes due to incorrect
   * memory management between C++ and Python. Exposing the C++ getNode
   * function to Python directly would thus result in returning Node
   * objects, which are sliced copies of the object retained in the map.
   *
   * Much nicer behaviour is obtained by letting Python return
   * objects of the same class as the requested node really is. To do so,
   * we need to know which Python class should wrap a requested node.
   *
   * The C++ <-> Python class link is maintained by a lookup table called
   * `Attributes' in Python, which has the internal C++ class name (typeid)
   * linked to its corresponding Python class. When a node is requested in
   * our Python getNode funtion, we first ask in C++ what the class of that
   * node is. Then, we ask the corresponding Python wrapper class to
   * request the node and force a downcast.
   *
   * The following functionality is used in the process:
   *
   * 1) AttributeXXXX._typeName()
   *      returns the internal C++ ABI type name of the wrapped Attribute<T> class.
   * 2) _Attributes
   *      is a dict resolving C++ ABI type names to AttributeXXXX classes.
   * 3) Group._getNodeTypeName(name)
   *      returns the internal C++ ABI type name of a node
   * 4) AttributeXXXX._castNode(nodeSet, name)
   *      returns nodeSet.getNode(name) forcably upcast to AttributeXXXX.
   * 5) Node.getNode(name) (Python implementation to allow weakly typed return values)
   *      returns a node, forcably downcast to the AttributeXXXX class
   *      registered to the internal C++ ABI name of the node.
   *
   * In short, Node.getNode(name) will return an object of the proper
   * AttributeXXXX type. If the type of the node is not registered, a generic
   * Node object is returned instead.
   */

  // A generic getNode replacement that always returns an Node
  Node _getNode( const std::string &name ) {
    return $self->getNode(name);
  }

  // The C++ ABI name of a specific node
  std::string _getNodeTypeName( const std::string &name ) {
    Node &obj = $self->getNode(name);
    return typeid(obj).name();
  }

  %pythoncode {
    def getNode(self, name):
      """
        Returns a registered node `name'.
        
        If the attribute type is present in DAL._Attributes.values(),
        the returned object will have the correct type. Otherwise,
        a generic Node object is returned.

        Python example:

             # Create a new HDF5 file with a predefined format
             >>> f = BF_File("example.h5", File.CREATE)

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

      if typename in _Attributes:
        # attribute type is registered, so cast to it
        return _Attributes[typename]._castNode(self, name)
      else:
        # cast to the lowest common denominator
        return self._getNode(name)
  }
}

// ignore the original getNode routine, which cannot be exported
// because it returns a fancy ImplicitDowncast<Node>.
%ignore DAL::Group::getNode;

// do not bother renaming operator=: Python users do not need it
%ignore DAL::Group::operator=;

%include hdf5/Group.h

%extend DAL::Group {
  %pythoncode {
    def create(self, *args, **kwargs):
      self._create(*args, **kwargs)
      return self
  }    
}

