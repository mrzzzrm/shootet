#include "./Csv.hpp"

using namespace std;

using namespace error;



namespace util
{
  Csv::Csv()
  {
    init();
  }


  Csv::Csv(const Path &path, const string &seperators)
  {
    init();
    load(path, seperators);
  }


  Csv::Csv(const string &text, const string &seperators)
  {
    init();
    load(text, seperators);
  }


  Csv::Csv(const Csv &csv)
  {
    init();
    load(csv);
  }


  Csv::~Csv()
  {
    clear();
  }


  void Csv::load(const Path &path, const string &seperators)
  {
    load(file_to_string(path), seperators);
  }


  void Csv::load(const string &text, const string &seperators)
  {
    u32 lsc; /* Line start char */

    if(text.size() > 0)
      linevector.resize(1);
    else
      return;

    lsc = 0;
    while(true)
    {
      string line;
      u32 csc; /* Cell start character */
      u32 end;
      u32 nl, cr, crnl;

      /* Split into lines */
        nl = text.find("\n", lsc);
        cr = text.find("\r", lsc);
        crnl = text.find("\r\n", lsc);

        if(nl < cr)
        {
          if(nl < crnl)
            end = nl;
          else
            end = crnl;
        }
        else
        {
          if(cr < crnl)
            end = cr;
          else
            end = crnl;
        }

        if(end == text.npos)
          line = text.substr(lsc);
        else
          line = text.substr(lsc, end - lsc);


        if(end == crnl)
          lsc = end + 2;
        else
          lsc = end + 1;


      /* Split into cells */
        csc = 0;
        while(true)
        {
          u32 end = text.npos;

          for(uint s = 0; s < seperators.size(); s++)
          {
            if(line.find(seperators[s], csc) < end)
              end = line.find(seperators[s], csc);
          }

          if(end == text.npos)
            linevector.back().push_back(line.substr(csc));
          else
            linevector.back().push_back(line.substr(csc, end - csc));

          if(end == text.npos)
            break;

          csc = end + 1;
        }


      /* Add another line or finish */
        if(end == text.npos)
          break;
        else
          linevector.resize(linevector.size() + 1);
    }


  }

  void Csv::load(const Csv &csv)
  {
    if(&csv == this)
      return;

    linevector = csv.linevector;
  }


  void Csv::clear()
  {
    linevector.clear();
    def._string.clear();
    init();
  }


  u32 Csv::getLineCount() const
  {
    return linevector.size();
  }


  u32 Csv::getCellCount(u32 line) const
  {
    if(line >= linevector.size())
      throw Exception() << "No such line '" << line << "', linecount is '" << linevector.size() << "'";

    return linevector[line].size();
  }


  bool Csv::hasCell(u32 line, u32 cell) const
  {
    if(line >= linevector.size())
      return false;
    if(cell >= linevector[line].size())
      return false;

    return true;
  }


  bool Csv::isInteger(u32 line, u32 cell) const
  {
    char *end;
    int i;
    string str;

    if(!hasCell(line, cell))
      return false;

    str = linevector[line][cell];

    i = strtol(str.c_str(), &end, 10);

    if(static_cast<u32>(end - str.c_str()) == str.size())
      return true;
    else
      return false;
  }


  bool Csv::isFloat(u32 line, u32 cell) const
  {
    char *end;
    double d;
    string str;

    if(!hasCell(line, cell))
      return false;

    str = linevector[line][cell];

    d = strtod(str.c_str(), &end);

    if(static_cast<u32>(end - str.c_str()) == str.size())
      return true;
    else
      return false;
  }


  const string &Csv::getString(u32 line, u32 cell) const
  {
    return linevector[line][cell];
  }


  u32 Csv::getInteger(u32 line, u32 cell) const
  {
    char *end;
    int i;
    string str;

    if(!hasCell(line, cell))
      return def._integer;

    str = linevector[line][cell];
    i = strtol(str.c_str(), &end, 10);

    if(static_cast<u32>(end - str.c_str()) == str.size())
      return i;
    else
      return def._integer;
  }


  double Csv::getFloat(u32 line, u32 cell) const
  {
    char *end;
    double d;
    string str;

    if(!hasCell(line, cell))
      return def._float;

    str = linevector[line][cell];
    d = strtod(str.c_str(), &end);

    if(static_cast<u32>(end - str.c_str()) == str.size())
      return d;
    else
      return def._float;
  }


  void Csv::setString(u32 line, u32 cell, const string &_string)
  {
    if(line >= linevector.size())
      linevector.resize(line + 1);
    if(cell >= linevector[line].size())
      linevector[line].resize(cell + 1);

    linevector[line][cell] = _string;
  }


  void Csv::setInteger(u32 line, u32 cell, int _integer)
  {
    stringstream ss;

    ss << _integer;
    setString(line, cell, ss.str());
  }


  void Csv::setFloat(u32 line, u32 cell, double _float)
  {
    stringstream ss;

    ss << _float;
    setString(line, cell, ss.str());
  }


  void Csv::setDefaultString(const string &_string)
  {
    def._string = _string;
  }


  void Csv::setDefaultInteger(int _integer)
  {
    def._integer = _integer;
  }


  void Csv::setDefaultFloat(double _float)
  {
    def._float = _float;
  }


  std::string Csv::toString() const
  {
    stringstream ss;

    for(uint l = 0; l < linevector.size(); l++)
    {
      for(uint c = 0; c < linevector[l].size(); c++)
      {
        ss << linevector[l][c];

        if(c < linevector[l].size()-1)
          ss << ",";
      }

      ss << "\n";
    }

    return ss.str();
  }


  Csv &Csv::operator=(const Csv &csv)
  {
    load(csv);
    return *this;
  }


  void Csv::init()
  {
    def._integer = 0;
    def._float = 0;
  }

}
