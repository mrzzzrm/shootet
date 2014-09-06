#ifndef GEO_GEO_TPP
#define GEO_GEO_TPP

  namespace geo
  {
    template<typename PTPos, typename VTAxis>
    Point<PTPos> operator+(const Point<PTPos> &point, const Vector<VTAxis> &vector)
    {
      Point<PTPos> respoint;

      respoint.setX(static_cast<PTPos>(point.getX() + vector.getX()));
      respoint.setY(static_cast<PTPos>(point.getY() + vector.getY()));

      return respoint;
    }


    template<typename PTPos, typename VTAxis>
    Point<PTPos> operator-(const Point<PTPos> &point, const Vector<VTAxis> &vector)
    {
      Point<PTPos> respoint;

      respoint.setX(static_cast<PTPos>(point.getX() - vector.getX()));
      respoint.setY(static_cast<PTPos>(point.getY() - vector.getY()));

      return respoint;
    }


    template<typename PTPos, typename VTAxis>
    Point<PTPos> &operator+=(Point<PTPos> &point, const Vector<VTAxis> &vector)
    {
      point.setX(static_cast<PTPos>(point.getX() + vector.getX()));
      point.setY(static_cast<PTPos>(point.getY() + vector.getY()));

      return point;
    }


    template<typename PTPos, typename VTAxis>
    Point<PTPos> &operator-=(Point<PTPos> &point, const Vector<VTAxis> &vector)
    {
      point.setX(static_cast<PTPos>(point.getX() - vector.getX()));
      point.setY(static_cast<PTPos>(point.getY() - vector.getY()));

      return point;
    }

    template<typename RTPos, typename RTAxis, typename VTAxis>
    Rect<RTPos, RTAxis> &operator+(const Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector)
    {
      Rect<RTPos, RTAxis> resrect(rect);

      resrect.setX(static_cast<RTPos>(resrect.getX() + vector.getX()));
      resrect.setY(static_cast<RTPos>(resrect.getY() + vector.getY()));

      return resrect;
    }


    template<typename RTPos, typename RTAxis, typename VTAxis>
    Rect<RTPos, RTAxis> &operator-(const Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector)
    {
      Rect<RTPos, RTAxis> resrect(rect);

      resrect.setX(static_cast<RTPos>(resrect.getX() - vector.getX()));
      resrect.setY(static_cast<RTPos>(resrect.getY() - vector.getY()));

      return resrect;
    }



    template<typename RTPos, typename RTAxis, typename VTAxis>
    Rect<RTPos, RTAxis> &operator+=(Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector)
    {
      rect.setX(static_cast<RTPos>(rect.getX() + vector.getX()));
      rect.setY(static_cast<RTPos>(rect.getY() + vector.getY()));

      return rect;
    }



    template<typename RTPos, typename RTAxis, typename VTAxis>
    Rect<RTPos, RTAxis> &operator-=(Rect<RTPos, RTAxis> &rect, const Vector<VTAxis> &vector)
    {
      rect.setX(static_cast<RTPos>(rect.getX() - vector.getX()));
      rect.setY(static_cast<RTPos>(rect.getY() - vector.getY()));

      return rect;
    }


    template<typename CTPos, typename CTRadius, typename VTAxis>
    Circle<CTPos, CTRadius> &operator+(const Circle<CTPos, CTRadius> &circle, const Vector<VTAxis> &vector)
    {
      Circle<CTPos, CTRadius> res(circle);
      return res += vector;
    }


    template<typename CTPos, typename CTRadius, typename VTAxis>
    Circle<CTPos, CTRadius> &operator-(const Circle<CTPos, CTRadius> &circle, const Vector<VTAxis> &vector)
    {
      Circle<CTPos, CTRadius> res(circle);
      return res -= vector;
    }


    template<typename CTPos, typename CTRadius, typename VTAxis>
    Circle<CTPos, CTRadius> &operator+=(Circle<CTPos, CTRadius> &circle, const Vector<VTAxis> &vector)
    {
      circle.incX((CTPos)vector.getX());
      circle.incY((CTPos)vector.getY());

      return circle;
    }


    template<typename CTPos, typename CTRadius, typename VTAxis>
    Circle<CTPos, CTRadius> &operator-=(Circle<CTPos, CTRadius> &circle, const Vector<VTAxis> &vector)
    {
      circle.decX((CTPos)vector.getX());
      circle.decY((CTPos)vector.getY());

      return circle;
    }


    template<typename TPos>
    Vector<TPos> operator-(const Point<TPos> &point1, const Point<TPos> &point2)
    {
      return Vector<TPos>(point1.getX() - point2.getX(), point1.getY() - point2.getY());
    }







    template<typename TCoordinate>
    Vector<TCoordinate> point_to_vector(const Point<TCoordinate> &point)
    {
      return Vector<TCoordinate>(point.getX(), point.getY());
    }


    template<typename TCoordinate>
    Point<TCoordinate> vector_to_point(const Vector<TCoordinate> &vector)
    {
      return Point<TCoordinate>(vector.getX(), vector.getY());
    }






    template<typename TAxis>
    Rect<TAxis, TAxis> size_to_rect(const Size<TAxis> &size)
    {
      return Rect<TAxis, TAxis>(0, 0, size.getWidth(), size.getHeight());
    }


    template<typename TPos, typename TAxis>
    Size<TAxis> rect_to_size(const Rect<TPos, TAxis> &rect)
    {
      return Size<TAxis>(rect.getWidth(), rect.getHeight());
    }







    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> rect_translate_negative_axises(const Rect<TPos, TAxis> &rect, const Size<TAxis> &size)
    {
      Rect<TPos, TAxis> res(rect);

      if(rect.getWidth() < 0)
        res.setWidth(size.getWidth() + rect.getWidth() + 1 - rect.getX());
      if(rect.getHeight() < 0)
        res.setHeight(size.getHeight() + rect.getHeight() + 1 - rect.getY());

      return res;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> rect_translate_negative_axises(const Rect<TPos, TAxis> &rect, const Rect<TPos, TAxis> &targetrect)
    {
      Rect<TPos, TAxis> res(rect);

      if(rect.getWidth() < 0)
        res.setWidth(targetrect.getWidth() + rect.getWidth() - rect.getX() + 1);
      if(rect.getHeight() < 0)
        res.setHeight(targetrect.getHeight() + rect.getHeight() - rect.getX() + 1);

      res.incX(targetrect.getX());
      res.incY(targetrect.getY());

      return res;
    }







    template<typename PTPos, typename RTPos, typename RTAxis>
    bool is_point_in_rect(const Point<PTPos> &point, const Rect<RTPos, RTAxis> &rect)
    {
      Rect<RTPos, RTAxis> nrect(rect);

      nrect.normalise();

      if(point.getX() < (PTPos)nrect.getX() || point.getY() < (PTPos)nrect.getY())
        return false;
      else if(point.getX() >= (PTPos)(nrect.getX() + nrect.getWidth()) || point.getY() >= (PTPos)(nrect.getY() + nrect.getHeight()))
        return false;
      else
        return true;
    }


    template<typename PTPos, typename STAxis>
    bool is_point_in_size(const Point<PTPos> &point, const Size<STAxis> &size)
    {
      if(point.getX() >= (PTPos)(size.getWidth()) || point.getY() >= (PTPos)(size.getHeight()))
        return false;
      else
        return true;
    }




    template<typename T>
    geo::Vector<T> operator*(const etc::Alignment &alignment,const geo::Size<T> &size)
    {
      geo::Vector<T> res;

      res.setX((T)(alignment.getX() * size.getWidth()));
      res.setY((T)(alignment.getY() * size.getHeight()));

      return res;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> rect_align(const Rect<TPos, TAxis> &rect, const etc::Alignment &alignment)
    {
      Rect<TPos, TAxis> res(rect);

      res.decX((TPos)(rect.getWidth() * alignment.getX()));
      res.decY((TPos)(rect.getHeight() * alignment.getY()));

      return res;
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius> circle_align(const Circle<TPos, TRadius> &cricle, const etc::Alignment &alignment)
    {
      Circle<TPos, TRadius> res(cricle);

      res.decX((TPos)(cricle.getRadius()*2 * alignment.getX()));
      res.decY((TPos)(cricle.getRadius()*2 * alignment.getY()));

      return res;
    }

  }


#endif // GEO_GEO_HPP
