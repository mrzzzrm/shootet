#ifndef XML_XML_HPP
#define XML_XML_HPP

  #include <map>
  #include <string>
  #include <cstdlib>

  #include "etc/int.h"
  #include "util/Path.hpp"
  #include "error/Exception.hpp"

  #include "./tinyxml/tinyxml.h"


  namespace xml
  {
    enum XML_BLOCK_TYPE
    {
      XML_BLOCK_UNKNOWN,
      XML_BLOCK_DOCUMENT,
      XML_BLOCK_ELEMENT,
      XML_BLOCK_TEXT
    };

    class XmlVisitor;

    class Xml
    {
      friend class XmlVisitor;

      public:

        Xml();
        Xml(const util::Path &path);
        Xml(const std::string &string);
        Xml(const Xml &xml);
        ~Xml();


        /* Load */
          void load(const util::Path &path);
          void load(const std::string &string);
          void load(const Xml &xml);


        /* Clear */
          void clear();


        /* Path */
          const util::Path &getPath() const;


        /**
          READ THE DOM
       **/
        /* Parse */
          bool toRootBlock();
          bool toRootBlock(const std::string &name);
          bool toSubBlock();
          bool toSubBlock(const std::string &name);
          bool toNextBlock();
          bool toNextBlock(const std::string &name);
          bool toBaseBlock();
          bool toBaseBlock(const std::string &name);


        /* Count subblocks */
          int getSubBlockCount() const;
          int getSubBlockCount(const std::string &name) const;


        /* Check attributes */
          bool hasAttribute(const std::string &name) const;

          bool isString(const std::string &name) const;
          bool isInteger(const std::string &name) const;
          bool isFloat(const std::string &name) const;


        /* Read attributes */
          std::string getString(const std::string &name) const;
          int getInteger(const std::string &name) const;
          double getFloat(const std::string &name) const;


        /* Get the name/text of a block */
          std::string getBlockValue() const;


        /* Type of the current block */
          XML_BLOCK_TYPE getBlockType() const;


        /* Read the declaration */
          bool hasDeclaration() const;

          bool hasVersion() const;
          bool hasEncoding() const;
          bool hasStandalone() const;

          std::string getVersion() const;
          std::string getEncoding() const;
          std::string getStandalone() const;


        /* Default Values */
          void setDefaultString(const std::string &_string);
          void setDefaultInteger(int _integer);
          void setDefaultFloat(double _float);


        /**
          WRITE THE DOM
       **/
       /* Attributes */
         void setAttribute(const std::string &name, const std::string &value);
         void setAttribute(const std::string &name, int value);
         void setAttribute(const std::string &name, double value);

         void removeAttribute(const std::string &name);


       /* Blocks */
         void setBlockValue(const std::string &value);

         void addBlockBefore(const std::string &value, XML_BLOCK_TYPE type = XML_BLOCK_ELEMENT);

         void addBlockAfter(const std::string &value, XML_BLOCK_TYPE type = XML_BLOCK_ELEMENT);
         void addBlockAfterAndFollow(const std::string &value, XML_BLOCK_TYPE type = XML_BLOCK_ELEMENT);

         void addSubBlock(const std::string &value, XML_BLOCK_TYPE type = XML_BLOCK_ELEMENT);
         void addSubBlockAndFollow(const std::string &value, XML_BLOCK_TYPE type = XML_BLOCK_ELEMENT);

         void removeBlock();



        /**
          MISC
       **/
        /* Visitor */
          XmlVisitor getVisitor() const;


        /* Doc2String */
          std::string toString() const;


        /* Operators */
          Xml &operator=(const Xml &xml);



      private:

        /* Data */
          util::Path path;
          TiXmlDocument *doc;
          TiXmlNode *pollnode;

          struct
          {
            std::string _string;
            int _integer;
            double _float;
          }def;


        /* Internals */
          void init();
          const std::string *getAttribute(const std::string &name, TiXmlNode *pollnode) const;


    };
  }

#endif // XML_XML_HPP
