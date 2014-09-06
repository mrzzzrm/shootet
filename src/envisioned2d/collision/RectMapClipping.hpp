#ifndef COLLISION_RECTMAPCLIPPING_HPP
#define COLLISION_RECTMAPCLIPPING_HPP

  #include "./CollMapClipping.hpp"
  #include "./PixelMap.hpp"
  #include "./RectMap.hpp"  
  #include "./RasterMap.hpp"
  
  
  namespace collision
  {
    #include "./CollMapClipping.tpp"
    typedef CollMapClipping<RectMap> RectMapClipping;
  }

#endif

