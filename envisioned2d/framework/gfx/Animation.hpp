#ifndef GFX_ANIMATION_HPP
#define GFX_ANIMATION_HPP

  #include <list>
  #include <map>

  #include "geo/geo.hpp"

  #include "xml/Xml.hpp"
  #include "util/Path.hpp"
  #include "error/Exception.hpp"
  #include "util/util.hpp"


  #include "./Frame.hpp"


  namespace gfx
  {
    class Animation
    {
      public:

        Animation();
        Animation(const util::Path &xmlpath);
        Animation(const Animation &animation);
        ~Animation();


        /* Load */
          void load(const util::Path &xmlpath);
          void load(const Animation &animation);


        /* Clear */
          void clear();


        /* Path */
          const util::Path &getPath() const;


        /* Frames */
          int getFrameCount() const;

          Frame &getFrame(int index);
          const Frame &getFrameConst(int index) const;

          Frame &getCurrentFrame();
          Frame &getCurrentFrameConst();

          void addFrame(const Frame &frame, int index = -1);


        /* Offset */
          const geo::IntVector &getOffset() const;
          void setOffset(const geo::IntVector &offset);


        /* Loopcount */
          int getLoopCount() const;


        /* Reset time for frame or entire animation */
          void reset();
          void resetLoop();
          void resetFrame();


        /* Update */
          void update();


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment, const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL);
          void draw(const geo::IntPoint &corner, Image *image = NULL);
          void drawConst(const geo::IntPoint &pos, const etc::Alignment &alignment, const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL) const;
          void drawConst(const geo::IntPoint &corner, Image *image = NULL) const;


        /* Operators */
          Animation &operator=(const Animation &animation);



      private:

        /* Data */
          util::Path path;
          util::Timer timer;
          geo::IntVector offset;

          struct
          {
            std::list<Frame*> list;
            Frame *current;
            std::list<Frame*>::iterator poll;
            int elapsed;
          }frame;

          std::list<Image*> imagelist;

          int loopcount;


        /* Internals */
          void init();

    };
  }


#endif // ANIMATION_HPP
