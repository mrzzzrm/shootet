#include "./Map.hpp"

using namespace std;

using namespace geo;
using namespace util;
using namespace etc;
using namespace gfx;
using namespace error;

using namespace tmx;
using namespace tmx::render;


/*
  Class Map
*/
  Map::Map()
  {

  }


  Map::Map(const Path &path)
  {
    load(path);
  }


  Map::Map(const base::Map &map)
  {
    load(map);
  }


  Map::~Map()
  {
    clear();
  }


  void Map::load(const Path &path)
  {
    clear();
    base::Map::load(path);
  }


  void Map::load(const base::Map &map)
  {
    if(&map == this)
      return;

    clear();
    base::Map::load(map);
  }


  void Map::clear()
  {
    tmx::base::Map::clear();
    clearDynamicData();
//    objectlinklist.clear();
  }


//  void Map::linkObject(object::Object &object, int tilelayer, OBJECT_DRAWMODE drawmode)
//  {
//    ObjectLink *objectlink;
//
//    /* Create link */
//      objectlink = new ObjectLink;
//        objectlink->object = &object;
//        objectlink->tilelayer = tilelayer;
//        objectlink->drawmode = drawmode;
//
//
//    /* Add link to list */
//      objectlinklist.push_back(objectlink);
//
//  }
//
//
//  void Map::unlinkObject(object::Object &object)
//  {
//    for(list<Map::ObjectLink*>::iterator i = objectlinklist.begin(); i != objectlinklist.end(); i++)
//    {
//      if(&object == (*i)->object)
//      {
//        list<Map::ObjectLink*>::iterator ti;
//
//        /* Create iterator pointing to previous element */
//          ti = i;
//            ti--;
//
//        /* Delete current link */
//          delete *i;
//            objectlinklist.erase(i);
//
//        /* Set iterator to previous element*/
//          i = ti;
//      }
//    }
//  }

  void Map::draw(const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, const etc::Alignment &alignment, gfx::Image *image)
  {
    int tw, th;
    int omtw, omth;
    IntRect btargetrect;
    IntSize target_size;
//    list<ObjectLink_TileLayer_pair> objectlinklist_by_tilelayer;
//    list<ObjectLink_Row_pair> objectlinklist_by_row;

    /* Target-size */
    if(image != NULL)
      target_size = image->getSize();
    else if(SDL_GetVideoSurface())
      target_size.load(SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);
    else
      return;


    /* Translate negative axises on targetrect */
      btargetrect = rect_translate_negative_axises(targetrect, target_size);

    /* Get layer tilesize */
      tw = getTileWidth();
      th = getTileHeight();


    /* Get overall maximum tilesize */
      omtw = tw;
      omth = th;

      for(int ts = 0; ts < getTilesetCount(); ts++)
      {
        /* Check if size is bigger */
          if(getTileset(ts).getTileWidth() > omtw)
            omtw = getTileset(ts).getTileWidth();
          if(getTileset(ts).getTileHeight() > omth)
            omth = getTileset(ts).getTileHeight();
      }


    /* Transfer all objectlinks from list to new list and sort this new one by layer */
//      for(list<ObjectLink*>::iterator i = objectlinklist.begin(); i != objectlinklist.end(); i++)
//      {
//        objectlinklist_by_tilelayer.push_back(ObjectLink_TileLayer_pair(*i, (*i)->tilelayer));
//      }
//      objectlinklist_by_tilelayer.sort();



    /* Draw layers */
      for(int l = 0, tl = 0; l < getLayerCount(); l++)
      {
        /* Continue */
          if(getLayer(l).getType() != base::LAYER_TILELAYER)
            continue;


        /* Draw */
            switch(getOrientation())
            {
              case base::ORTHOGONAL:
              {
                /* Search all objectlinks that are on this tilelayer & sort them by row */
//                  objectlinklist_by_row.clear();
//                  for(list<ObjectLink_TileLayer_pair>::iterator i = objectlinklist_by_tilelayer.begin(); i != objectlinklist_by_tilelayer.end(); i++)
//                  {
//                    if(i->second == (int)(tl))
//                    {
//                      /* Add to layer */
//                        if(i->first->object->getPosition().getX() + i->first->object->getPosition().getY() < 0)
//                          objectlinklist_by_row.push_back(ObjectLink_Row_pair(i->first, (int)(i->first->object->getPosition().getY() / th - 1)));
//                        else
//                          objectlinklist_by_row.push_back(ObjectLink_Row_pair(i->first, (int)(i->first->object->getPosition().getY() / th)));
//                    }
//                  }
//
//                  /* Sort links by row */
//                    objectlinklist_by_row.sort();


                /* Draw */
                  drawOrthogonalLayer(*dynamic_cast<const base::TileLayer*>(&getLayer(l)), btargetrect, sourcecorner, tw, th, omtw, omth/*, objectlinklist_by_row*/, image);
              }
              break;


              case base::ISOMETRIC:
              {
//                int axis;
//
//                /* Search all objectlinks that are on this tilelayer & sort them by row */
//                  axis = (int)(sqrt((tw/2) * (tw/2) + (th/2) * (th/2)));
//
//                  objectlinklist_by_row.clear();
//                  for(list<ObjectLink_TileLayer_pair>::iterator i = objectlinklist_by_tilelayer.begin(); i != objectlinklist_by_tilelayer.end(); i++)
//                  {
//                    if(i->second == (int)(tl))
//                    {
//                      /* Add to layer */
//                        if(i->first->object->getPosition().getY() < 0)
//                          objectlinklist_by_row.push_back(ObjectLink_Row_pair(
//                                                                              i->first,
//                                                                              (int)(i->first->object->getPosition().getX() / axis - 1) +
//                                                                              (int)(i->first->object->getPosition().getY() / axis - 1)));
//                        else
//                          objectlinklist_by_row.push_back(ObjectLink_Row_pair(
//                                                                              i->first,
//                                                                              (int)(i->first->object->getPosition().getX() / axis) +
//                                                                              (int)(i->first->object->getPosition().getY() / axis)));
//                    }
//                  }
//
//                  /* Sort links by row */
//                    objectlinklist_by_row.sort();


                /* Draw */
                  drawIsometricLayer(*dynamic_cast<const base::TileLayer*>(&getLayer(l)), btargetrect, sourcecorner, tw, th, omtw, omth/*, objectlinklist_by_row*/, image);
              }
              break;


              default:
              break;
            }


        /* Increase tilelayer-counter */
          tl++;
      }
  }


  void Map::drawTileLayer(int index, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, const etc::Alignment &alignment, gfx::Image *image)
  {
    int tw, th;
    int omtw, omth;
    IntRect btargetrect;
    IntSize target_size;
    const base::TileLayer &tilelayer = getTileLayerConst(index);


    /* Target-size */
    if(image != NULL)
      target_size = image->getSize();
    else if(SDL_GetVideoSurface())
      target_size.load(SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);
    else
      return;

    /* Translate negative axises on targetrect */
    btargetrect = rect_translate_negative_axises(targetrect, target_size);

    /* Tilesize */
    tw = getTileWidth();
    th = getTileHeight();


    /* Get overall maximum tilesize */
    omtw = tw;
    omth = th;

    for(int ts = 0; ts < getTilesetCount(); ts++)
    {
      if(getTileset(ts).getTileWidth() > omtw)
        omtw = getTileset(ts).getTileWidth();
      if(getTileset(ts).getTileHeight() > omth)
        omth = getTileset(ts).getTileHeight();
    }

    switch(getOrientation())
    {
      case base::ORTHOGONAL:
      {
        drawOrthogonalLayer(tilelayer, btargetrect, sourcecorner, tw, th, omtw, omth/*, objectlinklist_by_row*/, image);
      }
      break;


      case base::ISOMETRIC:
      {
        drawIsometricLayer(tilelayer, btargetrect, sourcecorner, tw, th, omtw, omth/*, objectlinklist_by_row*/, image);
      }
      break;


      default:
      break;
    }
  }


  void Map::drawOrthogonalLayer(const base::TileLayer &layer, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, int tw, int th, int omtw, int omth/*, list<ObjectLink_Row_pair> &objectlinklist_by_row*/, gfx::Image *image)
  {
    int ox, oy;
    int ftx, fty;
    int ltx, lty;
//    list<ObjectLink_Column_pair> objectlinklist_by_column;


    /* Get bounds and offset of tiles to draw */
      if((sourcecorner.getX() - (int)(omtw) + (int)(tw)) >= 0)
      {
        ftx = (sourcecorner.getX() - (int)(omtw) + (int)(tw)) / tw;
        ox = sourcecorner.getX() - ftx * tw;
      }
      else
      {
        ftx = 0;
        ox = sourcecorner.getX();
      }

      if(sourcecorner.getX() + targetrect.getWidth() < 0)
        return;
      else
        ltx = (sourcecorner.getX() + targetrect.getWidth()) / tw;

        if(ltx >= layer.getWidth())
          ltx = layer.getWidth() - 1;



      if(sourcecorner.getY() >= 0)
      {
        fty = sourcecorner.getY() / th;
        oy = sourcecorner.getY() - fty * th;
      }
      else
      {
         fty = 0;
         oy = sourcecorner.getY() ;
      }

      if(sourcecorner.getY() + targetrect.getHeight() + (int)(omth) - (int)(th) < 0)
        return;
      else
        lty = (sourcecorner.getY() + targetrect.getHeight() + (int)(omth) - (int)(th)) / th;

        if(lty >= layer.getHeight())
          lty = layer.getHeight() - 1;




    /* Draw rowwise */
      for(int ty = fty; ty <= lty; ty++)
      {
        /* Search all objectlinks that are on this row & sort them by column */
//          objectlinklist_by_column.clear();
//          for(list<ObjectLink_Row_pair>::iterator i = objectlinklist_by_row.begin(); i != objectlinklist_by_row.end(); i++)
//          {
//            if(i->second == (int)(ty) || (i->second < (int)(ty) && ty == fty) || (i->second > (int)(ty) && ty == lty))
//            {
//              /* Add to row */
//                if(i->first->object->getPosition().getX() < 0)
//                  objectlinklist_by_column.push_back(ObjectLink_Column_pair(i->first, (int)(i->first->object->getPosition().getX() / tw - 1)));
//                else
//                  objectlinklist_by_column.push_back(ObjectLink_Column_pair(i->first, (int)(i->first->object->getPosition().getX() / tw)));
//            }
//          }
//
//          /* Sort links by column */
//            objectlinklist_by_column.sort();


        /* Draw objects in this columns */
//          for(list<ObjectLink_Column_pair>::iterator i = objectlinklist_by_column.begin(); i != objectlinklist_by_column.end(); i++)
//          {
//            IntPoint position;
//            const gfx::Frame *frame;
//
//
//            /* Continue */
//              if(i->first->object->getState() == NULL || (frame = i->first->object->getState()->getAnimation().getCurrentFrame()) == NULL)
//                continue;
//
//            /* Get position */
//              position = i->first->object->getPosition();
//              position += i->first->object->getDrawOffset() +
//                        i->first->object->getState()->getDrawOffset() +
//                        frame->getOffset();
//
//            /* Draw */
//              if(i->first->drawmode == OBJECT_DRAW_BY_CORNER)
//              {
//                /* Break/Continue */
//                  if(
//                       position.getX() > sourcecorner.getX() + targetrect.getWidth() ||
//                       position.getY() > sourcecorner.getY() + targetrect.getHeight() ||
//                       position.getX() + (int)(frame->getWidth()) < sourcecorner.getX() ||
//                       position.getY() + (int)(frame->getHeight()) < sourcecorner.getY()
//                     )
//                      continue;
//
//
//                /* Draw */
//                  i->first->object->drawByCorner(IntVector(-sourcecorner.getX() + targetrect.getX(), -sourcecorner.getY() + targetrect.getY()));
//              }
//              else
//              {
//                /* Break/Continue */
//                  if(
//                       position.getX() - (int)(frame->getWidth())/2 > sourcecorner.getX() + targetrect.getWidth() ||
//                       position.getY() - (int)(frame->getHeight())/2 > sourcecorner.getY() + targetrect.getHeight() ||
//                       position.getX() + (int)(frame->getWidth())/2 < sourcecorner.getX() ||
//                       position.getY() + (int)(frame->getHeight())/2 < sourcecorner.getY()
//                     )
//                      continue;
//
//                /* Draw */
//                  i->first->object->drawByCenter(IntVector(-sourcecorner.getX() + targetrect.getX(), -sourcecorner.getY() + targetrect.getY()));
//              }
//
//          }


        /* Draw tile columns */
          for(int tx = ftx; tx <= ltx; tx++)
          {
            int gid;

            /* Get tile gid */
              gid = layer.getTile(tx, ty);


            /* Draw tile */
              if(gid != 0)
              {
                ImageClipping clipping;
                int x, y;


                /* ImageClipping */
                  clipping = getTileAsImageClipping(gid);


                /* Get position on image */
                  x = targetrect.getX() + (tx - ftx) * tw - ox ;
                  y = targetrect.getY() + (ty - fty) * th - oy + th - clipping.getHeight();


                /* Boundscheck */
                  if(
                      (x + (int)(clipping.getWidth()) < targetrect.getX()) ||
                      (y + (int)(clipping.getHeight())  < targetrect.getY()) ||
                      (x > targetrect.getX() + targetrect.getWidth()) ||
                      (y - (int)(clipping.getHeight()) + (int)(th) > targetrect.getY() + targetrect.getHeight())
                     )
                     continue;



                /* Draw */
                  clipping.draw(IntPoint(x, y));
              }
          }
      }
  }


  void Map::drawIsometricLayer(const base::TileLayer &layer, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, int tw, int th, int omtw, int omth/*, list<ObjectLink_Row_pair> &objectlinklist_by_row*/, gfx::Image *image)
  {
    int axis; // Iso axis of a tile
    int ftx, fty; // First tile to handle
    int sx, sy; // First tile in current line
    int tx, ty; // current tile
    double iox, ioy; // Offset sourcorner -> first isometric tile
    double ox, oy; // Offset sourcorner -> first tile corner
    u8  sd; // Step direction to move cursor of sx/sy
    double alpha; // Half of the angle between iso axises
    double _ox1, _oy1, _ox2, _oy2; // Orthogonal transformation of iso offset axises
    int iao; // Offset on iso axises caused by overall maximum tilesize != standart map
    int lr; // Last row
//    list<ObjectLink_Column_pair> objectlinklist_by_column;



    /* Get axis */
      axis = (int)(sqrt((tw/2) * (tw/2) + (th/2) * (th/2)));


    /* Get half of the angle between iso - axises */
      alpha = atan(static_cast<double>(th)/static_cast<double>(tw));


    /* Set offset to 0 to be able to take premodifications from first tile */
      ox = 0;
      oy = 0;


    /* Get additional checking offset caused by overall maximum tilesize != standart map */
      iao = (int)(((int)(tw - omtw) / 2) / cos(alpha));
        ox += (int)(tw - omtw);


    /* Get first tile  */
      ftx = (sourcecorner.getX() + iao) / axis;
      fty = (sourcecorner.getY() - iao) / axis;


    /* Correct firsttile if x/y < 0 */
      if((sourcecorner.getX() + iao)  < 0)
      {
        ftx--;
          ox -= tw/2;
          oy -= th/2;
      }

      if((sourcecorner.getY() - iao) < 0)
      {
        fty--;
          ox += tw/2;
          oy -= th/2;
      }


    /* Correct first tile to get all tiles */
      ftx--;
        ox -= tw/2;
        oy -= th/2;


    /* Get offset of first tile */
      iox = (sourcecorner.getX() + iao) % axis;
      ioy = (sourcecorner.getY() - iao) % axis;



    /* Transform offset from iso to orthogonal system */
      _ox1 = cos(alpha) * iox;
      _oy1 = sin(alpha) * iox;
      _ox2 = cos(alpha) * ioy;
      _oy2 = sin(alpha) * ioy;

      ox += _ox2 - _ox1;
      oy += -(_oy1 + _oy2);


    /* Correct offset */
      ox -= tw/2;


    /* Round up to avoid wrong positions if positions result to be negative */
      ox = ceil(ox);
      oy = ceil(oy);


    /* Get the last row */
      lr = (int)((sourcecorner.getX() + sourcecorner.getY() + 2*((targetrect.getHeight() + ((int)(omth) - (int)(th))) / (2 * sin(alpha)))) / axis);



    /* Init draw loop */
      sx = ftx;
      sy = fty;
      sd = 0; // x - axis


    /* Iterate rows */
      while(sx + sy <= lr)
      {
        /* Set cursor */
          tx = sx;
          ty = sy;


        /* Search all objectlinks that are on this row & sort them by column */
//          objectlinklist_by_column.clear();
//          for(list<ObjectLink_Row_pair>::iterator i = objectlinklist_by_row.begin(); i != objectlinklist_by_row.end(); i++)
//          {
//            int r;
//
//            r = (int)((i->first->object->getPosition().getX() + i->first->object->getPosition().getY()) / axis);
//
//            if(r == sx + sy || (r < ftx + fty && sx + sy == ftx + fty) || (r > lr && sx + sy == lr))
//            {
//              /* Add to row */
//                if(i->first->object->getPosition().getX() < 0)
//                  objectlinklist_by_column.push_back(ObjectLink_Column_pair(i->first, (int)(i->first->object->getPosition().getY() / axis - 1)));
//                else
//                  objectlinklist_by_column.push_back(ObjectLink_Column_pair(i->first, (int)(i->first->object->getPosition().getY() / axis)));
//            }
//          }
//
//          /* Sort links by column */
//            objectlinklist_by_column.sort();
//
//
//        /* Draw objects in this columns */
//          for(list<ObjectLink_Column_pair>::iterator i = objectlinklist_by_column.begin(); i != objectlinklist_by_column.end(); i++)
//          {
//            IntPoint position;
//            IntPoint realposition;
//            const gfx::Frame *frame;
//
//
//            /* Continue */
//              if(i->first->object->getState() == NULL || (frame = i->first->object->getState()->getAnimation().getCurrentFrame()) == NULL)
//                continue;
//
//            /* Get position */
//              position.setX(targetrect.getX() + (int)(cos(alpha) * ((i->first->object->getPosition().getX() - sourcecorner.getX()) - (i->first->object->getPosition().getY() - sourcecorner.getY()))));
//              position.setY(targetrect.getY() + (int)(sin(alpha) * ((i->first->object->getPosition().getX() - sourcecorner.getX()) + (i->first->object->getPosition().getY() - sourcecorner.getY()))));
//
//              realposition = position + i->first->object->getDrawOffset() + i->first->object->getState()->getDrawOffset() + i->first->object->getState()->getAnimation().getOffset() +  frame->getOffset();
//
//
//            /* Draw */
//              if(i->first->drawmode == OBJECT_DRAW_BY_CORNER)
//              {
//                /* Boundscheck */
//                  if(
//                      realposition.getX() > targetrect.getX() + targetrect.getWidth() ||
//                      realposition.getY() > targetrect.getY() + targetrect.getHeight() ||
//                      realposition.getX() + (int)(frame->getWidth()) < targetrect.getX() ||
//                      realposition.getY() + (int)(frame->getHeight()) < targetrect.getY()
//                     )
//                     continue;
//
//
//                /* Draw */
//                  i->first->object->drawByCorner(position);
//              }
//              else
//              {
//                /* Boundscheck */
//                  if(
//                       realposition.getX() - (int)(frame->getWidth())/2 > targetrect.getX() + targetrect.getWidth() ||
//                       realposition.getY() - (int)(frame->getHeight())/2 > targetrect.getY() + targetrect.getHeight() ||
//                       realposition.getX() + (int)(frame->getWidth())/2 < targetrect.getX() ||
//                       realposition.getY() + (int)(frame->getHeight())/2 < targetrect.getY()
//                     )
//                      continue;
//
//
//                /* Draw */
//                  i->first->object->drawByCenter(position);
//              }
//
//          }


        /* Iterate tiles */
          while(true)
          {
            int gid;

            /* Draw tile */
              /* Get gid */
                gid = layer.getTile(tx, ty);


              /* Draw */
                if(gid != 0)
                {
                  ImageClipping clipping;
                  int x, y;

                  /* ImageClipping */
                    clipping = getTileAsImageClipping(gid);


                  /* Get position on image */
                    x = (int)(targetrect.getX() + (tx - ftx) * (tw/2) - (ty - fty) * (tw/2) + ox);
                    y = (int)(targetrect.getY() + (tx - ftx) * (th/2) + (ty - fty) * (th/2) + oy + th - clipping.getHeight());


                  /* Rangecheck */
                    if
                      (
                        x < targetrect.getX() + targetrect.getWidth() &&
                        y < targetrect.getY() + targetrect.getHeight() &&
                        x + (int)(clipping.getWidth()) >= targetrect.getX() &&
                        y + (int)(clipping.getHeight()) >= targetrect.getY()
                      )
                    {
                      clipping.draw(IntPoint(x, y));
                    }
                }

            /* Next tile */
              tx++;
              ty--;


            /* Line complete */
              if((tx - ftx) * (tw/2) - (ty - fty) * (tw/2) + ox > targetrect.getWidth())
                break;
          }


        /* Go to next line */
          if(sd == 0)
            sx++;
          else
            sy++;

          /* Set direction */
            sd = !sd;

      }
  }


//  void Map::drawOrthogonalLine(const geo::IntPoint &corner, const geo::IntVector &offset, int ftx, int ltx, int line, list<ObjectLink_Column_pair> &objectlinklist_by_column)
//  {
//
//  }
//
//  void Map::drawIsometricLine(const geo::IntPoint &corner, const geo::IntVector &offset, int ftx, int ltx, int line, list<ObjectLink_Column_pair> &objectlinklist_by_column)
//  {
//
//  }
//
//

  void Map::clearDynamicData()
  {
//    for(list<Map::ObjectLink*>::iterator i = objectlinklist.begin(); i != objectlinklist.end(); i++)
//    {
//      if(*i != NULL)
//        delete *i;
//    }
  }


  void Map::reinstanciateDynamicData()
  {
//    for(list<Map::ObjectLink*>::iterator i = objectlinklist.begin(); i != objectlinklist.end(); i++)
//    {
//      if(*i != NULL)
//      {
//        ObjectLink *objectlink = *i;
//
//        *i = new ObjectLink;
//          (*i)->object = objectlink->object;
//          (*i)->tilelayer = objectlink->tilelayer;
//          (*i)->drawmode = objectlink->drawmode;
//      }
//    }
  }

