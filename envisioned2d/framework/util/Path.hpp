#ifndef UTIL_PATH_HPP
#define UTIL_PATH_HPP

  #include <string>
  #include <fstream>
  #include <cstdio>
  #include <string.h>
  #include <errno.h>

  #include "error/Exception.hpp"

  namespace util
  {

    class Path: public std::string
    {
      public:

        Path();
        Path(const std::string &str);
        Path(const char *cstr);
        Path(const Path &path);
        ~Path();


        /* Load */
          void load(const std::string &str);
          void load(const char *cstr);
          void load(const Path &path);


        /* Clear */
          void clear();


        /* Append */
          Path &append(const std::string &str);
          Path appendConst(const std::string &str) const;


        /* Directory */
          Path getDirectory() const;
          Path &stripFile();


        /* File operations */
          bool exists() const;
          bool remove();


        /* operators */
          Path &operator=(const Path &path);


      private:


    };
  }

#endif // UTIL_PATH_HPP
