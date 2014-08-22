#ifndef NEWTMX_BASE_OBJECTGROUP_HPP
#define NEWTMX_BASE_OBJECTGROUP_HPP

  #include <map>
  #include <vector>
  #include <string>

  #include "etc/int.h"
  #include "xml/Xml.hpp"
  #include "util/util.hpp"
  #include "error/Exception.hpp"


  #include "./Layer.hpp"
  #include "./Object.hpp"
  #include "./Properties.hpp"


  namespace tmx
  {
  namespace base
  {
    class Map;

    class Objectgroup: public Layer
    {
      friend class Map;

      public:

        Objectgroup(const Map &map);
        Objectgroup(xml::Xml &xml, const Map &map);
        ~Objectgroup();


        /* Load */
          void load(xml::Xml &xml);



        /* Get attributes */
          const std::string &getName() const;
          int getWidth() const;
          int getHeight() const;


        /* Get elementcount */
          int getObjectCount() const;


        /* Get elements */
          Object &getObject(int index) const;


        /* Get properties */
          Properties &getProperties();
          const Properties &getPropertiesConst() const;


        /* Get parent map */
          const Map &getMap() const;


        /* Set attributes */
          void setName(const std::string &name);

        /* Add/Remove elements */
          Object *addObject(int index);
          void removeObject(int index);
          void removeObject(const Object *object);




      private:

        /* Data */
          /* Attributes */
            std::string name;
            int width;
            int height;


          /* Properties */
            Properties properties;


          /* Parent map */
            const Map &map;


          /* Elements */
            std::vector<Object*> objectvector;



        /* Internal */
          void clear();


        /* Internal methods - Attention! Not memory save!!! */
          void init();

        /* Disabled functionality */
          Objectgroup();
          Objectgroup &operator=(const Objectgroup &objectgroup);


        /* Access only for manager - class map */
          Objectgroup(const Objectgroup &objectgroup);
          void setWidth(int width);
          void setHeight(int height);

      };


  }
  }


#endif // TMX_OBJECTGROUP_HPP
