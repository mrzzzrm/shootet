#include "./audio.hpp"

using namespace std;
using namespace error;




namespace audio
{
  void _open()
  {
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    #if (SDL_MIXER_MAJOR_VERSION == 1 && SDL_MIXER_MINOR_VERSION == 2 && SDL_MIXER_PATCHLEVEL >= 11) || \
        (SDL_MIXER_MAJOR_VERSION == 1 && SDL_MIXER_MINOR_VERSION > 2) || \
        (SDL_MIXER_MAJOR_VERSION > 1)
    if(!(Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD) & (MIX_INIT_OGG | MIX_INIT_MOD)))
    {
      throw Exception() << "Error whilst initialising SDL_mixer: '" << Mix_GetError() << "'";
    }
    #endif
    if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 1024) < 0)
    {
      throw Exception() << "Error whilst opening SDL_mixer: '" << Mix_GetError() << "'";
    }

    Mix_AllocateChannels(16);
  }


  void _close()
  {
    Mix_CloseAudio();
  }
}
