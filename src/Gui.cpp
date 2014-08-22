#include "./Gui.hpp"

using namespace std;
using namespace geo;
using namespace util;
using namespace gfx;
using namespace etc;
using namespace font;

/*
  class Gui
*/
  Gui::Gui()
  {
    clear();
  }


  Gui::~Gui()
  {

  }


  void Gui::load()
  {
    multiplier.label_factor.load(&media::font::multiplier, "", Color(255, 255, 255), TTF_BLENDED);

    for(int i = 0; i < ITEM_TYPE_END; i++)
    {
      itemcount.label_count[i].load(&media::font::item_count, "", Color(255, 255, 255), TTF_BLENDED);
    }

    score.label_prefix.load(&media::font::score, "", Color(128, 128, 128), TTF_BLENDED);
    score.label_suffix.load(&media::font::score, "", Color(255, 255, 255), TTF_BLENDED);
  }


  void Gui::clear()
  {
    timer.update();

    multiplier.displayed_filling = 0;
    multiplier.rel_factor = 1;
  }


  void Gui::update(Level &level)
  {
    stringstream ss;
    int digits;
    s8 s;
    double remain;


    timer.update();


    /* Multiplier */
      if(level.getMultiplier().getFactor() == multiplier.rel_factor)
      {
        remain = level.getMultiplier().getRelativeFilling() - multiplier.displayed_filling;
        s = sgn(remain);
      }
      else if(level.getMultiplier().getFactor() > multiplier.rel_factor)
      {
        remain = 1 - multiplier.displayed_filling;
        s = sgn(remain);
      }
      else
      {
        remain = -multiplier.displayed_filling;
        s = sgn(remain);
      }

      if(abs(remain) < abs(timer.getPerSecond(MULTIPLIER_FILL_SPEED)))
      {
        if(level.getMultiplier().getFactor() > multiplier.rel_factor)
          multiplier.displayed_filling = 0;
        else if(level.getMultiplier().getFactor() < multiplier.rel_factor)
          multiplier.displayed_filling = 1;
        else
          multiplier.displayed_filling += remain;

        multiplier.rel_factor = level.getMultiplier().getFactor();
      }
      else
      {
        multiplier.displayed_filling += timer.getPerSecond(MULTIPLIER_FILL_SPEED) * s;
      }

      multiplier.label_factor.setText(integer_to_string(level.getMultiplier().getFactor()));

    /* Itemcount */
      for(int i = 0; i < ITEM_TYPE_END; i++)
      {
        itemcount.label_count[i].setText(integer_to_string(level.getPlayer().getItemCount((ITEM_TYPE)i)));
      }


    /* Score */
      ss.str("");
      digits = integer_get_digitcount(level.getScore());
      for(int d = 0; d < SCORE_DIGIT_COUNT - digits; d++)
      {
        ss << "0";
      }
      score.label_prefix.setText(ss.str());
      score.label_suffix.setText(integer_to_string(level.getScore()));

  }


  void Gui::draw(Level &level)
  {
    /* Update */
      update(level);


    /* Main */
      media::gfx::gui::left.draw(IntPoint(GUI_LEFT_X, GUI_LEFT_Y));
      media::gfx::gui::right.draw(IntPoint(GUI_RIGHT_X, GUI_RIGHT_Y));

      media::gfx::gui::border.draw(IntPoint
        (
          (int)(level.getCamera().getOffset().getX() * level.getTileWidth())  + MAP_MIDDLE_X,
          (int)(level.getCamera().getOffset().getY() * level.getTileHeight()) + (int)(MAP_START_Y + MAP_RANGE_Y - level.getTileHeight() * BORDER_OFFSET)),
           ALIGN_BY_CENTER
        );


    /* Items */
      for(int i = 0; i < ITEM_TYPE_END; i++)
      {
        itemcount.label_count[i].draw(IntPoint
          (
            ITEM_COUNT_RIGHT_X - itemcount.label_count[i].getSize().getWidth(),
            ITEM_COUNT_START_Y + ITEM_COUNT_STEP_Y*i
          ));
      }


    /* Score */
      score.label_prefix.draw(IntPoint(SCORE_X, SCORE_Y));
      score.label_suffix.draw(IntPoint(SCORE_X + score.label_prefix.getSize().getWidth(), SCORE_Y));


    /* Multiplier */
      level.getMultiplier().draw(multiplier.displayed_filling);
      multiplier.label_factor.draw(IntPoint(MULTIPLIER_FACTOR_RIGHT_X - multiplier.label_factor.getSize().getWidth(), MULTIPLIER_FACTOR_Y));
  }


