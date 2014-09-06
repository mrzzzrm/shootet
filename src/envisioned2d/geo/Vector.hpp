#ifndef GEO_VECTOR_HPP
#define GEO_VECTOR_HPP

  #include <cmath>
  #include "etc/int.h"

  namespace geo
  {
    template<typename TAxis>
    class Vector
    {
      template<typename> friend class Vector;

      public:

        Vector();
        Vector(TAxis x, TAxis y);
        Vector(const Vector &vector);
        ~Vector();


        /* Load */
          inline void load(TAxis x, TAxis y);
          template<typename P2TAxis> inline void load(const Vector<P2TAxis> &vector);


        /* Clear */
          inline void clear();


        /* Get coordinates */
          inline TAxis getX() const;
          inline TAxis getY() const;


        /* Set coordinates */
          inline void setX(TAxis x);
          inline void setY(TAxis x);


        /* Increase/decrease coordinates */
          inline void incX(TAxis dx);
          inline void incY(TAxis dy);
          inline void decX(TAxis dx);
          inline void decY(TAxis dy);


        /* Length/Direction */
          inline double getLength() const;
          inline double getDirection() const;


        /* Operators */
          template<typename V2TAxis> inline Vector<TAxis> &operator=(const Vector<V2TAxis> &vector2);

          template<typename V2TAxis> inline Vector<TAxis> operator+(const Vector<V2TAxis> &vector2) const;
          template<typename V2TAxis> inline Vector<TAxis> operator-(const Vector<V2TAxis> &vector2) const;
          template<typename V2TAxis> inline Vector<TAxis> &operator+=(const Vector<V2TAxis> &vector2);
          template<typename V2TAxis> inline Vector<TAxis> &operator-=(const Vector<V2TAxis> &vector2);

          template<typename TOp> inline Vector<TAxis> operator/(const TOp &divider) const;
          template<typename TOp> inline Vector<TAxis> operator*(const TOp &factor) const;
          template<typename TOp> inline Vector<TAxis> &operator/=(const TOp &divider);
          template<typename TOp> inline Vector<TAxis> &operator*=(const TOp &factor);

          template<typename V2TAxis> inline bool operator==(const Vector<V2TAxis> &vector);
          template<typename V2TAxis> inline bool operator!=(const Vector<V2TAxis> &vector);
          template<typename V2TAxis> inline operator Vector<V2TAxis>();



      private:

        /* Data */
          TAxis x, y;

    };

    typedef Vector<int> IntVector;
    typedef Vector<double> FloatVector;
  }


  #include "./Vector.tpp"


#endif // VECTOR2D_HPP
