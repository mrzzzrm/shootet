#ifndef AUDIO_SOUND_HPP
#define AUDIO_SOUND_HPP

  #include <iostream>
  #include <list>
  #include <SDL/SDL_mixer.h>

  #include "util/util.hpp"
  #include "error/Exception.hpp"


  namespace audio
  {

    class Sound
    {
      friend class SoundPlayer;

      public:

        Sound();
        Sound(const util::Path &path);
        Sound(const Sound &sound);
        ~Sound();


        /* Load */
          void load(const util::Path &path);
          void load(const Sound &sound);


        /* Clear */
          void clear();


        /* Path */
          const util::Path &getPath() const;


        /* Volume */
          double getVolume() const;
          void setVolume(double volume);


        /* Play */
          uint play();
          void playInChannel(uint channel);



        /* Operators */
          Sound &operator=(const Sound &sound);
          bool operator==(const Sound &sound) const;


      private:

        /* Data */
          util::Path path;
          Mix_Chunk *sound;


        /* Internals */
          void init();

    };
  }


#endif // AUDIO_SOUND_HPP
