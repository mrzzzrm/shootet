#ifndef MAINMENU_HPP
#define MAINMENU_HPP

  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"
  #include "./Highscore.hpp"


  class Mainmenu
  {
    public:

      Mainmenu();
      ~Mainmenu();


      /* Clear */
        void clear();


      /* Selection */
        MAINMENU_MAIN_SELECTION getMainSelection() const;
        MAINMENU_SUB_SELECTION getSubSelection() const;

        bool isSelectionDone();

      /* Loop */
        void update();
        void draw(Highscore &highscore);


    private:

      /* Data */
        int mainselection;
        int subselection;
        bool sub_selected;
        bool howto_selected;
        bool selection_done;
        double block_offset;
        double howto_offset;
        int howto_shown;

        util::Timer timer;

  };

#endif // MAINMENU_HPP
