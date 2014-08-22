#ifndef AUDIO_MUSICPLAYER_HPP
#define AUDIO_MUSICPLAYER_HPP

  #include <string>
  #include <list>
  #include <SDL/SDL_mixer.h>

  #include "etc/int.h"
  #include "util/util.hpp"
  #include "error/Exception.hpp"

  #include "./Track.hpp"
  #include "./__assert.hpp"



  namespace audio
  {

    class MusicPlayer
    {
      friend void audio::open();

      public:

        /* Play a track */
          static void play(const Track *track, uint fadein_ms = 0);


        /* Various operations on the playng track */
          static void pause();
          static void resume();
          static void halt();
          static void rewind();
          static void fadeOut(uint ms);


        /* Check the state of the track */
          static bool isPlaying();
          static bool isPaused();
          static bool isHalted();


        /* Manage the software volume */
          static double getVolume();
          static void setVolume(double volume);




        /* Return the current track */
          static const Track *getCurrentTrack();


      private:

        /* Data */
          static bool is_playing;
          static bool is_paused;

          static const Track *track;


        /* Internals */
          static void music_finished();



    };
  }

#endif // AUDIO_MUSICPLAYER_HPP
