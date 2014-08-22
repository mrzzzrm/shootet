#include "./Multiplier.hpp"

using namespace std;
using namespace geo;
using namespace etc;
using namespace util;



/*
  Class Multiplier
*/
  Multiplier::Multiplier()
  {
    factor = 1;
    filling = 0;
  }


  Multiplier::~Multiplier()
  {

  }


  int Multiplier::getWidth()
  {
    return media::gfx::gui::multiplier.getFrame(0).getWidth();
  }


  int Multiplier::getFactor() const
  {
    return factor;
  }


  void Multiplier::setFactor(int factor)
  {
    this->factor = factor;

    if(factor >= MULTIPLIER_MAX_FACTOR)
      factor = MULTIPLIER_MAX_FACTOR;
  }


  double Multiplier::getFilling() const
  {
    return filling;
  }


  double Multiplier::getRelativeFilling() const
  {
    return filling / MULTIPLIER_MAX_FILLING;
  }


  void Multiplier::setFilling(double filling)
  {
    this->filling = filling;

    while(this->filling >= (int)MULTIPLIER_MAX_FILLING)
    {
      if(factor < MULTIPLIER_MAX_FACTOR)
      {
        factor++;
        this->filling -= MULTIPLIER_MAX_FILLING;
      }
      else
      {
        this->filling = MULTIPLIER_MAX_FILLING;
        break;
      }
    }

    if(filling >= (int)MULTIPLIER_MAX_FILLING )
      this->filling = (int)(MULTIPLIER_INIT_FILLING * MULTIPLIER_MAX_FILLING);


    if(this->filling <= 0)
    {
      this->filling = 0;
      this->factor = 1;
    }


    if(filling >= (int)MULTIPLIER_MAX_FILLING)
      this->filling = (int)(MULTIPLIER_INIT_FILLING * MULTIPLIER_MAX_FILLING);

  }

  void Multiplier::setRelativeFilling(double rel_filling)
  {
    setFilling(rel_filling * MULTIPLIER_MAX_FILLING);
  }


  void Multiplier::update()
  {
    double dec;

    Timer::update();

    dec = min(MULTIPLIER_DECREASE_SPEED_MAX, MULTIPLIER_DECREASE_SPEED_BASE + MULTIPLIER_DECREASE_SPEED_FACTOR * factor);

    setFilling(filling - Timer::getPerSecond(dec) * MULTIPLIER_MAX_FILLING);
  }


  void Multiplier::draw(double rel_filling)
  {
    media::gfx::gui::multiplier.draw
    (
      IntPoint(MULTIPLIER_BAR_X, MULTIPLIER_BAR_Y),
      ALIGN_BY_CORNER,
      IntRect(0, 0, (int)(rel_filling * getWidth()), media::gfx::gui::multiplier.getFrame(0).getHeight())
    );

  }

