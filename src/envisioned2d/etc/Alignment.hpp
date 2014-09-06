#ifndef ETC_ALIGNMENT_HPP
#define ETC_ALIGNMENT_HPP

  namespace etc
  {
    enum ALIGNMENT
    {
      ALIGN_BY_CORNER,
      ALIGN_BY_CENTER
    };

    class Alignment
    {
      public:

        Alignment();
        Alignment(const double &x, const double &y);
        Alignment(ALIGNMENT alignment);
        Alignment(const Alignment &alignment);


        /* Load */
          void load(const double &x, const double &y);
          void load(ALIGNMENT alignment);
          void load(const Alignment &alignment);


        /* Clear */
          void clear();


        /* Access axis */
          const double &getX() const;
          const double &getY() const;
          void setX(const double &x);
          void setY(const double &y);


        /* Operators */
          Alignment &operator=(const Alignment &alignment);


      private:

        /* Data */
          double x, y;

        /* Internal */
          void init();
    };
  }


#endif // ETC_ALIGNMENT_HPP
