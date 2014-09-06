#include "./MusicPlayer.hpp"


using namespace std;
using namespace error;
using namespace util;


namespace audio
{
/*
  Class MusicPlayer
*/
  bool MusicPlayer::is_playing = false;
  bool MusicPlayer::is_paused = false;

  const Track *MusicPlayer::track = NULL;


  void MusicPlayer::play(const Track *track, uint fadein_ms)
  {
    __audio__assert_open();

    /* Stop/FadeOut old track */
      if(!isHalted())
        halt();


    /* Play new track */
      if(track != NULL && track->track != NULL)
      {
        if(Mix_FadeInMusic(track->track, 1, fadein_ms) == -1)
          throw Exception() << "Cannot play track '" << track->getPath() << "': " << Mix_GetError();

        /* Set state */
          is_playing = true;
          is_paused = false;
      }
      else
      {
        is_playing = false;
        is_paused = false;
      }


    /* Set track */
      MusicPlayer::track = track;


    /* Set the music finished hook */
      Mix_HookMusicFinished(music_finished);
  }


  void MusicPlayer::pause()
  {
    if(is_playing)
    {
      Mix_PauseMusic();

      is_playing = false;
      is_paused = true;
    }
  }


  void MusicPlayer::resume()
  {
    if(is_paused)
    {
      Mix_ResumeMusic();

      is_playing = true;
      is_paused = false;
    }
  }


  void MusicPlayer::halt()
  {
    if(is_playing || is_paused)
    {
      Mix_HaltMusic();

      /* music_finished should be called according to SDL_mixer doc, but obviously isn't */
        music_finished();
    }
  }


  void MusicPlayer::rewind()
  {
    if(is_playing || is_paused)
    {
      if(is_paused)
        resume();

      Mix_RewindMusic();

      is_playing = true;
      is_paused = false;
    }
  }

  void MusicPlayer::fadeOut(uint ms)
  {
    if(is_playing || is_paused)
    {
      Mix_FadeOutMusic(ms);
    }
  }


  bool MusicPlayer::isPlaying()
  {
    return is_playing;
  }


  bool MusicPlayer::isPaused()
  {
    return is_paused;
  }


  bool MusicPlayer::isHalted()
  {
    return !is_playing && !is_paused;
  }


  double MusicPlayer::getVolume()
  {
    return ((double)Mix_VolumeMusic(-1))/MIX_MAX_VOLUME;
  }


  void MusicPlayer::setVolume(double volume)
  {
    if(!in_range(volume, 1.0))
      cerr << "Overrunning music volume range 0...1 with value '" << volume << "'" << endl;

    limit(volume, 1.0);

    Mix_VolumeMusic((int)(volume * MIX_MAX_VOLUME));
  }

  const Track *MusicPlayer::getCurrentTrack()
  {
    return track;
  }


  void MusicPlayer::music_finished()
  {
    is_playing = false;
    is_paused = false;

    track = NULL;
  }


}

