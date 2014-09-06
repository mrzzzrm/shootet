#ifndef GFX___ASSERT_HPP_INCLUDED
#define GFX___ASSERT_HPP_INCLUDED

  #include <iostream>
  #include <SDL/SDL.h>
  #include "etc/int.h"


  namespace gfx
  {
    void __assert_open(const char *file, uint line);
  }

  #define __gfx__assert_open() gfx::__assert_open(__FILE__, __LINE__)

#endif // GFX___ASSERT_HPP_INCLUDED
