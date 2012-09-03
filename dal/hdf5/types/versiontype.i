%include dal/hdf5/types/versiontype.h

%extend dal::VersionType {
  %pythoncode {
    __repr__ = to_string
    __str__  = __repr__
  }
}

AddAttribute( VersionType, VersionType );

