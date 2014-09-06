#ifndef GEO_SIZE_HPP
#define GEO_SIZE_HPP


  #include "error/Exception.hpp"

  namespace geo
  {
    template<typename T>
    class Size
    {
      template<typename> friend class Size;

      public:

        Size();
        Size(const T &width, const T &height);
        Size(const Size &size);
        ~Size();


        /* Load */
          inline void load(const T &width, const T &height);
          template<typename T2> inline void load(const Size<T2> &size);


        /* Clear */
          inline void clear();


        /* Acess axises */
          inline const T &getWidth() const;
          inline const T &getHeight() const;
          inline void setWidth(const T &width);
          inline void setHeight(const T &height);


        /* Size */
          inline T getSize() const;


        /* Operators */
          template<typename T2> inline Size<T> &operator=(const Size<T2> &size);

          template<typename TFac> inline Size<T> operator*(const TFac &fac) const;
          template<typename TDiv> inline Size<T> operator/(const TDiv &div) const;
          template<typename TFac> inline Size<T> &operator*=(const TFac &fac);
          template<typename TDiv> inline Size<T> &operator/=(const TDiv &div);

          template<typename T2> inline Size<T> operator*(const Size<T2> &size) const;
          template<typename T2> inline Size<T> &operator*=(const Size<T2> &size);

//          template<typename TNum> bool operator>(const TNum &num) const;
//          template<typename TNum> bool operator>=(const TNum &num) const;
//          template<typename TNum> bool operator<(const TNum &num) const;
//          template<typename TNum> bool operator<=(const TNum &num) const;
//          template<t  ypename TNum> bool operator==(const TNum &num) const;

          inline operator T() const;
          template<typename T2> inline operator Size<T2>();


      private:

        /* Data */
          T width, height;

        /* Internal */
          inline void init();
    };

    typedef Size<double> FloatSize;
    typedef Size<int> IntSize;
  }

  #include "./Size.tpp"

#endif // GEO_SIZE_HPP
