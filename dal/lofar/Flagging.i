AddAttributeAndVector( Range, %arg(DAL::Range) );

%include dal/lofar/Flagging.h

%extend DAL::Range {
  %pythoncode {
    __repr__ = to_string
  }
}

