#include "Objectgroup.hpp"


using namespace std;

using namespace error;
using namespace util;


namespace tmx
{
namespace base
{
  Objectgroup::Objectgroup(const Map &map):
    Layer(LAYER_OBJECTGROUP),
    map(map)
  {
    init();
  }


  Objectgroup::Objectgroup(xml::Xml &xml, const Map &map):
    Layer(LAYER_OBJECTGROUP),
    map(map)
  {
    init();
    load(xml);
  }


  Objectgroup::~Objectgroup()
  {
    clear();
  }


  void Objectgroup::load(xml::Xml &xml)
  {
    clear();


    /* Attributes */
      if(xml.isString("name") && xml.isInteger("width") && xml.isInteger("height"))
      {
        name = xml.getString("name");
        width = xml.getInteger("width");
        height = xml.getInteger("height");
      }
      else
      {
        throw Exception() << "Missing or wrong type attribute";
      }


    /* Objects */
      if(xml.toSubBlock("object"))
      {
        /* Iterate */
          for(uint currentobject = 0; currentobject > 0 ? xml.toNextBlock("object") : true; currentobject++)
          {
            Object *object;

            try
            {
              object = new Object(xml, *this);
            }
            catch(Exception &exception)
            {
              xml.toBaseBlock();
              throw Exception() << "Error whilst loading object " << currentobject << ": " << exception.getDescription();
            }

            objectvector.push_back(object);

          }while(xml.toNextBlock("object"));

         xml.toBaseBlock();
      }


    /* Properties */
      if(xml.toSubBlock("properties"))
      {
        /* Read properties */
          try
          {
            properties.load(xml);
          }
          catch(Exception &exception)
          {
            xml.toBaseBlock();
            throw Exception() << "Error whilst loading properties: " << exception.getDescription();
          }

          xml.toBaseBlock();
      }
  }


  void Objectgroup::clear()
  {
    for(int o = 0; o < (int)objectvector.size(); o++)
    {
      delete objectvector[o];
    }
    objectvector.clear();

    properties.clear();
    name.clear();

    init();
  }


  const string &Objectgroup::getName() const
  {
    return name;
  }


  int Objectgroup::getWidth() const
  {
    return width;
  }


  int Objectgroup::getHeight() const
  {
    return height;
  }


  int Objectgroup::getObjectCount() const
  {
    return objectvector.size();
  }


  Object &Objectgroup::getObject(int index) const
  {
    if(!in_range(index, (int)objectvector.size() - 1))
      throw Exception() << "No such object with index '" << index << "', vectorsize is '" << objectvector.size() << "'";

    return *(objectvector[index]);
  }


  Properties &Objectgroup::getProperties()
  {
    return properties;
  }


  const Properties &Objectgroup::getPropertiesConst() const
  {
    return properties;
  }


  const Map &Objectgroup::getMap() const
  {
    return map;
  }


  void Objectgroup::setName(const std::string &name)
  {
    this->name = name;
  }


  Object *Objectgroup::addObject(int index)
  {
    Object *object;
    vector<Object*>::iterator i;

    if(index < 0)
      index = objectvector.size() + index + 1;

    if(!in_range(index, (int)objectvector.size() - 1))
      i = objectvector.end();
    else
      i = objectvector.begin() + index;

    objectvector.insert(i, object = new Object(*this));

    return object;
  }


  void Objectgroup::removeObject(int index)
  {
    vector<Object*>::iterator i;

    if(!in_range(index, (int)objectvector.size() - 1))
      throw Exception() << "No object '" << index << "' there. vector.size() = " << objectvector.size();

    i = objectvector.begin() + index;
    delete *i;
    objectvector.erase(i);

  }


  void Objectgroup::removeObject(const Object *object)
  {
    for(int o = 0; o < (int)objectvector.size(); o++)
    {
      if(objectvector[o] == object)
      {
        delete objectvector[o];
          objectvector.erase(objectvector.begin() + o);

        return;
      }
    }

    throw Exception() << "No such object '" << object << "'";
  }


  void Objectgroup::init()
  {
    width = 0;
    height = 0;
  }



  Objectgroup::Objectgroup(const Objectgroup &objectgroup):
    Layer(LAYER_OBJECTGROUP),
    map(objectgroup.map)
  {
    clear();

    name = objectgroup.name;
    width = objectgroup.width;
    height = objectgroup.height;
    properties = objectgroup.properties;

    objectvector.resize(objectgroup.objectvector.size());
    for(int o = 0; o < (int)objectgroup.objectvector.size(); o++)
    {
      objectvector[o] = new Object(*(objectgroup.objectvector[o]));
    }
  }


  void Objectgroup::setWidth(int width)
  {
    this->width = width;
  }


  void Objectgroup::setHeight(int height)
  {
    this->height = height;
  }


}
}




