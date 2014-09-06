#include "./ImageFont.hpp"


using namespace std;

using namespace gfx;
using namespace geo;
using namespace etc;
using namespace util;

using namespace font;

/*
  Class ImageFont
*/

  ImageFont::ImageFont()
  {

  }


  ImageFont::ImageFont(const gfx::Image &image)
  {
    load(image);
  }


  ImageFont::ImageFont(const Path &path)
  {

    load(path);
  }


  ImageFont::ImageFont(const ImageFont &imagefont)
  {
    if(&imagefont == this)
      return;


    load(imagefont);
  }


  void ImageFont::load(const gfx::Image &image)
  {
    clear();

    Image::load(image);

    /* Set char-size */
    char_size.setWidth(Image::getSize().getWidth()/16);

    if(Image::getSize().getWidth() > Image::getSize().getHeight())
      char_size.setHeight(Image::getSize().getHeight()/8);
    else
      char_size.setHeight(Image::getSize().getHeight()/16);

  }


  void ImageFont::load(const Path &path)
  {
    clear();

    Image::load(path);

    /* Set char-size */
    char_size.setWidth(Image::getSize().getWidth()/16);

    if(Image::getSize().getWidth() > Image::getSize().getHeight())
      char_size.setHeight(Image::getSize().getHeight()/8);
    else
      char_size.setHeight(Image::getSize().getHeight()/16);
  }


  void ImageFont::load(const ImageFont &imagefont)
  {
    clear();

    Image::load(imagefont);
    char_size = imagefont.char_size;
  }


  void ImageFont::clear()
  {
    Image::clear();
    char_size.clear();
  }


  const geo::IntSize &ImageFont::getCharacterSize() const
  {
    return char_size;
  }


  void ImageFont::draw(const IntPoint &pos, const std::string &string, const Alignment &alignment, Image *image) const
  {
    IntPoint corner;
    IntRect crect(0, 0, char_size.getWidth(), char_size.getHeight());

    corner.setX(pos.getX() - (int)(char_size.getWidth() * string.size() * alignment.getX()));
    corner.setY(pos.getY() - (int)(char_size.getHeight() * alignment.getY()));

    for(uint c = 0; c < string.size(); c++)
    {
      crect.setX((string[c] % 16) * char_size.getWidth());
      crect.setY((string[c] / 16) * char_size.getHeight());

      Image::draw(corner + IntVector(char_size.getWidth() * c, 0), Alignment(ALIGN_BY_CORNER), crect, image);
    }
  }



  ImageFont &ImageFont::operator=(const ImageFont &imagefont)
  {
    load(imagefont);
    return *this;
  }



