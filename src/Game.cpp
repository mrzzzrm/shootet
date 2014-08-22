#include "./Game.hpp"

using namespace std;

using namespace error;
using namespace input;
using namespace audio;
using namespace geo;
using namespace util;
using namespace font;
using namespace gfx;
using namespace etc;




//FpsCounter fps;


Game::Game()
{
  Init();
  MainIntro();
  MainLoop();

  Mix_HaltChannel(-1); // Hack, has to be implemented into SoundPlayer lateron. Prevents unlikly but possible bufferreading from deleted sound
  MainQuit();
}


Game::~Game()
{
  media::free();
}


void Game::Init()
{
  config::load();
  media::load();
  highscore.load();
  gui.load();

  fading.load(BLACK, FADING_TIME, FADE_NOT);

  playlist.addTrack(media::music::track[0]);
  playlist.addTrack(media::music::track[1]);
}


void Game::MainIntro()
{
  Timer timer;
  int phase;
  double ox, oy;


  phase = 0;
  ox = 1;
  oy = 1;


  while(phase != 5)
  {
    Input::update();
    timer.update();

    switch(phase)
    {
      case 0:
      {
        ox -= timer.getPerSecond(SPLASH_SPEED);

        if(ox <= 0)
        {
          timer.reset();
          ox = 0;
          phase = 1;
        }
      }
      break;
      case 1:
      {
        if(timer.getElapsed() >= SPLASH_TIME)
          phase = 2;
      }
      break;
      case 2:
      {
        ox -= timer.getPerSecond(SPLASH_SPEED);

        if(ox <= -1)
        {
          timer.reset();
          ox = -1;
          phase = 3;
        }
      }
      break;
      case 3:
      {
        if(timer.getElapsed() >= SPLASH_TIME)
          phase = 4;
      }
      break;
      case 4:
      {
        ox -= timer.getPerSecond(SPLASH_SPEED);

        if(ox <= -2)
        {
          timer.reset();
          ox = -2;
          phase = 5;
        }
      }
      break;
    }


    if(phase >= 4)
      mainmenu.draw(highscore);

    for(int s = 0, x = 0; s < 2 /* SPLASH_COUNT */; s++, x += SCREEN_WIDTH)
    {
      media::gfx::splash::splash[s].draw(IntPoint((int)((int)x + ox * SCREEN_WIDTH), 0));
    }


    gfx::updateScreen();
  }
}


void Game::MainLoop()
{
  playlist.play();

  while(true)
  {
    Level level;
    LEVEL_DIFFICULTY difficulty;
    Path levelpath;
    Path levelpath_base;

    mainmenu.clear();
    RunMainmenu();

    switch(mainmenu.getMainSelection())
    {
      case MAINMENU_START:
        switch(mainmenu.getSubSelection())
        {
          case MAINMENU_EASY:   levelpath_base = "dat/level/easy_";   difficulty = LEVEL_EASY;    break;
          case MAINMENU_MEDIUM: levelpath_base = "dat/level/medium_"; difficulty = LEVEL_MEDIUM;  break;
          case MAINMENU_HARD:   levelpath_base = "dat/level/hard_";   difficulty = LEVEL_HARD;    break;

          default: return; break; /* To prevent warnings */
        }
      break;

      case MAINMENU_QUIT:
        return;
      break;


      default: return; break; /* To prevent warnings */
    }


    gui.clear();
    for(int l = DEBUG_STARTLEVEL; true; l++)
    {
      levelpath = levelpath_base + integer_to_string(l) + ".tmx";
        if(!levelpath.exists())
          break;

      level.load(levelpath, difficulty, l);

      LevelSceneIntro(level);

      level.getMultiplier().run();

      LevelLoop(level);

      level.getMultiplier().pause();

      switch(level.getState())
      {
        case LEVEL_SCENE_SUCCESS: LevelSceneSuccess(level); break;
        case LEVEL_SCENE_FAILURE: LevelSceneFailure(level); break;
        case LEVEL_SCENE_QUIT:    LevelSceneQuit(level);    break;
        default: break;
      }

      if(level.getState() == LEVEL_SCENE_FAILURE || level.getState() == LEVEL_SCENE_QUIT)
        break;
    }

    HandleHighscore(level);
  }

}


void Game::MainQuit()
{

}


void Game::HandleHighscore(Level &level)
{
  /**
    TODO secure from no level played - 'level' would be in unstable state
  **/

  int place;

  place = highscore.getHighscore(level.getDifficulty()).addEntry(level.getScore(), "ingame");

  if(place != -1)
  {
    LevelSceneNewHighscore(level);
    highscore.save();
  }
}


void Game::RunMainmenu()
{
  if(fading.getAlpha() != ALPHA_TRANSPARENT)
    fading.forceStart(FADE_OUT);

  while(!mainmenu.isSelectionDone() || !fading.isDone())
  {
    Input::update();
    playlist.update();

    mainmenu.update();

    if(mainmenu.isSelectionDone() && fading.getType() != FADE_IN)
      fading.forceStart(FADE_IN);

    mainmenu.draw(highscore);
    fading.draw();

    gfx::updateScreen();
  }
}


