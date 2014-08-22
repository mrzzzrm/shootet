#ifndef EXCEPTION_EXCEPTION_TPP
#define EXCEPTION_EXCEPTION_TPP

  template<typename TArg>
  error::Exception &error::Exception::operator<<(const TArg &arg)
  {
    description << arg;
    return *this;
  }


#endif // EXCEPTION_EXCEPTION_TPP
