#ifndef INT_H
#define INT_H

  #include <stdint.h>
  #include <math.h>

  typedef uint64_t u64;
  typedef uint32_t u32;
  typedef uint16_t u16;
  typedef uint8_t u8;

  typedef int64_t s64;
  typedef int32_t s32;
  typedef int16_t s16;
  typedef int8_t s8;

  typedef unsigned int uint;

  namespace etc
  {
    uint integer_get_digitcount(int integer);
  }

#endif // TYPES_H
