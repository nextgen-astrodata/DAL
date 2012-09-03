AddAttributeAndVector( Range, %arg(dal::Range) );

%include dal/lofar/Flagging.h

%extend dal::Range {
  %pythoncode {
    __repr__ = to_string
    __str__ = __repr__
  }
}

