#ifndef FONT_TTFLABEL_HPP
#define FONT_TTFLABEL_HPP

  #include <string>

  #include <SDL/SDL.h>
  #include <SDL/SDL_ttf.h>

  #include "etc/int.h"
  #include "geo/geo.hpp"
  #include "gfx/gfx.hpp"
  #include "util/util.hpp"

  #include "./TtfFont.hpp"

  namespace font
  {

    class TtfLabel
    {
      public:

        TtfLabel();
        TtfLabel(const TtfFont *font, const std::string &text="", const gfx::Color &color = gfx::Color(gfx::WHITE), TTF_RENDERMODE rendermode = TTF_SOLID);
        TtfLabel(const TtfLabel &ttflabel);
        ~TtfLabel();


        /* Load */
          void load(const TtfFont *font, const std::string &text="", const gfx::Color &color = gfx::Color(gfx::WHITE), TTF_RENDERMODE rendermode = TTF_SOLID);
          void load(const TtfLabel &ttflabel);


        /* Clear */
          void clear();


        /* Font */
          const TtfFont *getFont() const;
          void setFont(const TtfFont *font);


        /* Color */
          const gfx::Color &getColor() const;
          void setColor(const gfx::Color &color);


        /* Text  */
          const std::string &getText() const;
          void setText(const std::string &text);


        /* Mode */
          TTF_RENDERMODE getRendermode() const;
          void setRendermode(TTF_RENDERMODE rendermode);


        /* Render */
          void render();
          void renderIfChanged();


        /* Size */
          geo::IntSize getSize() const;


        /* Draw */
          void draw(const geo::IntPoint &pos, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL);
          void drawConst(const geo::IntPoint &pos, const etc::Alignment &alignment = etc::Alignment(etc::ALIGN_BY_CORNER), gfx::Image *image = NULL) const;


        /* Operators */
          TtfLabel &operator=(const TtfLabel &ttflabel);


      private:

        /* Data */
          struct
          {
            const TtfFont *font;
            std::string text;
            gfx::Color color;
            TTF_RENDERMODE rendermode;
          }current, requested;

          gfx::Image *image;

        /* Internals */
          void init();

    };
  }


#endif // FONT_TTFLABEL_HPP
