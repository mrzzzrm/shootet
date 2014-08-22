#include "./Sound.hpp"
#include "./SoundPlayer.hpp"


using namespace std;

using namespace error;;
using namespace util;



namespace audio
{
  Sound::Sound()
  {
    init();
  }


  Sound::Sound(const Path &path)
  {
    init();
    load(path);
  }


  Sound::Sound(const Sound &sound)
  {
    init();
    load(sound);
  }


  Sound::~Sound()
  {
    clear();
  }


  void Sound::load(const Path &path)
  {
    __audio__assert_open();

    clear();

    if((sound = Mix_LoadWAV(path.c_str())) == NULL)
      throw Exception() << "Couldn't load " << path << ": '" << Mix_GetError() << "'";

    this->path = path;
  }


  void Sound::load(const Sound &sound)
  {
    if(&sound == this)
      return;

    load(sound.path);
  }


  void Sound::clear()
  {
//    if(SoundPlayer::haltSound(*this))
//      cout << "<Warning>: audio::Sound " << path << " gets cleared whilst still playing" << endl;

    if(sound != NULL)
      Mix_FreeChunk(sound);

    path.clear();

    init();
  }


  const Path &Sound::getPath() const
  {
    return path;
  }


  double Sound::getVolume() const
  {
    if(sound != NULL)
      return (double)Mix_VolumeChunk(sound, -1)/255.0f;
    else
      return 0;
  }


  void Sound::setVolume(double volume)
  {

    if(!in_range(volume, 1.0))
      cerr << "Overrunning volume range 0...1 with value '" << volume << "'" << endl;

    limit(volume, 1.0);
    if(sound != NULL)
      Mix_VolumeChunk(sound, (int)(volume * 255));
  }


  uint Sound::play()
  {
    return SoundPlayer::play(*this);
  }


  void Sound::playInChannel(uint channel)
  {
    SoundPlayer::playInChannel(*this, channel);
  }


  Sound &Sound::operator=(const Sound &sound)
  {
    load(sound);
    return *this;
  }


  bool Sound::operator==(const Sound &sound) const
  {
    return path == sound.path;
  }


  void Sound::init()
  {
    sound = NULL;
  }

}

