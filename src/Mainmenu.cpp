#include "./Mainmenu.hpp"

using namespace std;

using namespace input;
using namespace geo;
using namespace etc;


/*
  Class Mainmenu
*/
  Mainmenu::Mainmenu()
  {
    clear();
  }


  Mainmenu::~Mainmenu()
  {

  }


  void Mainmenu::clear()
  {
    mainselection = 0;
    subselection = 0;
    sub_selected = false;
    howto_selected = false;
    selection_done = false;
    block_offset = 0;
    howto_offset = 0;
    howto_shown = -1;
  }


  MAINMENU_MAIN_SELECTION Mainmenu::getMainSelection() const
  {
    return (MAINMENU_MAIN_SELECTION)mainselection;
  }


  MAINMENU_SUB_SELECTION Mainmenu::getSubSelection() const
  {
    return (MAINMENU_SUB_SELECTION)subselection;
  }


  bool Mainmenu::isSelectionDone()
  {
    return selection_done;
  }


  void Mainmenu::update()
  {
    double target_offset, remain_offset;

    timer.update();


    /* Selection */
      if(sub_selected)
      {
        if(Input::isButtonPressed(BUTTON_RIGHT) && subselection < MAINMENU_SUB_END-1)
          subselection++;
        if(Input::isButtonPressed(BUTTON_LEFT) && subselection > 0)
          subselection--;

        if(Input::isButtonPressed(BUTTON_X))
        {
          sub_selected = false;
          media::sfx::deny.play();
        }

        if(Input::isButtonPressed(BUTTON_B))
        {
          selection_done = true;
          media::sfx::accept.play();
        }

      }
      else if(howto_selected)
      {

      }
      else
      {
        if(Input::isButtonPressed(BUTTON_RIGHT) && mainselection < MAINMENU_MAIN_END-1)
          mainselection++;
        if(Input::isButtonPressed(BUTTON_LEFT) && mainselection > 0)
          mainselection--;

        if(Input::isButtonPressed(BUTTON_B) && mainselection == 0)
        {
          sub_selected = true;
          media::sfx::accept.play();
        }
        if(Input::isButtonPressed(BUTTON_B) && mainselection == 1)
        {
          howto_selected = true;
          howto_shown = 0;
          howto_offset = 0;
          media::sfx::accept.play();
        }
        if(Input::isButtonPressed(BUTTON_B) && mainselection == 2)
        {
          selection_done = true;
        }
      }


    /* Move blocks */
      if(sub_selected && mainselection == MAINMENU_START)
        target_offset = -(int)MAINMENU_BLOCK_OFFSET;
      else
        target_offset = 0;

      remain_offset = target_offset - block_offset;
      block_offset += util::abs_min(remain_offset, (double)timer.getPerSecond((double)MAINMENU_BLOCK_SPEED) * util::sgn(remain_offset));


    /* Move howtoscreen */
      if(howto_shown != -1)
      {
        howto_offset += timer.getPerSecond(MAINMENU_HOWTO_SPEED);

        if(howto_shown == 0 && howto_offset >= 1)
        {
          howto_offset = 1;

          if(Input::isButtonPressed(BUTTON_B))
            howto_shown = 1;
        }

        if(howto_shown == 1 && howto_offset >= 2)
        {
          howto_offset = 2;

          if(Input::isButtonPressed(BUTTON_B))
            howto_shown = 2;
        }

        if(howto_shown == 2 && howto_offset >= 3)
        {
          howto_offset = 0;
          howto_shown = -1;
          howto_selected = false;
        }
      }
  }


  void Mainmenu::draw(Highscore &highscore)
  {
    media::gfx::mainmenu::background.draw(IntPoint(0, 0));
    media::gfx::mainmenu::title.draw(IntPoint(MAINMENU_TITLE_X, MAINMENU_TITLE_Y), ALIGN_BY_CENTER);


    /* Main - block */
      for(int m = 0; m < MAINMENU_MAIN_END; m++)
      {
        IntPoint center;
        center.setX((int)(MAINMENU_MAIN_X[m] + block_offset));
        center.setY(MAINMENU_MAIN_Y);

        if(m != mainselection)
          media::gfx::mainmenu::main[m][0].draw(center, ALIGN_BY_CENTER);
        else
          media::gfx::mainmenu::main[m][1].draw(center, ALIGN_BY_CENTER);
      }

    /* Sub - block */
      for(int s = 0; s < MAINMENU_SUB_END; s++)
      {
        IntPoint center;

        center.setX((int)(MAINMENU_SUB_X[s] + MAINMENU_BLOCK_OFFSET + block_offset));
        center.setY(MAINMENU_SUB_Y);

        if(s != subselection)
          media::gfx::mainmenu::sub[s][0].draw(center, ALIGN_BY_CENTER);
        else
          media::gfx::mainmenu::sub[s][1].draw(center, ALIGN_BY_CENTER);
      }


    /* Highscore */
      highscore.draw();


    /* Howto */
      for(int ht = 0; ht < 2 /* HOWTO_COUNT */; ht++)
      {
        media::gfx::mainmenu::howto[ht].draw(IntPoint(0, (int)(SCREEN_HEIGHT * (-ht+howto_offset-1))));
      }
  }

