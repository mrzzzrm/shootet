#include "./std.hpp"

using namespace std;
using namespace error;


namespace util
{
  string file_to_string(const Path &path)
  {
    char *block;
    u32 size;
    std::string string;
    ifstream file;


    file.open(path.c_str(), ios::binary);

    if(!file.is_open())
      throw Exception() << "No such file " << path;


    file.seekg(0, ios::end);
    size = file.tellg();
    file.seekg(0, ios::beg);

    block = new char[size+1];
    file.read(block, size);
      block[size] = '\0';

    string = block;
    delete block;


    /* Erase lineendings with '\n' */
      for(size_t c = string.find("\r\n", 0); c != string.npos; c = string.find("\r\n", c))
      {
        string.replace(c, 2, "\n");
        c+=2;
      }
      for(size_t c = string.find("\r", 0); c != string.npos; c = string.find("\r", c))
      {
        string.replace(c, 1, "\n");
        c+=1;
      }

    /* Return */
      return string;
  }


  void string_to_file(const string &string, const Path &path)
  {
    ofstream file;

    file.open(path.c_str());

    if(!file.is_open())
      throw Exception() << "Couldn't open file " << path;


    file << string;

    file.close();
  }

}
