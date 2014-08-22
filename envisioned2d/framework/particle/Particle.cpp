#include "./Particle.hpp"

using namespace std;

using namespace util;
using namespace etc;
using namespace geo;
using namespace gfx;
using namespace error;

namespace particle
{

  Particle::Particle()
  {
    init();
  }


  Particle::Particle(const geo::FloatPoint &position, const geo::FloatVector &vector, uint duration, const ParticleProfile *profile)
  {
    init();
    load(position, vector, duration, profile);
  }


  Particle::Particle(const Particle &particle)
  {
    init();
    load(particle);
  }


  Particle::~Particle()
  {
    clear();
  }


  void Particle::load(const geo::FloatPoint &position, const geo::FloatVector &vector, uint duration, const ParticleProfile *profile)
  {
    clear();

    Movement::load(vector);
    this->duration = duration;
    this->position = position;
    this->profile = profile;
  }


  void Particle::load(const Particle &particle)
  {
    if(&particle == this)
      return;

    clear();

    Movement::load(particle);
    duration = particle.duration;
    timer = particle.timer;
    position = particle.position;
    profile = particle.profile;
  }


  void Particle::clear()
  {
    Movement::clear();

    timer.clear();
    position.clear();

    init();
  }


  double Particle::getX() const
  {
    return position.getX();
  }


  double Particle::getY() const
  {
    return position.getY();
  }


  void Particle::setX(double x)
  {
    position.setX(x);
  }


  void Particle::setY(double y)
  {
    position.setY(y);
  }



  const geo::FloatPoint &Particle::getPosition() const
  {
    return position;
  }


  void Particle::setPosition(const geo::FloatPoint &position)
  {
    this->position = position;
  }


  const geo::FloatVector &Particle::getVector() const
  {
    return *(static_cast<const FloatVector*>(this));
  }


  void Particle::setVector(const geo::FloatVector &vector)
  {
    Movement::load(vector);
  }


  int Particle::getDuration() const
  {
    return duration;
  }


  void Particle::setDuration(uint duration)
  {
    this->duration = duration;
  }


  const ParticleProfile *Particle::getProfile() const
  {
    return profile;
  }


  void Particle::setProfile(const ParticleProfile *profile)
  {
    this->profile = profile;
  }


  const ParticleFrame &Particle::getCurrentFrame() const
  {
    if(profile != NULL)
      return profile->getFrame(getCurrentFrameIndex());
    else
      throw Exception() << "No profile";
  }


  int Particle::getCurrentFrameIndex() const
  {
    double rel, passed;

    if(profile == NULL)
      throw Exception() << "No profile";
    if(profile->getFrameCount() == 0)
      throw Exception() << "No frames";

    if(duration == 0)
      return 0;


    rel = ((double)timer.getElapsed() / (double)duration) * profile->getDuration();
    passed = 0;
    for(uint f = 0; f < profile->getFrameCount(); f++)
    {
      passed += profile->getFrame(f).getDuration();

      if(rel <= passed)
        return f;
    }

    return profile->getFrameCount() - 1;
  }


  void Particle::update()
  {
    timer.update();

    Movement::update();

    position += timer.getPerSecond(getVector());
  }


  bool Particle::isDead() const
  {
    return timer.getElapsed() >= (int)duration;
  }

  void Particle::draw(const IntPoint &pos, const Alignment &alignment, Image *image) const
  {
    if(profile != NULL && profile->getFrameCount() > 0)
      getCurrentFrame().draw(pos, alignment, image);
  }


  Particle &Particle::operator=(const Particle &particle)
  {
    load(particle);
    return *this;
  }


  void Particle::init()
  {
    duration = 0;
    profile = NULL;
  }
}

