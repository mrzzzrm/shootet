#include "./Map.hpp"


using namespace std;

using namespace error;
using namespace util;
using namespace geo;
using namespace gfx;


namespace tmx
{
namespace base
{

  Map::Map()
  {
    init();
  }


  Map::Map(const Path &path)
  {
    init();
    load(path);
  }


  Map::Map(const Map &map)
  {
    init();
    load(map);
  }


  Map::~Map()
  {
    clear();
  }


  void Map::load(const Path &path)
  {
    Path tmxdir;
    xml::Xml xml;


    clear();


    this->path = path;
    tmxdir = path.getDirectory();

    /* Open Xml - file */
      try
      {
        xml.load(path);
      }
      catch(Exception &exception)
      {
        throw Exception() << exception.getDescription();
      }


    /* Go to root block */
      if(!xml.toRootBlock("map"))
      {
        throw Exception() << "Couldn't find root block 'map'";
      }


    /* Set Xml - defaults */
      xml.setDefaultString("");
      xml.setDefaultInteger(0);
      xml.setDefaultFloat(0);


    /* Load map - attributes */
      if(xml.isString("version") && xml.isString("orientation") && xml.isInteger("width") && xml.isInteger("height") && xml.isInteger("tilewidth") && xml.isInteger("tileheight"))
      {
        string orientation;

        /* Read */
          version = xml.getString("version");
          width = xml.getInteger("width");
          height = xml.getInteger("height");
          tilewidth = xml.getInteger("tilewidth");
          tileheight = xml.getInteger("tileheight");


        /* Read orientation */
          orientation = xml.getString("orientation");

          if(orientation == "orthogonal")
            this->orientation = ORTHOGONAL;
          else if(orientation == "isometric")
            this->orientation = ISOMETRIC;
          else
            this->orientation = UNKNOWN;

      }
      else
      {
        throw Exception() << "Missing or wrong typed attribute in root block 'map'";
      }



    /* Load Properties */
      if(xml.toSubBlock("properties"))
      {
        try
        {
          properties.load(xml);
        }
        catch(Exception &exception)
        {
          throw Exception() << "Error whilst loading properties: " << exception.getDescription();
        }

        xml.toBaseBlock();
      }


    /* Load elements */
      /* Tileset */
        if(xml.toSubBlock("tileset"))
        {
          /* Read data */
          for(int ts = 0; ts > 0 ? xml.toNextBlock("tileset") : true; ts++)
          {
            Tileset *tileset;
            xml::Xml *ts_xml;

            /* Open .tsx or read from .tmx */
            if(xml.hasAttribute("source"))
            {
              Path path;

              path = tmxdir.appendConst(xml.getString("source"));
              ts_xml = new xml::Xml(path);
              ts_xml->toRootBlock("tileset");
            }
            else
            {
              ts_xml = &xml;
            }


            try
            {
              tileset = new Tileset(*ts_xml, xml.getInteger("firstgid"), *this);
            }
            catch(Exception &exception)
            {
              throw Exception() << "Error whilst loading tileset " << ts << ": " << exception.getDescription();
            }

            tilesetvector.push_back(tileset);

            /* Delete xml if it was an external .tsx */
            if(&xml != ts_xml)
              delete ts_xml;
          }


          xml.toBaseBlock();
        }


        /* Layer */
          if(xml.toSubBlock())
          {
              for(int l = 0; l > 0 ? xml.toNextBlock() : true; l++)
              {
                Layer *layer;

                if(xml.getBlockValue() == "layer")
                {
                  try
                  {
                    layer = new TileLayer(xml, *this);
                  }
                  catch(Exception &exception)
                  {
                    throw Exception() << "Error whilst loading tilelayer (layer " << l << "): " << exception.getDescription();
                  }

                  layervector.push_back(layer);
                }
                else if(xml.getBlockValue() == "objectgroup")
                {
                  try
                  {
                    layer = new Objectgroup(xml, *this);
                  }
                  catch(Exception &exception)
                  {
                    throw Exception() << "Error whilst loading objectgroup (layer " << l << "): " << exception.getDescription();
                  }

                  layervector.push_back(layer);
                }

              }

              xml.toBaseBlock();
          }
  }


