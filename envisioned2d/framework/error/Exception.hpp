#ifndef EXCEPTION_EXCEPTION_HPP
#define EXCEPTION_EXCEPTION_HPP


  #include <string>
  #include <sstream>


  namespace error
  {
    class Exception
    {
      public:

        Exception();
        Exception(const Exception &exception);
        ~Exception();

        /* Get - Interface */
          const std::string getDescription() const;


        /* Operators */
          Exception &operator=(const Exception &exception);

          /* Add descriptional elements */
            template<typename TArg> Exception &operator<<(const TArg &arg);


      private:

        /* Data */
          std::stringstream description;

    };
  }


  /* Include templates */
    #include "./Exception.tpp"

#endif
