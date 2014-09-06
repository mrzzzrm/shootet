#ifndef GEO_CIRCLE_TPP
#define GEO_CIRCLE_TPP

  namespace geo
  {
    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius>::Circle()
    {
      init();
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius>::Circle(TPos x, TPos y, TRadius radius)
    {
      init();
      load(x, y, radius);
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius>::Circle(const Point<TPos> &point, TRadius radius)
    {
      init();
      load(point, radius);
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius>::Circle(const Circle &circle)
    {
      init();
      load(circle);
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius>::~Circle()
    {

    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::load(TPos x, TPos y, TRadius radius)
    {
      this->x = x;
      this->y = y;
      this->radius = radius;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::load(const Point<TPos> &point, TRadius radius)
    {
      x = point.getX();
      y = point.getY();
      this->radius = radius;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::load(const Circle &circle)
    {
      if((Circle<TPos, TRadius>*)&circle == this)
        return;

      x = circle.x;
      y = circle.y;
      radius = circle.radius;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::clear()
    {
      init();
    }


    template<typename TPos, typename TRadius>
    const Point<TPos> Circle<TPos, TRadius>::getPosition() const
    {
      return Point<TPos>(x, y);
    }



    template<typename TPos, typename TRadius>
    TPos Circle<TPos, TRadius>::getX() const
    {
      return x;
    }



    template<typename TPos, typename TRadius>
    TPos Circle<TPos, TRadius>::getY() const
    {
      return y;
    }



    template<typename TPos, typename TRadius>
    TRadius Circle<TPos, TRadius>::getRadius() const
    {
      return radius;
    }



    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::setPosition(const Point<TPos> &position)
    {
      x = position.getX();
      y = position.getY();
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::setX(TPos x)
    {
      this->x = x;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::setY(TPos y)
    {
      this->y = y;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::setRadius(TRadius radius)
    {
      this->radius = radius;
    }


    template<typename C1TPos, typename C1TRadius>
    template<typename C2TPos, typename C2TRadius>
    bool Circle<C1TPos, C1TRadius>::isCollision(const Circle<C2TPos, C2TRadius> &circle2, const geo::IntVector &offset1, const geo::IntVector &offset2, const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
    {
      Point<C1TPos> mid1(x + offset1.getX(), y + offset1.getY());
      Point<C2TPos> mid2(circle2.x + offset1.getX(), circle2.y + offset1.getY());

      /* Align */
      mid1.decX((int)(2 * radius * alignment1.getX()));
      mid1.decY((int)(2 * radius * alignment1.getY()));
      mid2.decX((int)(2 * circle2.radius * alignment2.getX()));
      mid2.decY((int)(2 * circle2.radius * alignment2.getY()));


      /* Check collision */
      if((mid1 - mid2).getLength() <= radius + circle2.radius)
        return true;
      else
        return false;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::incX(TPos delta)
    {
      x += delta;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::incY(TPos delta)
    {
      y += delta;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::decX(TPos delta)
    {
      x -= delta;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::decY(TPos delta)
    {
      y -= delta;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::incRadius(TRadius delta)
    {
      radius += delta;
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::decRadius(TRadius delta)
    {
      radius -= delta;
    }


    template<typename TPos, typename TRadius>
    Circle<TPos, TRadius> &Circle<TPos, TRadius>::operator=(const Circle &circle)
    {
      load(circle);
      return *this;
    }


    template<typename TPos1, typename TRadius1>
    template<typename TPos2, typename TRadius2>
    Circle<TPos1, TRadius1>::operator Circle<TPos2, TRadius2>()
    {
      return Circle<TPos2, TRadius2>(((TPos2)x,(TPos2)y, (TRadius2)radius));
    }


    template<typename TPos, typename TRadius>
    void Circle<TPos, TRadius>::init()
    {
      x = 0;
      y = 0;
      radius = 0;
    }


  }

#endif // GEO_CIRCLE_TPP
