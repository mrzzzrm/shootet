#ifndef NEWTMX_BASE_PROPERTIES_HPP
#define NEWTMX_BASE_PROPERTIES_HPP

  #include <map>
  #include <string>


  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"


  namespace tmx
  {
  namespace base
  {

    class Properties
    {
      public:

        Properties();
        Properties(xml::Xml &xml);
        Properties(const Properties &properties);
        ~Properties();


        /* Load properties from xml - block */
          void load(xml::Xml &xml);
          void load(const Properties &properties);


        /* Clear */
          void clear();


        /* Get value of a property */
          bool hasValue(const std::string &name) const;
          const std::string &getValue(const std::string &name) const;


        /* Add/Remove properties */
          void addProperty(const std::string &name, const std::string &value);
          void removeProperty(const std::string &name);


        /* Operators */
          Properties &operator=(const Properties &properties);
          const std::string *operator[](const std::string &name) const;



      private:

        /* Data */
          std::map<std::string, std::string> valuemap;
    };

  }
  }


#endif // TMX_PROPERTIES_HPP
