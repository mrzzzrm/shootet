#ifndef GFX_BMPFADING_HPP
#define GFX_BMPFADING_HPP

  #include <SDL/SDL.h>


  #include "geo/geo.hpp"
  #include "util/util.hpp"

  #include "./Image.hpp"
  #include "./Fading.hpp"


  namespace gfx
  {


    class ImageFading: public Fading
    {
      public:

        ImageFading();
        ImageFading(Image *image, uint ticks, FADE_TYPE type);
        ImageFading(const ImageFading &imagefading);
        ~ImageFading();


        /* Load */
          void load(Image *image, uint ticks, FADE_TYPE type);
          void load(const ImageFading &imagefading);


        /* Clear */
          void clear();


        /* Image */
          Image *getImage();
          const Image *getImageConst() const;
          void setImage(Image *image);


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL);
          void draw(const geo::IntPoint &corner, Image *image = NULL);


        /* Operators */
          ImageFading &operator=(const ImageFading &imagefading);


      private:

        /* Data */
          Image *image;


        /* Internals */
          void init();
    };
  }


#endif // GFX_BMPFADING_HPP
