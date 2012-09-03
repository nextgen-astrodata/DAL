// rename otherwise unreachable functions
%rename(get_hid_t)  operator hid_t;
%rename(get_hid_gc) operator hid_gc;

// do not bother renaming operator=: Python users do not need it
%ignore dal::Node::operator=;

%include dal/hdf5/Node.h