void Game::LevelLoop(Level &level)
{
  Pause pause;


  while(true)
  {
    Input::update();
    playlist.update();

    level.update();
    if(
        level.getState() == LEVEL_SCENE_SUCCESS ||
        level.getState() == LEVEL_SCENE_FAILURE ||
        level.getState() == LEVEL_SCENE_QUIT
       )
      break;

    LevelHandlePause(level, pause);

    level.draw();
    LevelDrawUiMain(level);
    LevelDrawUiPause(level, pause);
    //media::gfx::font.drawByCenter(IntPoint(704, 460), integer_to_string((int)fps.getFps()));
    fading.draw();

    gfx::updateScreen(false);

    //fps.frameFinished();
  }
}


void Game::LevelHandlePause(Level &level, Pause &pause)
{
  if(Input::isButtonPressed(BUTTON_START) && level.getState() == LEVEL_PLAYING)
  {
    level.setState(LEVEL_PAUSED);
    level.pause();
    timer.pause();
  }

  if(level.getState() == LEVEL_PAUSED)
  {
    if(Input::isButtonPressed(BUTTON_B))
    {
      switch(pause.getSelection())
      {
        case PAUSE_CONTINUE: level.setState(LEVEL_PLAYING);    break;
        case PAUSE_QUIT:     level.setState(LEVEL_SCENE_QUIT); break;

        default: break;
      }

      timer.run();
      level.run();

      media::sfx::accept.play();
    }
  }
}


void Game::LevelDrawUiMain(Level &level)
{
  gui.draw(level);
}


void Game::LevelDrawUiPause(Level &level, Pause &pause)
{

  if(level.getState() == LEVEL_PAUSED)
  {
    pause.update();

    media::gfx::pause::box.draw(IntPoint(PAUSE_BOX_MIDDLE_X, PAUSE_BOX_MIDDLE_Y), ALIGN_BY_CENTER);

    for(int s = 0, y = PAUSE_BOX_MIDDLE_Y - media::gfx::pause::box.getCurrentFrame().getHeight()/2 + PAUSE_BOX_FIRST_Y; s < PAUSE_SELECTION_END; s++)
    {
      bool enabled;

      if(pause.getSelection() == s)
        enabled = true;
      else
        enabled = false;

      media::gfx::pause::selection[s][enabled].draw(IntPoint(PAUSE_BOX_MIDDLE_X, y), ALIGN_BY_CENTER);

      y += media::gfx::pause::selection[s][enabled].getCurrentFrame().getHeight() + PAUSE_BOX_DISTANCE_Y;
    }
  }
}


void Game::LevelSceneIntro(Level &level)
{
  int phase;
  double pa, ca;
  double pv, cv;

  timer.update(); // To asure  pause before doesn't lead to high "timer.getPerSecond()"

  Player &player = level.getPlayer();
  Camera &camera = level.getCamera();

  phase = 0;

  pv = 0;
  cv = 0;
  pa = level.getSpeed()/LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME;
  ca = level.getSpeed()/LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME;


  fading.setType(FADE_OUT);

  while(phase != 2)
  {
    Input::update();
    timer.update();
    playlist.update();
    level.update();

    pv += timer.getPerSecond(pa);
    cv += timer.getPerSecond(ca);

    player.setY(level.getPlayer().getY() - timer.getPerSecond(pv));
    camera.setPosition(level.getCamera().getPosition() - FloatVector(0, timer.getPerSecond(cv)));

    switch(phase)
    {
      case 0:

        if(cv >= level.getSpeed())
        {
          ca = 0;
          pa = 0;
          pv = level.getSpeed() + LEVEL_SCENE_INTRO_PLAYER_MOVE_SPEED;

          phase = 1;
        }

      break;

      case 1:

        if(player.getY() <= camera.getPosition().getY() + ((double)MAP_RANGE_Y/(double)level.getTileHeight()))
        {
          player.setY(camera.getPosition().getY() + ((double)MAP_RANGE_Y/(double)level.getTileHeight()));
          phase = 2;
        }

      break;
    }


    level.draw();
    LevelDrawUiMain(level);
    //media::gfx::font.drawByCenter(IntPoint(704, 460), integer_to_string((int)fps.getFps()));
    fading.draw();


    gfx::updateScreen(false);
    //fps.frameFinished();
  }


  level.setState(LEVEL_PLAYING);
}


void Game::LevelSceneSuccess(Level &level)
{
  int phase;
  double pa, ca;
  double pv, cv;


  Player &player = level.getPlayer();
  Camera &camera = level.getCamera();

  timer.update();// To asure  pause before doesn't lead to high "timer.getPerSecond()"

  phase = 0;

  pv = level.getSpeed();
  cv = level.getSpeed();
  pa = LEVEL_SCENE_SUCCESS_PLAYER_ACCELERATION;
  ca = 0;


  while(phase != 2)
  {
    Input::update();
    timer.update();
    playlist.update();
    level.update();

    pv += timer.getPerSecond(pa);
    cv += timer.getPerSecond(ca);

    player.setY(player.getY() - timer.getPerSecond(pv));
    camera.setPosition(camera.getPosition() - FloatVector(0, timer.getPerSecond(cv)));

    switch(phase)
    {
      case 0:

        if(player.getY() < camera.getY() + ((double)MAP_RANGE_Y/(double)level.getTileHeight())/2)
        {
          phase = 1;
          fading.setType(FADE_IN);
        }

      break;

      case 1:

        if(fading.isDone() && player.getY() - camera.getY() < 0)
          phase = 2;

      break;

    }


    level.draw();
    LevelDrawUiMain(level);
    //media::gfx::font.drawByCenter(IntPoint(704, 460), integer_to_string((int)fps.getFps()));
    fading.draw();
    gfx::updateScreen(false);
    //fps.frameFinished();
  }
}


