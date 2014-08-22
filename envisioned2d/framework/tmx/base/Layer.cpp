#include "./Layer.hpp"

using namespace std;




namespace tmx
{
namespace base
{
  Layer::Layer(LAYERTYPE type)
  {
    this->type = type;
  }


  Layer::Layer(const Layer &layer)
  {
    type = layer.type;
  }


  Layer::~Layer()
  {

  }


  LAYERTYPE Layer::getType() const
  {
    return type;
  }

}
}


