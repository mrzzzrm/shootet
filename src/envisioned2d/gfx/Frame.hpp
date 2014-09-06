#ifndef GFX_FRAME_HPP
#define GFX_FRAME_HPP


  #include "geo/geo.hpp"

  #include "./ImageClipping.hpp"


  namespace gfx
  {

    class Frame: public ImageClipping
    {
      public:

        Frame();
        Frame(const Image *image, const geo::IntRect &rect, int ms, const geo::IntVector &offset = geo::IntVector(0, 0));
        Frame(const ImageClipping &imageclipping, int ms, const geo::IntVector &offset = geo::IntVector(0, 0));
        Frame(const Frame &frame);
        ~Frame();


        /* Load */
          void load(const Image *image, const geo::IntRect &rect, int ms, const geo::IntVector &offset = geo::IntVector(0, 0));
          void load(const ImageClipping &imageclipping, int ms, const geo::IntVector &offset = geo::IntVector(0, 0));
          void load(const Frame &frame);


        /* Clear */
          void clear();


        /* Manage offset */
          const geo::IntVector &getOffset() const;
          void setOffset(const geo::IntVector &offset);


        /* Manage duration */
          int getMilliseconds() const;
          void setMilliseconds(int ms);


        /* Draw - Interface */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment, const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL) const;
          void draw(const geo::IntPoint &corner, Image *image = NULL) const;


        /* Operators */
          Frame &operator=(const Frame &frame);


      private:

        /* Data */
          geo::IntVector offset;
          int ms;


        /* Internal */
          void init();

    };
  };


#endif // GFX_FRAME_HPP
