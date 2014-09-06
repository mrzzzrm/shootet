#ifndef UTIL_CONFIG_HPP
#define UTIL_CONFIG_HPP

  #include <map>
  #include <sstream>

  #include "util/Path.hpp"
  #include "error/Exception.hpp"


  #include "./std.hpp"
  #include "./string.hpp"

  namespace util
  {

    class Config
    {
      public:

        Config();
        Config(const Path &path);
        Config(const std::string &string);
        Config(const Config &config);
        ~Config();


        /* Load */
          void load(const Path &path);
          void load(const std::string &string);
          void load(const Config &config);


        /* Clear */
          void clear();


        /* Read */
          const std::string &getString(const std::string &name) const;
          int getInteger(const std::string &name) const;
          double getFloat(const std::string &name) const;


        /* Write */
          void setValue(const std::string &name, const std::string &value);
          void setValue(const std::string &name, int value);
          void setValue(const std::string &name, double value);


        /* Remove */
          void remove(const std::string &name);


        /* To String */
          std::string toString() const;


        /* Operators */
          Config &operator=(const Config &config);


      private:

        /* Data */
          std::map<std::string, std::string> valuemap;

    };
  }

#endif // UTIL_CONFIG_HPP
