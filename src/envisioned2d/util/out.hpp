#ifndef UTIL_OUT_HPP
#define UTIL_OUT_HPP

  #include <ostream>


  #include "util/Path.hpp"
  #include "geo/geo.hpp"

  namespace util
  {
    /* etc */
      std::ostream &operator<<(std::ostream &out, const util::Path &path);

    /* exception */
      std::ostream &operator<<(std::ostream &out, const error::Exception &exception);

    /* geo */
      template<typename TPos, typename TAxis>  std::ostream &operator<<(std::ostream &out, const geo::Rect<TPos, TAxis> &rect);
      template<typename TPos>                   std::ostream &operator<<(std::ostream &out, const geo::Point<TPos> &point);
      template<typename TPos>                   std::ostream &operator<<(std::ostream &out, const geo::Vector<TPos> &vector);
      template<typename TAxis>                  std::ostream &operator<<(std::ostream &out, const geo::Size<TAxis> &size);
  }

  /* Implementations for templates */
    #include "./out.tpp"

#endif // UTIL_OUT_HPP
