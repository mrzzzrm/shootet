#ifndef GEO_SIZE_TPP
#define GEO_SIZE_TPP

  namespace geo
  {
    template<typename T>
    Size<T>::Size()
    {
      init();
    }


    template<typename T>
    Size<T>::Size(const T &width, const T &height)
    {
      load(width, height);
    }


    template<typename T>
    Size<T>::Size(const Size &size)
    {
      load(size);
    }



    template<typename T>
    Size<T>::~Size()
    {

    }



    template<typename T>
    void Size<T>::load(const T &width, const T &height)
    {
      this->width = width;
      this->height = height;
    }


    template<typename T>
    template<typename T2>
    void Size<T>::load(const Size<T2> &size)
    {
      width = static_cast<T>(size.width);
      height = static_cast<T>(size.height);
    }


    template<typename T>
    void Size<T>::clear()
    {
      init();
    }


    template<typename T>
    const T &Size<T>::getWidth() const
    {
      return width;
    }


    template<typename T>
    const T &Size<T>::getHeight() const
    {
      return height;
    }


    template<typename T>
    void Size<T>::setWidth(const T &width)
    {
      this->width = width;
    }


    template<typename T>
    void Size<T>::setHeight(const T &height)
    {
      this->height = height;
    }


    template<typename T>
    T Size<T>::getSize() const
    {
      return width*height;
    }


    template<typename T>
    template<typename T2>
    Size<T> &Size<T>::operator=(const Size<T2> &size)
    {
      load(size);
      return *this;
    }


    template<typename T>
    template<typename TFac>
    Size<T> Size<T>::operator*(const TFac &fac) const
    {
      Size res(*this);
      return res *= fac;
    }


    template<typename T>
    template<typename TDiv>
    Size<T> Size<T>::operator/(const TDiv &div) const
    {
      Size res(*this);
      return res /= div;
    }


    template<typename T>
    template<typename TFac>
    Size<T> &Size<T>::operator*=(const TFac &fac)
    {
      width = static_cast<T>(width*fac);
      height = static_cast<T>(height*fac);

      return *this;
    }


    template<typename T>
    template<typename TDiv>
    Size<T> &Size<T>::operator/=(const TDiv &div)
    {
      if(div == 0)
        throw error::Exception() << "Cannot divide by '0'";

      width = static_cast<T>(width/div);
      height = static_cast<T>(height/div);

      return *this;
    }


    template<typename T>
    template<typename T2>
    Size<T> Size<T>::operator*(const Size<T2> &size) const
    {
      Size<T> res(*this);
      return res *= size;
    }


    template<typename T>
    template<typename T2>
    Size<T> &Size<T>::operator*=(const Size<T2> &size)
    {
      width *= size.width;
      height *= size.height;

      return *this;
    }

    template<typename T>
    Size<T>::operator T() const
    {
      return width * height;
    }


    template<typename T>
    template<typename T2>
    Size<T>::operator Size<T2>()
    {
      return Size<T2>((T2)width, (T2)height);
    }


    template<typename T>
    void Size<T>::init()
    {
      width = 0;
      height = 0;
    }

  }

#endif // GEO_SIZE_TPP
