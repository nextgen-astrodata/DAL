/*
 * Usage: define SRC_TYPE and DEST_TYPE; this program
 *        will only compile succesfully if both
 *        types are the same to the compiler.
 *
 * For example
 *
 * g++ -DSRC_TYPE=int -DDEST_TYPE="signed int" TestIsSame.cc
 *
 * will compile, while
 *
 * g++ -DSRC_TYPE=int -DDEST_TYPE="unsigned int" TestIsSame.cc
 *
 * will not.
 *
 */

#if !defined SRC_TYPE || !defined DEST_TYPE
#error Define SRC_TYPE and DEST_TYPE. 
#endif

#include <iostream>

// Don't use hdf5/types/issame.h, as compilation could also
// fail if that header cannot be found.

// Tester<T,U> compiles if T == U

template<typename T, typename U> class Tester {
public:
  static void valid() { 0 = 1; /* trigger a compile error */ };
};

template<typename T> class Tester<T,T> {
public:
  static void valid() { /* don't trigger a compile error */ };
};

int main() {
  Tester<SRC_TYPE, DEST_TYPE>::valid();

  return 0;
}
