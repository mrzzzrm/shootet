#include "./__assert.hpp"

using namespace std;

namespace gfx
{
  void __assert_open(const char *file, uint line)
  {
    if(!SDL_WasInit(SDL_INIT_VIDEO) || SDL_GetVideoSurface() == NULL)
    {
      cerr << "Error: in '" << file << "' line '" << line << "'" << endl;
      cerr << "Video call before subsystem 'gfx' was opened via gfx::open(...) or ev2d::open(...). Terminating." << endl;
      abort();
    }
  }
}
