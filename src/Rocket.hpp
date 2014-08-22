#ifndef ROCKET_HPP
#define ROCKET_HPP

  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"


  class Rocket: public geo::FloatPoint
  {
    public:

      Rocket(const geo::FloatPoint &position);
      ~Rocket();


      /* Column */
        int getColumn() const;


      /* Height */
        static int getHeight();


      /* Loop */
        void update();


    private:

      /* Data */
        util::Timer timer;
        int column;

  };

#endif // ROCKET_HPP
