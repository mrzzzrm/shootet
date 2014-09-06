#ifndef GFX_GFX_HPP
#define GFX_GFX_HPP

  #include <cassert>
  #include <cstdlib>

  #include <SDL/SDL.h>
  #include <SDL/SDL_image.h>

  #include "etc/int.h"
  #include "error/Exception.hpp"

  #include "./Animation.hpp"
  #include "./ImageFading.hpp"
  #include "./ColorFading.hpp"
  #include "./Image.hpp"
  #include "./ImageClipping.hpp"
  #include "./__assert.hpp"


  namespace gfx
  {
    /* Open and close display */
      void _open(u32 w, u32 h, u32 bpp = 16, bool fullscreen = false, bool showcursor = false);
      void _close();


    /* Check display for being open */
      bool isOpen();


    /* Target FPS */
      void setTargetFps(int fps);


    /* Flip/update display */
      void updateScreen(bool clear = true);


    /* Screensize */
      geo::IntSize getScreenSize();

  }



#endif // GFX_GFX_HPP
