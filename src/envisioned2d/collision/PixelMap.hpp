#ifndef COLLISION_PIXELMAP_HPP
#define COLLISION_PIXELMAP_HPP


  #include <cstdlib>

  #include <SDL/SDL.h>


  #include "etc/Alignment.hpp"
  #include "etc/int.h"
  #include "etc/bit.h"
  #include "util/util.hpp"
  #include "geo/geo.hpp"
  #include "gfx/gfx.hpp"
  #include "error/Exception.hpp"




  namespace collision
  {
    class RectMap;
    class RasterMap;

    template<typename TCollMap> class CollMapClipping;


    class PixelMap
    {
      public:

        PixelMap();
        PixelMap(const util::Path &imagepath);
        PixelMap(const gfx::Image &image);
        PixelMap(const PixelMap &pixelmap);
        PixelMap(const geo::IntSize &size);
        ~PixelMap();


        /* Load */
          void load(const util::Path &imagepath);
          void load(const gfx::Image &image);
          void load(const PixelMap &pixelmap);
          void load(const geo::IntSize &size);


        /* Clear */
          void clear();


        /* Individualise */
          void individualise();


        /* Manage mapsize */
          const geo::IntSize &getSize() const;
          void setSize(const geo::IntSize &size);
          void setWidth(int width);
          void setHeight(int height);


        /* Access pixels */
          bool isPixel(const geo::IntPoint &pixel);
          void setPixel(const geo::IntPoint &pixel, bool is);



        /* Check collision */
          bool isCollision(
                           const PixelMap &pixelmap2,
                           const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                           const geo::IntRect &rect1 = geo::IntRect(0, 0, -1, -1), const geo::IntRect &rect2 = geo::IntRect(0, 0, -1, -1),
                           const etc::Alignment &alignment1 = etc::Alignment(etc::ALIGN_BY_CORNER), const etc::Alignment &alignment2 = etc::Alignment(etc::ALIGN_BY_CORNER)) const;

          bool isCollision(
                           const RectMap &rectmap,
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


        /* Operators */
          PixelMap &operator=(const PixelMap &pixelmap);


      private:

        /* Data */
          u8 **map;
          geo::IntSize size;


        /* Internals */
          void generate(const gfx::Image &image);


        /* Internals - Attenion! Not memory save!!! */
          void init();


    };

    #include "./PixelMap.tpp"
  }

#endif // COLLISION_PIXELMAP_HPP
