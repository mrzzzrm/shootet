#include "./Animation.hpp"

using namespace std;

using namespace geo;
using namespace xml;
using namespace etc;
using namespace error;
using namespace util;




namespace gfx
{

  Animation::Animation()
  {
    init();
  }

  Animation::Animation(const util::Path &xmlpath)
  {
    init();
    load(xmlpath);
  }


  Animation::Animation(const Animation &animation)
  {
    init();
    load(animation);
  }


  Animation::~Animation()
  {
    clear();
  }


  void Animation::load(const util::Path &xmlpath)
  {
    bool has_global_imagepath;
    Frame *frame;

    std::map<util::Path, Image*> imagemap;
    util::Path xmldir;
    util::Path global_imagepath;
    Xml xml;


    clear();

    /* Open XML */
    try
    {
      xml.load(xmlpath);
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading xml: " << exception.getDescription();
    }


    /* Root block */
    if(!xml.toRootBlock("animation"))
    {
      throw Exception() << "Cannot find root block 'animation' in document " << xmlpath;
    }


    /* Get dir of the xml for relative locations */
    xmldir = xmlpath.getDirectory();


    /* Load Data */
      /* Image */
      if(xml.toSubBlock("image"))
      {
        if(xml.isString("path"))
        {
          has_global_imagepath = true;
            global_imagepath = xmldir;
            global_imagepath.append(xml.getString("path"));

          xml.toBaseBlock();
        }
        else
        {
          throw Exception() << "Missing or wrong typed attribute 'path' in block 'image' in document "  << xmlpath;
        }
      }
      else
      {
        has_global_imagepath = false;
      }


      /* Offset */
      if(xml.toSubBlock("offset"))
      {
        if((!xml.hasAttribute("x") || xml.isInteger("x")) || (!xml.hasAttribute("y") || xml.isInteger("y")))
        {
          offset.setX(xml.getInteger("x"));
          offset.setY(xml.getInteger("y"));

          xml.toBaseBlock();
        }
        else
        {
          throw Exception() << "Wrong typed attribute in 'offset' in document "  << xmlpath;
        }
      }
      else
      {
        offset.setX(0);
        offset.setY(0);
      }



      /* Frames */
      if(xml.toSubBlock("frame"))
      {
        int ms;
        util::Path imagepath;
        IntVector offset;
        IntRect rect;


        /* Iterate */
        for(int currentframe = 0; currentframe > 0 ? xml.toNextBlock("frame") : true; currentframe++)
        {
          /* Time */
          if(xml.toSubBlock("time"))
          {
            if(xml.isInteger("ms"))
            {
              ms = xml.getInteger("ms");

              xml.toBaseBlock();
            }
            else
            {
              throw Exception() << "Missing or wrong typed attribute 'ms' in block 'duration' in frame '" << currentframe << "' in document " << xmlpath;
            }
          }
          else
          {
            ms = 1;
          }


          /* Image */
          if(xml.toSubBlock("image"))
          {
            if(xml.isString("path"))
            {
              imagepath = xmldir;
              imagepath.append(xml.getString("path"));

              xml.toBaseBlock();
            }
            else
            {
              throw Exception() << "Missing or wrong typed attribute 'path' in block 'image' in frame '" << currentframe << "' in  document "<< xmlpath;
            }
          }
          else
          {
            if(has_global_imagepath)
            {
              imagepath = global_imagepath;
            }
            else
            {
              throw Exception() << "No imagepath defined in 'frame' '" << currentframe << "' in document " << xmlpath;
            }
          }


          /* OffSet */
          if(xml.toSubBlock("offset"))
          {
            if((!xml.hasAttribute("x") || xml.isInteger("x")) || (!xml.hasAttribute("y") || xml.isInteger("y")))
            {
              offset.setX(xml.getInteger("x"));
              offset.setY(xml.getInteger("y"));

              xml.toBaseBlock();
            }
            else
            {
              throw Exception() << "Wrong typed attribute in 'offset' of 'frame' '" << currentframe << "' in document " << xmlpath;
            }
          }
          else
          {
            offset.setX(0);
            offset.setY(0);
          }


          /* BlitRect */
          if(xml.toSubBlock("rect"))
          {
            if(xml.isInteger("x") && xml.isInteger("y") && xml.isInteger("w") && xml.isInteger("h"))
            {
              rect.setX(xml.getInteger("x"));
              rect.setY(xml.getInteger("y"));
              rect.setWidth(xml.getInteger("w"));
              rect.setHeight(xml.getInteger("h"));

              xml.toBaseBlock();
            }
            else
            {
              throw Exception() << "Missing or wrong typed attribute in 'rect' of 'frame' '" << currentframe << "' in document " << xmlpath;
            }
          }
          else
          {
            throw Exception() << "No 'rect' defined in 'frame' '" << currentframe << "' in document " << xmlpath;
          }


          /* Load */
          try
          {
            Image *image;

            if(imagemap[imagepath] == NULL)
            {
              image = new Image(imagepath);
                imagelist.push_back(image);
                imagemap[imagepath] = image;
            }
            else
            {
              image = imagemap[imagepath];
            }

            frame = new Frame(image, rect, ms, offset);
          }
          catch(Exception &exception)
          {
            throw Exception() << "Error in frame '"  << currentframe << "': '" << exception.getDescription() << "' in document " << xmlpath;
          }

          this->frame.list.push_back(frame);
        }


        /* Return to 'animation' block */
        xml.toBaseBlock();
      }


    /* Init poll */
    this->frame.current = this->frame.list.front();
    this->frame.poll = this->frame.list.begin();
  }


