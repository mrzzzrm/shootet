#ifndef PARTICLE_PARTICLE_HPP
#define PARTICLE_PARTICLE_HPP

  #include <list>

  #include "etc/int.h"

  #include "util/util.hpp"
  #include "gfx/gfx.hpp"
  #include "geo/geo.hpp"

  #include "./ParticleFrame.hpp"
  #include "./ParticleProfile.hpp"


  namespace particle
  {
    class Particle: public util::Movement
    {
      public:

        Particle();
        Particle(const geo::FloatPoint &position, const geo::FloatVector &vector, uint duration, const ParticleProfile *profile = NULL);
        Particle(const Particle &particle);
        ~Particle();


        /* Load */
          void load(const geo::FloatPoint &position, const geo::FloatVector &vector, uint duration, const ParticleProfile *profile = NULL);
          void load(const Particle &particle);


        /* Clear */
          void clear();



        /* Position */
          double getX() const;
          double getY() const;
          void setX(double x);
          void setY(double y);
          const geo::FloatPoint &getPosition() const;
          void setPosition(const geo::FloatPoint &position);


        /* Vector */
          const geo::FloatVector &getVector() const;
          void setVector(const geo::FloatVector &vector);


        /* Duration */
          int getDuration() const;
          void setDuration(uint duration);


        /* Profile */
          const ParticleProfile *getProfile() const;
          void setProfile(const ParticleProfile *profile);


        /* Frames */
          const ParticleFrame &getCurrentFrame() const;
          int getCurrentFrameIndex() const;


        /* Update */
          void update();


        /* Status */
          bool isDead() const;


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL) const;



        /* Operators */
          Particle &operator=(const Particle &particle);


      private:

        /* Data */
          uint duration;
          util::Timer timer;
          geo::FloatPoint position;

          const ParticleProfile *profile;



        /* Internals */
          void init();
    };
  }

#endif // PARTICLE_PARTICLE_HPP
