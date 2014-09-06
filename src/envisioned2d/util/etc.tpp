#ifndef UTIL_ETC_TPP
#define UTIL_ETC_TPP

  namespace util
  {
    template<typename T>
    const T &abs_min(const T &t1, const T &t2)
    {
      if(fabs(t1) <= fabs(t2))
        return t1;
      else
        return t2;
    }


    template<typename T>
    const T &abs_max(const T &t1, const T &t2)
    {
      if(fabs(t1) >= fabs(t2))
        return t1;
      else
        return t2;
    }


    template<typename T>
    s8 sgn(const T &t)
    {
      if(t < 0)
        return -1;
      else if(t == 0)
        return 0;
      else
        return 1;
    }


    template<typename T>
    bool in_range(const T &value, const T &min, const T &max)
    {
      if(value >= min && value <= max)
        return true;
      else
        return false;
    }


    template<typename T>
    bool in_range(const T &value, const T &max)
    {
      if(value >= 0 && value <= max)
        return true;
      else
        return false;
    }


    template<typename T>
    T &limit(T &value, const T &min, const T &max)
    {
      if(min > max)
        return value;

      if(value < min)
        value = min;
      if(value > max)
        value = max;

      return value;
    }

    template<typename T>
    T &limit(T &value, const T &max)
    {
      if(0 > max)
        return value;

      if(value < 0)
        value = 0;
      if(value > max)
        value = max;

      return value;
    }
  }

#endif // UTIL_ETC_TPP
