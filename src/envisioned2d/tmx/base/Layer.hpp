#ifndef NEWTMX_BASE_LAYER_HPP
#define NEWTMX_BASE_LAYER_HPP



  #include <map>
  #include <string>

  #include "etc/int.h"
  #include "geo/geo.hpp"
  #include "gfx/gfx.hpp"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"


  namespace tmx
  {
  namespace base
  {
    enum LAYERTYPE
    {
      LAYER_TILELAYER,
      LAYER_OBJECTGROUP
    };


    class Layer
    {
      public:

        Layer(LAYERTYPE type);
        Layer(const Layer &layer);
        virtual ~Layer();


        /* Get type */
          LAYERTYPE getType() const;


        /* Change size */
          virtual void setWidth(int width) = 0;
          virtual void setHeight(int height) = 0;


      private:

        /* Data */
          LAYERTYPE type;


        /* Disabled functionality */
          Layer();
          Layer &operator=(const Layer &layer);


    };
  }
  }
#endif // NEWTMX_BASE_LAYER_HPP
