#ifndef __IMPLICITDOWNCAST__
#define __IMPLICITDOWNCAST__

namespace DAL {

/*!
 * ImplicitDowncast< B > returns an object that can implictly be
 * cast to classes derived from B. For example:
 *
 * \code
 * class base {};
 * class derived: public base {};
 *
 * int main() {
 *    derived d;
 *    base *b = &d;
 *
 *    base    &b2 = ImplicitDowncast<base>(*b);
 *    derived &d2 = ImplicitDowncast<base>(*b);
 *
 *    // Without ImplicitDowncast, C++ would require this instead:
 *    base    &b3 = dynamic_cast<base&>(*b);
 *    derived &d3 = dynamic_cast<derived&>(*b);
 * }
 * \endcode
 *
 * Note that no check is performed whether the cast will
 * be succesful.
 */
template<typename B>
class ImplicitDowncast {
public:
  ImplicitDowncast( B &base ): base(base) {}

  // the cast-operator can be templated based on return-type: just what we need!
  template<typename D> operator D() {
    return dynamic_cast<D&>(base);
  }

private:
  B &base;
};

}

#endif
