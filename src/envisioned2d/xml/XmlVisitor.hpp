#ifndef XML_XMLVISITOR_HPP
#define XML_XMLVISITOR_HPP


  #include "error/Exception.hpp"

  #include "./Xml.hpp"

  namespace xml
  {


    class XmlVisitor: private Xml
    {
      friend class Xml;

      public:

        XmlVisitor();
        XmlVisitor(const XmlVisitor &xmlvisitor);
        ~XmlVisitor();


        /* Load */
          void load(const XmlVisitor &xmlvisitor);


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
          u32 getSubBlockCount() const;
          u32 getSubBlockCount(const std::string &name) const;


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
          MISC
       **/
        /* Doc2String */
          std::string convertDocumentToString() const;

        /* Operators */
          XmlVisitor &operator=(const XmlVisitor &xmlvisitor);


      private:

        /* Intern */
          void init();
          void assert_doc() const;
    };
  }

#endif // XML_XMLVISITOR_HPP
