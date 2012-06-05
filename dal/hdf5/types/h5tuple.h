#ifndef __H5TUPLE__
#define __H5TUPLE__

#include <hdf5.h>
#include <algorithm>
#include "hid_gc.h"
#include "dal/hdf5/exceptions/h5exception.h"

namespace DAL {

/*!
 * A (DAL) tuple is a structure consisting of N elements of type T. All
 * tuples derive from TupleBase<T,N>, which provides basic array-access
 * to all tuples by providing operator[], begin(), and end().
 *
 * Classes derived from TupleBase implement the storage as public
 * data members, allowing name-based access such as tuple.x and tuple.y
 * next to TupleBase's tuple[0] and tuple[1].
 */

// A non-templated common root, required for IsDerivedFrom checking
class TupleUntemplated {
protected:
  TupleUntemplated() {} // prevent direct instantiation
public:
  ~TupleUntemplated() {} // prevent generating a vtable by forbidding virtual functions
}; 

/*!
 * TupleBase<T,N> provides functionality common to all tuples.
 *
 * T: The data type of the tuple (the tuple is homogeneous).
 * N: The number of data elements in the tuple.
 *
 * The subclasses of TupleBase are responsible for providing the storage
 * for the elements as named data members. It is assumed that
 *    sizeof(TupleBase<T,N>) == N * sizeof(T),
 * the tuple is stored as a packed set of its members.
 *
 * Note that TupleBase cannot be directly instantiated, as it has
 * no storage for its data members.
 *
 */
template<typename T, size_t N> class TupleBase: public TupleUntemplated {
protected:
  TupleBase() {} // prevent direct instantiation
public:
  /*!
   * The type of elements in tuples of this type.
   */
  typedef T type;

  /*!
   * The number of elements in tuples of this type.
   */
  static size_t size() { return N; }

  /*
   * Provide some array-like and vector-like functionality.
   */

  typedef T *iterator;
  typedef const T *const_iterator;

  const T& operator[](size_t index) const { return *(begin() + index); }
        T& operator[](size_t index)       { return *(begin() + index); }

  const_iterator begin() const { return reinterpret_cast<const T*>(this); }
        iterator begin()       { return reinterpret_cast<T*>(this); }

  const_iterator end() const { return begin() + size(); }
        iterator end()       { return begin() + size(); }

  /*!
   * Return this tuple as a vector.
   */
  std::vector<T> get() const {
    std::vector<T> result(size());

    std::copy(begin(), end(), result.begin());

    return result;
  }

  /*!
   * Copy a vector into this tuple.
   */
  void set( const std::vector<T> &other ) {
    if (other.size() != size())
      throw DALValueError("Tuples can only be initialised with vectors of the same size");

    std::copy(other.begin(), other.end(), begin());
  }
};

/*! \class Tuple
 *
 * Tuple<T,N> provides a generic tuple for N=1..4 providing
 * fields with names `first`, `second`, `third`, and up to `fourth`.
 *
 * Python example:
 * \code
 *    # TupleUnsigned3() is a Tuple<unsigned int, 3>
 *    >>> t = TupleUnsigned3()
 *
 *    # Values can be modified in various ways:
 *    >>> t.set([0,0,3])
 *    >>> t.first = 1
 *    >>> t[1] = 2
 *
 *    # Values can be retrieved in various ways:
 *    >>> t.get()
 *    (1, 2, 3)
 *    >>> t[0]
 *    1
 *    >>> t.third
 *    3
 * \endcode
 */
template<typename T, size_t N> class Tuple: public TupleBase<T,N> {
private:
  // prevent construction of generic form, as it provides no storage
  Tuple();
  ~Tuple();
};

template<typename T> class Tuple<T,1>: public TupleBase<T,1> {
public:
  T first;  //!< First tuple element
};

template<typename T> class Tuple<T,2>: public TupleBase<T,2> {
public:
  T first;  //!< First tuple element
  T second; //!< Second tuple element
};

template<typename T> class Tuple<T,3>: public TupleBase<T,3> {
public:
  T first;  //!< First tuple element
  T second; //!< Second tuple element
  T third;  //!< Third tuple element
};

template<typename T> class Tuple<T,4>: public TupleBase<T,4> {
public:
  T first;  //!< First tuple element
  T second; //!< Second tuple element
  T third;  //!< Third tuple element
  T fourth; //!< Fourth tuple element
};

/*!
 * Array<T,N> provides an array of N elements of type T.
 */
template<typename T, size_t N> class Array: public TupleBase<T,N> {
public:
  T elems[N];
};

inline hid_gc h5tupleType( hid_t element, size_t num )
{
  hsize_t dims[1];

  dims[0] = num;

  hid_gc tuple_id(H5Tarray_create2(element, 1, dims), H5Tclose, "Could not create tuple datatype");

  return tuple_id;
}

}

#endif

