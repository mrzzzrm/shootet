#include "./Item.hpp"

using namespace std;
using namespace geo;


/*
  Class Item
*/
  Item::Item(ITEM_TYPE type, const FloatPoint &position):
    FloatPoint(position)
  {
    this->type = type;
  }


  Item::~Item()
  {

  }


  ITEM_TYPE Item::getType() const
  {
    return type;
  }

  int Item::getHeight(ITEM_TYPE type)
  {
    if(media::gfx::item[type].getFrameCount() != 0)
      return media::gfx::item[type].getFrame(0).getHeight();
    else
      return 0;
  }
