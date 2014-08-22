#include "./Config.hpp"

using namespace std;
using namespace error;
using namespace util;


namespace util
{

  Config::Config()
  {

  }


  Config::Config(const Path &path)
  {
    load(path);
  }


  Config::Config(const std::string &string)
  {
    load(string);
  }


  Config::Config(const Config &config)
  {
    load(config);
  }


  Config::~Config()
  {
    clear();
  }


  void Config::load(const Path &path)
  {
    load(file_to_string(path));
  }


  void Config::load(const std::string &string)
  {
    u32 l;
    list<std::string> lines;


    lines = string_split_to_list(string_wrap_newlines(string), "\n");

    l = 0;
    for(list<std::string>::iterator i = lines.begin(); i != lines.end(); i++, l++)
    {
      bool fc;
      vector<std::string> elements;
      std::string strip;
      std::string name;
      std::string value;

      /* Skip empty lines */
      strip = i->substr(0, i->find("#", 0));
      fc = false;
      for(uint p = 0; p < strip.size(); p++)
      {
        if(!isspace(strip[p]))
        {
          fc = true;
          break;
        }
      }

      if(!fc)
        continue;


      /* Read */
      elements = string_split_to_vector(strip, "=");

      if(elements.size() != 2)
        throw Exception() << "Error in line '" << l << "'('" << *i << "'): Illegal or missing '='";


      /* Verify elements */
      for(uint e = 0; e < 2; e++)
      {
        fc = false;
        for(uint p = 0; p < elements[e].size(); p++)
        {
          if(!isspace(strip[p]))
          {
            fc = true;
            break;
          }
        }
        if(!fc)
          throw Exception() << "Error in line '" << l << "'('" << *i << "'): Illegal or missing name/value '" << elements[e] << "'";
      }


      /* Strip name */
      for(uint p = 0; p < elements[0].size(); p++)
      {
        if(isspace(elements[0][p]))
        {
          if(name.size() == 0)
            continue;
          else
            break;
        }
        else
        {
          name += elements[0][p];
        }
      }


      /* Value */
        for(uint p = 0; p < elements[1].size(); p++)
        {
          u32 _p;

          if(isspace(elements[0][p]))
            continue;

          for(_p = elements[1].size() - 1; _p > p; _p--)
          {
            if(!isspace(elements[1][_p]))
              break;
          }
          value += elements[1].substr(p, _p - p + 1);
          break;
        }


      /* Add to valuemap */
        valuemap[name] = value;

    }
  }


  void Config::load(const Config &config)
  {
    if(&config == this)
      return;

    valuemap = config.valuemap;
  }


  void Config::clear()
  {
    valuemap.clear();
  }


  const std::string &Config::getString(const std::string &name) const
  {
    map<string, string>::const_iterator i;

    i = valuemap.find(name);

    if(i != valuemap.end())
      return i->second;
    else
      throw Exception() << "No such entry '" << name << "'";
  }


  int Config::getInteger(const std::string &name) const
  {
    try
    {
      return string_to_integer(getString(name));
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst reading integer '" << name << "': " << exception.getDescription();
    }
  }


  double Config::getFloat(const std::string &name) const
  {
    try
    {
      return string_to_float(getString(name));
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst reading float '" << name << "': " << exception.getDescription();
    }
  }

  void Config::setValue(const std::string &name, const std::string &value)
  {
    valuemap[name] = value;
  }


  void Config::setValue(const std::string &name, int value)
  {
    valuemap[name] = integer_to_string(value);
  }


  void Config::setValue(const std::string &name, double value)
  {
    valuemap[name] = float_to_string(value);
  }


  void Config::remove(const std::string &name)
  {
    map<string, string>::iterator i;

    i = valuemap.find(name);

    if(i != valuemap.end())
      valuemap.erase(i);
  }


  std::string Config::toString() const
  {
    stringstream res;

    for(map<string, string>::const_iterator i = valuemap.begin(); i != valuemap.end(); i++)
    {
      res << i->first << "=" << i->second << "\n";
    }

    return res.str();
  }


  Config &Config::operator=(const Config &config)
  {
    load(config);
    return *this;
  }


}
