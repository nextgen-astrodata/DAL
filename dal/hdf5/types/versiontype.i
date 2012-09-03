%include dal/hdf5/types/versiontype.h

%extend dal::VersionType {
  %pythoncode {
    __repr__ = to_string
    __str__  = __repr__

    def __iter__(self):
      yield self.major
      yield self.minor
      yield self.release
  }
}

AddAttribute( VersionType, VersionType );

