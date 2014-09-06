#include "gfx.hpp"

using namespace std;
using namespace error;
using namespace geo;




static const int DEFAULT_FPS = 60;
static int target_fps = DEFAULT_FPS;


namespace gfx
{
  void _open(u32 w, u32 h, u32 bpp, bool fullscreen, bool showcursor)
  {
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
      throw Exception() << "Error whilst initialising SDL: " << SDL_GetError();

    if(SDL_SetVideoMode(w, h, bpp, (fullscreen ? SDL_FULLSCREEN : 0)) == NULL)
      throw Exception() << "Error whilst setting video mode to " << w << "x" << h << "x" << bpp << " " << (fullscreen ? "fullscreen" : "windowed") << " : " << SDL_GetError();


    SDL_ShowCursor(showcursor);

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
      throw Exception() << "Failed to init SDL_image: '" << SDL_GetError() << "'";
  }


  void _close()
  {
    __gfx__assert_open();

    SDL_Quit();
    IMG_Quit();
  }


  bool isOpen()
  {
    return SDL_WasInit(SDL_INIT_VIDEO) && SDL_GetVideoSurface() != NULL;
  }


  void setTargetFps(int fps)
  {
    target_fps = fps;
  }


  void updateScreen(bool clear)
  {
    __gfx__assert_open();

    static u32 last_flip = 0;

    SDL_Flip(SDL_GetVideoSurface());

    if(clear)
      SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);

    if(target_fps > 0)
    {
      u32 ft = SDL_GetTicks() - last_flip;
      u32 tft = 1000/target_fps;

      if(ft < tft)
      {
        SDL_Delay(tft - ft);
      }
    }

    last_flip = SDL_GetTicks();
  }


  IntSize getScreenSize()
  {
    __gfx__assert_open();

    SDL_Surface *screen;

    screen = SDL_GetVideoSurface();

    if(screen != NULL)
      return IntSize(screen->w, screen->h);
    else
      return IntSize(0, 0);
  }



}

