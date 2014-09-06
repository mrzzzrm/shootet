#include "./Xml.hpp"
#include "./XmlVisitor.hpp"


using namespace std;
using namespace util;
using namespace error;


namespace xml
{

/*
  Class Xml
*/

  Xml::Xml()
  {
    init();
  }


  Xml::Xml(const Path &path)
  {
    init();
    load(path);
  }


  Xml::Xml(const std::string &string)
  {
    init();
    load(string);
  }


  Xml::Xml(const Xml &xml)
  {
    init();
    load(xml);
  }


  Xml::~Xml()
  {
    clear();
  }


  void Xml::load(const Path &path)
  {
    clear();

    doc->LoadFile((string)path);
      if(doc->Error())
        throw Exception() << "Error in doc '" << (string)path << "': " << doc->ErrorDesc() << " row: " << doc->ErrorRow() << " column: " << doc->ErrorCol();

    this->path = path;

    toRootBlock();
  }


  void Xml::load(const std::string &string)
  {
    clear();

    doc->Parse(string.c_str());
     if(doc->Error())
        throw Exception() << "Error in xmldata: " << doc->ErrorDesc() << " row: " << doc->ErrorRow() << " column: " << doc->ErrorCol();

    toRootBlock();
  }


  void Xml::load(const Xml &xml)
  {
    if(&xml == this)
      return;

    clear();

    path = xml.path;
    doc = xml.doc;
    def._string = xml.def._string;
    def._integer = xml.def._integer;
    def._float = xml.def._float;

    toRootBlock();
  }


  void Xml::clear()
  {
    if(doc != NULL)
      delete doc;

    path.clear();
    def._string.clear();

    init();
  }


  const Path &Xml::getPath() const
  {
    return path;
  }


  bool Xml::toRootBlock()
  {
    TiXmlNode *tpollnode;


    /* Search root block */
      tpollnode = doc->FirstChild();

      /* No children */
        if(tpollnode == NULL)
          return false;


      /* Search */
        do
        {
          /* Found it */
            if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
            {
              pollnode = tpollnode;
              return true;
            }

        }while((tpollnode = tpollnode->NextSibling()) != NULL);


    /* No matching block found */
      return false;
  }


  bool Xml::toRootBlock(const std::string &name)
  {
    TiXmlNode *tpollnode;


    /* Search root block */
      tpollnode = doc->FirstChild();

      /* No children */
        if(tpollnode == NULL)
          return false;


      /* Search */
        do
        {
          /* Found it */
            if(tpollnode->Value() == name && (tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT))
            {
              pollnode = tpollnode;
              return true;
            }

        }while((tpollnode = tpollnode->NextSibling()) != NULL);


    /* No matching block found */
      return false;
  }


  bool Xml::toSubBlock()
  {
    TiXmlNode *tpollnode;

    /* Break */
      if(pollnode == NULL)
        return false;


    /* To */
      if((tpollnode = pollnode->FirstChild()) != NULL)
      {
        /* Search the first block */
          do
          {
            if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
            {
              pollnode = tpollnode;
              return true;
            }
          }while((tpollnode = tpollnode->NextSibling()) != NULL);


        /* None found */
          return false;
      }
      else
      {
        return false;
      }
  }


  bool Xml::toSubBlock(const std::string &name)
  {
    TiXmlNode *tpollnode;

    /* Break */
      if(pollnode == NULL)
        return false;


    /* To */
      if((tpollnode = pollnode->FirstChild()) != NULL)
      {

        /* Search */
          do
          {
            if(name == tpollnode->ValueStr() && (tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT))
            {
              pollnode = tpollnode;
              return true;
            }

          }while((tpollnode = tpollnode->NextSibling()) != NULL);


        /* Not found */
          return false;

      }
      else
      {
        return false;
      }
  }


  bool Xml::toNextBlock()
  {
    TiXmlNode *tpollnode;

    /* Break */
      if(pollnode == NULL)
        return false;


    /* To */
      if((tpollnode = pollnode->NextSibling()) != NULL)
      {
        /* Search the next block */
          do
          {
            if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
            {
              pollnode = tpollnode;
              return true;
            }
          }while((tpollnode = tpollnode->NextSibling()) != NULL);


        /* None found */
          return false;
      }
      else
      {
        return false;
      }
  }


