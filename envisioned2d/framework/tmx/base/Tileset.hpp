#ifndef NEWTMX_BASE_TILESET_HPP
#define NEWTMX_BASE_TILESET_HPP


  #include <map>
  #include <vector>
  #include <string>
  #include <cstdlib>


  #include "etc/int.h"
  #include "util/Path.hpp"
  #include "gfx/gfx.hpp"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"


  #include "./TilesetTile.hpp"
  #include "./Properties.hpp"


  namespace tmx
  {
  namespace base
  {
    class Map;


    class Tileset: public gfx::Image
    {
      friend class Map;

      public:

        Tileset(xml::Xml &xml, int firstgid, const Map &map);
        Tileset(const util::Path &imagepath, int firstgid, const std::string &name, int tilewidth, int tileheight, int margin, int spacing, const Map &map);
        ~Tileset();


        /* Get attributes */
          const util::Path &getImagePath() const;
          int getFirstGid() const;
          const std::string &getName() const;
          int getTileWidth() const;
          int getTileHeight() const;
          int getMargin() const;
          int getSpacing() const;


        /* Get row and columncount */
          int getWidth() const;
          int getHeight() const;


        /* Get elementcount */
          int getTileCount() const;


        /* Get elements */
          TilesetTile *getTile(int id);


        /* Get properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get parent map */
          const Map &getMap() const;



        /* Set attributes */
          void setName(const std::string &name);



      private:

        /* Data */
          /* Attributes */
            util::Path imagepath;
            int imagetrans;
            int firstgid;
            std::string name;
            int tilewidth;
            int tileheight;
            int margin;
            int spacing;


          /* size in tiles */
            int width;
            int height;


          /* Properties */
            Properties properties;


          /* Elements */
            std::vector<TilesetTile*> tilevector;


          /* Parent map */
            const Map &map;



        /* Internal */
          void clear();


        /* Internal methods - Attention! Not memory save!!! */
          void init();


        /* Disabled functionality */
          Tileset();
          Tileset &operator=(const Tileset &tileset);



        /* Access only for manager - class */
          Tileset(const Tileset &tileset);
    };


  }
  }

#endif // TMX_TILESET_HPP
