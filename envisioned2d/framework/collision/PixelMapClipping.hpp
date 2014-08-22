#ifndef COLLISION_PIXELMAPCLIPPING_HPP
#define COLLISION_PIXELMAPCLIPPING_HPP


  #include "./PixelMap.hpp"
  #include "./RectMap.hpp"
  #include "./RasterMap.hpp"
  #include "./CollMapClipping.hpp"

  namespace collision
  {
    #include "./CollMapClipping.tpp"
    typedef CollMapClipping<PixelMap> PixelMapClipping;
  }


#endif

