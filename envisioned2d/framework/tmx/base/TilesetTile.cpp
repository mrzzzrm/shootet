#include "./TilesetTile.hpp"


using namespace std;
using namespace error;



namespace tmx
{
namespace base
{
  TilesetTile::TilesetTile(int id, const Tileset &tileset):
    tileset(tileset)
  {
    init();

    this->id = id;
  }


  TilesetTile::TilesetTile(xml::Xml &xml, const Tileset &tileset):
    tileset(tileset)
  {
    init();

    if(xml.isInteger("id"))
    {
      id = xml.getInteger("id");
    }
    else
    {
      throw Exception() << "Missing or wrong type attribute 'id'";
    }


    if(xml.toSubBlock("properties"))
    {
      try
      {
        properties.load(xml);
      }
      catch(Exception &exception)
      {
        xml.toBaseBlock();

        throw Exception() << "Error whilst reading properties: " << exception.getDescription();
      }

      xml.toBaseBlock();
    }
  }


  TilesetTile::~TilesetTile()
  {
    clear();
  }


  void TilesetTile::clear()
  {
    properties.clear();
  }


  int TilesetTile::getId() const
  {
    return id;
  }


  Properties &TilesetTile::getProperties()
  {
    return properties;
  }


  const Properties &TilesetTile::getPropertiesConst() const
  {
    return properties;
  }


  const Tileset &TilesetTile::getTileset() const
  {
    return tileset;
  }


  void TilesetTile::init()
  {
    id = 0;
  }


  TilesetTile::TilesetTile(const TilesetTile &tile):
    tileset(tile.tileset)
  {
    id = tile.id;
    properties = tile.properties;
  }


}
}

