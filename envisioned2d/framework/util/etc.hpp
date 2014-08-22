#ifndef UTIL_ETC_HPP
#define UTIL_ETC_HPP

  #include "etc/int.h"

  namespace util
  {
    template<typename T> const T &abs_min(const T &t1, const T &t2);
    template<typename T> const T &abs_max(const T &t1, const T &t2);

    template<typename T> s8 sgn(const T &t);

    template<typename T> bool in_range(const T &value, const T &min, const T &max);
    template<typename T> bool in_range(const T &value, const T &max);

    template<typename T> T &limit(T &value, const T &min, const T &max);
    template<typename T> T &limit(T &value, const T &max);
  }

  #include "./etc.tpp"

#endif // UTIL_ETC_HPP
