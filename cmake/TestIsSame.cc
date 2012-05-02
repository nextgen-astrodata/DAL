/*
 * Usage: define SRC_TYPE and DEST_TYPE; this program
 *        will only compile succesfully if both
 *        types are the same to the compiler.
 */

#include <iostream>
#include "hdf5/types/issame.h"

using namespace DAL;

#if !defined SRC_TYPE || !defined DEST_TYPE
#error Define SRC_TYPE and DEST_TYPE. 
#endif

template<int T> class Tester {
public:
  // trigger compile error if this object is constructed
  static void valid() { 0 = 1; };
};

template<> class Tester<1> {
public:
  // succesfully compile this object
  static void valid() {};
};

int main() {
  Tester< IsSame<SRC_TYPE, DEST_TYPE>::Is >::valid();

  return 0;
}
