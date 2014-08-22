#ifndef AUDIO_SOUNDPLAYER_HPP
#define AUDIO_SOUNDPLAYER_HPP

  #include <map>
  #include <SDL/SDL_mixer.h>

  #include "error/Exception.hpp"

  #include "./Sound.hpp"
  #include "./__assert.hpp"


  namespace audio
  {
    const int AUDIO_ALL_CHANNELS = -1;
    const int AUDIO_FREE_CHANNEL = -1;

    class SoundPlayer
    {
      public:

        /* Play a sound */
          static uint play(const Sound &sound);
          static void playInChannel(const Sound &sound, uint channel);


        /* Actions on channels */
          static void pause();
          static void resume();
          static void halt();
          static void fadeOut(uint ms);

          static void pause(uint channel);
          static void resume(uint channel);
          static void halt(uint channel);
          static void fadeOut(uint ms, uint channel);


        /* Prevent the same sound to be played again for a certain time */
          static void setDoublingProtectionActive(bool is);
          static bool isDoublingProtectionActive();
          static void setDoublingProtectionTicks(const time_t &ticks);
          static const time_t &getDoublingProtctionTicks();


        /* Check channel state */
          static bool isPlaying();
          static bool isPaused();
          static bool isHalted();

          static bool isChannelPlaying(uint channel);
          static bool isChannelPaused(uint channel);
          static bool isChannelHalted(uint channel);


        /* Manage channel count */
          static uint getChannelCount();
          static void setChannelCount(uint count);


        /* Set volume */
          static void setVolume(double volume);
          static double getChannelVolume(uint channel);
          static void setChannelVolume(uint channel, double volume);


        /* Stop a sound in all channels */
          static bool haltSound(const Sound &sound);



      private:

        /* Data */
          static util::Timer timer;
          static bool doubling_protection;
          static time_t doubling_protection_ticks;
          static std::map<uint, std::pair<const Sound*, time_t> > channelmap;


        /* Internals */
          static void channel_finished(int channel);
          static bool DoublingProtection(const Sound &sound);
    };
  }

#endif // AUDIO_SOUNDPLAYER_HPP
