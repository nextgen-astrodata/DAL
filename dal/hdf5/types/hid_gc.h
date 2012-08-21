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
#ifndef DAL_HID_GC_H
#define DAL_HID_GC_H

#include <hdf5.h>
#include "dal/hdf5/exceptions/exceptions.h"

namespace DAL {

// Autocloses hid_t types using closefunc() on destruction, and keeps a reference count.
class hid_gc
{
public:
  // allow deference of actual construction to operator=
  hid_gc(): hid(0), closefunc(0) {}

  hid_gc(hid_t hid, hid_t (*closefunc)(hid_t) = 0, const std::string &errordesc = ""): hid(hid), closefunc(closefunc) {
    // checking for success here greatly reduces the code base
    if (hid <= 0)
      throw HDF5Exception(errordesc);

    H5Iinc_ref(hid);
  }

  hid_gc( const hid_gc &other ): hid(other.hid), closefunc(other.closefunc) {
    if (isset()) {
      H5Iinc_ref(hid);
    }  
  }

  ~hid_gc() {
    if (isset() && H5Idec_ref(hid) == 1 && closefunc) {
      closefunc(hid);
    }
  }

  hid_gc &operator=( hid_gc other ) {
    swap(*this, other);
    return *this;
  }

  friend void swap( hid_gc& first, hid_gc& second ) {
    using namespace std;
    swap(first.hid,       second.hid);
    swap(first.closefunc, second.closefunc);
  }

  operator hid_t() const { return hid; }

  /*!
   * Returns true if this object wraps a hid.
   */
  bool isset() const { return hid > 0; }

private:
  hid_t hid;
  hid_t (*closefunc)(hid_t);
};

// Autocloses hid_t types using closefunc() on destruction, without using reference counting.
//
// This variant is faster than hid_gc, but cannot be copied.
class hid_gc_noref
{
public:
  hid_gc_noref(hid_t hid, hid_t (*closefunc)(hid_t) = 0, const std::string &errordesc = ""): hid(hid), closefunc(closefunc) {
    // checking for success here greatly reduces the code base
    if (hid <= 0)
      throw HDF5Exception(errordesc);
  }

  ~hid_gc_noref() {
    if (isset() && closefunc) {
      closefunc(hid);
    }  
  }

  operator hid_t() const { return hid; }

  /*!
   * Returns true if this object wraps a hid.
   */
  bool isset() const { return hid > 0; }

private:
  // do not use
  hid_gc_noref( const hid_gc &other );
  hid_gc_noref &operator=( const hid_gc & );
  void swap( hid_gc& first, hid_gc& second );

  const hid_t hid;
  hid_t (*const closefunc)(hid_t);
};

}

#endif

