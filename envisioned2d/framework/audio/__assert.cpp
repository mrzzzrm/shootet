#include "./__assert.hpp"

using namespace std;

namespace audio
{
  void __assert_open(const char *file, uint line)
  {
    #if SDL_MIXER_MAJOR_VERSION >= 1 && SDL_MIXER_MINOR_VERSION >= 2 && SDL_MIXER_PATCHLEVEL >= 11
    if(!(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG))
    {
      cerr << "Error: in '" << file << "' line '" << line << "'" << endl;
      cerr << "Audio call before subsystem 'audio' was opened via audio::open(...) or ev2d::open(...). Terminating." << endl;
      abort();
    }
    #endif


  }
}
