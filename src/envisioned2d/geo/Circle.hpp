#ifndef GEO_CIRCLE_HPP
#define GEO_CIRCLE_HPP

  #include "etc/int.h"

  namespace geo
  {
    template<typename TPos, typename TRadius>
    class Circle
    {
      template<typename, typename> friend class Circle;

      public:

        Circle();
        Circle(TPos x, TPos y, TRadius radius);
        Circle(const Point<TPos> &point, TRadius radius);
        Circle(const Circle &circle);
        ~Circle();


        /* Load */
          void load(TPos x, TPos y, TRadius radius);
          void load(const Point<TPos> &point, TRadius radius);
          void load(const Circle &circle);


        /* Clear */
          void clear();


        /* Read */
          const Point<TPos> getPosition() const;
          TPos getX() const;
          TPos getY() const;
          TRadius getRadius() const;


        /* Write */
          void setPosition(const Point<TPos> &position);
          void setX(TPos x);
          void setY(TPos y);
          void setRadius(TRadius radius);


        /* Modify */
          void incX(TPos delta);
          void incY(TPos delta);
          void decX(TPos delta);
          void decY(TPos delta);
          void incRadius(TRadius delta);
          void decRadius(TRadius delta);


        /* Collision */
          template<typename C2TPos, typename C2TRadius> inline bool isCollision(
                                                                                  const Circle<C2TPos, C2TRadius> &circle2,
                                                                                  const geo::IntVector &offset1 = geo::IntVector(0, 0),
                                                                                  const geo::IntVector &offset2 = geo::IntVector(0, 0),
                                                                                  const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER),
                                                                                  const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;


        /* Operators */
          Circle &operator=(const Circle &circle);
          template<typename TPos2, typename TRadius2> operator Circle<TPos2, TRadius2>();


      private:

        /* Data */
          TPos x, y;
          TRadius radius;


        /* Internals */
          void init();

    };

    typedef Circle<int, int> IntCircle;
    typedef Circle<double, double> FloatCircle;
  }

  #include "./Circle.tpp"


#endif // GEO_CIRCLE_HPP
