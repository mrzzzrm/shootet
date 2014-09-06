#ifndef COLLISION_RASTERMAP_HPP
#define COLLISION_RASTERMAP_HPP

  #include <cstdlib>

  #include "etc/Alignment.hpp"
  #include "etc/int.h"
  #include "etc/bit.h"
  #include "geo/geo.hpp"
  #include "error/Exception.hpp"


  namespace collision
  {
    class PixelMap;
    class RectMap;

    template<typename TCollMap> class CollMapClipping;


    class RasterMap
    {
      public:

        RasterMap();
        RasterMap(const geo::IntSize &mapsize, const geo::IntSize &cellsize);
        RasterMap(const RasterMap &rastermap);
        ~RasterMap();


        /* Load */
          void load(const geo::IntSize &mapsize, const geo::IntSize &cellsize);
          void load(const RasterMap &rastermap);


        /* Clear */
          void clear();


        /* Manage mapsize */
          const geo::IntSize &getMapSize() const;
          void setMapSize(const geo::IntSize &size);


        /* Manage cellsize */
          const geo::IntSize &getCellSize() const;
          void setCellSize(const geo::IntSize &size);


        /* Access cells */
          void setCell(const geo::IntPoint &cell, bool is);
          bool isCell(const geo::IntPoint &cell) const;



        /* Collision detection */
          bool isCollision(
                           const RasterMap &rastermap2,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const PixelMap &pixelmap,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const RectMap &rectmap,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;


          template<typename TCollMap>
          bool isCollision(
                           const CollMapClipping<TCollMap> &collmapclipping,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;



        /* Operators */
          RasterMap &operator=(const RasterMap &rastermap);


      private:

        /* Data */
          u8 **map;
          geo::IntSize mapsize;
          geo::IntSize cellsize;



        /* Internals - Attenion! Not memory save!!! */
          void init();
          void clearDynamicData();

    };

    #include "./RasterMap.tpp"
  }

#endif
