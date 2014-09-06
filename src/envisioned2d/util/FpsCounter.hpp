#ifndef UTIL_FPSCOUNTER_HPP
#define UTIL_FPSCOUNTER_HPP


  #include "etc/int.h"
  #include "util/Timer.hpp"


  namespace util
  {
    class FpsCounter
    {
      public:

        FpsCounter();
        ~FpsCounter();


        /* (Re-)Start the counter - called before loop */
        void start();

        /* Frame finished - called once per loop */
        void frameFinished();

        double getFps() const;
        double getAverageFps() const;


      private:

        /* Data */
          Timer timer;
          u32 lastsecondticks;
          u32 thissecondframes;
          u32 totalframes;
          double fps;
    };
  }

#endif // UTIL_FPSCOUNTER_HPP
