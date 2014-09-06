#ifndef GEO_POINT_TPP
#define GEO_POINT_TPP


/*
  Class Point
*/
  namespace geo
  {
    template<typename TPos>
    Point<TPos>::Point()
    {
      x = 0;
      y = 0;
    }


    template<typename TPos>
    Point<TPos>::Point(TPos x, TPos y)
    {
      this->x = x;
      this->y = y;
    }


    template<typename TPos>
    Point<TPos>::Point(const Point &point)
    {
      x = point.x;
      y = point.y;
    }


    template<typename TPos>
    Point<TPos>::~Point()
    {

    }


    template<typename TPos>
    void Point<TPos>::load(TPos x, TPos y)
    {
      this->x = x;
      this->y = y;
    }

    template<typename P1TPos>
    template<typename P2TPos>
    void Point<P1TPos>::load(const Point<P2TPos> &point)
    {
      if(&point == this)
        return;

      x = static_cast<P1TPos>(point.x);
      y = static_cast<P1TPos>(point.y);
    }


    template<typename TPos>
    void Point<TPos>::clear()
    {
      x = 0;
      y = 0;
    }


    template<typename TPos>
    TPos Point<TPos>::getX() const
    {
      return x;
    }


    template<typename TPos>
    TPos Point<TPos>::getY() const
    {
      return y;
    }


    template<typename TPos>
    void Point<TPos>::setX(TPos x)
    {
      this->x = x;
    }


    template<typename TPos>
    void Point<TPos>::setY(TPos y)
    {
      this->y = y;
    }


    template<typename TPos>
    void Point<TPos>::incX(TPos dx)
    {
      x += dx;
    }


    template<typename TPos>
    void Point<TPos>::incY(TPos dy)
    {
      y += dy;
    }


    template<typename TPos>
    void Point<TPos>::decX(TPos dx)
    {
      x -= dx;
    }


    template<typename TPos>
    void Point<TPos>::decY(TPos dy)
    {
      y -= dy;
    }


    template<typename P1TPos>
    template<typename P2TPos>
    Point<P1TPos> &Point<P1TPos>::operator=(const Point<P2TPos> &point)
    {
      x = static_cast<P1TPos>(point.getX());
      y = static_cast<P1TPos>(point.getY());

      return *this;
    }


    template<typename P1TPos>
    template<typename P2TPos>
    bool Point<P1TPos>::operator==(const Point<P2TPos> &point) const
    {
      return x == point.x && y == point.y;
    }


    template<typename P1TPos>
    template<typename P2TPos>
    bool Point<P1TPos>::operator!=(const Point<P2TPos> &point) const
    {
      return !operator==(point);
    }


    template<typename P1TPos>
    template<typename P2TPos>
    Point<P1TPos>::operator Point<P2TPos>() const
    {
      Point<P2TPos> respoint;

      respoint.setX((P2TPos)x);
      respoint.setY((P2TPos)y);

      return respoint;
    }
  }




#endif // GEO_POINT_HPP
