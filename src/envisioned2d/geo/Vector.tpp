#ifndef GEO_VECTOR_TPP
#define GEO_VECTOR_TPP


  namespace geo
  {
    template<typename TAxis>
    Vector<TAxis>::Vector()
    {
      x = 0;
      y = 0;
    }


    template<typename TAxis>
    Vector<TAxis>::Vector(TAxis x, TAxis y)
    {
      this->x = x;
      this->y = y;
    }

    template<typename TAxis>
    Vector<TAxis>::Vector(const Vector<TAxis> &vector)
    {
      this->x = vector.x;
      this->y = vector.y;
    }


    template<typename TAxis>
    Vector<TAxis>::~Vector()
    {

    }


    template<typename TAxis>
    void Vector<TAxis>::load(TAxis x, TAxis y)
    {
      this->x = 0;
      this->y = 0;
    }


    template<typename P1TAxis>
    template<typename P2TAxis>
    void Vector<P1TAxis>::load(const Vector<P2TAxis> &vector)
    {
      if((Vector<P1TAxis>*)&vector == this)
        return;

      x = vector.getX();
      y = vector.getY();
    }


    template<typename TAxis>
    void Vector<TAxis>::clear()
    {
      x = 0;
      y = 0;
    }


    template<typename TAxis>
    TAxis Vector<TAxis>::getX() const
    {
      return x;
    }


    template<typename TAxis>
    TAxis Vector<TAxis>::getY() const
    {
      return y;
    }


    template<typename TAxis>
    void Vector<TAxis>::setX(TAxis x)
    {
      this->x = x;
    }


    template<typename TAxis>
    void Vector<TAxis>::setY(TAxis y)
    {
      this->y = y;
    }


    template<typename TAxis>
    void Vector<TAxis>::incX(TAxis dx)
    {
      x += dx;
    }


    template<typename TAxis>
    void Vector<TAxis>::incY(TAxis dy)
    {
      y += dy;
    }


    template<typename TAxis>
    void Vector<TAxis>::decX(TAxis dx)
    {
      x -= dx;
    }


    template<typename TAxis>
    void Vector<TAxis>::decY(TAxis dy)
    {
      y -= dy;
    }


    template<typename TAxis>
    double Vector<TAxis>::getLength() const
    {
      return std::sqrt((double)(x*x + y*y));
    }


    template<typename TAxis>
    double Vector<TAxis>::getDirection() const
    {
      return std::atan2(-(double)y,(double)x);
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis> &Vector<V1TAxis>::operator=(const Vector<V2TAxis> &vector2)
    {
      /* Sync this typename */
        this->x = (V1TAxis)vector2.x;
        this->y = (V1TAxis)vector2.y;

      /* Return */
        return *this;
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    bool Vector<V1TAxis>::operator==(const Vector<V2TAxis> &vector)
    {
      return x == vector.x && y == vector.y;
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    bool Vector<V1TAxis>::operator!=(const Vector<V2TAxis> &vector)
    {
      return !operator=(vector);
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis> Vector<V1TAxis>::operator+(const Vector<V2TAxis> &vector2) const
    {
      Vector<V1TAxis> resvector(*this);

      /* Add */
        resvector.x += vector2.x;
        resvector.y += vector2.y;

      /* Return */
        return resvector;
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis> Vector<V1TAxis>::operator-(const Vector<V2TAxis> &vector2) const
    {
      Vector<V1TAxis> resvector(*this);

      /* Add */
        resvector.x -= vector2.x;
        resvector.y -= vector2.y;

      /* Return */
        return resvector;
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis> &Vector<V1TAxis>::operator-=(const Vector<V2TAxis> &vector2)
    {
      /* Take */
        x -= vector2.x;
        y -= vector2.y;

      /* Return */
        return *this;
    }


    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis> &Vector<V1TAxis>::operator+=(const Vector<V2TAxis> &vector2)
    {
      /* Add */
        x += vector2.x;
        y += vector2.y;

      /* Return */
        return *this;
    }


    template<typename TAxis>
    template<typename TOp>
    Vector<TAxis> Vector<TAxis>::operator/(const TOp &divider) const
    {
      Vector<TAxis> resvec;

      /* Divide */
        resvec.x = x / divider;
        resvec.y = y / divider;

      /* Return */
        return resvec;
    }

    template<typename TAxis>
    template<typename TOp>
    Vector<TAxis> Vector<TAxis>::operator*(const TOp &factor) const
    {
      Vector<TAxis> resvec;

      /* Multi */
        resvec.x = x * factor;
        resvec.y = y * factor;

      /* Return */
        return resvec;
    }


    template<typename TAxis>
    template<typename TOp>
    Vector<TAxis> &Vector<TAxis>::operator/=(const TOp &divider)
    {
      /* Divide */
        x /= divider;
        y /= divider;

      /* Return */
        return *this;
    }


    template<typename TAxis>
    template<typename TOp>
    Vector<TAxis> &Vector<TAxis>::operator*=(const TOp &factor)
    {
      /* Multi */
        x *= factor;
        y *= factor;

      /* Return */
        return *this;
    }



    template<typename V1TAxis>
    template<typename V2TAxis>
    Vector<V1TAxis>::operator Vector<V2TAxis>()
    {
      Vector<V2TAxis> resvector;

      /* Set */
        resvector.setX(x);
        resvector.setY(y);

      /* Return */
        return resvector;
    }

  }





#endif // VECTOR2D_HPP
