#ifndef DAL_ISDERIVEDFROM_H
#define DAL_ISDERIVEDFROM_H

#include "issame.h"

namespace DAL {

// Excerpted from the book More Exceptional C++ by Herb Sutter.
// see http://www.gotw.ca/publications/mxc++-item-4.htm

/*!
 * The IsDerivedFrom<D,B> class provides class hierarchy information at compile time, allowing
 * the programmer to implement different behaviours for different class hierarchies.
 *
 * The class provides two constructs.
 *   1: IsDerivedFrom<D,B>::Is == 1 at compile time if D is or derived from B, 0 otherwise.
 *   2: Inheriting from IsDerivedFrom<D,B> will only compile if D is or derived from B.
 *
 * Example uses:
 *   1: template<typename T, int> class Impl  { ... generic implementation ... };
 *      template<typename T,   1> class Impl  { ... specialization for B and subclasses ... };
 *      template<typename T>      class Class { Impl<T, IsDerivedFrom<T, B>::Is> impl;
 *                                              ... delegating to impl ... };
 *
 *      The above example will provide the generic impl if T is not derived from B (IsDerivedFrom::Is == 0),
 *      and the specialization if T is derived from B (IsDerivedFrom::Is == 1).
 *
 *   2: template<typename D> class Class: IsDerivedFrom<D,B> { ... };
 *
 *      The above example will throw a compile error if D is not (derived from) B.
 */
template<typename D, typename B>
class IsDerivedFrom
{
  // 1. Create a system to allow value-checking at compile time using IsDerivedFrom<D,B>::Is

  class No { };
  class Yes { No no[3]; }; // ensure sizeof(Yes) != sizeof(No)

  static Yes Test( B* ); // not defined
  static No Test( ... ); // not defined 

public:
  // A cast to D* steers the code to Test(B*) if B is a base class of D, and to Test(...) otherwise.
  // Because sizeof only evaluates types, no actual code is generated, and thus the Test() routine
  // implementations are not necessary.
  enum { Is = sizeof(Test(static_cast<D*>(0))) == sizeof(Yes) }; 

  // 2. Force derivation if a class inherits from IsDerivedFrom.

  // Note that, like all template functions, the code below will only be evaluated
  // if it is used, allowing safe compilation of the code above.

private:
  // Compiles only if D is-a B.
  static void Constraints(D* p) {
    B* pb = p;
    (void)pb; // suppress warning about an unused variable
  }

public:
  IsDerivedFrom() { void(*p)(D*) = Constraints; (void)p; }
};

// Force it to fail in the case where B is void (unless D is void as well)

template<typename D>
class IsDerivedFrom<D, void>
{
public:
  enum { Is = IsSame<D, void>::Is };

  // Note: C++11 14.6.8 says the template specialisation
  //       is ill-formed if it does not compile for any
  //       value of D. This can cause a compiler to bail
  //       even if this specialisation is never used.
  //
  //       clang is an example of such a compiler.
  IsDerivedFrom() { D* p = (void*)0; (void)p; /* error if D != void */ }
};

}

#endif
