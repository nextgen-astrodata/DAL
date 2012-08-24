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
namespace DAL {

/*
 * Many of these can be implemented more efficiently, but let's wait with
 * duplicating code until measurements indicate a bottleneck here that matters.
 */ 


template<typename T> Dataset1D<T>& Dataset1D<T>::create( ssize_t len, ssize_t maxlen,
               const std::string &filename, enum Dataset<T>::Endianness endianness ) {
  std::vector<ssize_t> vdims(1, len);
  std::vector<ssize_t> vmaxdims(1, maxlen);
  Dataset<T>::create(vdims, vmaxdims, filename, endianness);
  return *this;
}

template<typename T> ssize_t Dataset1D<T>::dims()
{
  return Dataset<T>::dims()[0];
}

template<typename T> ssize_t Dataset1D<T>::maxdims()
{
  return Dataset<T>::maxdims()[0];
}

template<typename T> void Dataset1D<T>::resize(ssize_t newlen )
{
  std::vector<ssize_t> newdims(1, newlen);
  Dataset<T>::resize(newdims);
}

template<typename T> void Dataset1D<T>::get( size_t pos, size_t len, T *outbuffer )
{
  std::vector<size_t> vpos(1, pos);
  Dataset<T>::get1D(vpos, len, outbuffer);
}

template<typename T> void Dataset1D<T>::set( size_t pos, size_t len, const T *inbuffer )
{
  std::vector<size_t> vpos(1, pos);
  Dataset<T>::set1D(vpos, len, inbuffer);
}

template<typename T> T Dataset1D<T>::get( size_t pos )
{
  std::vector<size_t> vpos(1, pos);
  return Dataset<T>::getScalar(vpos);
}

template<typename T> void Dataset1D<T>::set( size_t pos, T value )
{
  std::vector<size_t> vpos(1, pos);
  Dataset<T>::setScalar(vpos, value);
}

}

