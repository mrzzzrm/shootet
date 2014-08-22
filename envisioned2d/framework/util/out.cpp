#include "./out.hpp"

using namespace std;

namespace util
{
  std::ostream &operator<<(std::ostream &out, const util::Path &path)
  {
    out << "[Path: '" << (string)path << "']";
    return out;
  }


  std::ostream &operator<<(std::ostream &out, const error::Exception &exception)
  {
    out << exception.getDescription();
    return out;
  }
}
