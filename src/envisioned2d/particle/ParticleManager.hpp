#ifndef PARTICLE_PARTICLEMANAGER_HPP
#define PARTICLE_PARTICLEMANAGER_HPP

  #include <list>
  #include <map>
  #include <algorithm>


  #include "geo/geo.hpp"
  #include "util/util.hpp"
  #include "error/Exception.hpp"

  #include "./Particle.hpp"
  #include "./ParticleFrame.hpp"
  #include "./ParticleProfile.hpp"

  namespace particle
  {

    class ParticleManager
    {
      public:

        ParticleManager();
        ParticleManager(const ParticleManager &particlemanager);
        ~ParticleManager();


        /* Load */
          void load(const ParticleManager &particlemanager);


        /* Clear */
          void clear();


        /* Profiles */
          ParticleProfile &getParticleProfile(uint key);
          const ParticleProfile &getParticleProfileConst(uint key) const;
          bool hasParticleProfile(uint key) const;
          void setParticleProfile(uint key, ParticleProfile *particleprofile);


        /* Particles */
          Particle &getParticle(uint index);
          const Particle &getParticleConst(uint index) const;
          int getParticleCount() const;
          void addParticle(Particle *particle);
          void removeParticle(uint index);
          void removeParticle(Particle *particle);


        /* Living Area */
          const geo::IntRect &getLivingArea() const;
          bool isLivingAreaActive() const;
          void setLivingArea(bool active, const geo::IntRect &livingarea);


        /* Update */
          void update();


        /* Generate */
          void genExplosionRect(const geo::IntRect &rect, uint count, const util::FloatRandom &ran_speed, const util::IntRandom &ran_duration, uint particleprofile, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER));
          void genExplosionCircle(const geo::IntCircle &circle, uint count, const util::FloatRandom &ran_speed, const util::IntRandom &ran_duration, uint particleprofile, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CENTER));


        /* Draw */
          void draw(const geo::IntRect &rect, const geo::IntPoint &corner, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL);
          void drawConst(const geo::IntRect &rect, const geo::IntPoint &corner, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL) const;


        /* Operators */
          ParticleManager &operator=(const ParticleManager &particlemanager);


      private:

        /* Data */
          util::Timer timer;
          std::map<uint, ParticleProfile*> profiles;
          std::list<Particle*> particles;
          geo::IntRect livingarea;
          bool livingarea_active;


        /* Internals */
          void init();

    };
  }

#endif // PARTICLE_PARTICLEMANAGER_HPP
