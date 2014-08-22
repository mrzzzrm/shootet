#ifndef GFX_IMAGE_HPP
#define GFX_IMAGE_HPP

  #include <vector>
  #include <iostream>

  #include <SDL/SDL.h>
  #include <SDL/SDL_image.h>

  #include "geo/geo.hpp"
  #include "util/Path.hpp"
  #include "etc/Alignment.hpp"

  #include "./Color.hpp"
  #include "./SDL_gfx/SDL_gfxPrimitives.h"


  enum IMAGE_FORMAT
  {
    IMAGE_FORMAT_RGB,
    IMAGE_FORMAT_RGBA
  };


  namespace gfx
  {
    class Image
    {
      public:

        Image();
        Image(SDL_Surface *surface);
        Image(const util::Path &path, bool auto_colorkey = true);
        Image(const geo::IntSize &size, const Color &color = BLACK, bool auto_colorkey = true);
        Image(const Image &image);
        ~Image();


        /* Load */
          void load(SDL_Surface *surface);
          void load(const util::Path &path, bool auto_colorkey = true);
          void load(const geo::IntSize &size, const Color &color = BLACK, bool auto_colorkey = true);
          void load(const Image &image);


        /* Clear */
          void clear();


        /* Path */
          const util::Path &getPath() const;


        /* Format */
          IMAGE_FORMAT getFormat() const;
          void format(IMAGE_FORMAT format);


        /* Bytes per pixel */
          int getBytesPerPixel() const;


        /* Colorkey */
          const Color &getColorkey() const;
          void setColorkey(const Color &colorkey);
          bool hasColorkey() const;
          void removeColorkey();


        /* Alpha */
          const double &getAlpha() const;
          void setAlpha(const double &alpha);


        /* Size */
          const geo::IntSize getSize() const;
          void setSize(const geo::IntSize &size, const geo::IntVector &offset = geo::IntVector(0, 0));
          void setWidth(int width, int offset = 0);
          void setHeight(int height, int offset = 0);


        /* Stretch */
          void stretchBySize(const geo::IntSize &size);
          void stretchByFactor(double wfac, double hfac);


        /* Access Pixels */
          Color getPixel(const geo::IntPoint &pixel) const;


        /* Fill with color */
          void fill(const Color &color);


        /* Draw primtives */
          void drawPoint(const geo::IntPoint &pos, const Color &color);
          void drawLine(const geo::IntPoint &from, const geo::IntPoint &to, const Color &color, int width = 1, bool aa = false);
          void drawRect(const geo::IntRect &rect, const Color &color, bool filled = false);
          void drawRoundedRect(const geo::IntRect &rect, int radius, const Color &color, bool filled = false);
          void drawCircle(const geo::IntPoint &pos, int radius, const Color &color, bool filled = false, bool aa = false);
          void drawEllipse(const geo::IntPoint &pos, int radius_x, int radius_y, const Color &color, bool filled = false, bool aa = false);
          void drawArc(const geo::IntPoint &pos, int radius, int start, int end, const Color &color);
          void drawPie(const geo::IntPoint &pos, int radius, int start, int end, const Color &color);
          void drawTrigon(const geo::IntPoint &pos1, const geo::IntPoint &pos2, const geo::IntPoint &pos3, const Color &color, bool filled = false, bool aa = false);
          void drawPolygon(const std::vector<geo::IntPoint> posvec, const Color &color, bool filled = false, bool aa = false);
          void drawTexturedPolygon(const std::vector<geo::IntPoint> posvec, const Image &texture, const geo::IntVector &offset);


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment, const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL) const;
          void draw(const geo::IntPoint &corner, Image *image = NULL) const;


        /* Operators */
          Image &operator=(const Image &image);


      private:

        /* Data */
          SDL_Surface *surface;
          util::Path path;
          Color *colorkey;
          double alpha;


        /* Internal */
          void init();

    };
  }

#endif // GFX_IMAGE_HPP
