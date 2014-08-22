#ifndef AUDIO_PLAYLIST_HPP
#define AUDIO_PLAYLIST_HPP

  #include <algorithm>

  #include "error/Exception.hpp"
  #include "util/etc.hpp"

  #include "./MusicPlayer.hpp"

  namespace audio
  {
    class Playlist
    {
      public:

        Playlist();
        Playlist(const Playlist &playlist);
        ~Playlist();


        void load(const Playlist &playlist);

        void clear();

        void shuffle();

        void update();
        void play(int track = 0);
        void halt();

        void setFadeInMs(uint fadein_ms);
        uint getFadeInMs() const;

        bool isPlaying() const;

        int getTrackCount() const;
        Track &getTrack(int index);
        const Track &getTrackConst(int index);
        void removeTrack(int index);
        void addTrack(const Track &track, int index = -1);

        Playlist &operator=(const Playlist &playlist);


      private:

        /* Data */
        bool playing;
        int current_track;
        uint fadein_ms;
        std::vector<Track*> tracks;


        /* Internals */
        void init();


    };
  }


#endif // AUDIO_PLAYLIST_HPP
