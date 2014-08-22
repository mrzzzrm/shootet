#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP

  #include <cassert>
  #include <sstream>
  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"

  class Highscore
  {
    public:

      Highscore();
      ~Highscore();


      /* Load/Save */
        void load();
        void save();


      /* Access particular difficulties */
        util::Highscore &getHighscore(LEVEL_DIFFICULTY difficulty);


      /* Draw */
        void draw();


    private:

      /* Data */
        util::Timer timer;
        util::Highscore highscore[LEVEL_DIFFICULTY_END];

        double offset;
        int haltstart;
        int difficulty;
        bool shifting;

        struct
        {
          font::TtfLabel difficulty[LEVEL_DIFFICULTY_END];
          font::TtfLabel place[3/*HIGHSCORE_PLACECOUNT*/];
          font::TtfLabel score[LEVEL_DIFFICULTY_END][3/*HIGHSCORE_PLACECOUNT*/];
          font::TtfLabel prescore[LEVEL_DIFFICULTY_END][3/*HIGHSCORE_PLACECOUNT*/];
        }label;

  };

#endif // HIGHSCORE_HPP
