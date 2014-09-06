#ifndef COLLISION_RASTERMAPCLIPPING_HPP
#define COLLISION_RASTERMAPCLIPPING_HPP

  #include "./PixelMap.hpp"
  #include "./RectMap.hpp"
  #include "./RasterMap.hpp"
  #include "./CollMapClipping.hpp"

  namespace collision
  {
    #include "./CollMapClipping.tpp"
    typedef CollMapClipping<RasterMap> RasterMapClipping;
  }

#endif

