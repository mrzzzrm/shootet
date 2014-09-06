#ifndef NEWTMX_BASE_TILELAYER_HPP
#define NEWTMX_BASE_TILELAYER_HPP


  #include <map>
  #include <vector>
  #include <string>

  #include "etc/int.h"
  #include "util/Path.hpp"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"
  #include "util/util.hpp"


  #include "./Layer.hpp"
  #include "./LayerTile.hpp"
  #include "./Properties.hpp"


  namespace tmx
  {
  namespace base
  {
    class Map;


    class TileLayer: public Layer
    {
      friend class Map;

      public:

        TileLayer(const Map &map);
        TileLayer(xml::Xml &xml, const Map &map);
        ~TileLayer();


        /* Load */
          void load(xml::Xml &xml);


        /* Get Attributes */
          const std::string &getName() const;
          int getWidth() const;
          int getHeight() const;


        /* Get Properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get Tile */
          int getTile(int x, int y) const;


        /* Get parent map */
          const Map &getMap() const;


        /* Set Attributes */
          void setName(const std::string &name);


        /* Set Tile */
          void setTile(int x, int y, int gid);



      private:

        /* Data */
          /* Attributes */
            std::string name;
            int width;
            int height;


          /* Properties */
            Properties properties;


          /* Parent Map */
            const Map &map;


          /* Tile data */
            std::vector<std::vector<int> > tilevector;



        /* Internal */
          void clear();


        /* Internal methods - Attention! Not memory save!!! */
          void init();


        /* Disabled functionality */
          TileLayer();
          TileLayer &operator=(const TileLayer &tilelayer);



        /* Access only for manager-class Map */
          TileLayer(const TileLayer &tilelayer);
          void setWidth(int width);
          void setHeight(int height);
    };

  }
  }


#endif // TMX_LAYER_HPP
