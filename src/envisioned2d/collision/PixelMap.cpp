#include "./PixelMap.hpp"

#include "./RasterMap.hpp"
#include "./RectMap.hpp"


using namespace std;

using namespace geo;
using namespace gfx;
using namespace util;
using namespace etc;
using namespace error;

#define is_pixel(x, y) ( b_is(this->map[(y)][(x)>>3], (x)%8) )
#define is_pixel_on_map(map, x, y) ( b_is((map)[(y)][(x)>>3], (x)%8) )
#define set_pixel(x, y, is) ( b_set(this->map[(y)][(x)>>3], (x)%8, (is)) )
#define set_pixel_on_map(map, x, y, is) (b_set((map)[(y)][(x)>>3], (x)%8, (is)))


namespace collision
{
  PixelMap::PixelMap()
  {
    init();
  }


  PixelMap::PixelMap(const Path &path)
  {
    init();
    load(path);
  }


  PixelMap::PixelMap(const gfx::Image &image)
  {
    init();
    load(image);
  }


  PixelMap::PixelMap(const PixelMap &pixelmap)
  {
    init();
    load(pixelmap);
  }

  PixelMap::PixelMap(const IntSize &size)
  {
    init();
    load(size);
  }


  PixelMap::~PixelMap()
  {
    clear();
  }


  void PixelMap::load(const Path &imagepath)
  {
    Image image;

    try
    {
      image.load(imagepath);
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading image: " << exception.getDescription();
    }

    load(image);
  }


  void PixelMap::load(const Image &image)
  {
    clear();

    size = image.getSize();

    map = new u8*[size.getHeight()];

    for(int y = 0; y < size.getHeight(); y++)
    {
      int linelength;

      linelength = size.getWidth()%8 == 0 ? size.getWidth()/8 : size.getWidth()/8 + 1;

      map[y] = new u8[linelength];
        memset(map[y], 0, sizeof(*map[y]) * linelength);

      for(int x = 0; x < size.getWidth(); x++)
      {
        if(!image.hasColorkey())
          set_pixel(x, y, 1);
        else if(image.getPixel(IntPoint(x, y)) != image.getColorkey())
          set_pixel(x, y, 1);
      }
    }

  }


  void PixelMap::load(const PixelMap &pixelmap)
  {
    if(&pixelmap == this)
      return;

    clear();

    size = pixelmap.size;

    if(pixelmap.map != NULL)
    {
      map = new u8*[size.getHeight()];

      for(int y = 0; y < size.getHeight(); y++)
      {
        int linelength;

        linelength = size.getWidth()%8 == 0 ? size.getWidth()/8 : size.getWidth()/8 + 1;

        map[y] = new u8[linelength];
          memset(map[y], 0, sizeof(*map[y]) * linelength);

        for(int x = 0; x < size.getWidth(); x++)
        {
          if(is_pixel_on_map(pixelmap.map, x, y))
            set_pixel(x, y, 1);
        }
      }
    }
  }


  void PixelMap::load(const IntSize &size)
  {
    clear();
    setSize(size);
  }


  void PixelMap::clear()
  {
    if(map != NULL)
    {
      for(int y = 0; y < size.getHeight(); y++)
      {
        delete map[y];
      }
      delete map;
    }

    size.clear();

    init();
  }



  const IntSize &PixelMap::getSize() const
  {
    return size;
  }


  void PixelMap::setSize(const IntSize &size)
  {
    u8 **nmap;

    if(size != 0)
    {
      /* Create new map */
      nmap = new u8*[size.getHeight()];
      for(int y = 0; y < size.getHeight(); y++)
      {
        int linelength = size.getWidth()%8 == 0 ? size.getWidth()/8 : size.getWidth()/8 + 1;

        nmap[y] = new u8[linelength];
          memset(nmap[y], 0, sizeof(*nmap[y]) * linelength);
      }

      /* Copy content */
      if(nmap != NULL)
      {
        for(int y = 0; y < this->size.getHeight() && y < size.getHeight(); y++)
        {
          for(int x = 0; x < this->size.getWidth() && x < size.getWidth(); x++)
          {
            if(is_pixel(x, y))
              set_pixel_on_map(nmap, x, y, 1);
          }
        }
      }

      /* Clear old content */
      if(map != NULL)
      {
        for(int y = 0; y < size.getHeight(); y++)
        {
          delete map[y];
        }
        delete map;
      }

      /* Swap */
      map = nmap;
    }
    else
    {
      map = NULL;
    }

    this->size = size;
  }


