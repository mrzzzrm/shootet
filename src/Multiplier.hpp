#ifndef MULTIPLIER_HPP
#define MULTIPLIER_HPP

  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"

  class Multiplier: public util::Timer
  {
    public:

      Multiplier();
      ~Multiplier();


      /* Height */
        static int getWidth();


      /* Factor */
        int getFactor() const;
        void setFactor(int factor);


      /* Filling */
        double getFilling() const;
        double getRelativeFilling() const;
        void setFilling(double filling);
        void setRelativeFilling(double rel_filling);


      /* Loop */
        void update();
        void draw(double rel_filling);


    private:

      /* Data */
        int factor;
        double filling;

  };

#endif // MULTIPLIER_HPP
