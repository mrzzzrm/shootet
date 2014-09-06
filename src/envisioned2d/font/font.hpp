#ifndef FONT_FONT_HPP
#define FONT_FONT_HPP

  #include <SDL/SDL_ttf.h>

  #include "error/Exception.hpp"

  #include "./ImageFont.hpp"
  #include "./TtfFont.hpp"
  #include "./TtfLabel.hpp"

  namespace font
  {
    void _open();
    void _close();
  }

#endif // FONT_FONT_HPP
