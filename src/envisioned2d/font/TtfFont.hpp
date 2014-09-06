#ifndef FONT_TTFFONT_HPP
#define FONT_TTFFONT_HPP

  #include <string>

  #include <SDL/SDL.h>
  #include <SDL/SDL_ttf.h>

  #include "etc/Alignment.hpp"
  #include "util/Path.hpp"
  #include "gfx/gfx.hpp"
  #include "geo/geo.hpp"
  #include "error/Exception.hpp"

  #include "./__assert.hpp"


  namespace font
  {
    enum TTF_RENDERMODE
    {
      TTF_SOLID,
      TTF_BLENDED
    };


    class TtfFont
    {
      public:

        TtfFont();
        TtfFont(const util::Path &path, int height);
        TtfFont(const TtfFont &ttffont);
        ~TtfFont();


        /* Load */
          void load(const util::Path &path, int height);
          void load(const TtfFont &ttffont);


        /* Clear */
          void clear();


        /* Text size */


        /* Char/Font Attributes */
          int getHeight() const;
          geo::IntSize getTextSize(const std::string &text) const;

          geo::IntSize getCharSize(char c) const;
          int getCharMinX(char c) const;
          int getCharMaxX(char c) const;
          int getCharMinY(char c) const;
          int getCharMaxY(char c) const;
          int getCharAdvance(char c) const;
          int getAscent() const;
          int getDescent() const;



        /* Draw */
          void draw(const std::string &text, const geo::IntPoint &pos, const etc::Alignment &alignment = etc::ALIGN_BY_CORNER, const gfx::Color &color = gfx::Color(gfx::WHITE), TTF_RENDERMODE rendermode = TTF_SOLID, gfx::Image *target = NULL) const;
          gfx::Image *render(const std::string &text, const gfx::Color &color = gfx::Color(gfx::WHITE), TTF_RENDERMODE rendermode = TTF_SOLID) const;


        /* Advanced drawing */
          void drawInLine(const std::string &text, const geo::IntPoint &pos, const etc::Alignment &alignment = etc::ALIGN_BY_CORNER, const gfx::Color &color = gfx::Color(gfx::WHITE), TTF_RENDERMODE rendermode = TTF_SOLID, gfx::Image *target = NULL) const;


        /* Operators */
          TtfFont &operator=(const TtfFont &ttffont);
          bool operator==(const TtfFont &ttffont) const;
          bool operator!=(const TtfFont &ttffont) const;


      private:

        /* Data */
          util::Path path;
          int height;

          TTF_Font *font;



        /* Internals */
          void init();
    };
  }

#endif // FONT_TTFFONT_HPP
