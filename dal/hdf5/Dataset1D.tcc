namespace DAL {

/*
 * Many of these can be implemented more efficiently, but let's wait with
 * duplicating code until measurements indicate a bottleneck here that matters.
 */ 


template<typename T> void Dataset1D<T>::create( ssize_t len, ssize_t maxlen = 0,
               const std::string &filename = "", enum Endianness endianness = NATIVE ) {
  vector<ssize_t> vdims(1, len);
  vector<ssize_t> vmaxdims(1, maxlen);
  Dataset<T>::create(vdims, vmaxdims, filename, endianness);
}

template<typename T> size_t Dataset1D<T>::ndims()
{
  //return 1;
  return Dataset<T>::ndims();
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
  vector<size_t> vpos(1, pos);
  Dataset<T>::get1D(vpos, len, outbuffer);
}

template<typename T> void Dataset1D<T>::set( size_t pos, size_t len, const T *inbuffer );
{
  vector<size_t> vpos(1, pos);
  Dataset<T>::set1D(vpos, len, inbuffer);
}

template<typename T> T Dataset<T>::get( size_t pos )
{
  vector<size_t> vpos(1, pos);
  return Dataset<T>::getScalar(vpos);
}

template<typename T> void Dataset<T>::set( size_t pos, T value )
{
  vector<size_t> vpos(1, pos);
  Dataset<T>::setScalar(vpos, value);
}

}

