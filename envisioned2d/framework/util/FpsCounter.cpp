#include "FpsCounter.hpp"


namespace util
{
  FpsCounter::FpsCounter()
  {
    start();
  }


  FpsCounter::~FpsCounter()
  {

  }


  void FpsCounter::start()
  {
    /* Update timer */
      timer.update();


    /* Reset all values */
      lastsecondticks = timer.getTicks();
      thissecondframes = 0;
      totalframes = 0;
      fps = -1;
  }


  void FpsCounter::frameFinished()
  {
    /* Update the timer */
      timer.update();


    /* Add a new frame */
      thissecondframes++;
      totalframes++;


    /* If a second is over, update */
      if(timer.getTicks() - lastsecondticks >= 1000)
      {
        fps = (static_cast<double>(thissecondframes) * 1000) / (timer.getTicks() - lastsecondticks);
        lastsecondticks = timer.getTicks();
        thissecondframes = 0;
      }
  }


  double FpsCounter::getFps() const
  {
    return fps;
  }


  double FpsCounter::getAverageFps() const
  {
    return static_cast<double>(totalframes) / (static_cast<double>(timer.getElapsed()) / 1000);
  }


}

