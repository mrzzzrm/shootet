#ifndef GEO_GEO_HPP
#define GEO_GEO_HPP

  #include "./Rect.hpp"
  #include "./Point.hpp"
  #include "./Vector.hpp"
  #include "./Circle.hpp"
  #include "./Size.hpp"

  #include "etc/Alignment.hpp"

  namespace geo
  {
    /* Vector arithmetics */
      template<typename PTPos, typename VTAxis> Point<PTPos> operator+(const Point<PTPos> &point, const Vector<VTAxis> &vector);
      template<typename PTPos, typename VTAxis> Point<PTPos> operator-(const Point<PTPos> &point, const Vector<VTAxis> &vector);
      template<typename PTPos, typename VTAxis> Point<PTPos> &operator+=(Point<PTPos> &point, const Vector<VTAxis> &vector);
      template<typename PTPos, typename VTAxis> Point<PTPos> &operator-=(Point<PTPos> &point, const Vector<VTAxis> &vector);

      template<typename RTPos, typename RTAxis, typename VTAxis> Rect<RTPos, RTAxis> &operator+(const Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector);
      template<typename RTPos, typename RTAxis, typename VTAxis> Rect<RTPos, RTAxis> &operator-(const Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector);
      template<typename RTPos, typename RTAxis, typename VTAxis> Rect<RTPos, RTAxis> &operator+=(Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector);
      template<typename RTPos, typename RTAxis, typename VTAxis> Rect<RTPos, RTAxis> &operator-=(Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector);

      template<typename CTPos, typename CTRadius, typename VTAxis> Circle<CTPos, CTRadius> &operator+(const Circle<CTPos, CTRadius> &cricle, const Vector<VTAxis> &vector);
      template<typename CTPos, typename CTRadius, typename VTAxis> Circle<CTPos, CTRadius> &operator-(const Circle<CTPos, CTRadius> &cricle, const Vector<VTAxis> &vector);
      template<typename CTPos, typename CTRadius, typename VTAxis> Circle<CTPos, CTRadius> &operator+=(Circle<CTPos, CTRadius> &cricle, const Vector<VTAxis> &vector);
      template<typename CTPos, typename CTRadius, typename VTAxis> Circle<CTPos, CTRadius> &operator-=(Circle<CTPos, CTRadius> &cricle, const Vector<VTAxis> &vector);

      template<typename TPos> Vector<TPos> operator-(const Point<TPos> &point1, const Point<TPos> &point2);


    /* Convert between vectors and points */
      template<typename TCoordinate> Vector<TCoordinate> point_to_vector(const Point<TCoordinate> &point);
      template<typename TCoordinate> Point<TCoordinate> vector_to_point(const Vector<TCoordinate> &vector);


    /* Convert between size and rect */
      template<typename TAxis> Rect<TAxis, TAxis>          size_to_rect(const Size<TAxis> &size);
      template<typename TPos, typename TAxis> Size<TAxis> rect_to_size(const Rect<TPos, TAxis> &rect);


    /* Translate a rect with negative axises */
      template<typename TPos, typename TAxis> Rect<TPos, TAxis> rect_translate_negative_axises(const Rect<TPos, TAxis> &rect, const Size<TAxis> &size);
      template<typename TPos, typename TAxis> Rect<TPos, TAxis> rect_translate_negative_axises(const Rect<TPos, TAxis> &rect, const Rect<TPos, TAxis> &targetrect);


    /* Check if point is in size/rect */
      template<typename PTPos, typename RTPos, typename RTAxis> bool is_point_in_rect(const Point<PTPos> &point, const Rect<RTPos, RTAxis> &rect);
      template<typename PTPos, typename STAxis>                  bool is_point_in_size(const Point<PTPos> &point, const Size<STAxis> &size);


    /* Alignment */
      template<typename T> geo::Vector<T> operator*(const etc::Alignment &alignment, const geo::Size<T> &size);
      template<typename TPos, typename TAxis> Rect<TPos, TAxis> rect_align(const Rect<TPos, TAxis> &rect, const etc::Alignment &alignment);
      template<typename TPos, typename TRadius> Circle<TPos, TRadius> circle_align(const Circle<TPos, TRadius> &cricle, const etc::Alignment &alignment);





  }

  #include "./geo.tpp"

#endif // GEO_GEO_HPP
