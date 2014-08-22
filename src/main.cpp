#include "framework.hpp"
#include <iostream>

#include "./Game.hpp"

// http://www.file-upload.net/delete-3525304/dn62m.html
// http://www.file-upload.net/delete-3536811/op6mx.html
// http://www.file-upload.net/delete-3541297/hbt6gd.html
// http://www.file-upload.net/delete-3547829/jmhhti.html
// http://www.file-upload.net/delete-3555912/69w5ht.html
// http://www.file-upload.net/delete-3566486/ttdgln.html
// http://www.file-upload.net/delete-3571672/g8bddw.html
// http://www.file-upload.net/delete-3572962/il9l29.html

using namespace error;
using namespace std;


void run()
{
  Game();
}


int main(int argc, char **argv)
{
  try
  {
    env2d::open(SCREEN_WIDTH, SCREEN_HEIGHT, 16, FULLSCREEN);
    run();
    env2d::close();
  }
  catch(Exception &exception)
  {
    cerr << "Error: " << exception.getDescription() << endl;
      return 1;
  }
  catch(...)
  {
    cerr << "Unknown error" << endl;
      return 1;
  }

  return 0;
}
