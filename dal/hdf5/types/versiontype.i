%ignore dal::VersionType::operator<;
%ignore dal::VersionType::operator<=;
%ignore dal::VersionType::operator>;
%ignore dal::VersionType::operator>=;
%ignore dal::VersionType::operator==;
%ignore dal::VersionType::operator!=;

%include dal/hdf5/types/versiontype.h

%extend dal::VersionType {
  %pythoncode {
    __repr__ = to_string
    __str__  = __repr__

    def __iter__(self):
      yield self.major
      yield self.minor
      yield self.release

    def __cmp__(self, other):
      try:
        return self.cmp(self, other)
      except TypeError:
        # fall-back to allow comparisons with sequences
        return cmp(tuple(self), other)
  }
}

AddAttribute( VersionType, VersionType );

