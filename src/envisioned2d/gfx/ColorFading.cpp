#include "./ColorFading.hpp"
#include "gfx/gfx.hpp"

using namespace std;

using namespace geo;
using namespace etc;



namespace gfx
{

  ColorFading::ColorFading()
  {

  }


  ColorFading::ColorFading(const Color &color, int ticks, FADE_TYPE type, const geo::IntSize &size)
  {
    load(color, ticks, type, size);
  }


  ColorFading::ColorFading(const ColorFading &colorfading)
  {

    load(colorfading);
  }


  ColorFading::~ColorFading()
  {

  }


  void ColorFading::load(const Color &color, int ticks, FADE_TYPE type, const geo::IntSize &size)
  {
    Fading::load(ticks, type);
    this->color = color;
    setSize(size); // Also fills with color
    image.setAlpha(Fading::getAlpha());
  }


  void ColorFading::load(const ColorFading &colorfading)
  {
    if(&colorfading == this)
      return;

    Fading::load(colorfading);
    color = colorfading.color;
    setSize(colorfading.image.getSize()); // Also fills with color
    image.setAlpha(Fading::getAlpha());
  }


  void ColorFading::clear()
  {
    Fading::clear();
    color.clear();
    image.clear();
  }

  const Color &ColorFading::getColor() const
  {
    return color;
  }


  void ColorFading::setColor(const Color &color)
  {
    if(this->color == color)
      return;

    image.fill(color);
    this->color = color;
  }


  const geo::IntSize ColorFading::getSize() const
  {
    return IntSize(image.getSize());
  }


  void ColorFading::setSize(const geo::IntSize &size)
  {
    IntSize tsize(size);

    if(size.getWidth() < 0)
      tsize.setWidth(gfx::getScreenSize().getWidth());
    if(size.getHeight() < 0)
      tsize.setHeight(gfx::getScreenSize().getHeight());

    image.setSize(tsize);
    image.fill(color);
  }


  void ColorFading::draw(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image)
  {
    update();

    if(Fading::getAlpha() == 0)
      return;

    this->image.setAlpha(Fading::getAlpha());
    this->image.draw(pos, alignment, rect, image);
  }


  void ColorFading::drawConst(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image) const
  {
    if(Fading::getAlpha() == 0)
      return;

    this->image.draw(pos, alignment, rect, image);
  }


  ColorFading &ColorFading::operator=(const ColorFading &colorfading)
  {
    load(colorfading);
    return *this;
  }

}
