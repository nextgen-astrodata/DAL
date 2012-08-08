/* Copyright 2011-2012  ASTRON, Netherlands Institute for Radio Astronomy
 * This file is part of the Data Access Library (DAL).
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DAL_IMPLICITDOWNCAST_H
#define DAL_IMPLICITDOWNCAST_H

#include "isderivedfrom.h"

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
  template<typename D> operator D&() {
    // trigger a compile error if an incompatible cast is requested
    IsDerivedFrom<D,B> type_safety;
    (void)type_safety;

    return dynamic_cast<D&>(base);
  }

private:
  B &base;
};

}

#endif
