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

#include <cstddef> // import size_t, ssize_t, ptrdiff_t, etc

// Tester<T,U> can be constructed if T == U

template<typename T, typename U> class Tester {
private:
  Tester();
};

template<typename T> class Tester<T,T> {
};

int main() {
  (void)Tester<TYPE_A, TYPE_B>();

  return 0;
}
