#ifndef GAME_HPP
#define GAME_HPP

  #include <cmath>
  #include "framework.hpp"

  #include "./media.hpp"
  #include "./config.hpp"
  #include "./Pause.hpp"
  #include "./Level.hpp"
  #include "./Mainmenu.hpp"
  #include "./Highscore.hpp"
  #include "./Gui.hpp"


  class Game
  {
    public:

      Game();
      ~Game();


    private:

      /* Data */
        audio::Playlist playlist;
        gfx::ColorFading fading;
        Highscore highscore;
        Gui gui;
        util::Timer timer;
        Mainmenu mainmenu;


      /* Internals */
        void Init();

        void MainIntro();
        void MainLoop();
        void MainQuit();

        void HandleHighscore(Level &level);

        void RunMainmenu();

        void LevelLoop(Level &level);

        void LevelHandlePause(Level &level, Pause &pause);

        void LevelDrawUiMain(Level &level);
        void LevelDrawUiPause(Level &level, Pause &pause);

        void LevelSceneIntro(Level &level);
        void LevelSceneSuccess(Level &level);
        void LevelSceneFailure(Level &level);
        void LevelSceneQuit(Level &level);
        void LevelSceneNewHighscore(Level &level);

  };

#endif // GAME_HPP
