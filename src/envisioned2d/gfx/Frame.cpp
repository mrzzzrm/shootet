#include "./Frame.hpp"

using namespace std;

using namespace geo;
using namespace etc;


namespace gfx
{

  Frame::Frame()
  {
    init();
  }


  Frame::Frame(const Image *image, const geo::IntRect &rect, int ms, const geo::IntVector &offset)
  {
    init();
    load(image, rect, ms, offset);
  }


  Frame::Frame(const ImageClipping &imageclipping, int ms, const geo::IntVector &offset)
  {
    init();
    load(imageclipping, ms, offset);
  }


  Frame::Frame(const Frame &frame)
  {
    init();
    load(frame);
  }


  Frame::~Frame()
  {

  }


  void Frame::load(const Image *image, const geo::IntRect &rect, int ms, const geo::IntVector &offset)
  {
    clear();

    ImageClipping::load(image, rect);
    setMilliseconds(ms);
    this->offset = offset;
  }


  void Frame::load(const ImageClipping &imageclipping, int ms, const geo::IntVector &offset)
  {
    ImageClipping::load(imageclipping);

    setMilliseconds(ms);
    this->offset = offset;
  }


  void Frame::load(const Frame &frame)
  {
    if(&frame == this)
      return;

    clear();

    ImageClipping::load(frame);
    ms = frame.ms;
    offset = frame.offset;
  }


  void Frame::clear()
  {
    ImageClipping::clear();
    offset.clear();

    init();
  }


  int Frame::getMilliseconds() const
  {
    return ms;
  }


  void Frame::setMilliseconds(int ms)
  {
    if(ms == 0)
      this->ms = -1;
    else
      this->ms = ms;
  }


  const IntVector &Frame::getOffset() const
  {
    return offset;
  }


  void Frame::setOffset(const IntVector &offset)
  {
    this->offset = offset;
  }


  void Frame::draw(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image) const
  {
    ImageClipping::draw(pos + offset, alignment, rect, image);
  }


  void Frame::draw(const geo::IntPoint &corner, Image *image) const
  {
    ImageClipping::draw(corner + offset, image);
  }

  Frame &Frame::operator=(const Frame &frame)
  {
    load(frame);
    return *this;
  }

  void Frame::init()
  {
    ms = -1;
  }
}


