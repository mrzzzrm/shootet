#include "./ParticleFrame.hpp"

using namespace std;

using namespace geo;
using namespace gfx;
using namespace error;
using namespace util;
using namespace etc;
using namespace particle;


/*
  Class ParticleFrame
*/

  ParticleFrame::ParticleFrame()
  {
    init();
  }


  ParticleFrame::ParticleFrame(const gfx::ImageClipping &imageclipping, double duration)
  {
    init();
    load(imageclipping, duration);
  }


  ParticleFrame::ParticleFrame(const ParticleFrame &particleframe)
  {
    init();
    load(particleframe);
  }


  ParticleFrame::~ParticleFrame()
  {
    clear();
  }


  void ParticleFrame::load(const gfx::ImageClipping &imageclipping, double duration)
  {
    ImageClipping::load(imageclipping);
    this->duration = duration;
  }


  void ParticleFrame::load(const ParticleFrame &particleframe)
  {
    if(&particleframe == this)
      return;

    ImageClipping::load(particleframe);
    duration = particleframe.duration;
  }



  void ParticleFrame::clear()
  {
    ImageClipping::clear();
    init();
  }

  double ParticleFrame::getDuration() const
  {
    return duration;
  }


  void ParticleFrame::setDuration(double duration)
  {
    this->duration = duration;
  }


  void ParticleFrame::draw(const IntPoint &pos, const Alignment &alignment, Image *image) const
  {
    ImageClipping::draw(pos, alignment, IntRect(0, 0, -1, -1), image);
  }


  void ParticleFrame::init()
  {
    duration = 0;
  }