  void Map::load(const Map &map)
  {
    if(&map == this)
      return;

    clear();


    path = map.path;

    version = map.version;
    orientation = map.orientation;
    width = map.width;
    height = map.height;
    tilewidth = map.tilewidth;
    tileheight = map.tileheight;
    properties = map.properties;


    tilesetvector.resize(map.tilesetvector.size());
    for(int ts = 0; ts < (int)map.tilesetvector.size(); ts++)
    {
      tilesetvector[ts] = new Tileset(*(map.tilesetvector[ts]));
    }


    layervector.resize(map.layervector.size());
    for(int l = 0; l < (int)map.layervector.size(); l++)
    {
      switch(layervector[l]->getType())
      {
        case LAYER_TILELAYER:
          layervector.push_back(new TileLayer(*dynamic_cast<TileLayer*>(layervector[l])));
        break;

        case LAYER_OBJECTGROUP:
          layervector.push_back(new Objectgroup(*dynamic_cast<Objectgroup*>(layervector[l])));
        break;
      }
    }

  }


  void Map::clear()
  {
    for(int ts = 0; ts  < (int)tilesetvector.size(); ts ++)
    {
      delete tilesetvector[ts];
    }
    tilesetvector.clear();


    for(int l = 0; l < (int)layervector.size(); l++)
    {
      delete layervector[l];
    }
    layervector.clear();

    version.clear();
    properties.clear();
    path.clear();

    init();
  }


  const util::Path &Map::getPath() const
  {
    return path;
  }


  const ImageClipping Map::getTileAsImageClipping(uint gid) const
  {
    ImageClipping res;
    const base::Tileset *tileset;
    int tsx, tsy;

    /* Tileset */
    tileset = NULL;
    for(int ts = 0; ts < getTilesetCount(); ts++)
    {
      tileset = &getTilesetConst(ts);
      if(
         (int)gid >= tileset->getFirstGid() &&
         (int)gid < tileset->getFirstGid() + tileset->getTileCount()
         )
      {
        break;
      }
    }

    if(tileset == NULL)
      throw Exception() << "No tileset found for gid " << gid;


    /* ImageClipping */
    tsx = (gid - tileset->getFirstGid()) % tileset->getWidth();
      tsx *= tileset->getTileWidth() + tileset->getSpacing();
      tsx += tileset->getMargin();
    tsy = (gid - tileset->getFirstGid()) / tileset->getWidth();
      tsy *= tileset->getTileHeight() + tileset->getSpacing();
      tsy += tileset->getMargin();


    return ImageClipping(tileset, IntRect(tsx, tsy, tileset->getTileWidth(), tileset->getTileHeight()));
  }


  const string &Map::getVersion() const
  {
    return version;
  }


  ORIENTATION Map::getOrientation() const
  {
    return orientation;
  }


  int Map::getWidth() const
  {
    return width;
  }


  int Map::getHeight() const
  {
    return height;
  }


  int Map::getTileWidth() const
  {
    return tilewidth;
  }


  int Map::getTileHeight() const
  {
    return tileheight;
  }


  Properties &Map::getProperties()
  {
    return properties;
  }


  const Properties &Map::getPropertiesConst() const
  {
    return properties;
  }


  int Map::getTilesetCount() const
  {
    return tilesetvector.size();
  }


  int Map::getLayerCount() const
  {
    return layervector.size();
  }


  int Map::getTileLayerCount() const
  {
    int c = 0;
    for(int l = 0; l < (int)layervector.size(); l++)
    {
      if(layervector[l]->getType() == LAYER_TILELAYER)
        c++;
    }

    return c;
  }


  int Map::getObjectgroupCount() const
  {
    int c = 0;
    for(int l = 0; l < (int)layervector.size(); l++)
    {
      if(layervector[l]->getType() == LAYER_OBJECTGROUP)
        c++;
    }

    return c;
  }


  Tileset &Map::getTileset(int index)
  {
    return *const_cast<Tileset*>(&getTilesetConst(index));
  }


  const Tileset &Map::getTilesetConst(int index) const
  {
    if(index < 0)
      index = tilesetvector.size() + index;

    if(!in_range(index, (int)tilesetvector.size() - 1))
      throw Exception() << "No such tileset with index '" << index << "'. Vectorsize is '" << tilesetvector.size() << "'";

    return *(tilesetvector[index]);
  }


  Layer &Map::getLayer(int index)
  {
    return *const_cast<Layer*>(&getLayerConst(index));
  }


  const Layer &Map::getLayerConst(int index) const
  {
    if(index < 0)
      index = layervector.size() + index;

    if(!in_range(index, (int)layervector.size() - 1))
      throw Exception() << "No such layer with index '" << index << "'. Vectorsize is '" << layervector.size() << "'";

    return *(layervector[index]);
  }


  TileLayer &Map::getTileLayer(int index)
  {
    return *const_cast<TileLayer*>(&getTileLayerConst(index));
  }


