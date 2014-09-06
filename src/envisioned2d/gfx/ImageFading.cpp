#include "./ImageFading.hpp"

using namespace std;

using namespace etc;
using namespace geo;

namespace gfx
{

  ImageFading::ImageFading()
  {
    init();
  }


  ImageFading::ImageFading(Image *image, uint ticks, FADE_TYPE type)
  {
    init();
    load(image, ticks, type);
  }


  ImageFading::ImageFading(const ImageFading &imagefading)
  {
    init();
    load(imagefading);
  }


  ImageFading::~ImageFading()
  {

  }


  void ImageFading::load(Image *image, uint ticks, FADE_TYPE type)
  {
    Fading::load(ticks, type);

    this->image = image;
  }


  void ImageFading::load(const ImageFading &imagefading)
  {
    if(&imagefading == this)
      return;

    Fading::load(imagefading);

    image = imagefading.image;
  }


  void ImageFading::clear()
  {
    Fading::clear();

    init();
  }


  Image *ImageFading::getImage()
  {
    return image;
  }


  const Image *ImageFading::getImageConst() const
  {
    return image;
  }


  void ImageFading::setImage(Image *image)
  {
    this->image = image;
  }


  void ImageFading::draw(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image)
  {
    double alpha;

    update();

    if(type == FADE_NOT)
      return;
    if(this->image == NULL)
      return;
    if(this->alpha == 0)
      return;

    alpha = this->image->getAlpha();
    this->image->setAlpha(this->alpha);
    this->image->draw(pos, alignment, rect, image);
    this->image->setAlpha(alpha);
  }


  void ImageFading::draw(const geo::IntPoint &corner, Image *image)
  {
    double alpha;

    update();

    if(type == FADE_NOT)
      return;
    if(this->image == NULL)
      return;
    if(this->alpha == 0)
      return;

    alpha = this->image->getAlpha();
    this->image->setAlpha(this->alpha);
    this->image->draw(corner, image);
    this->image->setAlpha(alpha);
  }


  ImageFading &ImageFading::operator=(const ImageFading &imagefading)
  {
    load(imagefading);
    return *this;
  }


  void ImageFading::init()
  {
    image = NULL;
  }


}
