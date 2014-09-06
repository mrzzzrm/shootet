#include "./Highscore.hpp"

using namespace std;

using namespace xml;
using namespace error;


namespace util
{

/*
  Class Highscore
*/
  Highscore::Highscore()
  {

  }


  Highscore::Highscore(uint max_entries)
  {
    load(max_entries);
  }


  Highscore::Highscore(const Xml &xml)
  {
    load(xml);
  }


  Highscore::Highscore(const Highscore &highscore)
  {
    load(highscore);
  }


  Highscore::~Highscore()
  {
    clear();
  }


  void Highscore::load(uint max_entries)
  {
    clear();

    entrylist.resize(max_entries, pair<uint, string>(0, string("")));
  }


  void Highscore::load(const xml::Xml &xml)
  {
    XmlVisitor xmlvisitor = xml.getVisitor();

    clear();

    if(xmlvisitor.getBlockValue() != "highscore" || xmlvisitor.getBlockType() != XML_BLOCK_ELEMENT)
      throw Exception() << "Element blocks name must be 'highscore'";

    if(xmlvisitor.toSubBlock("entry"))
    {
      do
      {
        if(!xmlvisitor.isInteger("score"))
          {clear(); throw Exception() << "No such integer attribute 'score' in entry";}
        if(!xmlvisitor.isString("name"))
          {clear(); throw Exception() << "No such attribute 'name' in entry";}

        entrylist.push_back(pair<uint, string>(xmlvisitor.getInteger("score"), xmlvisitor.getString("name")));

      }while(xmlvisitor.toNextBlock("entry"));
    }

    entrylist.sort(cmp);
  }


  void Highscore::load(const Highscore &highscore)
  {
    if(&highscore == this)
      return;

    entrylist = highscore.entrylist;
  }


  void Highscore::clear()
  {
    entrylist.clear();
  }


  uint Highscore::getMaxEntries() const
  {
    return entrylist.size();
  }


  const string &Highscore::getEntryName(uint index) const
  {
    list<pair<uint, string> >::const_iterator i;

    if(index >= entrylist.size())
      throw Exception() << "No such entry with index '" << index << "' in list of size '" << entrylist.size() << "'";

    i = entrylist.begin();
    advance(i, index);

    return i->second;
  }


  uint Highscore::getEntryScore(uint index) const
  {
    list<pair<uint, string> >::const_iterator i;

    if(index >= entrylist.size())
      throw Exception() << "No such entry with index '" << index << "' in list of size '" << entrylist.size() << "'";

    i = entrylist.begin();
    advance(i, index);

    return i->first;
  }


  void Highscore::setEntryName(uint index, const string &name)
  {
    list<pair<uint, string> >::iterator i;

    if(index >= entrylist.size())
      throw Exception() << "No such entry with index '" << index << "' in list of size '" << entrylist.size() << "'";

    i = entrylist.begin();
    advance(i, index);

    i->second = name;
  }


  void Highscore::removeEntry(uint index)
  {
    list<pair<uint, string> >::iterator i;

    if(index >= entrylist.size())
      throw Exception() << "No such entry with index '" << index << "' in list of size '" << entrylist.size() << "'";

    i = entrylist.begin();
    advance(i, index);

    entrylist.erase(i);
  }


  int Highscore::checkEntryPosition(uint score)
  {
    uint pos = 0;

    for(list<pair<uint, string> >::iterator i = entrylist.begin(); i != entrylist.end(); i++, pos++)
    {
      if(i->first < score)
        return pos;
    }

    return -1;
  }


  int Highscore::addEntry(uint score, const string &name)
  {
    uint pos = 0;

    for(list<pair<uint, string> >::iterator i = entrylist.begin(); i != entrylist.end(); i++, pos++)
    {
      if(i->first < score)
      {
        entrylist.insert(i, pair<uint, string>(score, name));
        entrylist.pop_back();
        return pos;
      }
    }

    return -1;
  }


  Xml Highscore::getXml() const
  {
    Xml xml;

    xml.addSubBlock("highscore");
    xml.toSubBlock("highscore");

    xml.addSubBlock("entry");
    xml.toSubBlock("entry");

    for(list<pair<uint, string> >::const_iterator i = entrylist.begin(); i != entrylist.end();)
    {
      xml.setAttribute("score", (int)i->first);
      xml.setAttribute("name", i->second);

      i++;

      if(i != entrylist.end())
      {
        xml.addBlockAfter("entry");
        xml.toNextBlock("entry");
      }
    }

    return xml;
  }


  Highscore &Highscore::operator=(const Highscore &highscore)
  {
    load(highscore);
    return *this;
  }


  bool Highscore::cmp(const std::pair<uint, std::string> &p1, const std::pair<uint, std::string> &p2)
  {
    if(p1.first > p2.first)
      return true;
    else
      return false;
  }

}


