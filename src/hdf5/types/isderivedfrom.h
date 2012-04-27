#ifndef __ISDERIVEDFROM__
#define __ISDERIVEDFROM__

// Excerpted from the book More Exceptional C++ by Herb Sutter.
// see http://www.gotw.ca/publications/mxc++-item-4.htm

// IsDerivedFrom<D,B>::Is == 1 at compile time if D is or derived from B, 0 otherwise (use #1).
//
// This allows one to select implementations based on D's class hierarchy, and thus
// create template specializations for whole class hierarchies at once. Example:
#if 0

template<typename T, int>
class XImpl
{
  // general case: T is not derived from Cloneable
}; 

template<typename T>
class XImpl<T, 1>
{
  // T is derived from Cloneable
}; 

template<typename T>
class X
{
  XImpl<T, IsDerivedFrom<T, Cloneable>::Is> impl_;
  // ... delegates to impl_ ...
};

#endif
// 
// alternatively (use #2), a class can be forced to inherit from B during its construction. Example:
//
#if 0

template<typename D>
class X : IsDerivedFrom<D,B>
{
  // ...
};

#endif
//
// The above code will only compile if D is or derives from B.

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
  IsDerivedFrom() { void(*p)(D*) = Constraints; }
};

// Force it to fail in the case where B is void

template<typename D>
class IsDerivedFrom<D, void>
{
public:
  enum { Is = 0 };

  IsDerivedFrom() { char* p = (int*)0; /* error */ }
};

#endif
