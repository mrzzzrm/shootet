#include "./ParticleProfile.hpp"

using namespace std;

using namespace error;
using namespace util;

using namespace particle;


/*
  Class ParticleProfile
*/

  ParticleProfile::ParticleProfile()
  {
    init();
  }


  ParticleProfile::ParticleProfile(const ParticleProfile &particleprofile)
  {
    init();
    load(particleprofile);
  }


  ParticleProfile::~ParticleProfile()
  {
    clear();
  }


  void ParticleProfile::load(const ParticleProfile &particleprofile)
  {
    if(&particleprofile == this)
      return;

    clear();

    frames = vector_copy(particleprofile.frames);
    duration = particleprofile.duration;
  }


  void ParticleProfile::clear()
  {
    vector_delete_all_and_clear(frames);
    init();
  }


  double ParticleProfile::getDuration() const
  {
    return duration;
  }


  const ParticleFrame &ParticleProfile::getFrame(u32 index) const
  {
    vector<const ParticleFrame*>::const_iterator i = frames.begin();

    if(index >= frames.size())
      throw Exception() << "No such frame with index '" << index << "', listsize is '" << frames.size() << "'";

    advance(i, index);

    return *(*i);
  }


  u32 ParticleProfile::getFrameCount() const
  {
    return frames.size();
  }

  void ParticleProfile::addFrame(const ParticleFrame &frame, int index)
  {
    vector<const ParticleFrame*>::iterator i = frames.begin();

    if(index < 0)
      index = frames.size() + index;
    index++;

    if(index > (int)frames.size())
      throw Exception() << "No such frame with index '" << index << "', listsize is '" << frames.size() << "'";

    advance(i, index);

    frames.insert(i, new ParticleFrame(frame));

    duration += frame.getDuration();
  }


  void ParticleProfile::removeFrame(int index)
  {
    vector<const ParticleFrame*>::iterator i = frames.begin();

    if(index > 0)
      index = frames.size() + index;
    index++;

    if(index > (int)frames.size())
      throw Exception() << "No such frame with index '" << index << "', listsize is '" << frames.size() << "'";

    advance(i, index);
    duration -= (*i)->getDuration();

    vector_erase_and_delete(frames, i);
  }


  ParticleProfile &ParticleProfile::operator=(const ParticleProfile &particleprofile)
  {
    load(particleprofile);
    return *this;
  }

  void ParticleProfile::init()
  {
    duration = 0;
  }

