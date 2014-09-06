#include "./int.h"
#include <iostream>

using namespace std;

namespace etc
{
  uint integer_get_digitcount(int integer)
  {
    uint uinteger;
    uint digits = 0;

    if(integer < 0)
      uinteger = -integer;
    else
      uinteger = integer;


    for(digits = 1;;)
    {
      if((int)(uinteger/pow(10, digits)) == 0)
        break;
      else
        digits++;
    }

    if(integer < 0)
      digits++;

    return digits;
  }
}
