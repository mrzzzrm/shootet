#include "./Highscore.hpp"

using namespace std;

using namespace xml;
using namespace util;
using namespace gfx;
using namespace font;
using namespace geo;
using namespace etc;
using namespace error;


/*
  Class Highscore
*/
  ::Highscore::Highscore()
  {
    /* Labels */
    for(int d = 0; d < LEVEL_DIFFICULTY_END; d++)
    {
      label.difficulty[d].setFont(&media::font::font);
      label.difficulty[d].setColor(Color(255, 255, 255));
      label.difficulty[d].setRendermode(TTF_BLENDED);

      for(int p = 0; p < HIGHSCORE_BAR_PLACECOUNT; p++)
      {
        label.score[d][p].setFont(&media::font::font);
        label.score[d][p].setColor(Color(255, 255, 255));
        label.score[d][p].setRendermode(TTF_BLENDED);
        label.prescore[d][p].setFont(&media::font::font);
        label.prescore[d][p].setColor(Color(128, 128, 128));
        label.prescore[d][p].setRendermode(TTF_BLENDED);
      }
    }

    for(int p = 0; p < HIGHSCORE_BAR_PLACECOUNT; p++)
    {
      label.place[p].setFont(&media::font::font);
      label.place[p].setColor(Color(255, 0, 0));
      label.place[p].setRendermode(TTF_BLENDED);
    }


    label.difficulty[LEVEL_EASY].setText("EASY");
    label.difficulty[LEVEL_MEDIUM].setText("MEDIUM");
    label.difficulty[LEVEL_HARD].setText("HARD");

    label.place[0].setText("1ST");
    label.place[1].setText("2ND");
    label.place[2].setText("3RD");


    /* Values */
    offset = 0;
    haltstart = timer.getTicks();
    difficulty = 0;
    shifting = false;

  }


  ::Highscore::~Highscore()
  {

  }


  void ::Highscore::load()
  {
    Xml xml;

    if(Path("hs.xml").exists())
    {
      xml.load(Path(HIGHSCORE_PATH));
    }
    else
    {
      xml.load(Path(DEFAULT_HIGHSCORE_PATH));
    }


    if(!xml.toRootBlock("highscores"))
      throw Exception() << "Illegal rootblock of 'hs.xml'";


    if(xml.toSubBlock("highscore"))
    {
      for(int hs = 0; hs > 0 ? xml.toNextBlock("highscore") : true; hs++)
      {
        if(hs >= LEVEL_DIFFICULTY_END)
          throw Exception() << "Too many 'highscore' blocks";

        highscore[hs].load(xml);
      }

      xml.toBaseBlock();
    }

  }


  void ::Highscore::save()
  {
    stringstream ss;

    ss << "<highscores>";
    for(int hs = 0; hs < LEVEL_DIFFICULTY_END; hs++)
    {
      ss << highscore[hs].getXml().toString();
    }
    ss << "</highscores>";

    string_to_file(ss.str(), HIGHSCORE_PATH);
  }


  util::Highscore &::Highscore::getHighscore(LEVEL_DIFFICULTY difficulty)
  {
    assert(difficulty != LEVEL_DIFFICULTY_END);
    return highscore[difficulty];
  }


  void ::Highscore::draw()
  {
    int x;
    int sx[HIGHSCORE_BAR_PLACECOUNT];
    int order[HIGHSCORE_BAR_PLACECOUNT];


    timer.update();

    /* Shifting/Offset */
      if(timer.getTicks() - haltstart > HIGHSCORE_BAR_HALT_TIME)
      {
        if(shifting)
        {
          offset -= timer.getPerSecond(HIGHSCORE_BAR_SPEED * SCREEN_WIDTH);
        }
        else
        {
          offset = SCREEN_WIDTH;
          shifting = true;
          difficulty++;

          if(difficulty == LEVEL_DIFFICULTY_END)
            difficulty = 0;
        }
      }

      if(offset < 0)
      {
        offset = 0;
        haltstart = timer.getTicks();
        shifting = false;
      }


    /* Order */
      order[1] = difficulty;

      if(order[1] > 0)
        order[0] = order[1] - 1;
      else
        order[0] = LEVEL_DIFFICULTY_END - 1;

      if(order[1] < LEVEL_DIFFICULTY_END - 1)
        order[2] = order[1] + 1;
      else
        order[2] = 0;


    /* Texts */
      for(int d = 0; d < LEVEL_DIFFICULTY_END; d++)
      {
        for(int p = 0; p < HIGHSCORE_BAR_PLACECOUNT; p++)
        {
          int score = highscore[d].getEntryScore(p);
          int digits = integer_get_digitcount(score);

          label.score[d][p].setText(integer_to_string(score));
          label.prescore[d][p].setText("");
          if(HIGHSCORE_BAR_SCOREDIGITS > digits)
          {
            string ps;

            for(int z = 0; z < HIGHSCORE_BAR_SCOREDIGITS - digits; z++)
              ps.append("0");
            label.prescore[d][p].setText(ps);
          }
        }
      }


    /* Draw */
      sx[0] = (int)offset - SCREEN_WIDTH;
      sx[1] = (int)offset;
      sx[2] = (int)offset + SCREEN_WIDTH;

      for(int o = 0; o < 3; o++)
      {
        label.difficulty[order[o]].draw(IntPoint(sx[o] + HIGHSCORE_BAR_DIFFICULTY_START_X, HIGHSCORE_BAR_START_Y));

        x = HIGHSCORE_BAR_PLACES_START_X;
        for(int p = 0; p < HIGHSCORE_BAR_PLACECOUNT; p++)
        {
          label.place[p].draw(IntPoint(sx[o] + x, HIGHSCORE_BAR_START_Y));
            x += label.place[p].getSize().getWidth() + HIGHSCORE_BAR_PLACE_SCORE_SPACING;

          label.prescore[order[o]][p].draw(IntPoint(sx[o] + x, HIGHSCORE_BAR_START_Y));
            x += label.prescore[order[o]][p].getSize().getWidth();

          label.score[order[o]][p].draw(IntPoint(sx[o] + x, HIGHSCORE_BAR_START_Y));
            x += label.score[order[o]][p].getSize().getWidth() + HIGHSCORE_BAR_SCORE_PLACE_SPACING;
        }
      }
  }

