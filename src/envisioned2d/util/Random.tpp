#ifndef UTIL_RANDOM_TPP
#define UTIL_RANDOM_TPP

  namespace util
  {
    template<typename T>
    Random<T>::Random()
    {
      init();
    }


    template<typename T>
    Random<T>::Random(T max)
    {
      init();
      load(max);
    }


    template<typename T>
    Random<T>::Random(T min, T max)
    {
      init();
      load(min, max);
    }


    template<typename T>
    Random<T>::Random(const Random &random)
    {
      init();
      load(random);
    }


    template<typename T>
    Random<T>::~Random()
    {

    }


    template<typename T>
    void Random<T>::load(T max)
    {
      this->min = 0;
      this->max = max;
      genNewValue();
    }


    template<typename T>
    void Random<T>::load(T min, T max)
    {
      if(min > max)
        throw error::Exception() << "min(' "<< min <<" ') is forced to be <= than max(' "<< max <<" ')";

      this->min = min;
      this->max = max;
      genNewValue();
    }


    template<typename T>
    void Random<T>::load(const Random &random)
    {
      if(&random == this)
        return;

      min = random.min;
      max = random.max;
      value = random.value;
    }


    template<typename T>
    void Random<T>::clear()
    {
      init();
    }


    template<typename T>
    T Random<T>::getMin() const
    {
      return min;
    }


    template<typename T>
    T Random<T>::getMax() const
    {
      return max;
    }


    template<typename T>
    void Random<T>::setMin(T min)
    {
      if(min > max)
        throw error::Exception() << "min(' "<< min <<" ') has to be <= than max(' "<< max <<" ')";
      else
        this->min = min;

      genNewValue();
    }


    template<typename T>
    void Random<T>::setMax(T max)
    {
      if(min > max)
        throw error::Exception() << "max(' "<< max <<" ') has to be >= than min(' "<< min <<" ')";
      else
        this->min = min;

      genNewValue();
    }


    template<typename T>
    void Random<T>::setRange(T min, T max)
    {
      if(min > max)
        throw error::Exception() << "max(' "<< max <<" ') has to be >= than min(' "<< min <<" ')";

      this->min = min;
      this->max = max;

      genNewValue();
    }


    template<typename T>
    T Random<T>::getValue() const
    {
      return value;
    }


    template<typename T>
    T Random<T>::getNewValue() const
    {
      if(max == min)
        return min;
      else
        return (T)(min + ((double)rand() / (double)RAND_MAX) * (max - min));
    }


    template<typename T>
    T Random<T>::genNewValue()
    {
      return value = getNewValue();
    }


    template<typename T>
    Random<T> &Random<T>::operator=(const Random &random)
    {
      load(random);
      return *this;
    }


    template<typename T>
    Random<T>::operator T()
    {
      return value;
    }


    template<typename T1>
    template<typename T2>
    Random<T1>::operator Random<T2>()
    {
      Random<T2> resrandom;

      resrandom.min = (T2)min;
      resrandom.max = (T2)max;
      resrandom.value = (T2)value;

      return resrandom;
    }

    template<typename T>
    void Random<T>::init()
    {
      min = 0;
      max = 0;
      value = 0;
    }




  }

#endif // UTIL_RANDOM_TPP
