AddAttributeAndVector( Range, %arg(DAL::Range) );

%include dal/lofar/Flagging.h

%extend DAL::Range {
  %pythoncode {
    __repr__ = to_string
    __str__ = __repr__
  }
}

