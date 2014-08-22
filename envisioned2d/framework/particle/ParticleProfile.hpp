#ifndef PARTICLE_PARTICLEPROFILE_HPP
#define PARTICLE_PARTICLEPROFILE_HPP

  #include "geo/geo.hpp"
  #include "gfx/gfx.hpp"
  #include "util/util.hpp"
  #include "error/Exception.hpp"

  #include "./ParticleFrame.hpp"

  namespace particle
  {
    class ParticleProfile
    {
      public:

        ParticleProfile();
        ParticleProfile(const ParticleProfile &particleprofile);
        ~ParticleProfile();


        /* Load */
          void load(const ParticleProfile &particleprofile);


        /* Clear */
          void clear();


        /* Duration */
          double getDuration() const;


        /* Frames */
          const ParticleFrame &getFrame(u32 index) const;
          u32 getFrameCount() const;
          void addFrame(const ParticleFrame &frame, int index = -1);
          void removeFrame(int index);


        /* Operators */
          ParticleProfile &operator=(const ParticleProfile &particleprofile);


        private:

          /* Data */
            std::vector<const ParticleFrame*> frames;
            double duration;


          /* Internals */
            void init();

    };
  }

#endif // PARTICLE_PARTICLEPROFILE_HPP
