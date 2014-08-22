#include "./__assert.hpp"

using namespace std;

namespace input
{
  void __assert_open(const char *file, uint line)
  {
    if(!SDL_WasInit(SDL_INIT_VIDEO) || SDL_GetVideoSurface() == NULL)
    {
      cerr << "Error: in '" << file << "' line '" << line << "'" << endl;
      cerr << "Input call before subsystem 'input' was opened via gfx::open(...) or ev2d::open(...). Terminating." << endl;
      abort();
    }
  }
}
