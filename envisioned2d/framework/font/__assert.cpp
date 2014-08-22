#include "./__assert.hpp"

using namespace std;

namespace font
{
  void __assert_open(const char *file, uint line)
  {
    if(!TTF_WasInit())
    {
      cerr << "Error: in '" << file << "' line '" << line << "'" << endl;
      cerr << "Font call before subsystem 'font' was opened via font::open(...) or ev2d::open(...). Terminating." << endl;
      abort();
    }
  }
}
