#include "./Image.hpp"
#include "./__assert.hpp"


using namespace std;
using namespace etc;
using namespace geo;
using namespace util;
using namespace error;


static const Uint32     NEW_SURFACE_FLAGS = SDL_HWSURFACE;
static const gfx::Color DEFAULT_COLORKEY = gfx::Color(gfx::MAGNETA);
static const Uint32     DEFAULT_BITS_PER_PIXEL = 16;
static const Uint32     DEFAULT_RMASK = 0xf800;
static const Uint32     DEFAULT_GMASK = 0x07e0;
static const Uint32     DEFAULT_BMASK = 0x001f;
static const Uint32     DEFAULT_AMASK = 0x0000;


static inline SDL_Surface *format(SDL_Surface *src)
{
  SDL_Surface *res = NULL;
  u8 r, g, b, a;

  if(src->format->Amask == 0)
  {
    res = SDL_DisplayFormat(src);
  }
  else
  {
    for(int y = 0; y < src->h; y++)
    {
      for(int x = 0; x < src->w; x++)
      {
        u8 bpp;
        u8 *pixel;
        u32 color;

        bpp = src->format->BytesPerPixel;
        pixel = (u8*)src->pixels + y * src->pitch + x * bpp;

        switch(bpp)
        {
          case 1:
            color = *pixel;
          break;

          case 2:
            color = *(u16*)pixel;
          break;

          case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
              color = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            else
              color = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
          break;

          case 4:
             color = *(u32*)pixel;
          break;

          default:
              color = 0;
          break;
        }

        SDL_GetRGBA(color, src->format, &r, &g, &b, &a);

        if(a != 0 && a != 255)
        {
          res = SDL_DisplayFormatAlpha(src);
          break;
        }

      }

      if(res != NULL)
        break;
    }


    if(res == NULL)
      res = SDL_DisplayFormat(src);
  }


  if(src->flags & SDL_SRCCOLORKEY)
  {
    SDL_GetRGBA(src->format->colorkey, src->format, &r, &g, &b, &a);
    SDL_SetColorKey(res, SDL_SRCCOLORKEY, SDL_MapRGBA(res->format, r, g, b, a));
  }

  return res;
}




namespace gfx
{
  Image::Image()
  {
    init();
  }

  Image::Image(SDL_Surface *surface)
  {
    init();
    load(surface);
  }

  Image::Image(const Path &path, bool auto_colorkey)
  {
    init();
    load(path, auto_colorkey);
  }


  Image::Image(const geo::IntSize &size, const Color &color, bool auto_colorkey)
  {
    init();
    load(size, color, auto_colorkey);
  }


  Image::Image(const Image &image)
  {
    init();
    load(image);
  }


  Image::~Image()
  {
    clear();
  }


  void Image::load(SDL_Surface *surface)
  {
    __gfx__assert_open();


    clear();


    /* Setup */
    if(surface != NULL)
    {
      if(surface->format->Amask == 0)
      {
        alpha = (double)surface->format->alpha / 255;

        if(surface->flags & SDL_SRCCOLORKEY)
        {
          u8 r, g, b;
          SDL_GetRGB(surface->format->colorkey, surface->format, &r, &g, &b);
          if(colorkey != NULL)
            colorkey->load(r, g, b);
          else
            colorkey = new Color(r, g, b);
        }

        this->surface = ::format(surface);
        SDL_FreeSurface(surface);
      }
      else
      {
        this->surface = surface;
      }
    }
  }


  void Image::load(const Path &path, bool auto_colorkey)
  {
    __gfx__assert_open();

    SDL_Surface *tmp;


    clear();

    /* Load from file */
    tmp = IMG_Load(path.c_str());
    if(tmp == NULL)
      throw Exception() << "Failed to load Image '" << path << "': " << SDL_GetError();

    /* Display format and setup */
    surface = ::format(tmp);
    SDL_FreeSurface(tmp);
    if(auto_colorkey && !(surface->flags & SDL_SRCCOLORKEY) && getFormat() == IMAGE_FORMAT_RGB)
      setColorkey(DEFAULT_COLORKEY);

    /* Set path */
    this->path = path;
  }


