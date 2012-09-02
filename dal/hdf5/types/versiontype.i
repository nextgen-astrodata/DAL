%include dal/hdf5/types/versiontype.h

%extend DAL::VersionType {
  %pythoncode {
    __repr__ = to_string
  }
}

AddAttribute( VersionType, VersionType );

