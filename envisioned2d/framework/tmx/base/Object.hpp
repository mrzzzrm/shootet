#ifndef NEWTMX_BASE_OBJECT_HPP
#define NEWTMX_BASE_OBJECT_HPP


  #include <map>
  #include <vector>
  #include <string>


  #include "etc/int.h"
  #include "geo/Rect.hpp"
  #include "xml/Xml.hpp"
  #include "error/Exception.hpp"

  #include "./Properties.hpp"


  namespace tmx
  {
  namespace base
  {
    class Objectgroup;

    class Object: public geo::IntRect
    {
      friend class Objectgroup;

      public:

        Object(const Objectgroup &objectgroup);
        Object(xml::Xml &xml, const Objectgroup &objectgroup);
        ~Object();


        /* Load */
          void load(xml::Xml &xml);


        /* Get attributes */
          const std::string &getName() const;
          const std::string &getType() const;


        /* Get properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get parent objectgroup */
          const Objectgroup &getObjectgroup() const;


        /* Set attributes */
          void setName(const std::string &name);
          void setType(const std::string &type);



      private:

        /* Data */
          /* Attributes */
            std::string name;
            std::string type;


          /* Properties */
            Properties properties;


          /* Parent objectgroup */
            const Objectgroup &objectgroup;


        /* Internal */
          void clear();



        /* Disabled functionality */
          Object();
          Object &operator=(const Object &object);


        /* Access only for manager - class */
          Object(const Object &object);

    };

  }
  }


#endif
