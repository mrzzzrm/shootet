#ifndef AUDIO_AUDIO_HPP
#define AUDIO_AUDIO_HPP

  #include <SDL/SDL.h>

  #include "error/Exception.hpp"

  #include "./Track.hpp"
  #include "./MusicPlayer.hpp"
  #include "./Sound.hpp"
  #include "./SoundPlayer.hpp"
  #include "./Playlist.hpp"


  namespace audio
  {
    void _open();
    void _close();
  };

#endif
