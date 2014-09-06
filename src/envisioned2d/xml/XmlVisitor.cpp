#include "./XmlVisitor.hpp"

using namespace std;
using namespace error;


namespace xml
{

  XmlVisitor::XmlVisitor()
  {
    init();
  }


  XmlVisitor::XmlVisitor(const XmlVisitor &xmlvisitor)
  {
    init();
    load(xmlvisitor);
  }


  XmlVisitor::~XmlVisitor()
  {
    clear();
  }


  void XmlVisitor::load(const XmlVisitor &xmlvisitor)
  {
    if(&xmlvisitor == this)
      return;

    clear();

    doc = xmlvisitor.doc;
    pollnode = xmlvisitor.pollnode;
    path = xmlvisitor.path;
    def = xmlvisitor.def;
  }


  void XmlVisitor::clear()
  {
    path.clear();
    def._string.clear();

    init();
  }


  const util::Path &XmlVisitor::getPath() const
  {
    return path;
  }


  bool XmlVisitor::toRootBlock()
  {
    assert_doc();
    return Xml::toRootBlock();
  }


  bool XmlVisitor::toRootBlock(const std::string &name)
  {
    assert_doc();
    return Xml::toRootBlock(name);
  }


  bool XmlVisitor::toSubBlock()
  {
    assert_doc();
    return Xml::toSubBlock();
  }


  bool XmlVisitor::toSubBlock(const std::string &name)
  {
    assert_doc();
    return Xml::toSubBlock(name);
  }


  bool XmlVisitor::toNextBlock()
  {
    assert_doc();
    return Xml::toNextBlock();
  }


  bool XmlVisitor::toNextBlock(const std::string &name)
  {
    assert_doc();
    return Xml::toNextBlock(name);
  }


  bool XmlVisitor::toBaseBlock()
  {
    assert_doc();
    return Xml::toBaseBlock();
  }


  bool XmlVisitor::toBaseBlock(const std::string &name)
  {
    assert_doc();
    return Xml::toBaseBlock(name);
  }


  u32 XmlVisitor::getSubBlockCount() const
  {
    assert_doc();
    return Xml::getSubBlockCount();
  }


  u32 XmlVisitor::getSubBlockCount(const std::string &name) const
  {
    assert_doc();
    return Xml::getSubBlockCount(name);
  }


  bool XmlVisitor::hasAttribute(const std::string &name) const
  {
    assert_doc();
    return Xml::hasAttribute(name);
  }


  bool XmlVisitor::isString(const std::string &name) const
  {
    assert_doc();
    return Xml::isString(name);
  }


  bool XmlVisitor::isInteger(const std::string &name) const
  {
    assert_doc();
    return Xml::isInteger(name);
  }


  bool XmlVisitor::isFloat(const std::string &name) const
  {
    assert_doc();
    return Xml::isFloat(name);
  }


  std::string XmlVisitor::getString(const std::string &name) const
  {
    assert_doc();
    return Xml::getString(name);
  }


  int XmlVisitor::getInteger(const std::string &name) const
  {
    assert_doc();
    return Xml::getInteger(name);
  }


  double XmlVisitor::getFloat(const std::string &name) const
  {
    assert_doc();
    return Xml::getFloat(name);
  }


  std::string XmlVisitor::getBlockValue() const
  {
    assert_doc();
    return Xml::getBlockValue();
  }


  XML_BLOCK_TYPE XmlVisitor::getBlockType() const
  {
    assert_doc();
    return Xml::getBlockType();
  }


  bool XmlVisitor::hasDeclaration() const
  {
    assert_doc();
    return Xml::hasDeclaration();
  }


  bool XmlVisitor::hasVersion() const
  {
    assert_doc();
    return Xml::hasVersion();
  }


  bool XmlVisitor::hasEncoding() const
  {
    assert_doc();
    return Xml::hasEncoding();
  }


  bool XmlVisitor::hasStandalone() const
  {
    assert_doc();
    return Xml::hasStandalone();
  }


  std::string XmlVisitor::getVersion() const
  {
    assert_doc();
    return Xml::getVersion();
  }


  std::string XmlVisitor::getEncoding() const
  {
    assert_doc();
    return Xml::getEncoding();
  }


  std::string XmlVisitor::getStandalone() const
  {
    assert_doc();
    return Xml::getStandalone();
  }


  void XmlVisitor::setDefaultString(const std::string &_string)
  {
     Xml::setDefaultString(_string);
  }


  void XmlVisitor::setDefaultInteger(int _integer)
  {
     Xml::setDefaultInteger(_integer);
  }


  void XmlVisitor::setDefaultFloat(double _float)
  {
    Xml::setDefaultFloat(_float);
  }


  std::string XmlVisitor::convertDocumentToString() const
  {
    assert_doc();
    return Xml::toString();
  }


  XmlVisitor &XmlVisitor::operator=(const XmlVisitor &xmlvisitor)
  {
    load(xmlvisitor);
    return *this;
  }


  void XmlVisitor::init()
  {
    doc = NULL;
    pollnode = NULL;
    def._integer = 0;
    def._float = 0;
  }


  void XmlVisitor::assert_doc() const
  {
    if(doc == NULL)
      throw Exception() << "Not connected with xml";
  }
}
