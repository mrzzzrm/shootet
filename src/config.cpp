#include "./config.hpp"


#if defined(PLATFORM_WINDOWS) | defined(PLATFORM_LINUX) | defined(PLATFORM_PANDORA)
  int SCREEN_WIDTH = 800;
  int SCREEN_HEIGHT = 480;
#elif defined(PLATFORM_WIZ) | defined(PLATFORM_CAANOO) | defined(PLATFORM_GP2X)
  int SCREEN_WIDTH = 320;
  int SCREEN_HEIGHT = 240;
#else
  #error No known platform specified
#endif


#if defined(PLATFORM_WINDOWS) | defined(PLATFORM_LINUX)
  bool FULLSCREEN = false;
#elif defined(PLATFORM_PANDORA) | defined(PLATFORM_WIZ) | defined(PLATFORM_CAANOO) | defined(PLATFORM_GP2X)
  bool FULLSCREEN = true;
#else
  #error No known platform specified
#endif


#include <iostream>
using namespace std;
using namespace util;
using namespace error;


/**
  Level
**/
  int MAP_START_Y;
  int MAP_RANGE_Y;
  int MAP_MIDDLE_X;

  double PLAYER_OFFSET;
  double BORDER_OFFSET;

  double NO_TILES_IN_SCREEN_SPEED;

  double QUAD_SPEED;
  double PLAYER_BUTTON_UP_EXTRA_SPEED;
  double ROCKET_SPEED;
  double ITEM_SPEED;
  double ITEM_FASTCOLLECT_SPEED;

  double PLAYER_SPEED_X;

  double QUAD_RAPIDFIRE_SPEED;


  int SCORE_PER_TILE;
  double SCORE_SIZE_FACTOR;

  int QUAD_TILE_ID;

  int PARTICLES_PER_TILE;
  int PARTICLES_SPEED_MIN;
  int PARTICLES_SPEED_MAX;
  int PARTICLES_DURATION_MIN;
  int PARTICLES_DURATION_MAX;

  double ERUPTION_OFFSET_MAX;
  int ERUPTION_TIME_PER_TILE ;
  int ERUPTION_TIME_MAX;
  int ERUPTION_TIME_FAILURE;

  int MULTIPLIER_MAX_FACTOR;
  double MULTIPLIER_DECREASE_SPEED_BASE;
  double MULTIPLIER_DECREASE_SPEED_FACTOR;
  double MULTIPLIER_DECREASE_SPEED_MAX;
  int MULTIPLIER_MAX_FILLING;
  int MULTIPLIER_MIN_DESTRUCTION;
  double MULTIPLIER_INIT_FILLING;
  double MULTIPLIER_FAIL_FACTOR;

  double DESTHALT_PER_TILE;
  double DESTHALT_MAX;

  int STOP_TIME;
  int RAPIDFIRE_TIME;

  int ITEM_REQUIRED_DESTRUCTION[ITEM_TYPE_END];
  int ITEM_COUNT_LIMIT[ITEM_TYPE_END];

  int ROCKET_CURVE_TIME_DIVIDOR;
  int ROCKET_CURVE_SIN_DIVIDOR;



