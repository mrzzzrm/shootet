#include "./RectMap.hpp"

#include "./PixelMap.hpp"
#include "./RasterMap.hpp"

using namespace std;

using namespace util;
using namespace geo;
using namespace etc;
using namespace error;

using namespace collision;


/*
  Class RectMap
*/
  RectMap::RectMap()
  {

  }


  RectMap::RectMap(const RectMap &rectmap)
  {
    load(rectmap);
  }


  RectMap::~RectMap()
  {
    clear();
  }

  void RectMap::load(const RectMap &rectmap)
  {
    if(&rectmap == this)
      return;

    clear();

    size = rectmap.size;

    for(list<IntRect*>::const_iterator i = rectmap.rectlist.begin(); i != rectmap.rectlist.end(); i++)
    {
      rectlist.push_back(new IntRect(*(*i)));
    }
  }


  void RectMap::clear()
  {
    clearDynamicData();

    rectlist.clear();
    size.clear();
  }


  int RectMap::getRectCount() const
  {
    return rectlist.size();
  }


  const IntRect &RectMap::getRect(int index) const
  {
    list<IntRect*>::const_iterator i = rectlist.begin();

    /* Translate negative index */
      if(index < 0)
        index = rectlist.size() + index;

    /* Break */
      if(index > (int)rectlist.size() - 1)
        throw Exception() << "Out of bounds! There is no rect '" << index << "', listsize is " << rectlist.size() << "!";

    /* Advance iterator */
      advance(i, index);

    /* Return */
      return *(*i);
  }


  int RectMap::addRect(const IntRect &rect)
  {
    IntRect *addrect;

    addrect = new IntRect(rect);
    addrect->normalise();

    if(clipRect(addrect))
    {
      rectlist.push_back(addrect);
      return rectlist.size() - 1;
    }
    else
    {
      return -1;
    }
  }


  void RectMap::removeRect(int index)
  {
    list<IntRect*>::iterator i = rectlist.begin();


    /* Translate negative index */
      if(index < 0);
        index = rectlist.size() + index;

    /* Break */
      if(index > (int)rectlist.size() - 1)
        throw Exception() << "Out of bounds! There is no rect '" << index << "', listsize is " << rectlist.size() << "!";

    /* Advance iterator */
      advance(i, index);

    /* Delete */
      rectlist.erase(i);
  }


  const IntSize &RectMap::getSize() const
  {
    return size;
  }


  void RectMap::setSize(const IntSize &size)
  {
    this->size = size;

    for(list<IntRect*>::iterator i = rectlist.begin(); i != rectlist.end();)
    {
      if(!clipRect(*i))
        i = list_erase_and_delete(rectlist, i);
      else
        i++;
    }
  }


  bool RectMap::isCollision(const RectMap &rectmap2, const IntPoint &pos1, const geo::IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const etc::Alignment &alignment2) const
  {
    IntPoint corner1(pos1), corner2(pos2);
    IntRect framerect1, framerect2;
    IntRect mrect1, mrect2;
    IntRect *cutrect;


    /* Translate negative axises */
      mrect1 = rect_translate_negative_axises(rect1, size);
      mrect2 = rect_translate_negative_axises(rect2, rectmap2.size);


    /* Align */
      if(alignment1.getX() != 0) corner1.decX((int)(mrect1.getWidth() * alignment1.getX()));
      if(alignment1.getY() != 0) corner1.decY((int)(mrect1.getHeight() * alignment1.getY()));
      if(alignment2.getX() != 0) corner2.decX((int)(mrect2.getWidth() * alignment2.getX()));
      if(alignment2.getY() != 0) corner2.decY((int)(mrect2.getHeight() * alignment2.getY()));


    /* Framerects */
      framerect1.load(corner1.getX(), corner1.getY(), mrect1.getWidth(), mrect1.getHeight());
      framerect2.load(corner2.getX(), corner2.getY(), mrect2.getWidth(), mrect2.getHeight());


    /* Cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* Iterate all rects */
      for(list<IntRect*>::const_iterator i1 = rectlist.begin(); i1 != rectlist.end(); i1++)
      {
        IntRect srect1 = *(*i1) + point_to_vector(corner1) - IntVector(mrect1.getX(), mrect1.getY());
        IntRect *scutrect1;

        /* Clip */
          if((scutrect1 = srect1.getCutrect(*cutrect)) == NULL)
            continue;


        /* Check for collision with all rects of rectmap 2 */
          for(list<IntRect*>::const_iterator i2 = rectmap2.rectlist.begin(); i2 != rectmap2.rectlist.end(); i2++)
          {
            IntRect srect2 = *(*i2) + point_to_vector(corner2) - IntVector(mrect2.getX(), mrect2.getY());
            IntRect *scutrect2;

            /* Clip */
              if((scutrect2 = srect2.getCutrect(*cutrect)) == NULL)
                continue;

            /* Check for collision */
              if(scutrect2->isCollision(*scutrect1))
              {
                /* Free mem */
                  delete cutrect;
                  delete scutrect1;
                  delete scutrect2;

                /* Collision detected */
                  return true;
              }


            /* Delete old cutrect */
              delete scutrect2;
          }

        /* Delete old cutrect */
          delete scutrect1;
      }


    /* Delete old cutrect */
      delete cutrect;

    /* Return */
      return false;
  }


  bool RectMap::isCollision(const PixelMap &pixelmap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    return pixelmap.isCollision(*this, pos2, pos1, rect2, rect1, alignment2, alignment1);
  }

  bool RectMap::isCollision(const RasterMap &rastermap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    IntPoint corner1(pos1), corner2(pos2);
    IntRect framerect1, framerect2;
    IntRect mrect1, mrect2;
    IntRect *cutrect;


    /* Translate negative axises */
      mrect1 = rect_translate_negative_axises(rect1, size);
      mrect2 = rect_translate_negative_axises(rect2, rastermap.getMapSize() * rastermap.getCellSize());


    /* Align */
      if(alignment1.getX() != 0) corner1.decX((int)(mrect1.getWidth() * alignment1.getX()));
      if(alignment1.getY() != 0) corner1.decY((int)(mrect1.getHeight() * alignment1.getY()));
      if(alignment2.getX() != 0) corner2.decX((int)(mrect2.getWidth() * alignment2.getX()));
      if(alignment2.getY() != 0) corner2.decY((int)(mrect2.getHeight() * alignment2.getY()));


    /* Framerects */
      framerect1.load(corner1.getX(), corner1.getY(), mrect1.getWidth(), mrect1.getHeight());
      framerect2.load(corner2.getX(), corner2.getY(), mrect2.getWidth(), mrect2.getHeight());

    /* Break */
      if(!size_to_rect(size).isCovering(mrect1))
        throw Exception() << "rectmap doesn't fully cover rect1";
      if(!size_to_rect(rastermap.getMapSize() * rastermap.getCellSize()).isCovering(mrect2))
        throw Exception() << "rastermap doesnt fully cover rect2";


    /* Global cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* Iterate all rects */
      for(list<IntRect*>::const_iterator i = rectlist.begin(); i != rectlist.end(); i++)
      {
        uint fcx, fcy;
        uint lcx, lcy;

        IntRect srect = *(*i) + point_to_vector(corner1) - IntVector(mrect1.getX(), mrect1.getY());
        IntRect *scutrect;

        /* Clip */
          if((scutrect = srect.getCutrect(*cutrect)) == NULL)
            continue;


        /* Cells to check */
          fcx = (scutrect->getX() - (corner2.getX() - mrect2.getX())) / rastermap.getCellSize().getWidth();
          fcy = (scutrect->getY() - (corner2.getY() - mrect2.getY())) / rastermap.getCellSize().getHeight();
          lcx = (scutrect->getX() - (corner2.getX() - mrect2.getX()) + scutrect->getWidth() - 1) / rastermap.getCellSize().getWidth();
          lcy = (scutrect->getY() - (corner2.getY() - mrect2.getY()) + scutrect->getHeight() - 1) / rastermap.getCellSize().getHeight();


        /* Check cells */
          for(uint cy = fcy; cy <= lcy; cy++)
          {
            for(uint cx = fcx; cx <= lcx; cx++)
            {
              if(rastermap.isCell(IntPoint(cx, cy)))
              {
                /* Free mem */
                  delete cutrect;
                  delete scutrect;

                /* Return */
                  return true;
              }
            }
          }


        /* Delete old cutrect */
          delete scutrect;
      }


    /* Delete old cutrect */
      delete cutrect;

    /* Return */
      return false;
  }


  bool RectMap::isCollision(const IntRect &rect2, const IntPoint &pos1, const IntRect &rect1, const Alignment &alignment1, const Alignment &alignment2) const
  {
    IntPoint corner1(pos1), corner2(rect2.getX(), rect2.getY());
    IntRect framerect1;
    IntRect mrect1;
    IntRect *cutrect;


    /* Translate negative axises */
      mrect1 = rect_translate_negative_axises(rect1, size);


    /* Align */
      if(alignment1.getX() != 0) corner1.decX((int)(mrect1.getWidth() * alignment1.getX()));
      if(alignment1.getY() != 0) corner1.decY((int)(mrect1.getHeight() * alignment1.getY()));
      if(alignment2.getX() != 0) corner2.decX((int)(rect2.getWidth() * alignment2.getX()));
      if(alignment2.getY() != 0) corner2.decY((int)(rect2.getHeight() * alignment2.getY()));


    /* Framerects */
      framerect1.load(corner1.getX(), corner1.getY(), mrect1.getWidth(), mrect1.getHeight());

    /* Break */
      if(!size_to_rect(size).isCovering(mrect1))
        throw Exception() << "rectmap doesn't fully cover rect1";


    /* Global cutrect */
      if((cutrect = framerect1.getCutrect(rect2)) == NULL)
        return false;


     /* Iterate all rects */
      for(list<IntRect*>::const_iterator i = rectlist.begin(); i != rectlist.end(); i++)
      {
        IntRect srect1 = *(*i) + point_to_vector(corner1) - IntVector(mrect1.getX(), mrect1.getY());
        IntRect *scutrect;

        /* Clip */
          if((scutrect = srect1.getCutrect(*cutrect)) == NULL)
            continue;


        /* Check coll */
          if(rect2.isCollision(*scutrect))
            return true;

        /* Delete old cutrect */
          delete scutrect;
      }


    /* Delete old cutrect */
      delete cutrect;

    /* Return */
      return false;
  }


  RectMap &RectMap::operator=(const RectMap &rectmap)
  {
    load(rectmap);
    return *this;
  }



  void RectMap::clearDynamicData()
  {
    for(list<IntRect*>::iterator i = rectlist.begin(); i != rectlist.end(); i++)
    {
      delete *i;
    }
  }

  bool RectMap::clipRect(IntRect *rect)
  {
    if(rect->getX() > size.getWidth())
      return false;

    if(rect->getY() > size.getHeight())
      return false;

    if(rect->getX() + rect->getWidth() > size.getWidth())
      rect->setWidth(size.getWidth() - rect->getX());

    if(rect->getY() + rect->getHeight() > size.getHeight())
      rect->setHeight(size.getHeight() - rect->getY());

    return true;
  }
