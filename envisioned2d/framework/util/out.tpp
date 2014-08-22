#ifndef UTIL_OUT_TPP
#define UTIL_OUT_TPP

namespace util
{
  /*
    namespace geo
  */
  template<typename TPos, typename TAxis>
  std::ostream &operator<<(std::ostream &out, const geo::Rect<TPos, TAxis> &rect)
  {
    return out << "[geo::Rect: " << rect.getX() << "/" << rect.getY() << " " << rect.getWidth() << "x" << rect.getHeight() << "]";
  }


  template<typename TPos>
  std::ostream &operator<<(std::ostream &out, const geo::Point<TPos> &point)
  {
    return out << "[geo::Point: " << point.getX() << "/" << point.getY() << "]";
  }


  template<typename TPos>
  std::ostream &operator<<(std::ostream &out, const geo::Vector<TPos> &vector)
  {
    return out << "[geo::Vector: " << vector.getX() << "/" << vector.getY() << "]";
  }


  template<typename TAxis>
  std::ostream &operator<<(std::ostream &out, const geo::Size<TAxis> &size)
  {
    return out << "[geo::Size: " << size.getWidth() << "/" << size.getHeight() << " = " << size.getWidth() * size.getHeight() << "]";
  }
}


#endif // UTIL_OUT_TPP
