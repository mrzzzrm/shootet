#include "./Playlist.hpp"

using namespace std;
using namespace util;
using namespace error;

namespace audio
{
  Playlist::Playlist()
  {
    init();
  }

  Playlist::Playlist(const Playlist &playlist)
  {
    if(this == &playlist)
      return;

    init();
    load(playlist);
  }

  Playlist::~Playlist()
  {
    vector_delete_all_and_clear(tracks);
  }

  void Playlist::load(const Playlist &playlist)
  {
    if(this == &playlist)
      return;

    current_track = playlist.current_track;
    fadein_ms = playlist.fadein_ms;
    tracks = playlist.tracks;
  }

  void Playlist::clear()
  {
    vector_delete_all_and_clear(tracks);
    init();
  }

  void Playlist::shuffle()
  {
    random_shuffle(tracks.begin(), tracks.end());
  }

  void Playlist::update()
  {
    if(tracks.size() == 0)
    {
      playing = false;
      return;
    }

    if(!MusicPlayer::isPlaying() && playing)
    {
      ++current_track %= tracks.size();
      MusicPlayer::play(tracks[current_track], fadein_ms);
    }
  }

  void Playlist::play(int index)
  {
    if(tracks.size() == 0)
    {
      playing = false;
      return;
    }

    if(index < 0)
      index = tracks.size() + index + 1;

    if(!in_range(index, (int)tracks.size()))
      throw Exception() << "No such track with index '" << index << "'";


    current_track = index;
    MusicPlayer::play(tracks[current_track], fadein_ms);
    playing = true;
  }

  void Playlist::halt()
  {
    if(!playing)
      return;

    MusicPlayer::halt();
    playing = false;
  }

  void Playlist::setFadeInMs(uint fadein_ms)
  {
    this->fadein_ms = fadein_ms;
  }

  uint Playlist::getFadeInMs() const
  {
    return fadein_ms;
  }

  bool Playlist::isPlaying() const
  {
    return playing;
  }

  int Playlist::getTrackCount() const
  {
    return tracks.size();
  }

  Track &Playlist::getTrack(int index)
  {
    if(!in_range(index, (int)tracks.size() - 1))
      throw Exception() << "No such track with index '" << index << "'";

    return *tracks[index];
  }

  const Track &Playlist::getTrackConst(int index)
  {
    if(!in_range(index, (int)tracks.size() - 1))
      throw Exception() << "No such track with index '" << index << "'";

    return *tracks[index];
  }

  void Playlist::removeTrack(int index)
  {
    if(!in_range(index, (int)tracks.size() - 1))
      throw Exception() << "No such track with index '" << index << "'";

    delete *(tracks.begin() + index);
    tracks.erase(tracks.begin() + index);
  }

  void Playlist::addTrack(const Track &track, int index)
  {
    if(index < 0)
      index = tracks.size() + index + 1;

    if(!in_range(index, (int)tracks.size()))
      throw Exception() << "No such track with index '" << index << "'";


    if(index == (int)tracks.size())
      tracks.push_back(new Track(track));
    else
      tracks.insert(tracks.begin() + index, new Track(track));
  }


  Playlist &Playlist::operator=(const Playlist &playlist)
  {
    load(playlist);
    return *this;
  }

  void Playlist::init()
  {
    playing = false;
    current_track = -1;
    fadein_ms = 0;
  }
}
