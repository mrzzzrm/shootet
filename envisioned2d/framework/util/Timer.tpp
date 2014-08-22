#ifndef UTIL_TIMER_TPP
#define UTIL_TIMER_TPP

  
  namespace util
  {
    template<typename T>
    T Timer::getPerSecond(const T &val) const
    {
      return (val * period)/1000;
    }
  }

#endif // TIMER_HPP