/**
  UI
**/
  int GUI_LEFT_X;
  int GUI_LEFT_Y;
  int GUI_RIGHT_X;
  int GUI_RIGHT_Y;
  int ITEM_COUNT_START_Y;
  int ITEM_COUNT_STEP_Y;
  int ITEM_COUNT_RIGHT_X;
  int ITEM_COUNT_FONT_SIZE;
  int SCORE_X;
  int SCORE_Y;
  int SCORE_DIGIT_COUNT;
  int SCORE_FONT_SIZE;

  int GUI_VIEWPORT_X;
  int GUI_VIEWPORT_Y;
  int GUI_VIEWPORT_WIDTH;
  int GUI_VIEWPORT_HEIGHT;

  int MAINMENU_BLOCK_OFFSET;
  int MAINMENU_BLOCK_SPEED;
  int MAINMENU_MAIN_Y;
  int MAINMENU_MAIN_X[MAINMENU_MAIN_END];
  int MAINMENU_SUB_Y;
  int MAINMENU_SUB_X[MAINMENU_SUB_END];
  int MAINMENU_TITLE_X;
  int MAINMENU_TITLE_Y;
  double MAINMENU_HOWTO_SPEED;

  int PAUSE_BOX_MIDDLE_X;
  int PAUSE_BOX_MIDDLE_Y;
  int PAUSE_BOX_FIRST_Y;
  int PAUSE_BOX_DISTANCE_Y;

  int MULTIPLIER_BAR_X;
  int MULTIPLIER_BAR_Y;
  double MULTIPLIER_FILL_SPEED;
  int MULTIPLIER_FONT_SIZE;
  int MULTIPLIER_FACTOR_RIGHT_X;
  int MULTIPLIER_FACTOR_Y;

  int HIGHSCORE_BAR_START_Y;
  int HIGHSCORE_BAR_DIFFICULTY_START_X;
  int HIGHSCORE_BAR_PLACES_START_X ;
  int HIGHSCORE_BAR_PLACE_SCORE_SPACING;
  int HIGHSCORE_BAR_SCORE_PLACE_SPACING;
  int HIGHSCORE_BAR_HALT_TIME ;
  double HIGHSCORE_BAR_SPEED;
  int HIGHSCORE_BAR_PLACECOUNT = 3;
  int HIGHSCORE_BAR_SCOREDIGITS = 8;


/**
  SCENES
**/
  double LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME;
  double LEVEL_SCENE_INTRO_PLAYER_MOVE_SPEED;

  double LEVEL_SCENE_SUCCESS_PLAYER_ACCELERATION;

  int LEVEL_SCENE_FAILURE_TIME;
  int LEVEL_SCENE_FAILURE_PLAYER_PARTICLES;

  int LEVEL_SCENE_QUIT_TIME ;

  int LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_X;
  int LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_Y;
  int LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_X;
  int LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_Y;
  int LEVEL_SCENE_NEW_HIGHSCORE_FONT_SIZE;
  int LEVEL_SCENE_NEW_HIGHSCORE_TIME;




/**
	MISC
**/
  std::string HIGHSCORE_PATH;
  std::string DEFAULT_HIGHSCORE_PATH;
  int FADING_TIME;
  gfx::Color FADING_COLOR = gfx::Color(gfx::WHITE);
  int FONT_NORMAL_SIZE;
  //int SPLASH_COUNT;
  double SPLASH_SPEED;
  int SPLASH_TIME;

  int SFX_BLOCK_EXPLOSION_MINIMUM[3-1];
  int DEBUG_STARTLEVEL;



