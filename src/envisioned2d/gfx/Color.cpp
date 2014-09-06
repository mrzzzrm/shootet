#include "./Color.hpp"


using namespace std;


namespace gfx
{

  /*
    Class Color
  */

    Color::Color()
    {
      init();
    }


    Color::Color(u32 rgba)
    {
      load(rgba);
    }


    Color::Color(u8 r, u8 g, u8 b, u8 a)
    {
      load(r, g, b, a);
    }


    Color::Color(COLOR color)
    {
      load(color);
    }


    Color::Color(const Color &color)
    {
      load(color);
    }


    void Color::load(u32 rgba)
    {
      r = (rgba & 0xff000000) >> 24;
      g = (rgba & 0x00ff0000) >> 16;
      b = (rgba & 0x0000ff00) >> 8;
      a = (rgba & 0x000000ff) >> 0;
    }


    void Color::load(u8 r, u8 g, u8 b, u8 a)
    {
      this->r = r;
      this->g = g;
      this->b = b;
      this->a = a;
    }


    void Color::load(COLOR color)
    {
      switch(color)
      {
        case RED:      r = 0xff; g = 0x00; b = 0x00; a = 0xff; break;
        case GREEN:    r = 0x00; g = 0xff; b = 0x00; a = 0xff; break;
        case BLUE:     r = 0x00; g = 0x00; b = 0xff; a = 0xff; break;

        case YELLOW:   r = 0xff; g = 0xff; b = 0x00; a = 0xff; break;
        case MAGNETA:  r = 0xff; g = 0x00; b = 0x80; a = 0xff; break;

        case BLACK:    r = 0x00; g = 0x00; b = 0x00; a = 0xff; break;
        case WHITE:    r = 0xff; g = 0xff; b = 0xff; a = 0xff; break;
      }
    }


    void Color::load(const Color &color)
    {
      if(&color == this)
        return;

      r = color.r;
      g = color.g;
      b = color.b;
      a = color.a;
    }


    void Color::clear()
    {
      init();
    }


    u32 Color::getRGBA() const
    {
      return (r << 24) | (g << 16) | (b << 8) | (a << 0);
    }


    u8 Color::getRed() const
    {
      return r;
    }


    u8 Color::getGreen() const
    {
      return g;
    }


    u8 Color::getBlue() const
    {
      return b;
    }


    u8 Color::getAlpha() const
    {
      return a;
    }


    void Color::setRGBA(u32 rgba)
    {
      load(rgba);
    }


    void Color::setRed(u8 r)
    {
      this->r = r;
    }


    void Color::setGreen(u8 g)
    {
      this->g = g;
    }


    void Color::setBlue(u8 b)
    {
      this->b = b;
    }


    void Color::setAlpha(u8 a)
    {
      this->a = a;
    }


    Color &Color::operator=(const Color &color)
    {
      load(color);
      return *this;
    }


    bool Color::operator!=(const Color &color) const
    {
      return (r != color.r) || (g != color.g) || (b != color.b) || (a != color.a);
    }


    bool Color::operator==(const Color &color) const
    {
      return (r == color.r) && (g == color.g) && (b == color.b) && (a == color.a);
    }


    void Color::init()
    {
      r = 0;
      g = 0;
      b = 0;
      a = 0;
    }


}
