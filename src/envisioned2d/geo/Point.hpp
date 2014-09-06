#ifndef GEO_POINT_HPP
#define GEO_POINT_HPP

  #include "etc/int.h"

  namespace geo
  {

    template<typename TPos>
    class Point
    {
      template<typename> friend class Point;

      public:

        Point();
        Point(TPos x, TPos y);
        Point(const Point &point);
        ~Point();


        /* Load */
          inline void load(TPos x, TPos y);
          template<typename P2TPos> inline void load(const Point<P2TPos> &point);


        /* Clear */
          inline void clear();


        /* Get coordinates */
          inline TPos getX() const;
          inline TPos getY() const;


        /* Set coordinates */
          inline void setX(TPos x);
          inline void setY(TPos y);


        /* Increase / decrease coordinates */
          inline void incX(TPos dx);
          inline void incY(TPos dy);
          inline void decX(TPos dx);
          inline void decY(TPos dy);



        /* Operators */
          template<typename P2TPos> inline Point &operator=(const Point<P2TPos> &point);
          template<typename P2TPos> inline bool operator==(const Point<P2TPos> &point) const;
          template<typename P2TPos> inline bool operator!=(const Point<P2TPos> &point) const;
          template<typename P2TPos> inline operator Point<P2TPos>() const;



      private:

        /* Data */
          TPos x, y;

    };

    typedef Point<int> IntPoint;
    typedef Point<double> FloatPoint;
  }

   #include "Point.tpp"


#endif // GEO_POINT_HPP