  void Image::load(const geo::IntSize &size, const Color &color, bool auto_colorkey)
  {
    __gfx__assert_open();

    int bpp;
    Uint32 rm, gm, bm, am;


    clear();

    /* Get bits per pixel */
    if(SDL_GetVideoSurface() != NULL)
      bpp = SDL_GetVideoSurface()->format->BitsPerPixel;
    else
      bpp = DEFAULT_BITS_PER_PIXEL;


    /* Get masks */
    if(SDL_GetVideoSurface() != NULL)
    {
      rm = SDL_GetVideoSurface()->format->Rmask;
      gm = SDL_GetVideoSurface()->format->Gmask;
      bm = SDL_GetVideoSurface()->format->Bmask;
      am = SDL_GetVideoSurface()->format->Amask;
    }
    else
    {
      rm = DEFAULT_RMASK;
      gm = DEFAULT_GMASK;
      bm = DEFAULT_BMASK;
      am = DEFAULT_AMASK;
    }


    /* Create */
    surface = SDL_CreateRGBSurface(NEW_SURFACE_FLAGS, size.getWidth(), size.getHeight(), max(bpp, 15), rm, gm, bm, am);
    if(surface == NULL)
      throw Exception() << "Couldn't create image of size '" << size << "': " << SDL_GetError();


    setColorkey(DEFAULT_COLORKEY);


    /* Fill */
    if(color != BLACK)
      fill(color);
  }


  void Image::load(const Image &image)
  {
    __gfx__assert_open();


    if(this == &image)
      return;

    clear();


    if(image.surface == NULL)
      return;


    /* Create new surface  */
    surface = SDL_CreateRGBSurface(NEW_SURFACE_FLAGS, image.getSize().getWidth(), image.getSize().getHeight(), max(image.surface->format->BitsPerPixel, (Uint8)15), image.surface->format->Rmask, image.surface->format->Gmask, image.surface->format->Bmask, image.surface->format->Amask);
    if(surface == NULL)
      throw Exception() << "Failed to create image of size '" << image.getSize() << "': " << SDL_GetError();



    /* Copy content with disabled alpha*/
    surface = SDL_ConvertSurface(image.surface, image.surface->format, image.surface->flags);


    /* Setup */
    setAlpha(image.getAlpha());
    if(image.hasColorkey())
      setColorkey(image.getColorkey());
  }


  void Image::clear()
  {
    if(surface != NULL)
      SDL_FreeSurface(surface);

    path.clear();

    init();
  }


  const Path &Image::getPath() const
  {
    return path;
  }


  IMAGE_FORMAT Image::getFormat() const
  {
    if(surface != NULL)
    {
      if(surface->format->Amask != 0)
        return IMAGE_FORMAT_RGBA;
      else
        return IMAGE_FORMAT_RGB;
    }
    else
    {
      throw Exception() << "Empty image cannot have a format";
    }
  }


  void Image::format(IMAGE_FORMAT format)
  {
    SDL_Surface *tmp;

    if(surface == NULL)
      return;

    if(format == IMAGE_FORMAT_RGB && getFormat() != IMAGE_FORMAT_RGB)
    {
      tmp = SDL_DisplayFormat(surface);
      SDL_FreeSurface(surface);
      surface = tmp;
    }
    else if(format == IMAGE_FORMAT_RGBA && getFormat() != IMAGE_FORMAT_RGBA)
    {
      tmp = SDL_DisplayFormatAlpha(surface);
      SDL_FreeSurface(surface);
      surface = tmp;
    }
  }


  int Image::getBytesPerPixel() const
  {
    if(surface != NULL)
      return surface->format->BytesPerPixel;
    else
      return 0;
  }


