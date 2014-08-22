#ifndef ETC_BIT_H
#define ETC_BIT_H

template<typename F>
bool b_is(F flag, u8 bit)
{
  return flag & (1 << bit);
}

template<typename F>
void b_set(F &flag, u8 bit, u8 val)
{
  if(val)
    flag |= 1 << bit;
  else
    flag &= ~(1 << bit);
}

#endif
