#include "./Tileset.hpp"


using namespace std;

using namespace gfx;
using namespace util;
using namespace error;



namespace tmx
{
namespace base
{
  Tileset::Tileset(xml::Xml &xml, int firstgid, const Map &map):
    map(map)
  {
    init();

    this->firstgid = firstgid;

     /* Parse */
      /* Read attributes */
        if(xml.isString("name") && xml.isInteger("tilewidth") && xml.isInteger("tileheight"))
        {
          /* Read */
            name = xml.getString("name");
            tilewidth = xml.getInteger("tilewidth");
            tileheight = xml.getInteger("tileheight");
            margin = xml.getInteger("margin");
            spacing = xml.getInteger("spacing");
        }
        else
        {
          /* Throw */
            throw Exception() << "Missing or wrong - typed attribute";
        }


      /* Read image  */
        if(xml.toSubBlock("image"))
        {
            if(xml.isString("source"))
            {
              imagepath = xml.getPath().getDirectory();
              imagepath.append(xml.getString("source"));

              try
              {
                Image::load(imagepath, true);
              }
              catch(const Exception &exception)
              {
                throw Exception() << "Error whilst loading Image: " << exception.getDescription();
              }
            }
            else
            {
              xml.toBaseBlock();
              throw Exception() << "Missing or wrong typed attribute 'source' in block 'image'";
            }


          /* Transparency */
            if(xml.isString("trans"))
            {
              char *endptr;
              string tmpstring;

              tmpstring = xml.getString("trans");

              imagetrans = strtoul(tmpstring.c_str(), &endptr, 16);
                if(endptr - tmpstring.c_str() != (int)(strlen(tmpstring.c_str())))
                  throw Exception() << "Illegal image - transparency key '" << tmpstring << "'";

              setColorkey((imagetrans << 8) | 0xff);
            }

            xml.toBaseBlock();
        }
        else
        {
          xml.toBaseBlock();
          throw Exception() << "Missing block 'image'";
        }




      /* Properties */
        if(xml.toSubBlock("properties"))
        {
          try
          {
            properties.load(xml);
          }
          catch(Exception &exception)
          {
            xml.toBaseBlock();
            throw Exception() << "Error whilst loading properties: " << exception.getDescription();
          }

          xml.toBaseBlock();
        }



    /* Set size */
      width = (Image::getSize().getWidth() - margin) / (tilewidth + spacing);
      height = (Image::getSize().getHeight() - margin) / (tileheight + spacing);

      /* In case the spacing of the edge tiles was left away */
//        if((Image::getWidth() - margin) % (tilewidth + spacing) != 0)
//          width++;
//        if((Image::getHeight() - margin) % (tileheight + spacing) != 0)
//          height++;



      /* Assert no tiles */
        if(width == 0 || height == 0)
          throw Exception() << "No tiles found";



      /* Create tiles */
        tilevector.resize(width * height);

        /* Read those specified in the tmx */
          if(xml.toSubBlock("tile"))
          {
            for(int t = 0; t > 0 ? xml.toNextBlock("tile") : true; t++)
            {
              TilesetTile *tile;

                try
                {
                  tile = new TilesetTile(xml, *this);
                }
                catch(Exception &exception)
                {
                  xml.toBaseBlock();
                  throw Exception() << "Error whilst loading tile " << t << ": " << exception.getDescription();
                }

                tilevector[tile->getId()] = tile;


            }while(xml.toNextBlock("tile"));


            xml.toBaseBlock();
          }

        /* Fill the remaining */
          for(int t = 0; t < width * height; t++)
          {
            if(tilevector[t] == NULL)
              tilevector[t] = new TilesetTile(t, *this);
          }



  }


  Tileset::Tileset(const util::Path &imagepath, int firstgid, const string &name, int tilewidth, int tileheight, int margin, int spacing, const Map &map):
    map(map)
  {
    /* Set all attributes/values */
      this->imagepath = imagepath;
      this->firstgid = firstgid;
      this->name = name;
      this->tilewidth = tilewidth;
      this->tileheight = tileheight;
      this->margin = margin;
      this->spacing = spacing;


    /* Assert tilesize '0' */
      if(tilewidth == 0 || tileheight == 0)
        throw Exception() << "Tilesize is 0";


    /* Load image */
      try
      {
        Image::load(imagepath);
      }
      catch(const Exception &exception)
      {
        throw Exception() << "Error whilst loading Image: " << exception.getDescription();
      }


    /* Set size */
      width = (Image::getSize().getWidth() - margin) / (tilewidth + spacing);
      height = (Image::getSize().getHeight() - margin) / (tileheight + spacing);

      /* In case the spacing of the edge tiles was left away */
//        if((Image::getWidth() - margin) % (tilewidth + spacing) != 0)
//          width++;
//        if((Image::getHeight() - margin) % (tileheight + spacing) != 0)
//          height++;

      /* Assert no tiles */
        if(width == 0 || height == 0)
          throw Exception() << "No tiles found";


    /* Create all tiles */
      tilevector.resize(width * height);
      for(int t = 0; t < width * height; t++)
      {
        tilevector[t] = new TilesetTile(t, *this);
      }

  }


  Tileset::~Tileset()
  {
    clear();
  }


  void Tileset::clear()
  {
    for(uint t = 0; t < tilevector.size(); t++)
    {
      if(tilevector[t] != NULL)
        delete tilevector[t];
    }
    tilevector.clear();

    name.clear();
    properties.clear();

    init();
  }


  const util::Path &Tileset::getImagePath() const
  {
    return imagepath;
  }


  int Tileset::getFirstGid() const
  {
    return firstgid;
  }


  const string &Tileset::getName() const
  {
    return name;
  }


  int Tileset::getTileWidth() const
  {
    return tilewidth;
  }


  int Tileset::getTileHeight() const
  {
    return tileheight;
  }


  int Tileset::getMargin() const
  {
    return margin;
  }


  int Tileset::getSpacing() const
  {
    return spacing;
  }


  int Tileset::getWidth() const
  {
    return width;
  }


  int Tileset::getHeight() const
  {
    return height;
  }

  int Tileset::getTileCount() const
  {
    return tilevector.size();
  }


  TilesetTile *Tileset::getTile(int id)
  {
    if(!in_range(id, (int)tilevector.size()))
      return NULL;

    return tilevector[id];
  }


  Properties &Tileset::getProperties()
  {
    return properties;
  }


  const Properties &Tileset::getPropertiesConst() const
  {
    return properties;
  }


  const Map &Tileset::getMap() const
  {
    return map;
  }


  void Tileset::setName(const std::string &name)
  {
    this->name = name;
  }


  void Tileset::init()
  {
    firstgid = 0;
    tilewidth = 0;
    tileheight = 0;
    margin = 0;
    spacing = 0;
  }



  Tileset::Tileset(const Tileset &tileset):
    map(tileset.map)
  {
    clear();

    imagepath = tileset.imagepath;
    firstgid = tileset.firstgid;
    name = tileset.name;
    tilewidth = tileset.tilewidth;
    tileheight = tileset.tileheight;
    margin = tileset.margin;
    spacing = tileset.spacing;
    properties = tileset.properties;

    tilevector.resize(tileset.tilevector.size());
    for(uint t = 0; t < tileset.tilevector.size(); t++)
    {
      tilevector[t] =  new TilesetTile(*(tileset.tilevector[t]));
    }
  }


}
}