  const Color &Image::getColorkey() const
  {
    if(getFormat() == IMAGE_FORMAT_RGBA)
      throw Exception() << "Images of format 'IMAGE_FORMAT_RGBA' cannot have a colorkey";

    if(colorkey != NULL)
      return *colorkey;
    else
      throw Exception() << "No colorkey set";
  }


  void Image::setColorkey(const Color &colorkey)
  {
    __gfx__assert_open();

    Uint8 r, g, b;


    if(getFormat() == IMAGE_FORMAT_RGBA)
      throw Exception() << "Images of format 'IMAGE_FORMAT_RGBA' cannot have a colorkey";

    if(surface != NULL)
    {
      SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, colorkey.getRed(), colorkey.getGreen(), colorkey.getBlue()));

      /* Translate colorkey into surface pixel format */
      SDL_GetRGB(SDL_MapRGB(surface->format, colorkey.getRed(), colorkey.getGreen(), colorkey.getBlue()), surface->format, &r, &g, &b);
      if(this->colorkey != NULL)
        delete this->colorkey;
      this->colorkey = new Color(r, g, b);
    }
    else
    {
      Color *tmp;

      tmp = new Color(colorkey); // To avoid errors when called 'img.setColorkey(img.getColorkey())'
      if(this->colorkey != NULL)
        delete this->colorkey;
      this->colorkey = tmp;
    }
  }


  bool Image::hasColorkey() const
  {
    return colorkey != NULL;
  }


  void Image::removeColorkey()
  {
    __gfx__assert_open();

    if(surface != NULL)
      SDL_SetColorKey(surface, 0, 0);

    if(colorkey != NULL)
    {
      delete colorkey;
      colorkey = NULL;
    }
  }


  const geo::IntSize Image::getSize() const
  {
    if(surface != NULL)
      return IntSize(surface->w, surface->h);
    else
      return IntSize(0, 0);
  }


  void Image::setSize(const IntSize &size, const geo::IntVector &offset)
  {
    __gfx__assert_open();

    int bpp;
    u32 rm, gm, bm, am;
    SDL_Surface *tmp, *rev;

    /* Get bits per pixel */
    if(surface != NULL)
      bpp = surface->format->BitsPerPixel;
    else if(SDL_GetVideoSurface() != NULL)
      bpp = SDL_GetVideoSurface()->format->BitsPerPixel;
    else
      bpp = DEFAULT_BITS_PER_PIXEL;

    /* Mask */
    if(surface != NULL)
      rev = surface;
    else if(SDL_GetVideoSurface() != NULL)
      rev = SDL_GetVideoSurface();
    else
      rev = NULL;

    if(rev != NULL)
      {rm = rev->format->Rmask; gm = rev->format->Gmask; bm = rev->format->Bmask; am = rev->format->Amask;}
    else
      {rm = DEFAULT_RMASK;      gm = DEFAULT_GMASK;      bm = DEFAULT_BMASK;      am = DEFAULT_AMASK;}

    /* Create new surface */
    tmp = SDL_CreateRGBSurface(NEW_SURFACE_FLAGS, size.getWidth(), size.getHeight(), max(bpp, 15), rm, gm, bm, am);

    if(tmp == NULL)
      throw Exception() << "Failed to resize image to '" << size << "': " << SDL_GetError();
    if(colorkey != NULL)
      SDL_FillRect(tmp, NULL, SDL_MapRGB(tmp->format, colorkey->getRed(), colorkey->getGreen(), colorkey->getBlue()));


    /* Blit old surface (with disabled alpha) if it existed and delete it */
    if(surface != NULL)
    {
      SDL_Rect drect;

      /* Create SDL - rects for blit */
      drect.x = offset.getX();
      drect.y = offset.getY();
      drect.w = surface->w;
      drect.h = surface->h;

      /* Blit */
      SDL_SetAlpha(surface, SDL_SRCALPHA, 255);
      SDL_BlitSurface(surface, NULL, tmp, &drect);

      /* Delete old */
      SDL_FreeSurface(surface);
    }


    /* Assign new surface */
    surface = tmp;


    /* Setup surface */
    setAlpha(alpha);
    if(colorkey != NULL)
      setColorkey(*colorkey);
  }


  void Image::setWidth(int width, int offset)
  {
    setSize(IntSize(width, getSize().getHeight()), IntVector(offset, 0));
  }


  void Image::setHeight(int height, int offset)
  {
    setSize(IntSize(getSize().getWidth(), height), IntVector(0, offset));
  }


  const double &Image::getAlpha() const
  {
    return alpha;
  }


  void Image::setAlpha(const double &alpha)
  {
    __gfx__assert_open();


    if(getFormat() == IMAGE_FORMAT_RGBA)
      throw Exception() << "Images of format 'IMAGE_FORMAT_RGBA' cannot have per-image-alpha";

    this->alpha = alpha;

    if(surface == NULL)
      return;

    if(alpha != 255)
      SDL_SetAlpha(surface, SDL_SRCALPHA, (Uint8)(alpha * 255));
    else
      SDL_SetAlpha(surface, 0, 255);



  }


  void Image::stretchBySize(const IntSize &size)
  {
    __gfx__assert_open();

    double alpha;
    SDL_Surface *tmp;


    /* No surface -> create empty one with requested size */
    if(surface == NULL)
    {
      load(size);
      return;
    }

    /* Disable alpha on old surface */
    alpha = this->alpha;
    setAlpha(1);

    /* Create new surface/ zoom/ swap*/
    tmp = SDL_CreateRGBSurface(NEW_SURFACE_FLAGS, size.getWidth(), size.getHeight(), surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
    SDL_SoftStretch(surface, NULL, tmp, NULL);
    surface = tmp;

    /* Setup new surface */
    setAlpha(alpha);
    if(colorkey != NULL)
      setColorkey(*colorkey);
  }


  void Image::stretchByFactor(double wfac, double hfac)
  {
    if(surface != NULL)
      stretchBySize(IntSize((int)(surface->w * wfac), (int)(surface->h * hfac)));
  }



  Color Image::getPixel(const IntPoint &point) const
  {
    __gfx__assert_open();

    Uint8 r, g, b;
    int bpp;
    Uint8 *pixel;
    Uint32 color;


    if(surface == NULL)
      throw Exception() << "No such pixel '" << point.getX() << "/" << point.getY() << "'. Size is '0x0'!";
    if(point.getX() >= surface->w || point.getY() >= surface->h)
      throw Exception() << "No such pixel '" << point.getX() << "/" << point.getY() << "'. Size is '" << surface->w << "x" << surface->h << "'!";

    bpp = surface->format->BytesPerPixel;
    pixel = (u8*)surface->pixels + point.getY() * surface->pitch + point.getX() * bpp;

    switch(bpp)
    {
      case 1:
        color = *pixel;
      break;

      case 2:
        color = *(u16*)pixel;
      break;

      case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
          color = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
        else
          color = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
      break;

      case 4:
         color = *(u32*)pixel;
      break;

      default:
          color = 0;
      break;
    }

    SDL_GetRGB(color, surface->format, &r, &g, &b);
    return Color(r, g, b);
  }





  void Image::fill(const Color &color)
  {
    if(surface != NULL)
    {
      if(surface->format->Amask != 0)
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()));
      else
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.getRed(), color.getGreen(), color.getBlue()));
    }
  }


  void Image::drawPoint(const IntPoint &pos, const Color &color)
  {
    if(surface != NULL)
      pixelColor(surface, pos.getX(), pos.getY(), color.getRGBA());
  }


  void Image::drawLine(const IntPoint &from, const IntPoint &to, const Color &color, int width, bool aa)
  {
    if(surface == NULL)
      return;

    if(width > 1)
    {
      thickLineColor(surface, from.getX(), from.getY(), to.getX(), to.getY(), width, color.getRGBA());
    }
    else if(width == 1)
    {
      if(aa)
        lineColor(surface, from.getX(), from.getY(), to.getX(), to.getY(), color.getRGBA());
      else
        aalineColor(surface, from.getX(), from.getY(), to.getX(), to.getY(), color.getRGBA());
    }
  }

  void Image::drawRect(const IntRect &rect, const Color &color, bool filled)
  {
    IntRect trect;

    if(surface == NULL)
      return;

    trect = rect_translate_negative_axises(rect, getSize());
    if(trect.getWidth() < 0 || trect.getHeight() < 0 )
      return;

    if(filled)
      boxColor(surface, trect.getX(), trect.getY(), trect.getX() + trect.getWidth() - 1, trect.getY() + trect.getHeight() - 1, color.getRGBA());
    else
      rectangleColor(surface, trect.getX(), trect.getY(), trect.getX() + trect.getWidth() - 1, trect.getY() + trect.getHeight() - 1, color.getRGBA());
  }


  void Image::drawRoundedRect(const IntRect &rect, int radius, const Color &color, bool filled)
  {
    IntRect trect;

    if(surface == NULL)
      return;

    trect = rect_translate_negative_axises(rect, getSize());
    if(trect.getWidth() < 0 || trect.getHeight() < 0 )
      return;

    if(filled)
      roundedBoxColor(surface, trect.getX(), trect.getY(), trect.getX() + trect.getWidth() - 1, trect.getY() + trect.getHeight() - 1, radius, color.getRGBA());
    else
      roundedRectangleColor(surface, trect.getX(), trect.getY(), trect.getX() + trect.getWidth() - 1, trect.getY() + trect.getHeight() - 1, radius, color.getRGBA());
  }


  void Image::drawCircle(const IntPoint &pos, int radius, const Color &color, bool filled, bool aa)
  {
    if(surface == NULL)
      return;

    if(filled)
    {
      filledCircleColor(surface, pos.getX(), pos.getY(), radius, color.getRGBA());
    }
    else
    {
      if(aa)
        aacircleColor(surface, pos.getX(), pos.getY(), radius, color.getRGBA());
      else
        circleColor(surface, pos.getX(), pos.getY(), radius, color.getRGBA());
    }
  }


  void Image::drawEllipse(const IntPoint &pos, int radius_x, int radius_y, const Color &color, bool filled, bool aa)
  {
    if(surface == NULL)
      return;

    if(filled)
    {
      filledEllipseColor(surface, pos.getX(), pos.getY(), radius_x, radius_y, color.getRGBA());
    }
    else
    {
      if(aa)
        aaellipseColor(surface, pos.getX(), pos.getY(), radius_x, radius_y, color.getRGBA());
      else
        ellipseColor(surface, pos.getX(), pos.getY(), radius_x, radius_y, color.getRGBA());
    }
  }


  void Image::drawArc(const IntPoint &pos, int radius, int start, int end, const Color &color)
  {
    if(surface == NULL)
      return;

    arcColor(surface, pos.getX(), pos.getY(), radius, start, end, color.getRGBA());
  }


  void Image::drawPie(const IntPoint &pos, int radius, int start, int end, const Color &color)
  {
    if(surface == NULL)
      return;

    pieColor(surface, pos.getX(), pos.getY(), radius, start, end, color.getRGBA());
  }


  void Image::drawTrigon(const IntPoint &pos1, const IntPoint &pos2, const IntPoint &pos3, const Color &color, bool filled, bool aa)
  {
    if(surface == NULL)
      return;

    if(filled)
    {
      filledTrigonColor(surface, pos1.getX(), pos1.getY(), pos2.getX(), pos2.getY(), pos3.getX(), pos3.getY(), color.getRGBA());
    }
    else
    {
      if(aa)
        aatrigonColor(surface, pos1.getX(), pos1.getY(), pos2.getX(), pos2.getY(), pos3.getX(), pos3.getY(), color.getRGBA());
      else
        trigonColor(surface, pos1.getX(), pos1.getY(), pos2.getX(), pos2.getY(), pos3.getX(), pos3.getY(), color.getRGBA());
    }
  }


  void Image::drawPolygon(const std::vector<IntPoint> posvec, const Color &color, bool filled, bool aa)
  {
    int n;
    Sint16 *x, *y;


    if(surface == NULL)
      return;

    n = posvec.size();
    x = new Sint16[n];
    y = new Sint16[n];

    for(int v = 0; v < n; v++)
    {
      x[v] = posvec[v].getX();
      y[v] = posvec[v].getY();
    }

    if(filled)
    {
      filledPolygonColor(surface, x, y, n, color.getRGBA());
    }
    else
    {
      if(aa)
        aapolygonColor(surface, x, y, n, color.getRGBA());
      else
        polygonColor(surface, x, y, n, color.getRGBA());
    }
  }


  void Image::drawTexturedPolygon(const std::vector<IntPoint> posvec, const Image &texture, const IntVector &offset)
  {
    int n;
    Sint16 *x, *y;


    if(surface == NULL || texture.surface == NULL)
      return;

    n = posvec.size();
    x = new Sint16[n];
    y = new Sint16[n];

    for(int v = 0; v < n; v++)
    {
      x[v] = posvec[v].getX();
      y[v] = posvec[v].getY();
    }

    texturedPolygon(surface, x, y, n, texture.surface, offset.getX(), offset.getY());
  }



  void Image::draw(const IntPoint &pos, const Alignment &alignment, const IntRect &rect, Image *image) const
  {
    __gfx__assert_open();

    SDL_Rect srect, drect;
    SDL_Surface *target;
    IntPoint corner;
    IntRect brect;
    IntSize dim;


    if(surface == NULL)
      return;


    /* Translate negative rect - size */
    brect = rect_translate_negative_axises(rect, IntSize(surface->w, surface->h));
    if(brect.getWidth() < 0 || brect.getHeight() < 0)
      return;


    /* Translate pos to corner */
    dim.load(brect.getWidth(), brect.getHeight());
    corner = pos - alignment * dim;


    /* Generate SDL - rects */
    srect.x = brect.getX();
    srect.y = brect.getY();
    srect.w = brect.getWidth();
    srect.h = brect.getHeight();

    drect.x = corner.getX();
    drect.y = corner.getY();
    drect.w = brect.getWidth();
    drect.h = brect.getHeight();


    /* Get target - surface */
    if(image == NULL)
    {
      target = SDL_GetVideoSurface();
    }
    else
    {
      target = image->surface;

      /* If 'image' hasn't a surface make 'image' a copy of this */
      if(target == NULL)
      {
        image->load(*this);
        return;
      }
    }

    /* Blit */
    SDL_BlitSurface(surface, &srect, target, &drect);
  }

  void Image::draw(const IntPoint &corner, Image *image) const
  {
    __gfx__assert_open();

    SDL_Rect drect;
    SDL_Surface *target;


    if(surface == NULL)
      return;


    /* Generate SDL - rects */
    drect.x = corner.getX();
    drect.y = corner.getY();
    drect.w = surface->w;
    drect.h = surface->h;

    /* Get target - surface */
    if(image == NULL)
    {
      target = SDL_GetVideoSurface();
    }
    else
    {
      target = image->surface;

      /* If 'image' hasn't a surface make 'image' a copy of this */
      if(target == NULL)
      {
        image->load(*this);
        return;
      }
    }

    /* Blit */
    SDL_BlitSurface(surface, NULL, SDL_GetVideoSurface(), &drect);
  }


  Image &Image::operator=(const Image &image)
  {
    load(image);
    return *this;
  }


  void Image::init()
  {
    surface = NULL;
    colorkey = NULL;
    alpha = 1;
  }


}
