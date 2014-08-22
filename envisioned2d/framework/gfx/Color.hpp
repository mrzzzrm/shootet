#ifndef GFX_COLOR_HPP
#define GFX_COLOR_HPP

  #include "etc/int.h"


  namespace gfx
  {
    enum COLOR
    {
      RED,
      GREEN,
      BLUE,

      YELLOW,
      MAGNETA,

      BLACK,
      WHITE
    };


    class Color
    {
      public:

        Color();
        Color(u32 rgba);
        Color(u8 r, u8 g, u8 b, u8 a = 0xff);
        Color(COLOR color);
        Color(const Color &color);


        /* Load */
          void load(u32 rgba);
          void load(u8 r, u8 g, u8 b, u8 a = 0xff);
          void load(COLOR color);
          void load(const Color &color);


        /* Clear */
          void clear();


        /* Read */
          u32 getRGBA() const;
          u8 getRed() const;
          u8 getGreen() const;
          u8 getBlue() const;
          u8 getAlpha() const;


        /* Write */
          void setRGBA(u32 rgba);
          void setRed(u8 r);
          void setGreen(u8 g);
          void setBlue(u8 b);
          void setAlpha(u8 a);


        /* Operators */
          Color &operator=(const Color &color);
          bool operator!=(const Color &color) const;
          bool operator==(const Color &color) const;


      private:

        /* Data */
          u8 r, g, b, a;

        /* Internals */
          void init();
    };
  }

#endif // GFX_COLOR_HPP
