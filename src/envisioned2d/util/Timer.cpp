#include "Timer.hpp"

using namespace std;

namespace util
{


  Timer::Timer()
  {
    init();
  }


  Timer::Timer(const Timer &timer)
  {
    init();
    load(timer);
  }


  Timer::~Timer()
  {

  }


  void Timer::load(const Timer &timer)
  {
    if(&timer == this)
      return;

    start = timer.start;
    period = timer.period;
    ticks = timer.ticks;

    lastupdate = timer.lastupdate;

    paused = timer.paused;
    lastpauseupdate = timer.lastpauseupdate;
    pausedticks = timer.pausedticks;
  }


  void Timer::clear()
  {
    reset();
  }


  int Timer::getPeriod() const
  {
    return period;
  }


  int Timer::getStart() const
  {
    return start;
  }


  int Timer::getElapsed() const
  {
    return ticks - start;
  }


  int Timer::getTicks() const
  {
    return ticks;
  }


  void Timer::pause()
  {
    if(!paused)
    {
      paused = true;
      lastpauseupdate = ticks;
    }
  }


  int Timer::getGlobalTicks()
  {
    return SDL_GetTicks();
  }


  void Timer::run()
  {
    update();
    paused = false;
  }


  bool Timer::isPaused() const
  {
    return paused;
  }


  void Timer::update()
  {
    if(paused)
    {
      pausedticks += (SDL_GetTicks() - pausedticks) - lastpauseupdate;

      period = 0;
      lastpauseupdate = SDL_GetTicks() - pausedticks;
    }
    else
    {
      ticks = SDL_GetTicks() - pausedticks;
      period = ticks - lastupdate;

      lastupdate = ticks;
    }

  }


  void Timer::reset()
  {
    init();
  }


  Timer &Timer::operator=(const Timer &timer)
  {
    load(timer);
    return *this;
  }


  void Timer::init()
  {
    start = SDL_GetTicks();
    period = 0;
    ticks =  start;

    lastupdate = start;

    pausedticks = 0;
    lastpauseupdate = 0;
    paused = false;
  }
}
