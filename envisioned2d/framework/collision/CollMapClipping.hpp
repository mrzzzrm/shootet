#ifndef COLLISION_COLLMAPCLIPPING_HPP
#define COLLISION_COLLMAPCLIPPING_HPP

  #include <iostream>


  #include "etc/Alignment.hpp"
  #include "util/Path.hpp"
  #include "geo/geo.hpp"
  #include "gfx/gfx.hpp"



  namespace collision
  {
    class PixelMap;
    class RectMap;
    class RasterMap;


    template<typename TCollMap>
    class CollMapClipping: public geo::IntRect
    {
      public:

        CollMapClipping();
        CollMapClipping(const TCollMap *collmap, const geo::IntRect &rect);
        CollMapClipping(const CollMapClipping<TCollMap> &collmapclipping);
        ~CollMapClipping();


        /* Load */
          void load(const TCollMap *collmap, const geo::IntRect &rect);
          void load(const CollMapClipping<TCollMap> &collmapclipping);


        /* Clear */
          void clear();


        /* Manage collmap */
          const TCollMap *getCollMap() const;
          void setCollMap(const TCollMap *collmap);


        /* Collision detection */
          template<typename TCollMap2> bool isCollision(
                                                          const TCollMap2 &collmap2,
                                                          const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                                                          const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                                                          const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          template<typename TCollMap2> bool isCollision(
                                                          const CollMapClipping<TCollMap2> &collmapclipping2,
                                                          const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                                                          const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;




        /* Operators */
          CollMapClipping<TCollMap> &operator=(const CollMapClipping<TCollMap> &collmapclipping);


      private:

        /* Data */
          const TCollMap *collmap;


        /* Internals */
          void init();
    };


  }



#endif
