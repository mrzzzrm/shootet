#include "./Path.hpp"

using namespace std;
using namespace error;


namespace util
{

  Path::Path():
    string("./")
  {

  }


  Path::Path(const string &str):
    string(str)
  {

  }


  Path::Path(const char *cstr):
    string(cstr)
  {

  }


  Path::Path(const Path &path):
    string(path)
  {

  }


  Path::~Path()
  {

  }


  void Path::load(const string &str)
  {
    string::operator=(str);
  }


  void Path::load(const char *cstr)
  {
    string::operator=(cstr);
  }


  void Path::load(const Path &path)
  {
    string::operator=(path);
  }


  void Path::clear()
  {
    string::clear();
  }


  Path &Path::append(const std::string &str)
  {
    stripFile();
    string::append(str);
    return *this;
  }


  Path Path::appendConst(const std::string &str) const
  {
    Path res(*this);

    res.stripFile();
    res.string::append(str);
    return res;
  }


  Path Path::getDirectory() const
  {
    Path res(*this);

    res.stripFile();
    return *this;
  }


  Path &Path::stripFile()
  {
    size_t dpos, spos;
    Path res(*this);

    dpos = string::rfind(".");
    spos =  string::rfind("/");

    if(spos == string::npos)
    {
      string::operator=("./");
    }
    else if(dpos == string::npos)
    {
      if(string::at(string::size() - 1) != '/')
        string::append("/");
    }
    else
    {
      if(spos > dpos)
      {
        if(string::at(string::size() - 1) != '/')
          string::append("/");
      }
      else
      {
        string::replace(spos + 1, string::npos, "");
      }
    }

    return *this;
  }


  bool Path::exists() const
  {
    bool res;
    ifstream file;

    file.open(c_str());

    if(file.is_open())
      res = true;
    else
      res = false;

    file.close();

    return res;
  }

  bool Path::remove()
  {
    if(std::remove(c_str()) != 0)
    {

    }
  }

  Path &Path::operator=(const Path &path)
  {
    load(path);
    return *this;
  }


}