  bool PixelMap::isPixel(const IntPoint &pixel)
  {
    if(pixel.getX() >= size.getWidth() || pixel.getY() >= size.getHeight() || pixel.getX() < 0 || pixel.getY() < 0)
      return false;

    return is_pixel(pixel.getX(), pixel.getY());
  }


  void PixelMap::setPixel(const IntPoint &pixel, bool is)
  {
    if(pixel.getX() >= size.getWidth() || pixel.getY() >= size.getHeight() || pixel.getX() < 0 || pixel.getY() < 0)
      return;

    set_pixel(pixel.getX(), pixel.getY(), is);
  }


  bool PixelMap::isCollision(const PixelMap &pixelmap2, const IntPoint &pos1, const IntPoint &pos2, const geo::IntRect &rect1, const geo::IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    int fp1x, fp1y, fp2x, fp2y; /* First pixel to check */
    int cw, ch; /* Sizes of the rect to check on both maps */
    IntPoint corner1(pos1), corner2(pos2);
    IntRect mrect1, mrect2;
    IntRect framerect1, framerect2;
    IntRect *cutrect;


    /* Break */
      if(map == NULL)
        return false;


    /* Translate negative axises */
      mrect1 = rect_translate_negative_axises(rect1, size);
      mrect2 = rect_translate_negative_axises(rect2, pixelmap2.size);


    /* Align */
      if(alignment1.getX() != 0) corner1.decX((int)(mrect1.getWidth() * alignment1.getX()));
      if(alignment1.getY() != 0) corner1.decY((int)(mrect1.getHeight() * alignment1.getY()));
      if(alignment2.getX() != 0) corner2.decX((int)(mrect2.getWidth() * alignment2.getX()));
      if(alignment2.getY() != 0) corner2.decY((int)(mrect2.getHeight() * alignment2.getY()));


    /* Framerects */
      framerect1.load(corner1.getX(), corner1.getY(), mrect1.getWidth(), mrect1.getHeight());
      framerect2.load(corner2.getX(), corner2.getY(), mrect2.getWidth(), mrect2.getHeight());



    /* Break */
      if(!IntRect(0, 0, size.getWidth(), size.getHeight()).isCovering(mrect1))
        throw Exception() << "pixelmap1 doesn't fully cover rect";
      if(!IntRect(0, 0, pixelmap2.size.getWidth(), pixelmap2.size.getHeight()).isCovering(mrect2))
        throw Exception() << "pixelmap2 doesn't fully cover rect";


    /* Cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* Get first pixels and size to check */
      cw = cutrect->getWidth();
      ch = cutrect->getHeight();
      fp1x = cutrect->getX() - (framerect1.getX() - mrect1.getX());
      fp1y = cutrect->getY() - (framerect1.getY() - mrect1.getY());
      fp2x = cutrect->getX() - (framerect2.getX() - mrect2.getX());
      fp2y = cutrect->getY() - (framerect2.getY() - mrect2.getY());

      /* Delete cutrect */
        delete cutrect;


    /* Compare Pixels */
      for(int py = 0; py < ch; py++)
      {
        for(int px = 0; px < cw; px++)
        {
          if(is_pixel_on_map(map, px + fp1x, py + fp1y) && is_pixel_on_map(pixelmap2.map, px + fp2x, py + fp2y))
            return true;
        }
      }


    /* No collision detected */
      return false;
  }


