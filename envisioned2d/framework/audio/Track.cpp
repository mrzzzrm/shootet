#include "./Track.hpp"
#include "./MusicPlayer.hpp"

using namespace std;

using namespace error;
using namespace util;




namespace audio
{

  Track::Track()
  {
    track = NULL;
  }


  Track::Track(const Path &path)
  {
    track = NULL;

    load(path);
  }

  Track::Track(const Track &track)
  {
    if(&track == this)
      return;

    this->track = NULL;

    load(track);
  }


  Track::~Track()
  {
    if(this == MusicPlayer::getCurrentTrack())
      cout << "<Warning>: audio::Track " << path << " was deleted while still playing" << endl;

    if(track != NULL)
      Mix_FreeMusic(track);
  }


  void Track::load(const Path &path)
  {
    __audio__assert_open();

    clear();

    /* Free old data */
      if(track != NULL)
        Mix_FreeMusic(track);


    /* Load new */
      if((track = Mix_LoadMUS(path.c_str())) == NULL)
        throw Exception() << "Couldn't open track '" << track << "': " << Mix_GetError();


    /* Set path */
      this->path = path;
  }


  void Track::load(const Track &track)
  {
    __audio__assert_open();

    clear();

    /* Free old data */
      if(this->track != NULL)
        Mix_FreeMusic(this->track);

      path.clear();


    /* Load */
      if(track.track != NULL)
      {
        if((this->track = Mix_LoadMUS(track.getPath().c_str())) == NULL)
          throw Exception() << "Couldn't open track '" << track.getPath() << "': " << Mix_GetError();

        /* Set path */
          this->path = path;
      }
      else
      {
        this->track = NULL;
      }


  }


  void Track::clear()
  {
    if(track != NULL)
      Mix_FreeMusic(track);

    track = NULL;

    path.clear();
  }


  const Path &Track::getPath() const
  {
    return path;
  }


  Track &Track::operator=(const Track &track)
  {
    load(track);
    return *this;
  }

}




