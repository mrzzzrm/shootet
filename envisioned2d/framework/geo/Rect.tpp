#ifndef GEO_RECT_TPP
#define GEO_RECT_TPP

/*
  Class Rect
*/
  namespace geo
  {
    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis>::Rect()
    {
      /* Init */
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis>::Rect(TPos x, TPos y, TAxis width, TAxis height)
    {
      /* Init */
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis>::Rect(const Rect<TPos, TAxis> &rect)
    {
      /* Sync data */
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis>::~Rect()
    {
      clear();
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::load(TPos x, TPos y, TAxis width, TAxis height)
    {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    void Rect<R1TPos, R1TAxis>::load(const Rect<R2TPos, R2TAxis> &rect)
    {
      if(&rect == this)
        return;

      x = rect.x;
      y = rect.y;
      width = rect.width;
      height = rect.height;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::clear()
    {
      x = 0;
      y = 0;
      width = 0;
      height = 0;
    }

    template<typename TPos, typename TAxis>
    TPos Rect<TPos, TAxis>::getX() const
    {
      return x;
    }


    template<typename TPos, typename TAxis>
    TPos Rect<TPos, TAxis>::getY() const
    {
      return y;
    }


    template<typename TPos, typename TAxis>
    TAxis Rect<TPos, TAxis>::getWidth() const
    {
      return width;
    }


    template<typename TPos, typename TAxis>
    TAxis Rect<TPos, TAxis>::getHeight() const
    {
      return height;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::setX(TPos x)
    {
      this->x = x;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::setY(TPos y)
    {
      this->y = y;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::setWidth(TAxis width)
    {
      this->width = width;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::setHeight(TAxis height)
    {
      this->height = height;
    }

    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::incX(TPos dx)
    {
      x += dx;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::incY(TPos dy)
    {
      y += dy;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::incWidth(TAxis dwidth)
    {
      width += dwidth;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::incHeight(TAxis dheight)
    {
      height += dheight;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::decX(TPos dx)
    {
      x -= dx;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::decY(TPos dy)
    {
      y -= dy;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::decWidth(TAxis dwidth)
    {
      width -= dwidth;
    }


    template<typename TPos, typename TAxis>
    void Rect<TPos, TAxis>::decHeight(TAxis dheight)
    {
      height -= dheight;
    }


    template<typename TPos, typename TAxis>
    inline void Rect<TPos, TAxis>::normalise()
    {
      if(width < 0)
      {
        x += width;
        width = -width;
      }

      if(height < 0)
      {
        y += height;
        height = -height;
      }
    }




    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::isCollision(const Rect<R2TPos, R2TAxis> &rect2, const geo::IntVector &offset1, const geo::IntVector &offset2, const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
    {
      Rect<R1TPos, R1TAxis> mrect1(*this);
      Rect<R2TPos, R2TAxis> mrect2(rect2);

      if(width == 0 || height == 0 || rect2.width == 0 || rect2.height == 0)
        return false;

      mrect1.decX((R1TPos)(mrect1.width * alignment1.getX()));
      mrect1.decY((R1TPos)(mrect1.height * alignment1.getY()));
      mrect2.decX((R2TPos)(mrect2.width * alignment2.getX()));
      mrect2.decY((R2TPos)(mrect2.height * alignment2.getY()));

      mrect1 += offset1;
      mrect2 += offset2;

      return mrect1.isCollisionRaw(mrect2);
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::isCollision(const Rect<R2TPos, R2TAxis> &rect2) const
    {
      R1TPos ax, ay;
      R1TAxis aw, ah;

      /* Get surrounding rect */
      if(x < (R1TPos)rect2.x)
        ax = x;
      else
        ax = (R1TPos)rect2.x;

      if(y < (R1TPos)rect2.y)
        ay = y;
      else
        ay = (R1TPos)rect2.y;

      if((R1TAxis)(x + width) > (R1TAxis)(rect2.x + rect2.width))
        aw = (R1TAxis)(x + width - ax);
      else
        aw = (R1TAxis)(rect2.x + rect2.width - ax);

      if((R1TAxis)(y + height) > (R1TAxis)(rect2.y + rect2.height))
        ah = (R1TAxis)(y + height - ay);
      else
        ah = (R1TAxis)(rect2.y + rect2.height - ay);


      /* Check for overlap */
      if((width + rect2.width > aw) && (height + rect2.height > ah))
        return true;
      else
        return false;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    Rect<R1TPos, R1TAxis> *Rect<R1TPos, R1TAxis>::getCutrect(const Rect<R2TPos, R2TAxis> &rect2, const geo::IntVector &offset1, const geo::IntVector &offset2, const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
    {
      Rect<R1TPos, R1TAxis> mrect1(*this);
      Rect<R2TPos, R2TAxis> mrect2(rect2);


      mrect1.decX((R1TPos)(mrect1.width * alignment1.getX()));
      mrect1.decY((R1TPos)(mrect1.height * alignment1.getY()));
      mrect2.decX((R2TPos)(mrect2.width * alignment2.getX()));
      mrect2.decY((R2TPos)(mrect2.height * alignment2.getY()));

      mrect1 += offset1;
      mrect2 += offset2;

      return mrect1.getCutrectRaw(mrect2);
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    Rect<R1TPos, R1TAxis> *Rect<R1TPos, R1TAxis>::getCutrect(const Rect<R2TPos, R2TAxis> &rect2) const
    {
      R1TPos xl, xr, yo, yu;

      /* Get cutrect */
        if(rect2.x > x)
          xl = rect2.x;
        else
          xl = x;

        if(rect2.y > y)
          yo = rect2.y;
        else
          yo = y;


        if(x + width < rect2.x + rect2.width)
          xr = x + width;
        else
          xr = rect2.x + rect2.width;

        if(y + height < rect2.y + rect2.height)
          yu = y + height;
        else
          yu = rect2.y + rect2.height;


      /* Check if crect is valid/Return */
        if((xl < xr) && (yo < yu))
          return new Rect<R1TPos, R1TAxis>(xl, yo, xr-xl, yu-yo);
        else
          return NULL;

    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::isCovering(const Rect<R2TPos, R2TAxis> &rect2, const geo::IntVector &offset1, const geo::IntVector &offset2, const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
    {
      Rect<R1TPos, R1TAxis> mrect1(*this);
      Rect<R2TPos, R2TAxis> mrect2(rect2);

      mrect1.decX((R1TPos)(mrect1.width * alignment1.getX()));
      mrect1.decY((R1TPos)(mrect1.height * alignment1.getY()));
      mrect2.decX((R2TPos)(mrect2.width * alignment2.getX()));
      mrect2.decY((R2TPos)(mrect2.height * alignment2.getY()));

      mrect1 += offset1;
      mrect2 += offset2;

      return mrect1.isCovering(mrect2);
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::isCovering(const Rect<R2TPos, R2TAxis> &rect2) const
    {
      if(x > rect2.x || y > rect2.y)
        return false;

      if(x + width < rect2.x + rect2.width || y + height < rect2.y + rect2.height)
        return false;

      return true;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    Rect<R1TPos, R1TAxis> &Rect<R1TPos, R1TAxis>::operator=(const Rect<R2TPos, R2TAxis> &rect)
    {
      load(rect);
      return *this;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::operator==(const Rect<R2TPos, R2TAxis> &rect)
    {
      return x == rect.x && y == rect.y && width == rect.width && height == rect.height;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    bool Rect<R1TPos, R1TAxis>::operator!=(const Rect<R2TPos, R2TAxis> &rect)
    {
      return !operator==(rect);
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> Rect<TPos, TAxis>::operator+(const Vector<TPos> &vec) const
    {
      Rect<TPos, TAxis> resrect(*this);

      resrect += vec;

      return resrect;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> &Rect<TPos, TAxis>::operator+=(const Vector<TPos> &vec)
    {
      /* Add */
        x += vec.getX();
        y += vec.getY();

      /* Return */
        return *this;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> Rect<TPos, TAxis>::operator-(const Vector<TPos> &vec) const
    {
      Rect<TPos, TAxis> resrect(*this);

      /* Add */
        resrect -= vec;

      /* Return */
        return resrect;
    }


    template<typename TPos, typename TAxis>
    Rect<TPos, TAxis> &Rect<TPos, TAxis>::operator-=(const Vector<TPos> &vec)
    {
      /* Add */
        x -= vec.getX();
        y -= vec.getY();

      /* Return */
        return *this;
    }


    template<typename R1TPos, typename R1TAxis>
    template<typename R2TPos, typename R2TAxis>
    Rect<R1TPos, R1TAxis>::operator Rect<R2TPos, R2TAxis>()
    {
      Rect<R2TPos, R2TAxis> resrect
        (
          static_cast<R2TPos>(x),
          static_cast<R2TPos>(y),
          static_cast<R2TAxis>(width),
          static_cast<R2TAxis>(height)
        );

      return resrect;
    }

  }



#endif // RECT_HPP
