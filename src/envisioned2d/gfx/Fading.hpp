#ifndef GFX_FADING_HPP
#define GFX_FADING_HPP

  #include <iostream>

  #include "geo/geo.hpp"
  #include "util/util.hpp"



  namespace gfx
  {
    enum FADE_TYPE
    {
      FADE_NOT,
      FADE_IN,
      FADE_OUT
    };

    const double ALPHA_OPAQUE = 1;
    const double ALPHA_SEMI = 0.5;
    const double ALPHA_TRANSPARENT = 0;


    class Fading: public util::Timer
    {
      public:

        Fading();
        Fading(int ticks, FADE_TYPE type);
        Fading(const Fading &fading);
        ~Fading();


        /* Load */
          void load(int ticks, FADE_TYPE type);
          void load(const Fading &fading);


        /* Clear */
          void clear();


        /* Time */
          int getTicks() const;
          void setTicks(int ticks);
          int getRemainingTicks();
          void setRemainingTicks(int ticks);


        /* Type */
          FADE_TYPE getType() const;
          void setType(FADE_TYPE type);


        /* Alpha */
          double getAlpha() const;
          void setAlpha(double alpha);


        /* State */
          bool isDone() const;


        /* Update */
          void update();


        /* Start */
          void forceStart(FADE_TYPE type);


        /* Operators */
          Fading &operator=(const Fading &fading);


      protected:

        /* Data */
          double alpha;
          int ticks;
          int start;
          FADE_TYPE type;


      private:

        /* Internals */
          void init();
    };
  }

#endif // GFX_FADING_HPP
