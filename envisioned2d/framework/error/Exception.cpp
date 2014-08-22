#include "./Exception.hpp"

using namespace std;


namespace error
{
  Exception::Exception()
  {

  }

  Exception::Exception(const Exception &exception)
  {
    description.str(exception.description.str());
  }


  Exception::~Exception()
  {

  }


  const string Exception::getDescription() const
  {
    return description.str();
  }


  Exception &Exception::operator=(const Exception &exception)
  {
    description.str(exception.description.str());
    return *this;
  }
}



