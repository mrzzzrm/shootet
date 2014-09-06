#include "./Alignment.hpp"



namespace etc
{
  Alignment::Alignment()
  {
    init();
  }


  Alignment::Alignment(const double &x, const double &y)
  {
    load(x, y);
  }


  Alignment::Alignment(ALIGNMENT alignment)
  {
    load(alignment);
  }


  Alignment::Alignment(const Alignment &alignment)
  {
    load(alignment);
  }


  void Alignment::load(const double &x, const double &y)
  {
    this->x = x;
    this->y = y;
  }


  void Alignment::load(ALIGNMENT alignment)
  {
    switch(alignment)
    {
      case ALIGN_BY_CORNER: load(0.0, 0.0); break;
      case ALIGN_BY_CENTER: load(0.5, 0.5); break;
    }
  }


  void Alignment::load(const Alignment &alignment)
  {
    x = alignment.x;
    y = alignment.y;
  }


  void Alignment::clear()
  {
    init();
  }


  const double &Alignment::getX() const
  {
    return x;
  }


  const double &Alignment::getY() const
  {
    return y;
  }


  void Alignment::setX(const double &x)
  {
    this->x = x;
  }


  void Alignment::setY(const double &y)
  {
    this->y = y;
  }


  Alignment &Alignment::operator=(const Alignment &alignment)
  {
    load(alignment);
    return *this;
  }


  void Alignment::init()
  {
    x = 0;
    y = 0;
  }


}

