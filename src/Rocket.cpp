#include "./Rocket.hpp"

using namespace std;

using namespace geo;



Rocket::Rocket(const FloatPoint &position):
  FloatPoint(position)
{
  this->column = (int)position.getX();
}


Rocket::~Rocket()
{

}


int Rocket::getColumn() const
{
  return column;
}


int Rocket::getHeight()
{
  if(media::gfx::rocket.getFrameCount() != 0)
    return media::gfx::rocket.getFrame(0).getHeight();
  else
    return 0;
}


void Rocket::update()
{
  timer.update();

  setX(column + sin((double)timer.getElapsed()/ROCKET_CURVE_TIME_DIVIDOR)/ROCKET_CURVE_SIN_DIVIDOR);
}
