#include "./Properties.hpp"


using namespace std;

using namespace error;


namespace tmx
{
namespace base
{
  Properties::Properties()
  {

  }


  Properties::Properties(xml::Xml &xml)
  {
    load(xml);
  }

  Properties::Properties(const Properties &properties)
  {
    load(properties);
  }


  Properties::~Properties()
  {

  }


  void Properties::load(xml::Xml &xml)
  {
    clear();

    /* Read */
      if(xml.toSubBlock("property"))
      {
        for(uint currentproperty = 0; currentproperty > 0 ? xml.toNextBlock("property") : true; currentproperty++)
        {
          /* Read */
            if(xml.isString("name") && xml.isString("value"))
            {
              valuemap[xml.getString("name")] = xml.getString("value");
            }
            else
            {
              xml.toBaseBlock();

              throw Exception() << "Missing or wrong typed attribute";
            }

        }while(xml.toNextBlock("property"));

        /* Go back to base block */
          xml.toBaseBlock();
    }

  }


  void Properties::load(const Properties &properties)
  {
    if(&properties == this)
      return;

    clear();

    valuemap = properties.valuemap;
  }


  void Properties::clear()
  {
    valuemap.clear();
  }


  bool Properties::hasValue(const string &name) const
  {
    if(operator[](name) != NULL)
      return true;
    else
      return false;
  }


  const string &Properties::getValue(const string &name) const
  {
    if(hasValue(name))
      return *(operator[](name));
    else
      throw Exception() << "No such property '" << name << "'";
  }


  void Properties::addProperty(const std::string &name, const std::string &value)
  {
    valuemap[name] = value;
  }


  void Properties::removeProperty(const std::string &name)
  {
    valuemap.erase(name);
  }


  Properties &Properties::operator=(const Properties &properties)
  {
    load(properties);
    return *this;
  }


  const string *Properties::operator[](const string &name) const
  {
    map<string, string>::const_iterator i;

    if((i = valuemap.find(name)) != valuemap.end())
    {
      return &i->second;
    }
    else
    {
      return NULL;
    }
  }

}
}

