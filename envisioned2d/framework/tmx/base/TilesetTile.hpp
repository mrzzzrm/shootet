#ifndef NEWTMX_BASE_TILESETTILE_HPP
#define NEWTMX_BASE_TILESETTILE_HPP

  #include <map>
  #include <string>

  #include "etc/int.h"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"

  #include "./Properties.hpp"


  namespace tmx
  {
  namespace base
  {
    class Map;
    class Tileset;

    class TilesetTile
    {
      friend class Tileset;

      public:

        TilesetTile(int id, const Tileset &tileset);
        TilesetTile(xml::Xml &xml, const Tileset &tileset);
        ~TilesetTile();


        /* Get attributes */
          int getId() const;


        /* Get properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get parent tileset */
          const Tileset &getTileset() const;




      private:

        /* Data */
          /* Attributes */
            int id;

          /* Properties */
            Properties properties;

          /* Parent tileset */
            const Tileset &tileset;


        /* Internal */
          void clear();


        /* Internal methods - Attention! Not memory save!!! */
          void init();


        /* Disabled functionality */
          TilesetTile();
          TilesetTile &operator=(const TilesetTile &tile);



        /* Access only for manager - class */
          TilesetTile(const TilesetTile &tile);
    };

  }
  }


#endif
