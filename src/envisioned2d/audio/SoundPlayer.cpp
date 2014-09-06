#include "./SoundPlayer.hpp"

using namespace std;
using namespace error;
using namespace util;


const uint MAX_CHANNELS = 1024;

namespace audio
{
  Timer SoundPlayer::timer;
  bool SoundPlayer::doubling_protection = true;
  time_t SoundPlayer::doubling_protection_ticks = 100;
  std::map<uint, pair<const Sound*, time_t> > SoundPlayer::channelmap;


  uint SoundPlayer::play(const Sound &sound)
  {
    __audio__assert_open();

    int reschannel;

    timer.update();

    /* Break */
      if(sound.sound == NULL)
        throw Exception() << "Cannot play unloaded sound";

    /* Check if doubling protection is necesarry */
      if(DoublingProtection(sound))
        return 0;

    /* Allocate extra channels */
      if(Mix_Playing(-1) == Mix_AllocateChannels(-1))
        Mix_AllocateChannels(Mix_AllocateChannels(-1) + 1);

    /* Play */
      if((reschannel = Mix_PlayChannel(-1, sound.sound, 0)) < 0)
        throw Exception() << "Couldn't play sound " << sound.path << ": '" << Mix_GetError() << "'";

    /* Register */
      Mix_ChannelFinished(channel_finished);
      channelmap[reschannel].first = &sound;
      channelmap[reschannel].second = timer.getTicks();

    /* Return */
      return reschannel;
  }

  void SoundPlayer::playInChannel(const Sound &sound, uint channel)
  {
    __audio__assert_open();

    timer.update();

    /* Break */
      if(sound.sound == NULL)
        throw Exception() << "Cannot play unloaded sound";


    /* Check if doubling protection is necesarry */
      if(DoublingProtection(sound))
        return;

    /* Break */
      if(channel > MAX_CHANNELS)
        throw Exception() << "Cannot play in channel " << channel << ", max allowed channels are " << MAX_CHANNELS;


    /* Allocation of extra channels */
      if((int)(channel) >= Mix_AllocateChannels(-1))
        Mix_AllocateChannels(channel + 1);


    /* Play */
      if(Mix_PlayChannel(channel, sound.sound, 0) < 0)
        throw Exception() << "Couldn't play sound " << sound.path << ": '" << Mix_GetError() << "'";


    /* Register */
      Mix_ChannelFinished(channel_finished);
      channelmap[channel].first = &sound;
      channelmap[channel].second = timer.getTicks();

  }


  void SoundPlayer::pause()
  {
    Mix_Pause(-1);
  }


  void SoundPlayer::resume()
  {
    Mix_Resume(-1);
  }


  void SoundPlayer::halt()
  {
    Mix_HaltChannel(-1);
  }


  void SoundPlayer::fadeOut(uint ms)
  {
    Mix_FadeOutChannel(-1, ms);
  }


  void SoundPlayer::setDoublingProtectionActive(bool is)
  {
    doubling_protection = is;
  }


  bool SoundPlayer::isDoublingProtectionActive()
  {
    return doubling_protection;
  }


  void SoundPlayer::setDoublingProtectionTicks(const time_t &ticks)
  {
    doubling_protection_ticks = ticks;
  }


  const time_t &SoundPlayer::getDoublingProtctionTicks()
  {
    return doubling_protection_ticks;
  }


  void SoundPlayer::pause(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1) && channel >= 0)
      Mix_Pause(channel);

  }


  void SoundPlayer::resume(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1) && channel >= 0 && Mix_Paused(channel))
      Mix_Resume(channel);

  }


  void SoundPlayer::halt(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1) && channel >= 0 && Mix_Playing(channel))
      Mix_HaltChannel(channel);

  }


  void SoundPlayer::fadeOut(uint ms, uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1) && channel >= 0 && Mix_Playing(channel))
      Mix_FadeOutChannel(ms, channel);

  }


  bool SoundPlayer::isPlaying()
  {
    return Mix_Playing(-1) > Mix_Paused(-1);
  }


  bool SoundPlayer::isPaused()
  {
    return Mix_Paused(-1) > 0;
  }


  bool SoundPlayer::isHalted()
  {
    return Mix_Playing(-1) == 0;
  }


  bool SoundPlayer::isChannelPlaying(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1))
      return  Mix_Playing(channel) && !Mix_Paused(channel);
    else
      return false;
  }


  bool SoundPlayer::isChannelPaused(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1))
      return  Mix_Playing(channel) && Mix_Paused(channel);
    else
      return false;
  }


  bool SoundPlayer::isChannelHalted(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1))
      return  !Mix_Playing(channel);
    else
      return false;
  }


  uint SoundPlayer::getChannelCount()
  {
    return Mix_AllocateChannels(-1);
  }


  void SoundPlayer::setChannelCount(uint count)
  {
    if((int)(count) > Mix_AllocateChannels(-1))
    {
      for(std::map<uint, pair<const Sound*, time_t> >::iterator i = channelmap.begin(); i != channelmap.end(); i++)
      {
        if(i->first >= count)
        {
          Mix_HaltChannel(i->first);
        }
      }
    }

    if(count <= MAX_CHANNELS)
      Mix_AllocateChannels(count);
    else
      throw Exception() << "Cannot use more than " << MAX_CHANNELS << " channels";
  }


  void SoundPlayer::setVolume(double volume)
  {
    if(!in_range(volume, 1.0))
      cerr << "Overrunning sound volume range 0...1 with value '" << volume << "'" << endl;


    limit(volume, 1.0);


    Mix_Volume(-1, (int)(volume * MIX_MAX_VOLUME));
  }


  double SoundPlayer::getChannelVolume(uint channel)
  {
    if((int)channel < Mix_AllocateChannels(-1))
      return  Mix_Volume(channel, -1);
    else
      return 0;
  }


  void SoundPlayer::setChannelVolume(uint channel, double volume)
  {
    if(!in_range(volume, 1.0))
      cerr << "Overrunning channel volume range 0...1 with value '" << volume << "'" << endl;

    limit(volume, 1.0);

    if((int)channel < Mix_AllocateChannels(-1))
      Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
  }


  bool SoundPlayer::haltSound(const Sound &sound)
  {
    bool stopped = false;

    for(std::map<uint, pair<const Sound*, time_t> >::iterator i = channelmap.begin(); i != channelmap.end(); i++)
    {
      if(i->second.first == &sound)
      {
        std::map<uint, pair<const Sound*, time_t> >::iterator ti;

        if((int)(i->first) < Mix_AllocateChannels(-1))
          Mix_HaltChannel(i->first);

        ti = i;
          ti--;

        channelmap.erase(i);
          i = ti;

        stopped = true;
      }
    }

    return stopped;
  }


  void SoundPlayer::channel_finished(int channel)
  {
    channelmap[channel].first = NULL;
  }

  bool SoundPlayer::DoublingProtection(const Sound &sound)
  {
    if(doubling_protection)
      {
        for(map<uint, pair<const Sound*, time_t> >::const_iterator i = channelmap.begin(); i != channelmap.end(); i++)
        {
          if(i->second.first == NULL)
            continue;

          if(*(i->second.first) == sound && i->second.second + doubling_protection_ticks >= timer.getTicks())
            return true;
        }
      }
      return false;
  }

}


