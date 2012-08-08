#ifndef DAL_H5TYPEMAP_H
#define DAL_H5TYPEMAP_H

#include <hdf5.h>
#include "hid_gc.h"
#include "h5complex.h"
#include "h5tuple.h"
#include "isderivedfrom.h"

namespace DAL {

/*!
 * struct h5typemap<T>
 *
 * Implements compile-time type-marshalling functions from C++ to HDF5.
 */

/* As C++ does not allow us to specialise T as a class in general, that
 * implementation will actually be the default one, specified further down.
 * 
 * We only define its existence here.
 */
template<typename T> struct h5typemap;

/*
 * Specialisations for specific types.
 */

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

template<> struct h5typemap<unsigned long> {
  static inline hid_t memoryType()               { return H5T_NATIVE_ULONG; }
  static inline hid_t attributeType()            { return H5T_STD_U64LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_U64BE : H5T_STD_U64LE; }
};

template<> struct h5typemap<long> {
  static inline hid_t memoryType()               { return H5T_NATIVE_LONG; }
  static inline hid_t attributeType()            { return H5T_STD_I64LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I64BE : H5T_STD_I64LE; }
};

template<> struct h5typemap<unsigned long long> {
  static inline hid_t memoryType()               { return H5T_NATIVE_ULLONG; }
  static inline hid_t attributeType()            { return H5T_STD_U64LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_U64BE : H5T_STD_U64LE; }
};

template<> struct h5typemap<long long> {
  static inline hid_t memoryType()               { return H5T_NATIVE_LLONG; }
  static inline hid_t attributeType()            { return H5T_STD_I64LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I64BE : H5T_STD_I64LE; }
};

template<> struct h5typemap<short> {
  static inline hid_t memoryType()               { return H5T_NATIVE_SHORT; }
  static inline hid_t attributeType()            { return H5T_STD_I16LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_I16BE : H5T_STD_I16LE; }
};

template<> struct h5typemap<unsigned short> {
  static inline hid_t memoryType()               { return H5T_NATIVE_USHORT; }
  static inline hid_t attributeType()            { return H5T_STD_U16LE;   }
  static inline hid_t dataType( bool bigEndian ) { return bigEndian ? H5T_STD_U16BE : H5T_STD_U16LE; }
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

/*
 * A proxy class is required to allow switching based on class hierarchy, as direct specialization
 * covering subclasses is not possible in C++.
 *
 * The template parameters are, in order:
 *
 * T:   The class type for which an h5typemap is derived
 * int: 1 if T is (derived from) TupleUntemplated, 0 otherwise
 */

template<typename T, int> struct h5typemap_proxy {
  // The default implementation -- empty to trigger compile errors for unsupported types
};

template<typename T> struct h5typemap_proxy<T,1> {
  // The specialisation for TupleUntemplated and subclasses thereof

  static inline hid_gc memoryType()               { return h5tupleType( h5typemap<typename T::type>::memoryType(), T::size() );        }
  static inline hid_gc attributeType()            { return h5tupleType( h5typemap<typename T::type>::attributeType(), T::size() );     }
  static inline hid_gc dataType( bool bigEndian ) { return h5tupleType( h5typemap<typename T::type>::dataType(bigEndian), T::size() ); }
};

/*
 * The specialisation for classes (types) in general. This needs to be the default (non-specialised version),
 * as C++ does not allow us to provide a generic form of template<typename T> and a specialisation for template<class T>.
 */

template<typename T> struct h5typemap {
  /*!
   * HDF5 type identifier for type T in memory (the native C++ type)
   */
  static inline hid_gc memoryType()               { return proxy::memoryType(); }

  /*!
   * HDF5 type identifier for attributes of type T on disk
   */
  static inline hid_gc attributeType()            { return proxy::attributeType(); }

  /*!
   * HDF5 type identifier for datasets of type T on disk
   */
  static inline hid_gc dataType( bool bigEndian ) { return proxy::dataType(bigEndian); }

private:  
  // Defer calls to the proper specialisation
  typedef h5typemap_proxy<T, IsDerivedFrom<T, TupleUntemplated>::Is> proxy;
};

}

#endif

