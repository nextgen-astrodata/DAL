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
  static Attribute< T > _castNode( Group &nodeSet, const std::string &name ) {
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

%include dal/hdf5/Attribute.h

%extend DAL::Attribute {
  %pythoncode {
    def create(self, *args, **kwargs):
      self._create(*args, **kwargs)
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
      except TypeError as tpe:
        raise TypeError("'%s' cannot be assigned values of passed type '%s': %s" % (self.__class__.__name__, type(val).__name__, tpe.message,))

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
    _Attributes[Attribute ## PythonName ._typeName()] = Attribute ## PythonName;
  }
%enddef

%define AddSimpleAttributeAndVector( PythonName, CPPName )
  AddAttribute( PythonName, %arg(CPPName) );

  AddAttribute( V ## PythonName, %arg(std::vector< CPPName >) );
%enddef

%define AddAttributeAndVector( PythonName, CPPName )
  vector_typemap( %arg(CPPName) );
  AddSimpleAttributeAndVector( %arg(PythonName), %arg(CPPName) );
%enddef

%pythoncode {
  # DAL::Attribute templates can be registered here
  _Attributes = {}
}

AddAttribute( Bool, bool );
AddSimpleAttributeAndVector( Int,           int );
AddSimpleAttributeAndVector( Long,          long );
AddSimpleAttributeAndVector( UInt,          %arg(unsigned int) );
AddSimpleAttributeAndVector( ULong,         %arg(unsigned long) );
AddSimpleAttributeAndVector( LongLong,      %arg(long long) );
AddSimpleAttributeAndVector( ULongLong,     %arg(unsigned long long) );
AddSimpleAttributeAndVector( Float,         float );
AddSimpleAttributeAndVector( Double,        double );
AddSimpleAttributeAndVector( ComplexFloat,  %arg(std::complex<float>) );
AddSimpleAttributeAndVector( ComplexDouble, %arg(std::complex<double>) );
AddSimpleAttributeAndVector( String,        std::string );
AddAttributeAndVector( UInt3,         %arg(Tuple<unsigned int, 3>) );
AddAttributeAndVector( ULongLong2,    %arg(Tuple<unsigned long long, 2>) );
AddAttributeAndVector( Double3,       %arg(Tuple<double, 3>) );

