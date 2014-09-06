#ifndef UTIL_MOVEMENT_HPP
#define UTIL_MOVEMENT_HPP

  #include <map>

  #include "etc/int.h"
  #include "error/Exception.hpp"
  #include "geo/geo.hpp"
  #include "util/Timer.hpp"



  namespace util
  {

    class Movement: public geo::FloatVector
    {
      public:

        Movement();
        Movement(const geo::FloatVector &vector);
        Movement(const Movement &movement);
        ~Movement();


        /* Load */
          void load(const geo::FloatVector &vector);
          void load(const Movement &movement);


        /* Clear */
          void clear();


        /* Update(accelerate) */
          void update();


        /* Acceleration */
          bool isAccelerationSet(u32 index) const;
          const geo::FloatVector &getAcceleration(u32 index) const;
          void setAcceleration(u32 index, const geo::FloatVector &acceleration);


        /* Operators */
          Movement &operator=(const geo::FloatVector &vector);
          Movement &operator=(const Movement &movement);

          /* All other vector specific operators are inherited! */


      private:

        /* Data */
          Timer timer;
          geo::FloatVector vector;
          std::map<u32, geo::FloatVector*> accelerationmap;


    };
  }

#endif // UTIL_MOVEMENT_HPP
