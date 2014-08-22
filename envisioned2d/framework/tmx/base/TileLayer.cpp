#include "./TileLayer.hpp"
#include "./Map.hpp"


using namespace std;

using namespace geo;
using namespace gfx;
using namespace error;
using namespace xml;
using namespace util;


namespace tmx
{
namespace base
{
  TileLayer::TileLayer(const Map &map):
    Layer(LAYER_TILELAYER),
    map(map)
  {
    init();
  }


  TileLayer::TileLayer(xml::Xml &xml, const Map &map):
    Layer(LAYER_TILELAYER),
    map(map)
  {
    init();
    load(xml);
  }


  TileLayer::~TileLayer()
  {
    clear();
  }


  void TileLayer::load(xml::Xml &xml)
  {
    clear();

    /* Parse */
      /* Attributes */
        if(xml.isString("name") && xml.isInteger("width") && xml.isInteger("height"))
        {
          name = xml.getString("name");
          width = xml.getInteger("width");
          height = xml.getInteger("height");
        }
        else
        {
          throw Exception() << "Missing or wrong typed attribute";
        }


      /* Properties */
        if(xml.toSubBlock("properties"))
        {
          /* Read properties */
            try
            {
              properties.load(xml);
            }
            catch(Exception &exception)
            {
              xml.toBaseBlock();

              width = 0;
              height = 0;

              throw Exception() << "Error whilst loading properties: " << exception.getDescription();
            }

            xml.toBaseBlock();
        }


      /* Data */
        try
        {
          if(xml.toSubBlock("data"))
          {
            string encoding;

            /* Get encoding */
              if(xml.hasAttribute("encoding"))
                encoding = xml.getString("encoding");
              else
                encoding = "xml";

            /* Tiles */
              if(encoding == "xml")
              {
                if(xml.toSubBlock("tile"))
                {
                  tilevector.resize(height);

                  for(int y = 0; y < height; y++)
                  {
                      tilevector[y].resize(width);

                      for(int x = 0; x < width; x++)
                      {
                        /* Read */
                          tilevector[y][x] = xml.getInteger("gid");


                        /* Next block; error handling: unexpected end of data */
                          if(!xml.toNextBlock("tile"))
                          {
                            if(x != width - 1 && y != height - 1)
                            {
                              throw Exception() << "Not enough 'tile's specified in 'data'. Layersize is '" << width << "x" << height << "', but parsing ends at tile '" << x << "x" << y << "'";
                            }

                          }

                      }
                    }

                    xml.toBaseBlock();

                  }
                  else if(width * height > 0)
                  {
                    throw Exception() << "No 'tile' subblock found in 'data', but layersize is '" << width << "x" << height << "'";
                  }
              }
              else if(encoding == "csv")
              {
                Csv csv;

                /* Jump into data block */
                  xml.toSubBlock();


                /* First block is FORCED to be the csv block */
                  if(xml.getBlockType() != XML_BLOCK_TEXT)
                  {
                    width = 0;
                    height = 0;

                    throw Exception() << "In csv encoded layer: First block in 'data' isn't of type 'XML_BLOCK_TEXT'";
                  }


                /* Get the data */
                  csv.load(xml.getBlockValue(), ",");


                /* Parse the csv */
                  tilevector.resize(height);

                  for(int y = 0; y < height; y++)
                  {
                      tilevector[y].resize(width);

                      for(int x = 0; x < width; x++)
                      {
                        if(csv.hasCell(0, y * width + x))
                        {
                          tilevector[y][x] = csv.getInteger(0, y * width + x);
                        }
                        else
                        {
                          throw Exception() << "Not enough 'tile's specified in 'data'. Layersize is '" << width << "x" << height << "', but parsing ends at tile '" << x << "x" << y << "'";
                        }
                      }

                  }

                  xml.toBaseBlock();
              }
              else
              {
                throw Exception() << "Unknown encoding '" << encoding << "'";
              }
              xml.toBaseBlock();
          }
        }
        catch(Exception &exception)
        {
          width = 0;
          height = 0;

          throw;
        }

  }


  void TileLayer::clear()
  {
    tilevector.clear();
    properties.clear();
    name.clear();

    init();
  }


  const string &TileLayer::getName() const
  {
    return name;
  }


  int TileLayer::getWidth() const
  {
    return width;
  }


  int TileLayer::getHeight() const
  {
    return height;
  }


  Properties &TileLayer::getProperties()
  {
    return properties;
  }


  const Properties &TileLayer::getPropertiesConst() const
  {
    return properties;
  }


  int TileLayer::getTile(int x, int y) const
  {
    if(!in_range(x, width - 1) || !in_range(y, height - 1))
      return 0;

    return tilevector[y][x];
  }


  const Map &TileLayer::getMap() const
  {
    return map;
  }


  void TileLayer::setName(const std::string &name)
  {
    this->name = name;
  }


  void TileLayer::setWidth(int width)
  {
    for(int y = 0; y < (int)tilevector.size(); y++)
    {
      tilevector[y].resize(width);
      for(int x = this->width; x < (int)tilevector[y].size(); x++)
      {
        tilevector[y][x] = 0;
      }
    }

    this->width = width;
  }


  void TileLayer::setHeight(int height)
  {
    tilevector.resize(height);

    for(int y = this->height; y < (int)tilevector.size(); y++)
    {
      tilevector[y].resize(this->width);
      for(int x = 0; x < (int)tilevector[y].size(); x++)
      {
        tilevector[y][x] = 0;
      }
    }

    this->height = height;
  }


  void TileLayer::setTile(int x, int y, int gid)
  {
    if(!in_range(x, width-1) || !in_range(y, height-1))
      return;

    tilevector[y][x] = gid;
  }


  void TileLayer::init()
  {
    width = 0;
    height = 0;
  }


  TileLayer::TileLayer(const TileLayer &tilelayer):
    Layer(LAYER_TILELAYER),
    map(tilelayer.map)
  {
    name = tilelayer.name;
    width = tilelayer.width;
    height = tilelayer.height;
    properties = tilelayer.properties;
    tilevector = tilelayer.tilevector;
  }



}
}

