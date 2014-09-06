#ifndef NEWTMX_BASE_LAYERTILE_HPP
#define NEWTMX_BASE_LAYERTILE_HPP

  #include <map>
  #include <string>

  #include "etc/int.h"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"


  namespace tmx
  {
  namespace base
  {
    class TileLayer;

    class LayerTile
    {
      friend class TileLayer;

      public:

        LayerTile(const TileLayer &tilelayer);
        LayerTile(xml::Xml &xml, const TileLayer &tilelayer);
        ~LayerTile();


        /* Attributes */
          int getGid() const;
          void setGid(int gid);


        /* Parent tilelayer */
          const TileLayer &getTileLayer() const;




      private:

        /* Data */
          /* Attributes */
            int gid;

          /* Parent tilelayer */
            const TileLayer &tilelayer;



        /* Internal */
          void clear();
          void init();


        /* Disabled functionality */
          LayerTile();
          LayerTile &operator=(const LayerTile &layertile);


        /* Access only for manager - class */
          LayerTile(const LayerTile &layertile);
    };

  }
  }


#endif
