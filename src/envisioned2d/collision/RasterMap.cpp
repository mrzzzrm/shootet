#include "./RasterMap.hpp"

#include "./PixelMap.hpp"
#include "./RectMap.hpp"

using namespace std;

using namespace geo;
using namespace error;
using namespace etc;

using namespace collision;


#define is_cell(x, y) ( b_is(this->map[(y)][(x)>>3], (x)%8) )
#define is_cell_on_map(map, x, y) ( b_is((map)[(y)][(x)>>3], (x)%8) )
#define set_cell(x, y, is) ( b_set(this->map[(y)][(x)>>3], (x)%8, (is)) )
#define set_cell_on_map(map, x, y, is) (b_set((map)[(y)][(x)>>3], (x)%8, (is)))


/*
  Class RasterMap
*/

  RasterMap::RasterMap()
  {
    init();
  }


  RasterMap::RasterMap(const geo::IntSize &mapsize, const geo::IntSize &cellsize)
  {
    init();
    load(mapsize, cellsize);
  }


  RasterMap::RasterMap(const RasterMap &rastermap)
  {
    init();
    load(rastermap);
  }


  RasterMap::~RasterMap()
  {
    clear();
  }


  void RasterMap::load(const geo::IntSize &mapsize, const geo::IntSize &cellsize)
  {
    clear();
    setMapSize(mapsize);
    setCellSize(cellsize);
  }


  void RasterMap::load(const RasterMap &rastermap)
  {
    if(&rastermap == this)
      return;

    clear();

    setMapSize(rastermap.mapsize);
    setCellSize(rastermap.cellsize);

    /* Copy content */
    for(int y = 0; y < rastermap.mapsize.getHeight(); y++)
    {
      for(int x = 0; x < rastermap.mapsize.getWidth(); x++)
      {
        if(is_cell_on_map(rastermap.map, x, y))
          set_cell(x, y, 1);
      }
    }
  }


  void RasterMap::clear()
  {
    clearDynamicData();

    mapsize.clear();
    cellsize.clear();

    init();
  }


  const IntSize &RasterMap::getMapSize() const
  {
    return mapsize;
  }


  void RasterMap::setMapSize(const IntSize &mapsize)
  {
    u8 **nmap;

    if(mapsize != 0)
    {
      /* Create new map */
      nmap = new u8*[mapsize.getHeight()];
      for(int y = 0; y < mapsize.getHeight(); y++)
      {
        int linelength = mapsize.getWidth()%8 == 0 ? mapsize.getWidth()/8 : mapsize.getWidth()/8 + 1;

        nmap[y] = new u8[linelength];
          memset(nmap[y], 0, sizeof(*nmap[y]) * linelength);
      }

      /* Copy content */
      if(nmap != NULL)
      {
        for(int y = 0; y < this->mapsize.getHeight() && y < mapsize.getHeight(); y++)
        {
          for(int x = 0; x < this->mapsize.getWidth() && x < mapsize.getWidth(); x++)
          {
            if(is_cell(x, y))
              set_cell_on_map(nmap, x, y, 1);
          }
        }
      }

      /* Clear old content */
      if(map != NULL)
      {
        for(int y = 0; y < mapsize.getHeight(); y++)
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

    this->mapsize = mapsize;
  }


  const IntSize &RasterMap::getCellSize() const
  {
    return cellsize;
  }


  void RasterMap::setCellSize(const IntSize &mapsize)
  {
    this->cellsize = mapsize;
  }



  void RasterMap::setCell(const IntPoint &cell, bool is)
  {
    if(!is_point_in_size(cell, mapsize))
      return;

    set_cell(cell.getX(), cell.getY(), is);
  }


  bool RasterMap::isCell(const IntPoint &cell) const
  {
    if(!is_point_in_size(cell, mapsize))
      return false;

    return is_cell(cell.getX(), cell.getY());
  }


  bool RasterMap::isCollision(const RasterMap &rastermap2, const IntPoint &pos1, const IntPoint &pos2,const IntRect &rect1, const IntRect &rect2, const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
  {
    int br, bb;
    int rm1x, rm1y, rm2x, rm2y;
    int fr1x, fr1y, fr2x, fr2y;
    int fc1x, fc1y, lc1x, lc1y;
    int fc2x, fc2y, lc2x, lc2y;
    IntPoint corner1(pos1), corner2(pos2);
    IntRect framerect1, framerect2;
    IntRect mrect1, mrect2;
    IntRect *cutrect;



    /* Align */
      if(alignment1.getX() != 0) corner1.decX((int)(mrect1.getWidth() * alignment1.getX()));
      if(alignment1.getY() != 0) corner1.decY((int)(mrect1.getHeight() * alignment1.getY()));
      if(alignment2.getX() != 0) corner2.decX((int)(mrect2.getWidth() * alignment2.getX()));
      if(alignment2.getY() != 0) corner2.decY((int)(mrect2.getHeight() * alignment2.getY()));


    /* Framerects */
      framerect1.load(corner1.getX(), corner1.getY(), mrect1.getWidth(), mrect1.getHeight());
      framerect2.load(corner2.getX(), corner2.getY(), mrect2.getWidth(), mrect2.getHeight());


    /* Break */
      if(cellsize == 0 || rastermap2.cellsize == 0)
        return false;
      if(mapsize == 0 || rastermap2.mapsize == 0)
        return false;


    /* Clipping check */
      if(!size_to_rect(mapsize * cellsize).isCovering(mrect1))
        throw Exception() << "rastermap1 doesnt fully cover rect";
      if(!size_to_rect(rastermap2.mapsize * rastermap2.cellsize).isCovering(mrect2))
        throw Exception() << "rastermap2 doesnt fully cover rect";


    /* Get cutrect */
      if((cutrect = framerect1.getCutrect(framerect2)) == NULL)
        return false;


    /* Corners of both rastermaps */
      rm1x = corner1.getX() - mrect1.getX();
      rm1y = corner1.getY() - mrect1.getY();
      rm2x = corner2.getX() - mrect2.getX();
      rm2y = corner2.getY() - mrect2.getY();


    /* First pixel of cutrect relative to map */
      fr1x = cutrect->getX() - rm1x;
      fr1y = cutrect->getY() - rm1y;
      fr2x = cutrect->getX() - rm2x;
      fr2y = cutrect->getY() - rm2y;


    /* First/last cell */
      fc1x = fr1x / cellsize.getWidth();
      fc1y = fr1y / cellsize.getHeight();
      lc1x = (fr1x + cutrect->getWidth() - 1) / cellsize.getWidth();
      lc1y = (fr1y + cutrect->getHeight() - 1) / cellsize.getHeight();


    /* Borders of last cell on second rastermap that are still covered by rm1 */
    /* Not needed if axis is 0 */
      if(lc1x != fc1x)
        br = cellsize.getWidth() - ((lc1x - fc1x + 1) * cellsize.getWidth() - cutrect->getWidth() - (fr1x - fc1x * cellsize.getWidth()));
      else
        br = 0; // To avoid warnings

      if(lc1y != fc1y)
        bb = cellsize.getHeight() - ((lc1y - fc1y + 1) * cellsize.getHeight() - cutrect->getHeight() - (fr1y - fc1y * cellsize.getHeight()));
      else
        bb = 0; // To avoid warnings


    /* Iterate cells */
      for(int cy = fc1y, rgy = cutrect->getY() - rm2y; cy <= lc1y; cy++)
      {
        for(int cx = fc1x, rgx = cutrect->getX() - rm2x; cx <= lc1x; cx++)
        {

          if(is_cell(cx, cy))
          {
            /* Get checking range */
              fc2x = rgx / rastermap2.cellsize.getWidth();
              fc2y = rgy / rastermap2.cellsize.getHeight();

              if(cx == lc1x)
              {
                if(cx == fc1x)
                  lc2x = (rgx + cutrect->getWidth()) / rastermap2.cellsize.getWidth();
                else
                  lc2x = (rgx + br) / rastermap2.cellsize.getWidth();
              }
              else
                lc2x = (rgx + cellsize.getWidth()) / rastermap2.cellsize.getWidth();

              if(cy == lc1y)
              {
                if(cy == fc1y)
                  lc2y = (rgy + cutrect->getHeight()) / rastermap2.cellsize.getHeight();
                else
                  lc2y = (rgy + bb) / rastermap2.cellsize.getHeight();
              }
              else
                lc2y = (rgy + cellsize.getHeight()) / rastermap2.cellsize.getHeight();


            /* Do checking */
              for(int cy = fc2y; cy <= lc2y; cy++)
              {
                for(int cx = fc2x; cx <= lc2x; cx++)
                {
                  if(rastermap2.map[cy][cx>>3] & (1 << (cx%8)))
                  {
                    delete cutrect;
                    return true;
                  }

                }
              }

          }

          /* Inc iterator */
            if(cx == fc1x)
              rgx += cellsize.getWidth() - fr1x%cellsize.getWidth();
            else
              rgx += cellsize.getWidth();
        }


        /* Inc iterator */
          if(cy == fc1y)
            rgy += cellsize.getHeight() - fr1y%cellsize.getHeight();
          else
            rgy += cellsize.getHeight();
      }


    /* Delete cutrect */
      delete cutrect;

    return false;
  }


  bool RasterMap::isCollision(const PixelMap &pixelmap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    return pixelmap.isCollision(*this, pos2, pos1, rect2, rect1, alignment2, alignment1);
  }


  bool RasterMap::isCollision(const RectMap &rectmap, const IntPoint &pos1, const IntPoint &pos2, const IntRect &rect1, const IntRect &rect2, const Alignment &alignment1, const Alignment &alignment2) const
  {
    return rectmap.isCollision(*this, pos2, pos1, rect2, rect1, alignment2, alignment1);
  }


  RasterMap &RasterMap::operator=(const RasterMap &rastermap)
  {
    load(rastermap);
    return *this;
  }


  void RasterMap::init()
  {
    map = NULL;
  }


  void RasterMap::clearDynamicData()
  {
    if(map != NULL)
    {
      for(int y = 0; y < mapsize.getHeight(); y++)
      {
        delete map[y];
      }
      delete map;
    }
  }