  void Animation::load(const Animation &animation)
  {
    if(&animation == this)
      return;


    std::map<const Image*, Image*> imagemap;


    clear();

    path = animation.path;
    offset = animation.offset;
    timer = animation.timer;


    for(list<Image*>::const_iterator i = animation.imagelist.begin(); i != animation.imagelist.end(); i++)
    {
      Image *image = new Image(*(*i));

      imagemap[*i] = image;
      imagelist.push_back(image);
    }


    for(list<Frame*>::const_iterator i = animation.frame.list.begin(); i != animation.frame.list.end(); i++)
    {
      Image *image;

      if(imagemap[(*i)->getImage()] == NULL)
      {
        image = new Image(*((*i)->getImage()));
          imagelist.push_back(image);
          imagemap[(*i)->getImage()] = image;
      }
      else
      {
        image = imagemap[(*i)->getImage()];
      }


      frame.list.push_back(new Frame(image, *(*i), (*i)->getMilliseconds(), (*i)->getOffset()));

      if(animation.frame.current == *i)
      {
        frame.current = frame.list.back();
        frame.poll = frame.list.end();
          frame.poll--;
      }
    }
  }


  void Animation::clear()
  {
    list_delete_all_and_clear(frame.list);
    list_delete_all_and_clear(imagelist);

    path.clear();
    offset.clear();
    timer.clear();

    init();
  }


  const util::Path &Animation::getPath() const
  {
    return path;
  }


  const IntVector &Animation::getOffset() const
  {
    return offset;
  }


  void Animation::setOffset(const IntVector &offset)
  {
    this->offset = offset;
  }


  int Animation::getFrameCount() const
  {
    return frame.list.size();
  }


  Frame &Animation::getFrame(int index)
  {
    list<Frame*>::const_iterator i;

    if(index < 0)
      index = this->frame.list.size() + index + 1;

    if(index >= (int)frame.list.size())
      throw Exception() << "No such frame with index '" << index << "', framecoun is '" << frame.list.size() << "'";

    i = frame.list.begin();
      advance(i, index);

    return *(*i);
  }


  const Frame &Animation::getFrameConst(int index) const
  {
    list<Frame*>::const_iterator i;

    if(index < 0)
      index = this->frame.list.size() + index + 1;

    if(index >= (int)frame.list.size())
      throw Exception() << "No such frame with index '" << index << "', listlength is '" << frame.list.size() << "'";

    i = frame.list.begin();
      advance(i, index);

    return *(*i);
  }


  Frame &Animation::getCurrentFrame()
  {
    update();

    if(frame.current)
      return *frame.current;
    else
      throw Exception() << "No frames";
  }


  Frame &Animation::getCurrentFrameConst()
  {
    if(frame.current)
      return *frame.current;
    else
      throw Exception() << "No frames/loop not started";
  }


  void Animation::addFrame(const Frame &frame, int index)
  {
    list<Frame*>::iterator i;

    i = this->frame.list.begin();

    if(index < 0)
      index = this->frame.list.size() + index + 1;

    if(index > (int)(this->frame.list.size()))
        throw Exception() << "Cannot insert frame at index '" << index << "', listlength is '" << this->frame.list.size() << "'";

    advance(i, index);

    this->frame.list.insert(i, new Frame(frame));
  }


  int Animation::getLoopCount() const
  {
    return loopcount;
  }


  void Animation::reset()
  {
    resetLoop();
    loopcount = 0;
  }


  void Animation::resetLoop()
  {
    timer.reset();

    frame.current = frame.list.front();
    frame.poll = frame.list.begin();
    frame.elapsed = 0;
  }


  void Animation::resetFrame()
  {
    frame.elapsed = 0;
  }


  void Animation::update()
  {
    if(frame.current == NULL)
    {
      frame.current = frame.list.front();

      if(frame.current == NULL)
        return;
      else
        frame.poll = frame.list.begin();
    }

   if(frame.list.size() < 2)
      return;

   timer.update();
   frame.elapsed += timer.getPeriod();

    while(true)
    {
      if(frame.current->getMilliseconds() >= frame.elapsed || frame.current->getMilliseconds() < 0)
        break;

      frame.elapsed -= frame.current->getMilliseconds();

      if(++frame.poll == frame.list.end())
      {
        loopcount++;
        frame.poll = frame.list.begin();
      }

      frame.current = *frame.poll;
    }

  }


  void Animation::draw(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image)
  {
    update();

    if(frame.current != NULL)
      frame.current->draw(pos + offset, alignment, rect, image);
  }


  void Animation::draw(const geo::IntPoint &corner, Image *image )
  {
    update();

    if(frame.current != NULL)
      frame.current->draw(corner + offset, image);
  }


  void Animation::drawConst(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image) const
  {
    if(frame.current != NULL)
      frame.current->draw(pos + offset, alignment, rect, image);
  }


  void Animation::drawConst(const geo::IntPoint &corner, Image *image) const
  {
    if(frame.current != NULL)
      frame.current->draw(corner + offset, image);
  }


  Animation &Animation::operator=(const Animation &animation)
  {
    load(animation);
    return *this;
  }


  void Animation::init()
  {
    frame.current = NULL;
    frame.elapsed = 0;
    loopcount = 0;
  }


}


