#ifndef DAL_ISSAME_H
#define DAL_ISSAME_H

namespace DAL {

/*!
 * IsSame<T,U>::Is evaluates to true (at compile time!)
 * if T is the same type as U.
 */
template<typename T, typename U> class IsSame
{
public:
  enum { Is = false };
};

template<typename T> class IsSame<T, T>
{
public:
  enum { Is = true };
};

}

#endif