namespace config
{
  void load()
  {
    Config config(Path("dat/config.conf"));

    try
    {
      /**
        Level
      **/
        MAP_START_Y = config.getInteger("MAP_START_Y");
        MAP_RANGE_Y = config.getInteger("MAP_RANGE_Y");
        MAP_MIDDLE_X = config.getInteger("MAP_MIDDLE_X");

        BORDER_OFFSET = config.getFloat("BORDER_OFFSET");
        PLAYER_OFFSET = config.getFloat("PLAYER_OFFSET");

        NO_TILES_IN_SCREEN_SPEED = config.getFloat("NO_TILES_IN_SCREEN_SPEED");

        QUAD_SPEED = config.getFloat("QUAD_SPEED");
        QUAD_RAPIDFIRE_SPEED = config.getFloat("QUAD_RAPIDFIRE_SPEED");
        ROCKET_SPEED = config.getFloat("ROCKET_SPEED");
        ITEM_SPEED = config.getFloat("ITEM_SPEED");
        ITEM_FASTCOLLECT_SPEED = config.getFloat("ITEM_FASTCOLLECT_SPEED");

        PLAYER_SPEED_X = config.getFloat("PLAYER_SPEED_X");
        PLAYER_BUTTON_UP_EXTRA_SPEED = config.getFloat("PLAYER_BUTTON_UP_EXTRA_SPEED");

        SCORE_PER_TILE = config.getInteger("SCORE_PER_TILE");
        SCORE_SIZE_FACTOR = config.getFloat("SCORE_SIZE_FACTOR");

        QUAD_TILE_ID = config.getInteger("QUAD_TILE_ID");

        PARTICLES_PER_TILE = config.getInteger("PARTICLES_PER_TILE");
        PARTICLES_SPEED_MIN = config.getInteger("PARTICLES_SPEED_MIN");
        PARTICLES_SPEED_MAX = config.getInteger("PARTICLES_SPEED_MAX");
        PARTICLES_DURATION_MIN = config.getInteger("PARTICLES_DURATION_MIN");
        PARTICLES_DURATION_MAX = config.getInteger("PARTICLES_DURATION_MAX");

        ERUPTION_OFFSET_MAX = config.getFloat("ERUPTION_OFFSET_MAX");
        ERUPTION_TIME_PER_TILE = config.getInteger("ERUPTION_TIME_PER_TILE");
        ERUPTION_TIME_MAX = config.getInteger("ERUPTION_TIME_MAX");
        ERUPTION_TIME_FAILURE = config.getInteger("ERUPTION_TIME_FAILURE");


        MULTIPLIER_MAX_FACTOR = config.getInteger("MULTIPLIER_MAX_FACTOR");
        MULTIPLIER_DECREASE_SPEED_BASE = config.getFloat("MULTIPLIER_DECREASE_SPEED_BASE");
        MULTIPLIER_DECREASE_SPEED_FACTOR = config.getFloat("MULTIPLIER_DECREASE_SPEED_FACTOR");
        MULTIPLIER_DECREASE_SPEED_MAX = config.getFloat("MULTIPLIER_DECREASE_SPEED_MAX");
        MULTIPLIER_MAX_FILLING = config.getInteger("MULTIPLIER_MAX_FILLING");
        MULTIPLIER_MIN_DESTRUCTION = config.getInteger("MULTIPLIER_MIN_DESTRUCTION");
        MULTIPLIER_INIT_FILLING = config.getFloat("MULTIPLIER_INIT_FILLING");
        MULTIPLIER_FAIL_FACTOR = config.getFloat("MULTIPLIER_FAIL_FACTOR");

        DESTHALT_PER_TILE = config.getFloat("DESTHALT_PER_TILE");
        DESTHALT_MAX = config.getFloat("DESTHALT_MAX");

        STOP_TIME = config.getInteger("STOP_TIME");
        RAPIDFIRE_TIME = config.getInteger("RAPIDFIRE_TIME");

        ITEM_REQUIRED_DESTRUCTION[0] = config.getInteger("ITEM_REQUIRED_DESTRUCTION[0]");
        ITEM_REQUIRED_DESTRUCTION[1] = config.getInteger("ITEM_REQUIRED_DESTRUCTION[1]");
        ITEM_REQUIRED_DESTRUCTION[2] = config.getInteger("ITEM_REQUIRED_DESTRUCTION[2]");
        ITEM_REQUIRED_DESTRUCTION[3] = config.getInteger("ITEM_REQUIRED_DESTRUCTION[3]");

        ITEM_COUNT_LIMIT[0] = config.getInteger("ITEM_COUNT_LIMIT[0]");
        ITEM_COUNT_LIMIT[1] = config.getInteger("ITEM_COUNT_LIMIT[1]");
        ITEM_COUNT_LIMIT[2] = config.getInteger("ITEM_COUNT_LIMIT[2]");
        ITEM_COUNT_LIMIT[3] = config.getInteger("ITEM_COUNT_LIMIT[3]");

        ROCKET_CURVE_TIME_DIVIDOR = config.getInteger("ROCKET_CURVE_TIME_DIVIDOR");
        ROCKET_CURVE_SIN_DIVIDOR = config.getInteger("ROCKET_CURVE_SIN_DIVIDOR");






      /**
        UI
      **/
        GUI_LEFT_X = config.getInteger("GUI_LEFT_X");
        GUI_LEFT_Y = config.getInteger("GUI_LEFT_Y");
        GUI_RIGHT_X = config.getInteger("GUI_RIGHT_X");
        GUI_RIGHT_Y = config.getInteger("GUI_RIGHT_Y");
        ITEM_COUNT_START_Y = config.getInteger("ITEM_COUNT_START_Y");
        ITEM_COUNT_STEP_Y  = config.getInteger("ITEM_COUNT_STEP_Y");
        ITEM_COUNT_RIGHT_X = config.getInteger("ITEM_COUNT_RIGHT_X");
        ITEM_COUNT_FONT_SIZE = config.getInteger("ITEM_COUNT_FONT_SIZE");
        SCORE_X = config.getInteger("SCORE_X");
        SCORE_Y = config.getInteger("SCORE_Y");
        SCORE_DIGIT_COUNT = config.getInteger("SCORE_DIGIT_COUNT");
        SCORE_FONT_SIZE = config.getInteger("SCORE_FONT_SIZE");

        GUI_VIEWPORT_X = config.getInteger("GUI_VIEWPORT_X");
        GUI_VIEWPORT_Y = config.getInteger("GUI_VIEWPORT_Y");
        GUI_VIEWPORT_WIDTH = config.getInteger("GUI_VIEWPORT_WIDTH");
        GUI_VIEWPORT_HEIGHT = config.getInteger("GUI_VIEWPORT_HEIGHT");

        MAINMENU_BLOCK_OFFSET = config.getInteger("MAINMENU_BLOCK_OFFSET");
        MAINMENU_BLOCK_SPEED = config.getInteger("MAINMENU_BLOCK_SPEED");
        MAINMENU_MAIN_Y = config.getInteger("MAINMENU_MAIN_Y");
        MAINMENU_SUB_Y = config.getInteger("MAINMENU_SUB_Y");

        for(int m = 0; m < MAINMENU_MAIN_END; m++)
          MAINMENU_MAIN_X[m] = config.getInteger(string("MAINMENU_MAIN_X[") + integer_to_string(m) + string("]"));
        for(int s = 0; s < MAINMENU_SUB_END; s++)
          MAINMENU_SUB_X[s] = config.getInteger(string("MAINMENU_SUB_X[") + integer_to_string(s) + string("]"));

        MAINMENU_TITLE_X = config.getInteger("MAINMENU_TITLE_X");
        MAINMENU_TITLE_Y = config.getInteger("MAINMENU_TITLE_Y");
        MAINMENU_HOWTO_SPEED = config.getFloat("MAINMENU_HOWTO_SPEED");

        PAUSE_BOX_MIDDLE_X = config.getInteger("PAUSE_BOX_MIDDLE_X");
        PAUSE_BOX_MIDDLE_Y = config.getInteger("PAUSE_BOX_MIDDLE_Y");
        PAUSE_BOX_FIRST_Y = config.getInteger("PAUSE_BOX_FIRST_Y");
        PAUSE_BOX_DISTANCE_Y = config.getInteger("PAUSE_BOX_DISTANCE_Y");

        MULTIPLIER_BAR_X = config.getInteger("MULTIPLIER_BAR_X");
        MULTIPLIER_BAR_Y = config.getInteger("MULTIPLIER_BAR_Y");
        MULTIPLIER_FILL_SPEED = config.getFloat("MULTIPLIER_FILL_SPEED");
        MULTIPLIER_FONT_SIZE = config.getInteger("MULTIPLIER_FONT_SIZE");
        MULTIPLIER_FACTOR_RIGHT_X = config.getInteger("MULTIPLIER_FACTOR_RIGHT_X");
        MULTIPLIER_FACTOR_Y = config.getInteger("MULTIPLIER_FACTOR_Y");

        HIGHSCORE_BAR_START_Y = config.getInteger("HIGHSCORE_BAR_START_Y");
        HIGHSCORE_BAR_DIFFICULTY_START_X = config.getInteger("HIGHSCORE_BAR_DIFFICULTY_START_X");
        HIGHSCORE_BAR_PLACES_START_X = config.getInteger("HIGHSCORE_BAR_PLACES_START_X");
        HIGHSCORE_BAR_PLACE_SCORE_SPACING = config.getInteger("HIGHSCORE_BAR_PLACE_SCORE_SPACING");
        HIGHSCORE_BAR_SCORE_PLACE_SPACING = config.getInteger("HIGHSCORE_BAR_SCORE_PLACE_SPACING");
        HIGHSCORE_BAR_HALT_TIME = config.getInteger("HIGHSCORE_BAR_HALT_TIME");
        HIGHSCORE_BAR_SPEED = config.getFloat("HIGHSCORE_BAR_SPEED");
  //      HIGHSCORE_BAR_PLACECOUNT = config.getInteger("HIGHSCORE_BAR_PLACECOUNT");
  //      HIGHSCORE_BAR_SCOREDIGITS = config.getInteger("HIGHSCORE_BAR_SCOREDIGITS");



      /**
        SCENES
      **/
        LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME = config.getFloat("LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME");
        LEVEL_SCENE_INTRO_PLAYER_MOVE_SPEED = config.getFloat("LEVEL_SCENE_INTRO_PLAYER_MOVE_SPEED");
        LEVEL_SCENE_SUCCESS_PLAYER_ACCELERATION = config.getFloat("LEVEL_SCENE_SUCCESS_PLAYER_ACCELERATION");
        LEVEL_SCENE_FAILURE_TIME = config.getInteger("LEVEL_SCENE_FAILURE_TIME");
        LEVEL_SCENE_FAILURE_PLAYER_PARTICLES = config.getInteger("LEVEL_SCENE_FAILURE_PLAYER_PARTICLES");
        LEVEL_SCENE_QUIT_TIME = config.getInteger("LEVEL_SCENE_QUIT_TIME");
        LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_X = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_X");
        LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_Y = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_Y");
        LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_X = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_X");
        LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_Y = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_Y");
        LEVEL_SCENE_NEW_HIGHSCORE_FONT_SIZE = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_FONT_SIZE");
        LEVEL_SCENE_NEW_HIGHSCORE_TIME = config.getInteger("LEVEL_SCENE_NEW_HIGHSCORE_TIME");


      /**
        MISC
      **/
        HIGHSCORE_PATH = config.getString("HIGHSCORE_PATH");
        DEFAULT_HIGHSCORE_PATH = config.getString("DEFAULT_HIGHSCORE_PATH");
        FADING_TIME = config.getInteger("FADING_TIME");
        FONT_NORMAL_SIZE = config.getInteger("FONT_NORMAL_SIZE");
        //SPLASH_COUNT = config.getInteger("SPLASH_COUNT");
        SPLASH_SPEED = config.getFloat("SPLASH_SPEED");
        SPLASH_TIME = config.getInteger("SPLASH_TIME");

        SFX_BLOCK_EXPLOSION_MINIMUM[0] = config.getInteger("SFX_BLOCK_EXPLOSION_MINIMUM[0]");
        SFX_BLOCK_EXPLOSION_MINIMUM[1] = config.getInteger("SFX_BLOCK_EXPLOSION_MINIMUM[1]");

        DEBUG_STARTLEVEL = config.getInteger("DEBUG_STARTLEVEL");


    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading config: " << exception.getDescription();
    }
  }
}