  bool Xml::toNextBlock(const std::string &name)
  {
    TiXmlNode *tpollnode;

    /* Break */
      if(pollnode == NULL)
       return false;

    /* To */
      if((tpollnode = pollnode->NextSibling(name)) != NULL)
      {
        /* Search the next block */
          do
          {
            if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
            {
              pollnode = tpollnode;
              return true;
            }
          }while((tpollnode = tpollnode->NextSibling(name)) != NULL);


        /* None found */
          return false;
      }
      else
      {
        return false;
      }
  }


  bool Xml::toBaseBlock()
  {
    TiXmlNode *tpollnode;

    /* Break */
      if(pollnode == NULL)
        return false;


    /*  Init */
      tpollnode = pollnode;


    /* To */
      while((tpollnode = tpollnode->Parent()) != NULL)
      {
        if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT || tpollnode->Type() == TiXmlNode::TINYXML_DOCUMENT)
        {
          pollnode = tpollnode;
          return true;
        }
      }


    /* Return */
      return true;

  }


  bool Xml::toBaseBlock(const std::string &name)
  {
    TiXmlNode *tpollnode;


    /* Break */
      if(pollnode == NULL)
        return false;

    /*  Init */
      tpollnode = pollnode;


    /* Get */
      while((tpollnode = tpollnode->Parent()) != NULL)
      {
        if(tpollnode->ValueStr() == name && (tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT || tpollnode->Type() == TiXmlNode::TINYXML_DOCUMENT))
        {
          pollnode = tpollnode;
          return true;
        }
      }


    /* No matching block found */
      return false;
  }


  int Xml::getSubBlockCount() const
  {
    TiXmlNode *tpollnode;


    /* Break */
      if(pollnode == NULL)
        return 0;


    /* Go to first child */
      if((tpollnode = pollnode->FirstChild()) != NULL)
      {
        u32 count;

        /* Init counter */
          count = 0;

        /* Count */
          do
          {
            /* Check type */
              if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
              {
                count++;
              }

          }while((tpollnode = tpollnode->NextSibling()) != NULL);

        /* Return */
          return count;
      }
      else
      {
        return 0;
      }
  }


  int Xml::getSubBlockCount(const std::string &name) const
  {
    TiXmlNode *tpollnode;


    /* Break */
      if(pollnode == NULL)
        return 0;


    /* Go to first child */
      if((tpollnode = pollnode->FirstChild(name)) != NULL)
      {
        u32 count;

        /* Init counter */
          count = 0;

        /* Count */
          do
          {
            /* Check type */
              if(tpollnode->Type() == TiXmlNode::TINYXML_ELEMENT || tpollnode->Type() == TiXmlNode::TINYXML_TEXT)
              {

                count++;
              }

          }while((tpollnode = tpollnode->NextSibling(name)) != NULL);

        /* Return */
          return count;
      }
      else
      {
        return 0;
      }

  }


  bool Xml::hasAttribute(const std::string &name) const
  {
    return isString(name);
  }


  bool Xml::isString(const std::string &name) const
  {
    /* Break */
      if(pollnode == NULL)
        return false;

    /* Check */
      if(const_cast<string*>(getAttribute(name, pollnode)) == NULL)
        return false;
      else
        return true;
  }


  bool Xml::isInteger(const std::string &name) const
  {
    char *end;
    int in;
    string *str;

    /* Break */
      if(pollnode == NULL)
        return false;

    /* Get */
      if((str = const_cast<string*>(getAttribute(name, pollnode))) == NULL)
      {
        return false;
      }
      else
      {
        in = strtol(str->c_str(), &end, 10);

        if(end - str->c_str() == (int)(str->size()))
        {
          return true;
        }
        else
        {
          return false;
        }
      }
  }


  bool Xml::isFloat(const std::string &name) const
  {
    char *end;
    double fl;
    string *str;


    /* Break */
      if(pollnode == NULL)
       return false;


    /* Get */
      if((str = const_cast<string*>(getAttribute(name, pollnode))) == NULL)
      {
        return false;
      }
      else
      {
        fl = strtod(str->c_str(), &end);

        if(end - str->c_str() == (int)(str->size()))
        {
          return true;
        }
        else
        {
          return false;
        }
      }
  }


  std::string Xml::getString(const std::string &name) const
  {
    string *str;

    /* Break */
      if(pollnode == NULL)
        return def._string;

    /* Get */
      if((str = const_cast<string*>(getAttribute(name, pollnode))) == NULL)
        return def._string;
      else
        return *str;
  }


  int Xml::getInteger(const std::string &name) const
  {
    char *end;
    int in;
    string *str;

    /* Break */
      if(pollnode == NULL)
        return def._integer;


    /* Get */
      if((str = const_cast<string*>(getAttribute(name, pollnode))) == NULL)
      {
        return def._integer;
      }
      else
      {
        in = strtol(str->c_str(), &end, 10);

        if(static_cast<u32>(end - str->c_str()) == strlen(str->c_str()))
        {
          return in;
        }
        else
        {
          return def._integer;
        }
      }
  }


  double Xml::getFloat(const std::string &name) const
  {
    char *end;
    double fl;
    string *str;


    /* Break */
      if(pollnode == NULL)
       return def._float;


    /* Get */
      if((str = const_cast<string*>(getAttribute(name, pollnode))) == NULL)
      {
        return def._float;
      }
      else
      {
        fl = strtod(str->c_str(), &end);

        if(static_cast<u32>(end - str->c_str()) == strlen(str->c_str()))
        {
          return fl;
        }
        else
        {
          return def._float;
        }
      }
  }


  std::string Xml::getBlockValue() const
  {
    /* Break */
      if(pollnode == NULL)
       return string("");


    /* Get Name */
      return pollnode->ValueStr();
  }


  XML_BLOCK_TYPE Xml::getBlockType() const
  {
    if(pollnode == NULL)
     return XML_BLOCK_UNKNOWN;


    switch(pollnode->Type())
    {
      case TiXmlNode::TINYXML_DOCUMENT: return XML_BLOCK_DOCUMENT; break;
      case TiXmlNode::TINYXML_TEXT:     return XML_BLOCK_TEXT;     break;
      case TiXmlNode::TINYXML_ELEMENT:  return XML_BLOCK_ELEMENT;  break;

      default: return XML_BLOCK_UNKNOWN; break;
    }
  }


  bool Xml::hasDeclaration() const
  {
    const TiXmlNode *tpollnode;

    /* First block should be declaration */
      tpollnode = doc->FirstChild();
      if(tpollnode == NULL)
        return false;

    /* Check if it is a declaration */
      if(tpollnode->Type() == TiXmlNode::TINYXML_DECLARATION)
        return true;
      else
        return false;
  }


  bool Xml::hasVersion() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;

    if((tpollnode = doc->FirstChild()) == NULL)
      return false;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return false;

    return strlen(declaration->Version()) > 0;
  }


  bool Xml::hasEncoding() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;


    if((tpollnode = doc->FirstChild()) == NULL)
      return false;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return false;

    return strlen(declaration->Encoding()) > 0;
  }


  bool Xml::hasStandalone() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;


    if((tpollnode = doc->FirstChild()) == NULL)
      return false;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return false;

    return strlen(declaration->Standalone()) > 0;
  }


  std::string Xml::getVersion() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;


    if((tpollnode = doc->FirstChild()) == NULL)
      return def._string;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return def._string;

    if(strlen(declaration->Version()) > 0)
      return string(declaration->Version());
    else
      return def._string;
  }


  std::string Xml::getEncoding() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;


    if((tpollnode = doc->FirstChild()) == NULL)
      return def._string;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return def._string;

    if(strlen(declaration->Encoding()) > 0)
      return string(declaration->Encoding());
    else
      return def._string;
  }


  std::string Xml::getStandalone() const
  {
    const TiXmlNode *tpollnode;
    const TiXmlDeclaration *declaration;


    if((tpollnode = doc->FirstChild()) == NULL)
      return def._string;

    if((declaration = tpollnode->ToDeclaration()) == NULL)
      return def._string;

    if(strlen(declaration->Standalone()) > 0)
      return string(declaration->Standalone());
    else
      return def._string;
  }


  void Xml::setDefaultString(const std::string &_string)
  {
    def._string = _string;
  }


  void Xml::setDefaultInteger(int _integer)
  {
    def._integer = _integer;
  }


  void Xml::setDefaultFloat(double _float)
  {
    def._float = _float;
  }


  void Xml::setAttribute(const std::string &name, const std::string &value)
  {
    TiXmlElement *element;

    if(pollnode == NULL)
      return;

    if((element = pollnode->ToElement()) != NULL)
      element->SetAttribute(name, value);
  }


  void Xml::setAttribute(const std::string &name, int value)
  {
    stringstream ss;

    ss << value;
    setAttribute(name, ss.str());
  }


  void Xml::setAttribute(const std::string &name, double value)
  {
    stringstream ss;

    ss << value;
    setAttribute(name, ss.str());
  }


  void Xml::removeAttribute(const std::string &name)
  {
    TiXmlElement *element;

    if(pollnode == NULL)
      return;

    if((element = pollnode->ToElement()) != NULL)
      element->RemoveAttribute(name);
    }


  void Xml::setBlockValue(const std::string &value)
  {
    if(pollnode == NULL)
      return;

    pollnode->SetValue(value);
  }


  void Xml::addBlockBefore(const std::string &value, XML_BLOCK_TYPE type)
  {
    TiXmlNode *tpollnode;


    tpollnode = pollnode;
    toBaseBlock();

    if(pollnode == NULL || pollnode == tpollnode || getBlockType() == XML_BLOCK_DOCUMENT)
    {
      pollnode = tpollnode;
      return;
    }

    switch(type)
    {
      case XML_BLOCK_TEXT:    pollnode->InsertBeforeChild(tpollnode, TiXmlText(value));    break;
      case XML_BLOCK_ELEMENT: pollnode->InsertBeforeChild(tpollnode, TiXmlElement(value)); break;
      default: return;
    }

    pollnode = tpollnode;
  }


  void Xml::addBlockAfter(const std::string &value, XML_BLOCK_TYPE type)
  {
    TiXmlNode *tpollnode;


    tpollnode = pollnode;
    toBaseBlock();

    if(pollnode == NULL || pollnode == tpollnode || getBlockType() == XML_BLOCK_DOCUMENT)
    {
      pollnode = tpollnode;
      return;
    }

    switch(type)
    {
      case XML_BLOCK_TEXT:    pollnode->InsertAfterChild(tpollnode, TiXmlText(value));    break;
      case XML_BLOCK_ELEMENT: pollnode->InsertAfterChild(tpollnode, TiXmlElement(value)); break;
      default: return;
    }

    pollnode = tpollnode;
  }


  void Xml::addBlockAfterAndFollow(const std::string &value, XML_BLOCK_TYPE type)
  {
    addBlockAfter(value, type);
    toNextBlock(value);
  }


  void Xml::addSubBlock(const std::string &value, XML_BLOCK_TYPE type)
  {
    if(pollnode == NULL)
      return;
    if(getBlockType() == XML_BLOCK_DOCUMENT && getSubBlockCount() >= 1)
      return;

    switch(type)
    {
      case XML_BLOCK_TEXT:    pollnode->LinkEndChild(new TiXmlText(value));    break;
      case XML_BLOCK_ELEMENT: pollnode->LinkEndChild(new TiXmlElement(value)); break;
      default: return;
    }
  }


  void Xml::addSubBlockAndFollow(const std::string &value, XML_BLOCK_TYPE type)
  {
    addSubBlock(value, type);
    while(toNextBlock(value));
  }


  void Xml::removeBlock()
  {
    TiXmlNode *tpollnode;

    tpollnode = pollnode;
    toBaseBlock();

    if(pollnode == NULL || pollnode == tpollnode)
    {
      pollnode = tpollnode;
      return;
    }

    pollnode->RemoveChild(tpollnode);
  }


  XmlVisitor Xml::getVisitor() const
  {
    XmlVisitor visitor;

    visitor.path = path;
    visitor.doc = doc;
    visitor.pollnode = pollnode;
    visitor.def._string = def._string;
    visitor.def._integer = def._integer;
    visitor.def._float = def._float;

    return visitor;
  }


  std::string Xml::toString() const
  {
    TiXmlPrinter printer;
    doc->Accept(&printer);

    return printer.Str();
  }


  Xml &Xml::operator=(const Xml &xml)
  {
    load(xml);
    return *this;
  }


  void Xml::init()
  {
    doc = new TiXmlDocument();
    pollnode = doc;
    def._integer = 0;
    def._float = 0;
  }


  const std::string *Xml::getAttribute(const std::string &name, TiXmlNode *pollnode) const
  {
    TiXmlElement *element;

    if(pollnode == NULL)
      return NULL;

    if((element = pollnode->ToElement()) == NULL)
      return NULL;
    else
      return element->Attribute(name);
  }

}
