#include "framework.hpp"
#include <iostream>

#include "./Game.hpp"


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
