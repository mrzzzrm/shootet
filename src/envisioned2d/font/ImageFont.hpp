#ifndef FONT_BMPFONT_HPP
#define FONT_BMPFONT_HPP

  #include <string>

  #include "gfx/Image.hpp"
  #include "geo/geo.hpp"
  #include "geo/Point.hpp"
  #include "geo/Rect.hpp"
  #include "geo/Vector.hpp"
  #include "util/Path.hpp"

  namespace font
  {

    class ImageFont: public gfx::Image
    {
      public:

        ImageFont();
        ImageFont(const gfx::Image &image);
        ImageFont(const util::Path &path);
        ImageFont(const ImageFont &imagefont);


        /* Load */
          void load(const gfx::Image &image);
          void load(const util::Path &path);
          void load(const ImageFont &imagefont);


        /* Clear */
          void clear();


        /* Character size */
          const geo::IntSize &getCharacterSize() const;


        /* Draw String */
          void draw(const geo::IntPoint &pos, const std::string &string, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), Image *image = NULL) const;


        /* Operators */
          ImageFont &operator=(const ImageFont &imagefont);


      private:

        /* Data */
          geo::IntSize char_size;


    };
  }

#endif // FONT_BMPFONT_HPP
