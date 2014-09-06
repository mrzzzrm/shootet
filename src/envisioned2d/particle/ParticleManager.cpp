#include "./ParticleManager.hpp"

using namespace std;

using namespace util;
using namespace geo;
using namespace etc;
using namespace error;
using namespace gfx;

using namespace particle;

/*
  Class ParticleManager
*/

  ParticleManager::ParticleManager()
  {
    init();
  }


  ParticleManager::ParticleManager(const ParticleManager &particlemanager)
  {
    init();
    load(particlemanager);
  }


  ParticleManager::~ParticleManager()
  {
    clear();
  }


  void ParticleManager::load(const ParticleManager &particlemanager)
  {
    if(&particlemanager == this)
      return;

    clear();

    timer = particlemanager.timer;
    profiles = map_copy(particlemanager.profiles);
    particles = list_copy(particlemanager.particles);
    livingarea = particlemanager.livingarea;
    livingarea_active = particlemanager.livingarea_active;
  }


  void ParticleManager::clear()
  {
    timer.clear();
    map_delete_all_and_clear(profiles);
    list_delete_all_and_clear(particles);
    livingarea.clear();

    init();
  }


  ParticleProfile &ParticleManager::getParticleProfile(uint key)
  {
    std::map<uint, ParticleProfile*>::iterator i;

    i = profiles.find(key);

    if(i == profiles.end() || i->second == NULL)
      throw Exception() << "No such profile with key '" << key << "'";
    else
      return *(i->second);
  }


  const ParticleProfile &ParticleManager::getParticleProfileConst(uint key) const
  {
    std::map<uint, ParticleProfile*>::const_iterator i;

    i = profiles.find(key);

    if(i == profiles.end() || i->second == NULL)
      throw Exception() << "No such profile with key '" << key << "'";
    else
      return *(i->second);
  }


  bool ParticleManager::hasParticleProfile(uint key) const
  {
    std::map<uint, ParticleProfile*>::const_iterator i;

    i = profiles.find(key);

    if(i == profiles.end())
      return false;
    else
      return i->second != NULL;
  }


  void ParticleManager::setParticleProfile(uint key, ParticleProfile *particleprofile)
  {
    if(profiles[key] != NULL)
      delete profiles[key];

    profiles[key] = particleprofile;
  }


  Particle &ParticleManager::getParticle(uint index)
  {
    list<Particle*>::const_iterator i = particles.begin();

    if(index >= particles.size())
      throw Exception() << "No such praticle with index '" << index << "', listsize is '" << particles.size() << "'";

    advance(i, index);

    return *(*i);
  }


  const Particle &ParticleManager::getParticleConst(uint index) const
  {
    list<Particle*>::const_iterator i = particles.begin();

    if(index >= particles.size())
      throw Exception() << "No such praticle with index '" << index << "', listsize is '" << particles.size() << "'";

    advance(i, index);

    return *(*i);
  }


  int ParticleManager::getParticleCount() const
  {
    return particles.size();
  }


  void ParticleManager::addParticle(Particle *particle)
  {
    if(particle == NULL)
      throw Exception() << "Cannot add NULL-particle";
    else
      particles.push_back(particle);
  }


  void ParticleManager::removeParticle(uint index)
  {
    list<Particle*>::iterator i = particles.begin();

    if(index >= particles.size())
      throw Exception() << "No such praticle with index '" << index << "', listsize is '" << particles.size() << "'";

    advance(i, index);

    list_erase_and_delete(particles, i);
  }


  void ParticleManager::removeParticle(Particle *particle)
  {
    list<Particle*>::iterator i = std::find(particles.begin(), particles.end(), particle);

    if(i == particles.end())
      throw Exception() << "No such particle '" << particle << "'";
    else
      list_erase_and_delete(particles, i);
  }


  const IntRect &ParticleManager::getLivingArea() const
  {
    return livingarea;
  }


  bool ParticleManager::isLivingAreaActive() const
  {
    return livingarea_active;
  }


  void ParticleManager::setLivingArea(bool active, const IntRect &livingarea)
  {
    this->livingarea_active = active;
    this->livingarea = livingarea;
  }




  void ParticleManager::update()
  {

    for(list<Particle*>::iterator i = particles.begin(); i != particles.end();)
    {
      Particle *particle = *i;

      particle->update();

      /* Not updateable */
      if(particle->getProfile() == NULL || particle->getProfile()->getFrameCount() == 0)
        continue;


      /* Remove if dead */
      if(particle->isDead())
      {
        i = list_erase_and_delete(particles, i);
        continue;
      }

      /* Remove if outa living area */
      if(livingarea_active)
      {
        IntRect particlerect;

        particlerect.setX((int)particle->getX() - particle->getCurrentFrame().getWidth()/2);
        particlerect.setY((int)particle->getY() - particle->getCurrentFrame().getHeight()/2);
        particlerect.setWidth(particle->getCurrentFrame().getWidth());
        particlerect.setHeight(particle->getCurrentFrame().getHeight());

        if(!livingarea.isCovering(particlerect))
        {
          i = list_erase_and_delete(particles, i);
          continue;
        }
      }

      i++;
    }

  }


  void ParticleManager::genExplosionRect(const IntRect &rect, uint count, const FloatRandom &ran_speed, const IntRandom &ran_duration, uint particleprofile, const etc::Alignment &alignment)
  {
    IntRect brect;

    /* Align */
    brect = rect_align(rect, alignment);


    for(int p = 0; p < (int)count; p++)
    {
      double speed, deg;
      uint duration;
      IntPoint position;
      IntVector vector;

      speed = ran_speed.getNewValue();
      duration = ran_duration.getNewValue();

      position.setX(IntRandom(brect.getX(), brect.getX() + brect.getWidth()));
      position.setY(IntRandom(brect.getY(), brect.getY() + brect.getHeight()));

      deg = (position - IntPoint(brect.getX() + brect.getWidth()/2, brect.getY() + brect.getHeight()/2)).getDirection();

      vector.setX((int)(cos(deg) * speed));
      vector.setY((int)(-sin(deg) * speed));

      addParticle(new Particle(position, vector, duration, &getParticleProfile(particleprofile)));
    }
  }


  void ParticleManager::genExplosionCircle(const IntCircle &circle, uint count, const FloatRandom &ran_speed, const IntRandom &ran_duration, uint particleprofile, const etc::Alignment &alignment)
  {
    IntCircle bcircle;

    /* Align */
    bcircle = circle_align(circle, alignment);

    for(int p = 0; p < (int)count; p++)
    {
      double deg;
      double speed, dist;
      uint duration;
      IntPoint position;
      IntVector vector;

      deg = FloatRandom(2 * M_PI);
      dist = FloatRandom(bcircle.getRadius());

      speed = ran_speed.getNewValue();
      duration = ran_duration.getNewValue();

      position.setX(bcircle.getX() + bcircle.getRadius() + (int)(cos(deg) * dist));
      position.setY(bcircle.getY() + bcircle.getRadius() + (int)(-sin(deg) * dist));

      vector.setX((int)(cos(deg) * speed));
      vector.setY((int)(-sin(deg) * speed));

      addParticle(new Particle(position, vector, duration, &getParticleProfile(particleprofile)));
    }
  }



  void ParticleManager::draw(const IntRect &rect, const IntPoint &corner, const Alignment &alignment, Image *image)
  {
    update();
    drawConst(rect, corner, alignment, image);
  }


  void ParticleManager::drawConst(const IntRect &rect, const IntPoint &corner, const Alignment &alignment, Image *image) const
  {
    IntSize size;
    IntRect brect;


    /* Size */
    if(image != NULL)
      size = image->getSize();
    else if(SDL_GetVideoSurface() != NULL)
      size.load(gfx::getScreenSize());
    else
      return;

    /* Translate negative size and align */
    brect = rect_translate_negative_axises(rect, size);
    brect.setX(brect.getX() - (int)(brect.getWidth() * alignment.getX()));
    brect.setY(brect.getY() - (int)(brect.getHeight() * alignment.getY()));

    /* Draw */
    for(list<Particle*>::const_iterator i = particles.begin(); i != particles.end();i++)
    {
      Particle *particle = *i;
      IntPoint position = vector_to_point(IntVector(brect.getX(), brect.getY()) - point_to_vector(corner)) + point_to_vector(particle->getPosition());

      if(particle->getProfile() == NULL || particle->getProfile()->getFrameCount() == 0)
        continue;

      int wh = particle->getCurrentFrame().getWidth()/2;
      int hh = particle->getCurrentFrame().getHeight()/2;

      if(position.getX() + wh < brect.getX() || position.getY() + hh < brect.getY() ||
         position.getX() - wh > brect.getX() + brect.getWidth() ||
         position.getY() + hh > brect.getY() + brect.getHeight())
        continue;

      particle->draw(position, ALIGN_BY_CENTER);
    }
  }


  ParticleManager &ParticleManager::operator=(const ParticleManager &particlemanager)
  {
    load(particlemanager);
    return *this;
  }


  void ParticleManager::init()
  {
    livingarea_active = false;
  }

