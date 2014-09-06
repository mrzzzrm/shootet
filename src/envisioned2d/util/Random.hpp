#ifndef UTIL_RANDOM_HPP_INCLUDED
#define UTIL_RANDOM_HPP_INCLUDED

  #include <cmath>
  #include <cstdlib>

  #include "etc/int.h"
  #include "error/Exception.hpp"

  namespace util
  {
    template<typename T>
    class Random
    {
      template<typename T2> friend class Random;

      public:

        Random();
        Random(T max);
        Random(T min, T max);
        Random(const Random &random);
        ~Random();


        /* Load */
          void load(T max);
          void load(T min, T max);
          void load(const Random &random);


        /* Clear */
          void clear();


        /* Range */
          T getMin() const;
          T getMax() const;
          void setMin(T min);
          void setMax(T max);
          void setRange(T min, T max);


        /* Value */
          T getValue() const;
          T getNewValue() const;
          T genNewValue();


        /* Operators */
          Random &operator=(const Random &random);
          operator T();
          template<typename T2> operator Random<T2>();


      private:

        /* Data */
          T min, max;
          T value;


        /* Internals */
          void init();
    };

    typedef Random<int> IntRandom;
    typedef Random<double> FloatRandom;
  }

  #include "./Random.tpp"

#endif // UTIL_RANDOM_HPP_INCLUDED
