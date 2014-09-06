#include "./Fading.hpp"


using namespace std;

namespace gfx
{


  Fading::Fading()
  {
    init();
  }

  Fading::Fading(int ticks, FADE_TYPE type)
  {
    init();
    load(ticks, type);
  }

  Fading::Fading(const Fading &fading)
  {
    if(&fading == this)
      return;

    init();
    load(fading);
  }


  Fading::~Fading()
  {

  }


  void Fading::load(int ticks, FADE_TYPE type)
  {
    clear();

    this->start = Timer::getTicks();
    this->ticks = ticks;
    this->type = type;

    switch(type)
    {
      case FADE_NOT: alpha = 0; break;
      case FADE_IN: alpha = 0; break;
      case FADE_OUT: alpha = 1; break;
    }
  }


  void Fading::load(const Fading &fading)
  {
    Timer::load(fading);

    start = fading.start;
    ticks = fading.ticks;
    type = fading.type;
    alpha = fading.alpha;

  }


  void Fading::clear()
  {
    Timer::clear();

    init();
  }


  int Fading::getTicks() const
  {
    return ticks;
  }


  void Fading::setTicks(int ticks)
  {
    this->ticks = ticks;
  }


  int Fading::getRemainingTicks()
  {
    return ticks + start - Timer::getTicks();
  }


  void Fading::setRemainingTicks(int ticks)
  {
    this->ticks = (Timer::getTicks() - start) + ticks;
  }


  FADE_TYPE Fading::getType() const
  {
    return type;
  }


  void Fading::setType(FADE_TYPE type)
  {
    if(isDone())
      forceStart(type);
    else
      this->type = type;
  }


  double Fading::getAlpha() const
  {
    return alpha;
  }


  void Fading::setAlpha(double alpha)
  {
    this->alpha = alpha;
  }


  bool Fading::isDone() const
  {
    if(Timer::getTicks() >= start + ticks)
      return true;
    else if(type == FADE_NOT)
      return true;
    else
      return false;

  }


  void Fading::update()
  {
    int finish;

    Timer::update();

    finish = start + ticks;


    if(finish > Timer::getTicks())
    {
      int remaining_ticks;

      remaining_ticks = finish - Timer::getTicks();

      switch(type)
      {
        case FADE_IN:
          alpha += ((1.0f - alpha) / (double)remaining_ticks) * getPeriod();
        break;

        case FADE_OUT:
          alpha -= (alpha / (double)remaining_ticks) * getPeriod();
        break;

        default: break;
      }

      if(alpha > 1)
        alpha = 1;
      if(alpha < 0)
        alpha = 0;
    }
    else
    {
      switch(type)
      {
        case FADE_IN: alpha = 1; break;
        case FADE_OUT: alpha = 0; break;

        default: break;
      }

    }

  }


  void Fading::forceStart(FADE_TYPE type)
  {
    this->type = type;
    Timer::update();
    start = Timer::getTicks();

    if(type == FADE_IN)
      alpha = 0;
    else if(type == FADE_OUT)
      alpha = 1;
  }


  Fading &Fading::operator=(const Fading &fading)
  {
    load(fading);
    return *this;
  }

  void Fading::init()
  {
    alpha = 1;
    start = 0;
    ticks = 0;
    type = FADE_OUT;
  }
}