void Game::LevelSceneFailure(Level &level)
{
  IntRect playerrect;
  int phase;
  int start;
  double pa, ca;
  double pv, cv;


  Player &player = level.getPlayer();
  Camera &camera = level.getCamera();

  timer.update();// To asure  pause before doesn't lead to high "timer.getPerSecond()"
  start = timer.getTicks();

  phase = 0;

  pv = 0;
  cv = level.getSpeed();
  pa = 0;
  ca = 0;


  playerrect.setX((int)(player.getX() * level.getTileWidth() - Player::getWidth()/2));
  playerrect.setY((int)(player.getY() * level.getTileHeight() - Player::getHeight()/2));
  playerrect.setWidth(Player::getWidth());
  playerrect.setHeight(Player::getHeight());

  level.getParticleManager().genExplosionRect(playerrect, LEVEL_SCENE_FAILURE_PLAYER_PARTICLES, FloatRandom(PARTICLES_SPEED_MIN, PARTICLES_SPEED_MAX), IntRandom(PARTICLES_DURATION_MIN, PARTICLES_DURATION_MAX), 0);



  while(phase != 2)
  {
    Input::update();
    timer.update();
    playlist.update();
    level.update();


    pv += timer.getPerSecond(pa);
    cv += timer.getPerSecond(ca);

    player.setY(level.getPlayer().getY() - timer.getPerSecond(pv));
    camera.setPosition(level.getCamera().getPosition() - FloatVector(0, timer.getPerSecond(cv)));


    switch(phase)
    {
      case 0:
        if(timer.getTicks() - start > LEVEL_SCENE_FAILURE_TIME)
        {
          fading.forceStart(FADE_IN);
          phase = 1;
        }
      break;


      case 1:
        if(fading.isDone())
          phase = 2;
      break;
    }


    level.draw();
    LevelDrawUiMain(level);
    //media::gfx::font.drawByCenter(IntPoint(704, 460), integer_to_string((int)fps.getFps()));
    fading.draw();
    gfx::updateScreen(false);
    //fps.frameFinished();
  }
}


void Game::LevelSceneQuit(Level &level)
{
  int phase;
  double pa, ca;
  double pv, cv;


  Player &player = level.getPlayer();
  Camera &camera = level.getCamera();

  timer.update();// To asure  pause before doesn't lead to high "timer.getPerSecond()"

  phase = 0;

  pv = 0;
  cv = 0;
  pa = 0;
  ca = 0;


  fading.forceStart(FADE_IN);


  while(phase != 1)
  {
    Input::update();
    timer.update();
    playlist.update();
    level.update();


    pv += timer.getPerSecond(pa);
    cv += timer.getPerSecond(ca);

    player.setY(level.getPlayer().getY() - timer.getPerSecond(pv));
    camera.setPosition(level.getCamera().getPosition() - FloatVector(0, timer.getPerSecond(cv)));


    switch(phase)
    {
      case 0:
        if(fading.isDone())
          phase = 1;
      break;
    }



    level.draw();
    LevelDrawUiMain(level);
    //media::gfx::font.drawByCenter(IntPoint(704, 460), integer_to_string((int)fps.getFps()));
    fading.draw();
    gfx::updateScreen(false);
    //fps.frameFinished();
  }
}


void Game::LevelSceneNewHighscore(Level &level)
{
  TtfLabel label_score;
  Timer timer;
  int phase;


  phase = 0;

  fading.forceStart(FADE_OUT);

  label_score = TtfLabel(&media::font::new_highscore, integer_to_string(level.getScore()));


  while(phase != 3)
  {
    Input::update();
    timer.update();
    playlist.update();


    switch(phase)
    {
      case 0: // fade out
        if(fading.isDone())
        {
          timer.reset();
          phase = 1;
        }
      break;
      case 1: // Show score
      {
        if(timer.getElapsed() >= LEVEL_SCENE_NEW_HIGHSCORE_TIME)
        {
          fading.forceStart(FADE_IN);
          phase = 2;
        }
      }
      break;
      case 2: // Fade out
        if(fading.isDone())
        {
          phase = 3;
        }
      break;
    }

    media::gfx::new_highscore.draw(IntPoint(LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_X, LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_Y), ALIGN_BY_CENTER);
    label_score.draw(IntPoint(LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_X, LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_Y), ALIGN_BY_CENTER);
    fading.draw();

    gfx::updateScreen();
  }


}

