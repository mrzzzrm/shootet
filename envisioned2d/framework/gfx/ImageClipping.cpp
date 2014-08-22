#include "./ImageClipping.hpp"

using namespace std;

using namespace geo;
using namespace etc;
using namespace util;
using namespace error;using namespace error;




namespace gfx
{
  ImageClipping::ImageClipping()
  {
    init();
  }


  ImageClipping::ImageClipping(const Image *image, const IntRect &blitrect)
  {
    init();
    load(image, blitrect);
  }


  ImageClipping::ImageClipping(const ImageClipping &imageclipping)
  {
    init();
    load(imageclipping);
  }


  ImageClipping::~ImageClipping()
  {

  }


  void ImageClipping::load(const Image *image, const IntRect &blitrect)
  {
    this->image = image;
    IntRect::load(blitrect);
  }


  void ImageClipping::load(const ImageClipping &imageclipping)
  {
    if(&imageclipping == this)
      return;

    image = imageclipping.image;
    IntRect::load(imageclipping);
  }


  void ImageClipping::clear()
  {
    IntRect::clear();
    image = NULL;
  }


  const Image *ImageClipping::getImage() const
  {
    return image;
  }


  void ImageClipping::setImage(const Image *image)
  {
    this->image = image;
  }


  void ImageClipping::draw(const geo::IntPoint &pos, const Alignment &alignment, const geo::IntRect &rect, Image *image) const
  {
    IntRect brect;

    if(this->image == NULL)
      return;

    /* Translate negative size */
    brect = rect_translate_negative_axises(*(IntRect*)this, this->image->getSize());
    brect = rect_translate_negative_axises(rect, brect);
    brect.normalise();

    /* Draw */
    this->image->draw(pos, alignment, brect, image);
  }


  void ImageClipping::draw(const geo::IntPoint &corner, Image *image) const
  {
    if(this->image == NULL)
      return;

    this->image->draw(corner, ALIGN_BY_CORNER, *this, image);
  }


  ImageClipping &ImageClipping::operator=(const ImageClipping &imageclipping)
  {
    load(imageclipping);
    return *this;
  }


  void ImageClipping::init()
  {
    image = NULL;
  }
}





