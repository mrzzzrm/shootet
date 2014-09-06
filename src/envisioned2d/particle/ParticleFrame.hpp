#ifndef PARTICLE_PARTICLEFRAME_HPP
#define PARTICLE_PARTICLEFRAME_HPP

  #include "etc/Alignment.hpp"
  #include "gfx/gfx.hpp"
  #include "geo/geo.hpp"
  #include "error/Exception.hpp"


  #include "gfx/ImageClipping.hpp"

  namespace particle
  {
    class ParticleFrame: public gfx::ImageClipping
    {
      public:

        ParticleFrame();
        ParticleFrame(const gfx::ImageClipping &imageclipping, double duration);
        ParticleFrame(const ParticleFrame &particleframe);
        ~ParticleFrame();


        /* Load */
          void load(const gfx::ImageClipping &imageclipping, double duration);
          void load(const ParticleFrame &particleframe);


        /* Clear */
          void clear();

        /* Duration */
          double getDuration() const;
          void setDuration(double duration);


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL) const;



        /* Opartators */
          ParticleFrame &operator=(const ParticleFrame &particleframe);


      private:

        /* Data */
          double duration;


        /* Internals */
          void init();
    };
  }

#endif // PARTICLE_PARTICLEFRAME_HPP
