#ifndef GFX_COLORFADING_HPP
#define GFX_COLORFADING_HPP

  #include <SDL/SDL.h>
  #include "SDL_gfx/SDL_gfxPrimitives.h"

  #include "etc/Alignment.hpp"

  #include "./Color.hpp"
  #include "./Image.hpp"
  #include "./Fading.hpp"
  #include "./__assert.hpp"

  namespace gfx
  {

    class ColorFading: public Fading
    {
      public:

        ColorFading();
        ColorFading(const Color &color, int ticks, FADE_TYPE type, const geo::IntSize &size = geo::IntSize(-1, -1));
        ColorFading(const ColorFading &colorfading);
        ~ColorFading();


        /* Load */
          void load(const Color &color, int ticks, FADE_TYPE type, const geo::IntSize &size = geo::IntSize(-1, -1));
          void load(const ColorFading &colorfading);


        /* Clear */
          void clear();


        /* Color */
          const Color &getColor() const;
          void setColor(const Color &color);


        /* Size */
          const geo::IntSize getSize() const;
          void setSize(const geo::IntSize &size);


        /* Draw */
          void draw(const geo::IntPoint &pos = geo::IntPoint(0, 0), const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL);
          void drawConst(const geo::IntPoint &pos = geo::IntPoint(0, 0), const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), const geo::IntRect &rect = geo::IntRect(0, 0, -1, -1), Image *image = NULL) const;


        /* Operators */
          ColorFading &operator=(const ColorFading &colorfading);


      private:

        /* Data */
          Image image;
          Color color;
    };
  }

#endif // GFX_COLORFADING_HPP
