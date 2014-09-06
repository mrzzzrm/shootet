#ifndef UTIL_STRING_HPP_INCLUDED
#define UTIL_STRING_HPP_INCLUDED

  #include <list>
  #include <vector>
  #include <sstream>
  #include <string>
  #include <cstdlib>
  #include <iostream>

  #include "etc/int.h"
  #include "error/Exception.hpp"

  namespace util
  {
    bool string_is_integer(const std::string &string);
    bool string_is_float(const std::string &string);

    int string_to_integer(const std::string &string);
    double string_to_float(const std::string &string);

    std::string integer_to_string(int integer);
    std::string float_to_string(double _float);

    std::string string_wrap_newlines(const std::string &string);

    std::list<std::string> string_split_to_list(const std::string &string, const std::string seperator);
    std::vector<std::string> string_split_to_vector(const std::string &string, const std::string seperator);

    std::string char_to_string(char c);

    std::string operator+(const std::string &string, int integer);
    std::string &operator+=(std::string &string, int integer);
  }


#endif // UTIL_STRING_HPP_INCLUDED
