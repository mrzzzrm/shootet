#ifndef GUI_HPP
#define GUI_HPP

  #include <sstream>
  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"
  #include "./Level.hpp"


  class Gui
  {
    public:

      Gui();
      ~Gui();


      /* Load */
        void load();

      /* Clear */
        void clear();


      /* Loop */
        void update(Level &level);
        void draw(Level &level);


    private:

      /* Data */
        util::Timer timer;

        struct
        {
          font::TtfLabel label_factor;
          double displayed_filling;
          double rel_factor;
        }multiplier;

        struct
        {
           font::TtfLabel label_count[ITEM_TYPE_END];
        }itemcount;

        struct
        {
          font::TtfLabel label_prefix;
          font::TtfLabel label_suffix;
        }score;


  };


#endif
