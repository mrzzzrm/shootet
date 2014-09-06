#ifndef GFX_IMAGECLIPPING_HPP
#define GFX_IMAGECLIPPING_HPP


  #include "geo/geo.hpp"
  #include "util/util.hpp"

  #include "./Image.hpp"


  namespace gfx
  {
    class ImageClipping: public geo::IntRect
    {
      public:

        ImageClipping();
        ImageClipping(const Image *image, const geo::IntRect &rect);
        ImageClipping(const ImageClipping &clipping);
        ~ImageClipping();


        /* Load */
          void load(const Image *image, const geo::IntRect &rect);
          void load(const ImageClipping &imageclipping);


        /* Clear */
          void clear();


        /* Image */
          const Image *getImage() const;
          void setImage(const Image *image);


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment, const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL) const;
          void draw(const geo::IntPoint &corner, Image *image = NULL) const;



        /* Operators */
          ImageClipping &operator=(const ImageClipping &imageclipping);



      private:

        /* Data */
          const Image *image;


        /* Internal */
          void init();
    };

  }



#endif // GFX_IMAGECLIPPING_HPP
