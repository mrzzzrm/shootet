#ifndef FONT___ASSERT_HPP_INCLUDED
#define FONT___ASSERT_HPP_INCLUDED


  #include <iostream>
  #include <SDL/SDL_ttf.h>
  #include "etc/int.h"


  namespace font
  {
    void __assert_open(const char *file, uint line);
  }

  #define __font__assert_open() font:: __assert_open(__FILE__, __LINE__)

#endif // FONT___ASSERT_HPP_INCLUDED
