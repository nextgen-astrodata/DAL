#ifndef __H5TYPEMAP__
#define __H5TYPEMAP__

#include <hdf5.h>

// C->HDF5 translations of native types
template<typename T> hid_t h5nativeType();

template<> inline hid_t h5nativeType<float>()    { return H5T_NATIVE_FLOAT;  }
template<> inline hid_t h5nativeType<double>()   { return H5T_NATIVE_DOUBLE; }
template<> inline hid_t h5nativeType<unsigned>() { return H5T_NATIVE_UINT;   }
template<> inline hid_t h5nativeType<int>()      { return H5T_NATIVE_INT;    }
template<> inline hid_t h5nativeType<bool>()     { return H5T_NATIVE_CHAR;   } // assuming sizeof(bool) == 1

// C->HDF5 translations of types to use in header (ICD 003)
template<typename T> hid_t h5writeType();

template<> inline hid_t h5writeType<float>()    { return H5T_IEEE_F32LE; }
template<> inline hid_t h5writeType<double>()   { return H5T_IEEE_F64LE; }
template<> inline hid_t h5writeType<unsigned>() { return H5T_STD_U32LE;  }
template<> inline hid_t h5writeType<int>()      { return H5T_STD_I32LE;  }
template<> inline hid_t h5writeType<bool>()     { return H5T_STD_I32LE;  } // emulate bool with a 32-bit int

// C->HDF5 translations of types to use for data (CNProc endianness)
template<typename T> hid_t h5dataType( bool bigEndian );

template<> inline hid_t h5dataType<float>( bool bigEndian ) {
  return bigEndian ? H5T_IEEE_F32BE : H5T_IEEE_F32LE;
}


// DEBUG: let the compiler warn when it tries to use undefined T
template<class T> hid_t h5nativeType() {
  T::lol_no_this_wont_compile();

  return 0;
}

template<class T> hid_t h5writeType() {
  T::lol_no_this_wont_compile();

  return 0;
}

template<class T> hid_t h5dataType(bool) {
  T::lol_no_this_wont_compile();

  return 0;
}


#endif
