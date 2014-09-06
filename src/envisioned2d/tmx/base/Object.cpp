#include "./Object.hpp"


using namespace std;

using namespace geo;
using namespace error;


namespace tmx
{
namespace base
{

  Object::Object(const Objectgroup &objectgroup):
    objectgroup(objectgroup)
  {

  }


  Object::Object(xml::Xml &xml, const Objectgroup &objectgroup):
    objectgroup(objectgroup)
  {
    load(xml);
  }



  Object::~Object()
  {
    clear();
  }


  void Object::load(xml::Xml &xml)
  {
    clear();

    /* Set attribute defaults */
      xml.setDefaultString("");
      xml.setDefaultInteger(0);
      xml.setDefaultFloat(0);


    /* Attributes ('type' is not forced to be set) */
      if(xml.isInteger("x") && xml.isInteger("y"))
      {
        name = xml.getString("name");
        type = xml.getString("type");
        setX(xml.getInteger("x"));
        setY(xml.getInteger("y"));
        setWidth(xml.getInteger("width"));
        setHeight(xml.getInteger("height"));
      }
      else
      {
        /* Throw */
          throw Exception() << "Missing or wrong typed attribute";
      }

    /* Properties */
      if(xml.toSubBlock("properties"))
      {
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


  void Object::clear()
  {
    properties.clear();
    name.clear();
    type.clear();
  }


  const string &Object::getName() const
  {
    return name;
  }


  const string &Object::getType() const
  {
    return type;
  }


  Properties &Object::getProperties()
  {
    return properties;
  }


  const Properties &Object::getPropertiesConst() const
  {
    return properties;
  }


  const Objectgroup &Object::getObjectgroup() const
  {
    return objectgroup;
  }


  void Object::setName(const std::string &name)
  {
    this->name = name;
  }


  void Object::setType(const std::string &type)
  {
    this->name = name;
  }


  Object::Object(const Object &object):
    IntRect(object),
    objectgroup(object.objectgroup)
  {
    name = object.name;
    type = object.type;
    properties = object.properties;
  }

}
}