  bool PixelMap::isCollision(const RectMap &rectmap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    IntPoint corner1(pos1), corner2(pos2);
    IntRect framerect1, framerect2;
    IntRect mrect1, mrect2;
    IntRect *cutrect;


    /* Break */
      if(map == NULL)
        return false;


    /* Translate negative axises */
      mrect1 = rect_translate_negative_axises(rect1, size);
      mrect2 = rect_translate_negative_axises(rect2, rectmap.getSize());


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
        throw Exception() << "pixelmap1 doesn't fully cover rect";


    /* Cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* Iterate rects, check pixels */
      for(int r = 0; r < rectmap.getRectCount(); r++)
      {
        int fpx, fpy; /* First pixel to check */
        int lpx, lpy; /* Last pixel to check */

        IntRect srect = rectmap.getRect(r) + point_to_vector(corner2) - IntVector(mrect2.getX(), mrect2.getY());
        IntRect *scutrect;


        /* Clip with cutrect*/
          if((scutrect = srect.getCutrect(*cutrect)) == NULL)
            continue;


        /* Pixels to check */
          fpx = scutrect->getX() - (corner1.getX() - mrect1.getX());
          fpy = scutrect->getY() - (corner1.getY() - mrect1.getY());
          lpx = fpx + scutrect->getWidth() - 1;
          lpy = fpy + scutrect->getHeight() - 1;


        /* Check pixels */
          for(int py = fpy; py <= lpy; py++)
          {
            for(int px = fpx; px <= lpx; px++)
            {
              if(is_pixel(px, py))
              {
                /* Free mem */
                  delete cutrect;
                  delete scutrect;

                /* Collision detected */
                  return true;
              }
            }
          }

        delete scutrect;
      }

    delete cutrect;


    return false;

  }


  bool PixelMap::isCollision(const RasterMap &rastermap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    int fpx, fpy; /* First pixel to check */
    int lpx, lpy; /* Last pixel to check */
    int frx, fry; /* First pixel relative to rastermap */
    IntPoint corner1(pos1), corner2(pos2);
    IntRect framerect1, framerect2;
    IntRect mrect1, mrect2;
    IntRect *cutrect;


    /* Break */
      if(map == NULL)
        return false;


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
        throw Exception() << "pixelmap doesn't fully cover rect";
      if(!size_to_rect(rastermap.getMapSize() * rastermap.getCellSize()).isCovering(mrect2))
        throw Exception() << "rastermap doesn't fully cover rect";


   /* Cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* First / last pixel to check on pixelmap */
      fpx = cutrect->getX() - (corner1.getX() - mrect1.getX());
      fpy = cutrect->getY() - (corner1.getY() - mrect1.getY());

      lpx = fpx + cutrect->getWidth() - 1;
      lpy = fpy + cutrect->getHeight() - 1;


    /* Get first pixel relative to rastermap */
      frx = cutrect->getX() - (corner2.getX() - mrect2.getX());
      fry = cutrect->getY() - (corner2.getY() - mrect2.getY());


    /* Delete cutrect */
      delete cutrect;


    /* Iterate pixels */
      for(int py = fpy, ry = fry; py <= lpy; py++, ry++)
      {
        for(int px = fpx, rx = frx; px <= lpx; px++, rx++)
        {
          if(is_pixel(px, py))
          {
            int cx, cy;

            /* Get cell */
              cx = rx / rastermap.getCellSize().getWidth();
              cy = ry / rastermap.getCellSize().getHeight();

            /* Check */
              if(rastermap.isCell(IntPoint(cx, cy)))
              {
                return true;
              }
              else
              {
                int add = rastermap.getCellSize().getWidth() - (rx % rastermap.getCellSize().getWidth());
                  rx += add;
                  px += add;
              }
          }

        }
      }



    return false;
  }


  PixelMap &PixelMap::operator=(const PixelMap &pixelmap)
  {
    load(pixelmap);
    return *this;
  }


  void PixelMap::init()
  {
    map = NULL;
  }



}


