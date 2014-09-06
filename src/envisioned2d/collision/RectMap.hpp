#ifndef COLLISION_RECTMAP_HPP
#define COLLISION_RECTMAP_HPP

  #include <list>

  #include "etc/Alignment.hpp"
  #include "etc/int.h"
  #include "geo/geo.hpp"
  #include "error/Exception.hpp"


  namespace collision
  {
    class PixelMap;
    class RasterMap;

    template<typename TCollMap> class CollMapClipping;


    class RectMap
    {
      public:

        RectMap();
        RectMap(const RectMap &rectmap);
        ~RectMap();


        /* Load */
          void load(const RectMap &rectmap);


        /* Clear */
          void clear();


        /* Manage Rects */
          int getRectCount() const;
          const geo::IntRect &getRect(int index) const;
          int addRect(const geo::IntRect &rect);
          void removeRect(int index);


        /* Size */
          const geo::IntSize &getSize() const;
          void setSize(const geo::IntSize &size);


        /* Collision detection */
          bool isCollision(
                           const RectMap &rectmap2,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const PixelMap &pixelmap,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const RasterMap &rastermap,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;


          template<typename TCollMap>
          bool isCollision(
                           const CollMapClipping<TCollMap> &collmapclipping,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const geo::IntRect &rect2,
                           const geo::IntPoint &pos1,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

        /* Operators */
          RectMap &operator=(const RectMap &rectmap);


      private:

        /* Data */
          geo::IntSize size;
          std::list<geo::IntRect*> rectlist;


        /* Internals */
          void clearDynamicData();
          bool clipRect(geo::IntRect *rect);

    };

    #include "./RectMap.tpp"
  }

#endif // COLLISION_RECTMAP_HPP
