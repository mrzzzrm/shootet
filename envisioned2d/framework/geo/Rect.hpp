#ifndef GEO_RECT_HPP
#define GEO_RECT_HPP

  #include <stdlib.h>

  #include "etc/Alignment.hpp"
  #include "geo/Vector.hpp"

  namespace geo
  {
    template<typename TPos, typename TAxis>
    class Rect
    {
      template<typename, typename> friend class Rect;

      public:


        Rect();
        Rect(TPos x, TPos y, TAxis w, TAxis h);
        Rect(const Rect &rect);
        ~Rect();


        /* Load */
          inline void load(TPos x, TPos y, TAxis w, TAxis h);
          template<typename R2TPos, typename R2TAxis> inline void load(const Rect<R2TPos, R2TAxis> &rect);


        /* Clear */
          inline void clear();


        /* Get coordinates and size */
          inline TPos getX() const;
          inline TPos getY() const;
          inline TAxis getWidth() const;
          inline TAxis getHeight() const;


        /* Set coordinates and size */
          inline void setX(TPos x);
          inline void setY(TPos y);
          inline void setWidth(TAxis width);
          inline void setHeight(TAxis height);


        /* Increase/decrease coordinates and size */
          inline void incX(TPos dx);
          inline void incY(TPos dy);
          inline void incWidth(TAxis dx);
          inline void incHeight(TAxis dy);

          inline void decX(TPos dx);
          inline void decY(TPos dy);
          inline void decWidth(TAxis dx);
          inline void decHeight(TAxis dy);


        /* Normalise - Asure that size is positive */
          inline void normalise();



        /* Collision detection */
          template<typename R2TPos, typename R2TAxis> inline bool isCollision(
                                                                                  const Rect<R2TPos, R2TAxis> &rect2,
                                                                                  const geo::IntVector &offset1,
                                                                                  const geo::IntVector &offset2,
                                                                                  const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER),
                                                                                  const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          template<typename R2TPos, typename R2TAxis> inline bool isCollision(const Rect<R2TPos, R2TAxis> &rect2) const;

          template<typename R2TPos, typename R2TAxis> inline Rect<TPos, TAxis> *getCutrect(
                                                                                               const Rect<R2TPos, R2TAxis> &rect2,
                                                                                               const geo::IntVector &offset1,
                                                                                               const geo::IntVector &offset2,
                                                                                               const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER),
                                                                                               const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          template<typename R2TPos, typename R2TAxis> inline Rect<TPos, TAxis> *getCutrect(const Rect<R2TPos, R2TAxis> &rect2) const;


        /* Check for coverage */
          template<typename R2TPos, typename R2TAxis> inline bool isCovering(
                                                                                 const Rect<R2TPos, R2TAxis> &rect2,
                                                                                 const geo::IntVector &offset1,
                                                                                 const geo::IntVector &offset2,
                                                                                 const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER),
                                                                                 const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          template<typename R2TPos, typename R2TAxis> inline bool isCovering(const Rect<R2TPos, R2TAxis> &rect2) const;


        /* Operators */
          template<typename R2TPos, typename R2TAxis> inline Rect<TPos, TAxis> &operator=(const Rect<R2TPos, R2TAxis> &rect);

          template<typename R2TPos, typename R2TAxis> inline bool operator==(const Rect<R2TPos, R2TAxis> &rect);
          template<typename R2TPos, typename R2TAxis> inline bool operator!=(const Rect<R2TPos, R2TAxis> &rect);

          inline Rect<TPos, TAxis> operator+(const Vector<TPos> &vec) const;
          inline Rect<TPos, TAxis> &operator+=(const Vector<TPos> &vec);
          inline Rect<TPos, TAxis> operator-(const Vector<TPos> &vec) const;
          inline Rect<TPos, TAxis> &operator-=(const Vector<TPos> &vec);

          template<typename R2TPos, typename R2TAxis> inline operator Rect<R2TPos, R2TAxis>();




      private:

        /* Data */
          TPos x;
          TPos y;
          TAxis width;
          TAxis height;

    };

    typedef Rect<int, int> IntRect;
    typedef Rect<double, double> FloatRect;
  }


    #include "./Rect.tpp"

#endif // RECT_HPP