  const TileLayer &Map::getTileLayerConst(int index) const
  {
    if(index >= 0)
    {
      for(int l = 0, tlc = 0; l < (int)layervector.size(); l++)
      {
        if(layervector[l]->getType() == LAYER_TILELAYER)
        {
          if(tlc == index)
            return *dynamic_cast<TileLayer*>(layervector[l]);

          tlc++;
        }
      }

      throw Exception() << "No such layer with index '" << index << "'. Vectorsize is '" << layervector.size() << "'";
    }
    else
    {
      std::vector<const TileLayer*> tilelayervector;

      for(int l = 0; l < (int)layervector.size(); l++)
      {
        if(layervector[l]->getType() == LAYER_TILELAYER)
        {
          tilelayervector.push_back(dynamic_cast<const TileLayer*>(layervector[l]));
        }
      }

      index = tilelayervector.size() + index;

      if(!in_range(index, (int)tilelayervector.size() - 1))
        throw Exception() << "No such layer with index '" << index << "'. Vectorsize is '" << tilelayervector.size() << "'";

      return *tilelayervector[index];
    }
  }


  Objectgroup &Map::getObjectgroup(int index)
  {
    return *const_cast<Objectgroup*>(&getObjectgroupConst(index));
  }


  const Objectgroup &Map::getObjectgroupConst(int index) const
  {
    if(index >= 0)
    {
      for(int l = 0, tlc = 0; l < (int)layervector.size(); l++)
      {
        if(layervector[l]->getType() == LAYER_OBJECTGROUP)
        {
          if(tlc == index)
            return *dynamic_cast<Objectgroup*>(layervector[l]);

          tlc++;
        }
      }

      throw Exception() << "No such layer with index '" << index << "'. Vectorsize is '" << layervector.size() << "'";
    }
    else
    {
      std::vector<const Objectgroup*> objectgroupvector;

      for(int l = 0; l < (int)layervector.size(); l++)
      {
        if(layervector[l]->getType() == LAYER_OBJECTGROUP)
        {
          objectgroupvector.push_back(dynamic_cast<Objectgroup*>(layervector[l]));
        }
      }

      index = objectgroupvector.size() + index;

      if(!in_range(index, (int)objectgroupvector.size() - 1))
        throw Exception() << "No such layer with index '" << index << "'. Vectorsize is '" << objectgroupvector.size() << "'";

      return *objectgroupvector[index];
    }
  }




  void Map::setVersion(const std::string &version)
  {
    this->version = version;
  }


  void Map::setOrientation(ORIENTATION orientation)
  {
    this->orientation = orientation;
  }


  void Map::setWidth(int width)
  {
    this->width = width;

    for(int l = 0; l < (int)layervector.size(); l++)
    {
      layervector[l]->setWidth(width);
    }
  }


  void Map::setHeight(int height)
  {
    this->height = height;

    for(int l = 0; l < (int)layervector.size(); l++)
    {
      layervector[l]->setHeight(height);
    }
  }


  void Map::setTileWidth(int tilewidth)
  {
    this->tilewidth = tilewidth;
  }


  void Map::setTileHeight(int tileheight)
  {
    this->tileheight = tileheight;
  }


  Tileset &Map::addTileset(const util::Path &imagepath, const std::string &name, int tilewidth, int tileheight, int margin, int spacing)
  {
    u32 firstgid;
    Tileset *tileset;
    vector<Tileset*>::iterator i;

    if(tilesetvector.size() > 0)
      firstgid = tilesetvector.back()->getFirstGid() + tilesetvector.back()->getTileCount();
    else
      firstgid = 0;

    i = tilesetvector.end();

    tilesetvector.insert(i, tileset = new Tileset(imagepath, firstgid, name, tilewidth, tileheight, margin, spacing, *this));

    return *tileset;
  }


  Layer &Map::addLayer(int index, LAYERTYPE type)
  {
    Layer *layer;
    vector<Layer*>::iterator i;

    /* Set iterator */
      if(index >= (int)layervector.size())
        i = layervector.end();
      else
        i = layervector.begin() + index;


    /* Register new layer */
      switch(type)
      {
        case LAYER_TILELAYER:
          layervector.insert(i, layer = new TileLayer(*this));
        break;

        case LAYER_OBJECTGROUP:
          layervector.insert(i, layer = new Objectgroup(*this));
        break;
      }

      /* Set to mapsize */
        layer->setWidth(width);
        layer->setHeight(height);


    /* Return */
      return *layer;
  }





  Map &Map::operator=(const Map &map)
  {
    load(map);
    return *this;
  }


  void Map::init()
  {
    orientation = UNKNOWN;
    width = 0;
    height = 0;
    tilewidth = 0;
    tileheight = 0;
  }


}
}

