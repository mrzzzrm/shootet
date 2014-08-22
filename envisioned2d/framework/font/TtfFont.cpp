#include "./TtfFont.hpp"

using namespace std;

using namespace error;
using namespace geo;
using namespace gfx;
using namespace etc;
using namespace util;


namespace font
{

  TtfFont::TtfFont()
  {
    init();
  }


  TtfFont::TtfFont(const util::Path &path, int height)
  {
    init();
    load(path, height);
  }


  TtfFont::TtfFont(const TtfFont &ttffont)
  {
    init();
    load(ttffont);
  }


  TtfFont::~TtfFont()
  {
    clear();
  }


  void TtfFont::load(const util::Path &path, int height)
  {
    __font__assert_open();

    clear();

    this->path = path;
    this->height = height;

    font = TTF_OpenFont(path.c_str(), height);
      if(font == NULL)
        throw Exception() << "Couldn't load font " << path << ": '" << TTF_GetError() << "'";

  }


  void TtfFont::load(const TtfFont &ttffont)
  {
    if(&ttffont == this)
      return;

    load(ttffont.path, ttffont.height);
  }


  void TtfFont::clear()
  {
    if(font != NULL)
      TTF_CloseFont(font);

    path.clear();

    init();
  }


  int TtfFont::getHeight() const
  {
    if(font != NULL)
      return TTF_FontHeight(font);
    else
      return 0;
  }


  IntSize TtfFont::getTextSize(const std::string &text) const
  {
    __font__assert_open();

    int w, h;


    if(font == NULL)
      return IntSize(0, 0);

    TTF_SizeText(font, text.c_str(), &w, &h);

    return IntSize(w, h);
  }




  IntSize TtfFont::getCharSize(char c) const
  {
    __font__assert_open();

    int w, h;
    string text;


    if(font == NULL)
      return IntSize(0, 0);

    text += c;
    TTF_SizeText(font, text.c_str(), &w, &h);

    return IntSize(w, h);
  }



  int TtfFont::getCharMinX(char c) const
  {
    __font__assert_open();

    int val;

    if(font != NULL)
      TTF_GlyphMetrics(font, c, &val, NULL, NULL, NULL, NULL);
    else
      return 0;

    return val;
  }


  int TtfFont::getCharMaxX(char c) const
  {
    __font__assert_open();

    int val;

    if(font != NULL)
      TTF_GlyphMetrics(font, c, NULL, &val, NULL, NULL, NULL);
    else
      return 0;

    return val;
  }


  int TtfFont::getCharMinY(char c) const
  {
    __font__assert_open();

    int val;

    if(font != NULL)
      TTF_GlyphMetrics(font, c, NULL, NULL, &val, NULL, NULL);
    else
      return 0;

    return val;
  }


  int TtfFont::getCharMaxY(char c) const
  {
    __font__assert_open();

    int val;

    if(font != NULL)
      TTF_GlyphMetrics(font, c, NULL, NULL, NULL, &val, NULL);
    else
      return 0;

    return val;
  }


  int TtfFont::getCharAdvance(char c) const
  {
    __font__assert_open();

    int val;

    if(font != NULL)
      TTF_GlyphMetrics(font, c, NULL, NULL, NULL, NULL, &val);
    else
      return 0;

    return val;
  }


  int TtfFont::getAscent() const
  {
    __font__assert_open();

    if(font != NULL)
      return TTF_FontAscent(font);
    else
      return 0;
  }


  int TtfFont::getDescent() const
  {
    __font__assert_open();

    if(font != NULL)
      return -TTF_FontDescent(font);
    else
      return 0;
  }

  void TtfFont::draw(const string &text, const IntPoint &pos, const Alignment &alignment, const Color &color, TTF_RENDERMODE rendermode, Image *target) const
  {
    Image *image;

    image = render(text, color, rendermode);
    if(image == NULL)
      return;

    image->draw(pos, alignment, IntRect(0, 0, -1, -1), target);

    delete image;
  }


  Image *TtfFont::render(const string &text, const gfx::Color &color, TTF_RENDERMODE rendermode) const
  {
    __font__assert_open();

    SDL_Surface *srcsurface;
    SDL_Color sdlcolor;
    IntPoint corner;
    IntSize size;

    if(font == NULL)
      return NULL;
    if(text.size() == 0)
      return NULL;

    /* Translate color */
    sdlcolor.r = color.getRed();
    sdlcolor.g = color.getGreen();
    sdlcolor.b = color.getBlue();

    /* Get source and target */
    if(rendermode == TTF_SOLID)
      srcsurface = TTF_RenderText_Solid(font, text.c_str(), sdlcolor);
    else
      srcsurface = TTF_RenderText_Blended(font, text.c_str(), sdlcolor);

    if(srcsurface == NULL)
      throw Exception() << "Couldn't render text '" << text << "': '" << TTF_GetError() << "'";

    return new Image(srcsurface);
  }



  TtfFont &TtfFont::operator=(const TtfFont &ttffont)
  {
    load(ttffont);
    return *this;
  }


  bool TtfFont::operator==(const TtfFont &ttffont) const
  {
    return path == ttffont.path && height != ttffont.height;
  }

  bool TtfFont::operator!=(const TtfFont &ttffont) const
  {
    return !(*this == ttffont);
  }


  void TtfFont::init()
  {
    font = NULL;
    height = 0;
  }



}
