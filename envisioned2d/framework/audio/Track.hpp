#ifndef AUDIO_TRACK_HPP_INCLUDED
#define AUDIO_TRACK_HPP_INCLUDED


  #include <iostream>
  #include <string>
  #include <SDL/SDL_mixer.h>


  #include "util/util.hpp"
  #include "error/Exception.hpp"

  namespace audio
  {

    class Track
    {
      friend class MusicPlayer;

      public:

        Track();
        Track(const util::Path &path);
        Track(const Track &track);
        ~Track();


        /* Load */
          void load(const util::Path &path);
          void load(const Track &track);


        /* Clear */
          void clear();


        /* Get the path */
          const util::Path &getPath() const;


        /* Operators */
          Track &operator=(const Track &track);


      private:

        /* Data */
          util::Path path;
          Mix_Music *track;

    };
  }


#endif // AUDIO_TRACK_HPP_INCLUDED
