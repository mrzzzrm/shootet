#ifndef UTIL_HIGHSCORE_HPP
#define UTIL_HIGHSCORE_HPP

  #include <list>

  #include "etc/int.h"
  #include "error/Exception.hpp"
  #include "xml/Xml.hpp"
  #include "xml/XmlVisitor.hpp"

  namespace util
  {

    class Highscore
    {
      public:

        Highscore();
        Highscore(uint max_entries);
        Highscore(const xml::Xml &xml);
        Highscore(const Highscore &highscore);
        ~Highscore();


        /* Load */
          void load(uint max_entries);
          void load(const xml::Xml &xml);
          void load(const Highscore &highscore);


        /* Clear */
          void clear();


        /* Entries */
          uint getMaxEntries() const;

          const std::string &getEntryName(uint index) const;
          uint getEntryScore(uint index) const;

          void setEntryName(uint index, const std::string &name);

          void removeEntry(uint index);

          int checkEntryPosition(uint score);
          int addEntry(uint score, const std::string &name = std::string(""));


        /* Xml */
          xml::Xml getXml() const;


        /* Operators */
          Highscore &operator=(const Highscore &highscore);


      private:

        /* Data */
          std::list<std::pair<uint, std::string> > entrylist;


        /* Internals */
          static bool cmp(const std::pair<uint, std::string> &p1, const std::pair<uint, std::string> &p2);

    };
  }

#endif // UTIL_HIGHSCORE_HPP
