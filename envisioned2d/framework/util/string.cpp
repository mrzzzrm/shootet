#include "./string.hpp"

using namespace std;

using namespace error;

namespace util
{

  bool string_is_integer(const string &string)
  {
    char *end;

    strtol(string.c_str(), &end, 10); // Declare to avoid warnings in *nix

    if(static_cast<u32>(end - string.c_str()) == string.size())
      return true;
    else
      return false;
  }


  bool string_is_float(const string &string)
  {
    char *end;

    strtod(string.c_str(), &end); // Declare to avoid warnings in *nix

    if(static_cast<u32>(end - string.c_str()) == string.size())
      return true;
    else
      return false;
  }

  int string_to_integer(const string &string)
  {
    char *end;
    int res;

    res = strtol(string.c_str(), &end, 10);

    if(static_cast<u32>(end - string.c_str()) == string.size())
      return res;
    else
      throw Exception() << "Couldn't convert '" << string << "' to integer";

  }


  double string_to_float(const string &string)
  {
    char *end;
    double res;

    res = strtod(string.c_str(), &end);

    if(static_cast<u32>(end - string.c_str()) == string.size())
      return res;
    else
      throw Exception() << "Couldn't convert '" << string << "' to float";
  }


  string integer_to_string(int integer)
  {
    stringstream ss;
      ss << integer;

    return ss.str();
  }


  string float_to_string(double _float)
  {
    stringstream ss;
      ss << _float;

    return ss.str();
  }


  string string_wrap_newlines(const string &string)
  {
    std::string res;

    res = string;

    for(uint p = 0; p < string.size();)
    {
      u32 cr = res.find( "\r", p);
      u32 crnl = res.find("\r\n", p);

      if(cr < crnl)
      {
        if(cr == string.npos)
          break;

        res.replace(cr, 1, "\n");
        p = cr + 1;
      }
      else
      {
        if(crnl == string.npos)
          break;

        res.replace(crnl, 2, "\n");
        p = crnl + 1;
      }

    }

    return res;
  }


  std::list<std::string> string_split_to_list(const std::string &string, const std::string seperator)
  {
    list<std::string> res;

    for(uint p = 0; p < string.size();)
    {
      u32 ep;

      ep = string.find(seperator, p);
      res.push_back(string.substr(p, ep - p));

      if(ep != string.npos)
        p = ep + seperator.size();
      else
        break;
    }

    return res;
  }


  std::vector<std::string> string_split_to_vector(const std::string &string, const std::string seperator)
  {
    vector<std::string> res;

    for(uint p = 0; p < string.size();)
    {
      u32 ep;

      ep = string.find(seperator, p);
      if(ep != p)
        res.push_back(string.substr(p, ep - p));

      if(ep != string.npos)
        p = ep + seperator.size();
      else
        break;
    }

    return res;
  }


  std::string char_to_string(char c)
  {
    string res;
    return res += c;
  }


  string operator+(const string &string, int integer)
  {
    std::string resstring;
    stringstream ss;
      ss << string << integer;
    resstring = ss.str();

    return resstring;
  }


  string &operator+=(string &string, int integer)
  {
    stringstream ss;
      ss << string << integer;
    string = ss.str();

    return string;
  }

}


