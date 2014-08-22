#ifndef UTIL_TIMER_HPP
#define UTIL_TIMER_HPP

  #include <iostream>
  #include <SDL/SDL.h>

  #include "etc/int.h"

  namespace util
  {

    class Timer
    {
      public:

        Timer();
        Timer(const Timer &timer);
        ~Timer();


        /* Load */
          void load(const Timer &timer);


        /* Clear(=reset()) */
          void clear();


        /* Get - Interface */
          int getStart() const;
          int getElapsed() const;
          int getPeriod() const;
          int getTicks() const;


        /* 'val' relative to period  */
          template<typename T> T getPerSecond(const T &val) const;


        /* Pause/run */
          void pause();
          void run();
          bool isPaused() const;


        /* Up to date ticks */
          static int getGlobalTicks();


        /* Command - Interface */
          void update();
          void reset();


        /* Operators */
          Timer &operator=(const Timer &timer);


      //private:

        /* Data */
          int start;
          int period;
          int ticks;

          int lastupdate;

          int pausedticks;
          int lastpauseupdate;
          bool paused;


        /* Internals - Attention! Not memory save!!! */
          void init();
    };
  }

  /* Include template */
    #include "./Timer.tpp"

#endif // UTIL_TIMER_HPP
