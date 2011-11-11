#ifndef __H5TYPEMAP__
#define __H5TYPEMAP__

#include <hdf5.h>
#include "hdf5/types/hid_gc.h"
#include "hdf5/types/h5complex.h"

namespace LDA {

template<typename T> struct h5typemap {
  /*!
   * HDF5 type identifier for type T in memory (the native C++ type)
   */
  hid_t memoryType(); 

  /*!
   * HDF5 type identifier for attributes of type T on disk
   */
  hid_t attributeType();

  /*!
   * HDF5 type identifier for datasets of type T on disk
   */
  hid_t dataType( bool bigEndian );
};

template<> struct h5typemap<float> {
  static inline hid_t memoryType()               { return H5T_NATIVE_FLOAT; }
  static inline hid_t attributeType()            { return H5T_IEEE_F32LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_IEEE_F32BE : H5T_IEEE_F32LE; }
};

template<> struct h5typemap<double> {
  static inline hid_t memoryType()               { return H5T_NATIVE_DOUBLE; }
  static inline hid_t attributeType()            { return H5T_IEEE_F64LE;    }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_IEEE_F64BE : H5T_IEEE_F64LE; }
};

template<> struct h5typemap<unsigned> {
  static inline hid_t memoryType()               { return H5T_NATIVE_UINT; }
  static inline hid_t attributeType()            { return H5T_STD_U32LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_U32BE : H5T_STD_U32LE; }
};

template<> struct h5typemap<int> {
  static inline hid_t memoryType()               { return H5T_NATIVE_INT; }
  static inline hid_t attributeType()            { return H5T_STD_I32LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I32BE : H5T_STD_I32LE; }
};

template<> struct h5typemap<short> {
  static inline hid_t memoryType()               { return H5T_NATIVE_SHORT; }
  static inline hid_t attributeType()            { return H5T_STD_I16LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I16BE : H5T_STD_I16LE; }
};

template<> struct h5typemap<bool> {
  static inline hid_t memoryType()               { return sizeof (bool) == 1 ? H5T_NATIVE_CHAR : H5T_NATIVE_INT; } // assumes bool is either a char or an int
  static inline hid_t attributeType()            { return H5T_STD_I32LE;   } // emulate a bool as a 32-bit signed integer
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I32BE : H5T_STD_I32LE; }
};

template<typename T> struct h5typemap< std::complex<T> > {
  static inline hid_gc memoryType()               { return h5complexType( h5typemap<T>::memoryType() );        }
  static inline hid_gc attributeType()            { return h5complexType( h5typemap<T>::attributeType() );     }
  static inline hid_gc dataType( bool bigEndian ) { return h5complexType( h5typemap<T>::dataType(bigEndian) ); }
};

}

#endif
