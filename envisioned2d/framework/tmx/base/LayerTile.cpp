#include "./LayerTile.hpp"
#include "./Map.hpp"


using namespace std;

using namespace error;


namespace tmx
{
namespace base
{

  LayerTile::LayerTile(const TileLayer &tilelayer):
    tilelayer(tilelayer)
  {
    init();
  }


  LayerTile::LayerTile(xml::Xml &xml, const TileLayer &tilelayer):
    tilelayer(tilelayer)
  {
    init();

    if(xml.isInteger("gid"))
    {
      gid = xml.getInteger("gid");
    }
    else
    {
      throw Exception() << "Missing or wrong type attribute 'gid'";
    }
  }


  LayerTile::~LayerTile()
  {
    clear();
  }


  void LayerTile::clear()
  {
    init();
  }


  int LayerTile::getGid() const
  {
    return gid;
  }


  void LayerTile::setGid(int gid)
  {
    this->gid = gid;
  }


  const TileLayer &LayerTile::getTileLayer() const
  {
    return tilelayer;
  }


  void LayerTile::init()
  {
    gid = 0;
  }

  LayerTile::LayerTile(const LayerTile &layertile):
    tilelayer(layertile.tilelayer)
  {
    gid = layertile.gid;
  }

}
}

