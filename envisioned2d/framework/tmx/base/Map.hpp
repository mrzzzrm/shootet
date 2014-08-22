#ifndef NEWTMX_BASE_MAP_HPP
#define NEWTMX_BASE_MAP_HPP

  #include <map>
  #include <queue>
  #include <list>
  #include <vector>
  #include <string>
  #include <sstream>


  #include "etc/int.h"
  #include "gfx/gfx.hpp"
  #include "geo/geo.hpp"
  #include "util/Path.hpp"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"


  #include "./Layer.hpp"
  #include "./Tileset.hpp"
  #include "./TileLayer.hpp"
  #include "./Objectgroup.hpp"
  #include "./Properties.hpp"



  namespace tmx
  {
  namespace base
  {
    enum ORIENTATION
    {
      UNKNOWN,
      ORTHOGONAL,
      ISOMETRIC
    };


    class Map
    {
      public:

        Map();
        Map(const util::Path &path);
        Map(const Map &map);

        ~Map();


        /* Load */
          void load(const util::Path &path);
          void load(const Map &map);


        /* Clear */
          void clear();


        /* Path */
          const util::Path &getPath() const;


        /* Tile data */
          const gfx::ImageClipping getTileAsImageClipping(uint gid) const;


        /* Get Attributes */
          const std::string &getVersion() const;
          ORIENTATION getOrientation() const;
          int getWidth() const;
          int getHeight() const;
          int getTileWidth() const;
          int getTileHeight() const;


        /* Get Properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get counts */
          int getTilesetCount() const;
          int getLayerCount() const;
          int getTileLayerCount() const;
          int getObjectgroupCount() const;


        /* Get Elements */
          Tileset &getTileset(int index);
          const Tileset &getTilesetConst(int index) const;

          Layer &getLayer(int index);
          const Layer &getLayerConst(int index) const;

          TileLayer &getTileLayer(int index);
          const TileLayer &getTileLayerConst(int index) const;

          Objectgroup &getObjectgroup(int index);
          const Objectgroup &getObjectgroupConst(int index) const;



        /* Set attributes */
          void setVersion(const std::string &version);
          void setOrientation(ORIENTATION orientation);
          void setWidth(int width);
          void setHeight(int height);
          void setTileWidth(int tilewidth);
          void setTileHeight(int tileheight);


        /* Add elements */
          Tileset &addTileset(const util::Path &imagepath, const std::string &name, int tilewidth, int tileheight, int margin, int spacing);
          Layer &addLayer(int index, LAYERTYPE type);


        /* Operators */
          Map &operator=(const Map &map);


      private:

        /* Data */
          util::Path path;

          /* Attributes */
            std::string version;
            ORIENTATION orientation;
            int width;
            int height;
            int tilewidth;
            int tileheight;


          /* Properties */
            Properties properties;


          /* Elements */
            std::vector<Tileset*> tilesetvector;
            std::vector<Layer*> layervector;



        /* Internals */
          void init();
    };

  }
  }

#endif // NEWTMX_MAP_HPP
