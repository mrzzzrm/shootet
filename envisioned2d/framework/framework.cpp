#include "./framework.hpp"


namespace env2d
{
  void open(int w, int h, int bpp, bool fullscreen, bool show_cursor)
  {
    gfx::_open(w, h, bpp, fullscreen, show_cursor);
    audio::_open();
    font::_open();
  }

  void close()
  {
    gfx::_close();
    audio::_close();
    font::_close();
  }
}

