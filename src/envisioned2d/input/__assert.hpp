#ifndef INPUT___ASSERT_HPP_INCLUDED
#define INPUT___ASSERT_HPP_INCLUDED

  #include <iostream>
  #include <SDL/SDL.h>
  #include "etc/int.h"


  namespace input
  {
    void __assert_open(const char *file, uint line);
  }

  #define __input__assert_open() input::__assert_open(__FILE__, __LINE__)

#endif // INPUT___ASSERT_HPP_INCLUDED
