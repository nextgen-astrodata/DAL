
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
%extend DAL::Attribute {
  // The C++ ABI name for this Attribute class
  static std::string _typeName() {
    hid_gc dummy_hid;
    Attribute< T > dummy(dummy_hid, "");

    return typeid(Attribute< T >(dummy)).name();
  }

  // Force node `name' in nodeset `nodeSet' to be of our type
  // (will throw std::bad_cast on failure)
  static Attribute< T > _castNode( HDF5GroupBase &nodeSet, const std::string &name ) {
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
  // create the Python class AttributeXXX
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

AddAttribute( Int,        int );
AddAttribute( VInt,       std::vector<int> );

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

