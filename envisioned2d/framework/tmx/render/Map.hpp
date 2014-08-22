#ifndef NEWTMX_RENDER_MAP_HPP
#define NEWTMX_RENDER_MAP_HPP


  #include <list>
  #include <cmath>

  #include "etc/Alignment.hpp"
  #include "gfx/gfx.hpp"
  #include "geo/geo.hpp"
  #include "util/Path.hpp"
  #include "tmx/base/Map.hpp"


  namespace tmx
  {
  namespace render
  {
//    enum OBJECT_DRAWMODE
//    {
//      OBJECT_DRAW_BY_CORNER,
//      OBJECT_DRAW_BY_CENTER
//    };




    class Map: public base::Map
    {
      public:

        Map();
        Map(const util::Path &path);
        Map(const base::Map &map);

        ~Map();


        /* Load */
          void load(const util::Path &path);
          void load(const base::Map &map);


        /* Clear */
          void clear();


        /* Manage animation links */
//          void linkAnimation(int index, gfx::Animation *animation, const geo::IntPoint &position, int tilelayer, OBJECT_DRAWMODE drawmode = OBJECT_DRAW_BY_CENTER);
//          void unlinkAnimation(int index);
//          int getFreeLink() const;


        /* Draw */
          void draw(const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL);
          void drawTileLayer(int index, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL);



        /* Operators */
          Map &operator=(const Map &map);




      private:


        /* A link to an object to draw on map */
//          struct AnimationLink
//          {
//            int index;
//
//            gfx::Animation *animation;
//            geo::IntPoint &position;
//            int tilelayer;
//            OBJECT_DRAWMODE drawmode;
//          };


        /* Type for sorting the objectlinks */
//          struct AnimationLink_int_pair: public std::pair<AnimationLink*, int>
//          {
//            AnimationLink_int_pair(AnimationLink *first, int second)
//            {
//              this->first = first;
//              this->second = second;
//            }
//
//            bool operator<(const AnimationLink_int_pair &anim_int_pair)
//            {
//              return second < anim_int_pair.second;
//            }
//          };
//
//          typedef AnimationLink_int_pair AnimationLink_TileLayer_pair;
//          typedef AnimationLink_int_pair AnimationLink_Row_pair;
//          typedef AnimationLink_int_pair AnimationLink_Column_pair;


      private:

        /* Data */
//          std::list<ObjectLink*> objectlinklist;



        /* Internal render stuff for keeping main function simpler */
          void drawOrthogonalLayer(const base::TileLayer &layer, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, int tw, int th, int omtw, int omth/*, std::list<ObjectLink_Row_pair> &objectlinklist_by_row*/, gfx::Image *image);
          void drawIsometricLayer(const base::TileLayer &layer, const geo::IntRect &targetrect, const geo::IntPoint &sourcecorner, int tw, int th, int omtw, int omth/*, std::list<ObjectLink_Row_pair> &objectlinklist_by_row*/, gfx::Image *image);
//          void drawOrthogonalLine(const geo::IntPoint &corner, const geo::IntVector &offset, int ftx, int ltx, int line, std::list<ObjectLink_Column_pair> &objectlinklist);
//          void drawIsometricLine(const geo::IntPoint &corner, const geo::IntVector &offset, int ftx, int ltx, int line, std::list<ObjectLink_Column_pair> &objectlinklist);



        /* Internals - Attention! Not memory save!!! */
          void clearDynamicData();
          void reinstanciateDynamicData();

    };
  }
  }



#endif
