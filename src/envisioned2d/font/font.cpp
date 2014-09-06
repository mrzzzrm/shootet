#include "./font.hpp"

using namespace error;

namespace font
{
  void _open()
  {
    if(TTF_WasInit())
      return;

    if(TTF_Init() == -1)
      throw Exception() << "Could initialise SDL_ttf: '" << SDL_GetError() << "'";
  }


  void _close()
  {
    TTF_Quit();
  }
}
