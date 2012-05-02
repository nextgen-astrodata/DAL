/*
 * Usage: define TYPE_A and TYPE_B; this program
 *        will only compile succesfully if both
 *        types are the same to the compiler.
 *
 * For example
 *
 * g++ -DTYPE_A=int -DTYPE_B="signed int" TestIsSame.cc
 *
 * will compile, while
 *
 * g++ -DTYPE_A=int -DTYPE_B="unsigned int" TestIsSame.cc
 *
 * will not.
 *
 */

#if !defined TYPE_A || !defined TYPE_B
#error Define TYPE_A and TYPE_B. 
#endif

#include <sys/types.h> // import size_t and ssize_t

// Don't use hdf5/types/issame.h, as compilation could also
// fail if that header cannot be found.

// Tester<T,U> compiles if T == U

template<typename T, typename U> class Tester {
/* trigger a compile error if func() is used */
private:
  static void func();
};

template<typename T> class Tester<T,T> {
/* func() is valid to call */
public:
  static void func() {}
};

int main() {
  Tester<TYPE_A, TYPE_B>::func();

  return 0;
}
