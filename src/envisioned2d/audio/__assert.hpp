#ifndef AUDIO___ASSERT_HPP_INCLUDED
#define AUDIO___ASSERT_HPP_INCLUDED

  #include <iostream>
  #include <SDL/SDL_mixer.h>
  #include "etc/int.h"


  namespace audio
  {
    void __assert_open(const char *file, uint line);
  }

  #define __audio__assert_open() audio:: __assert_open(__FILE__, __LINE__)


#endif // AUDIO___ASSERT_HPP_INCLUDED
