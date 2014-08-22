#ifndef CONFIG_HPP
#define CONFIG_HPP

  #include "framework.hpp"


  /**
    Enums
  **/
  enum LEVEL_DIFFICULTY
  {
    LEVEL_EASY,
    LEVEL_MEDIUM,
    LEVEL_HARD,

    LEVEL_DIFFICULTY_END
  };

  enum LEVEL_STATE
  {
    LEVEL_PLAYING,
    LEVEL_PAUSED,
    LEVEL_SCENE_INTRO,
    LEVEL_SCENE_SUCCESS,
    LEVEL_SCENE_FAILURE,
    LEVEL_SCENE_QUIT
  };

  enum PLAYER_STATE
  {
    PLAYER_NORMAL,
    PLAYER_SHOOTING
  };

  enum ITEM_TYPE
  {
    ITEM_BOMB,
    ITEM_STOP,
    ITEM_ROCKET,
    ITEM_RAPIDFIRE,

    ITEM_TYPE_END
  };

  enum MAINMENU_MAIN_SELECTION
  {
    MAINMENU_START,
    MAINMENU_HOWTO,
    MAINMENU_QUIT,

    MAINMENU_MAIN_END
  };

  enum MAINMENU_SUB_SELECTION
  {
    MAINMENU_EASY,
    MAINMENU_MEDIUM,
    MAINMENU_HARD,

    MAINMENU_SUB_END
  };

  enum PAUSE_SELECTION
  {
    PAUSE_CONTINUE,
    PAUSE_QUIT,

    PAUSE_SELECTION_END
  };


  /**
    Screen
  **/
  extern int SCREEN_WIDTH;
  extern int SCREEN_HEIGHT;
  extern bool FULLSCREEN;



  /**
    Level
  **/
  extern int MAP_START_Y;
  extern int MAP_RANGE_Y;
  extern int MAP_MIDDLE_X;

  extern double BORDER_OFFSET;
  extern double PLAYER_OFFSET;

  extern double NO_TILES_IN_SCREEN_SPEED;

  extern double QUAD_SPEED;
  extern double PLAYER_BUTTON_UP_EXTRA_SPEED;
  extern double ROCKET_SPEED;
  extern double ITEM_SPEED;
  extern double ITEM_FASTCOLLECT_SPEED;

  extern double PLAYER_SPEED_X;

  extern double QUAD_RAPIDFIRE_SPEED;

  extern int SCORE_PER_TILE;
  extern double SCORE_SIZE_FACTOR;

  extern int QUAD_TILE_ID;

  extern int PARTICLES_PER_TILE;
  extern int PARTICLES_SPEED_MIN;
  extern int PARTICLES_SPEED_MAX;
  extern int PARTICLES_DURATION_MIN;
  extern int PARTICLES_DURATION_MAX;

  extern double ERUPTION_OFFSET_MAX;
  extern int ERUPTION_TIME_PER_TILE ;
  extern int ERUPTION_TIME_MAX;
  extern int ERUPTION_TIME_FAILURE;

  extern int MULTIPLIER_MAX_FACTOR;
  extern double MULTIPLIER_DECREASE_SPEED_BASE;
  extern double MULTIPLIER_DECREASE_SPEED_FACTOR;
  extern double MULTIPLIER_DECREASE_SPEED_MAX;
  extern int MULTIPLIER_MAX_FILLING;
  extern int MULTIPLIER_MIN_DESTRUCTION;
  extern double MULTIPLIER_INIT_FILLING;
  extern double MULTIPLIER_FAIL_FACTOR;

  extern double DESTHALT_PER_TILE;
  extern double DESTHALT_MAX;

  extern int STOP_TIME;
  extern int RAPIDFIRE_TIME;

  extern int ITEM_REQUIRED_DESTRUCTION[ITEM_TYPE_END];
  extern int ITEM_COUNT_LIMIT[ITEM_TYPE_END];

  extern int ROCKET_CURVE_TIME_DIVIDOR;
  extern int ROCKET_CURVE_SIN_DIVIDOR;




  /**
    UI
  **/
  extern int GUI_LEFT_X;
  extern int GUI_LEFT_Y;
  extern int GUI_RIGHT_X;
  extern int GUI_RIGHT_Y;
  extern int ITEM_COUNT_START_Y;
  extern int ITEM_COUNT_STEP_Y;
  extern int ITEM_COUNT_RIGHT_X;
  extern int ITEM_COUNT_FONT_SIZE;
  extern int SCORE_X;
  extern int SCORE_Y;
  extern int SCORE_DIGIT_COUNT;
  extern int SCORE_FONT_SIZE;

  extern int GUI_VIEWPORT_X;
  extern int GUI_VIEWPORT_Y;
  extern int GUI_VIEWPORT_WIDTH;
  extern int GUI_VIEWPORT_HEIGHT;

  extern int MAINMENU_BLOCK_OFFSET;
  extern int MAINMENU_BLOCK_SPEED;

  extern int MAINMENU_MAIN_Y;
  extern int MAINMENU_MAIN_X[MAINMENU_MAIN_END];
  extern int MAINMENU_SUB_Y;
  extern int MAINMENU_SUB_X[MAINMENU_SUB_END];
  extern int MAINMENU_TITLE_X;
  extern int MAINMENU_TITLE_Y;
  extern double MAINMENU_HOWTO_SPEED;

  extern int PAUSE_BOX_MIDDLE_X;
  extern int PAUSE_BOX_MIDDLE_Y;
  extern int PAUSE_BOX_FIRST_Y;
  extern int PAUSE_BOX_DISTANCE_Y;

  extern int MULTIPLIER_BAR_X;
  extern int MULTIPLIER_BAR_Y;
  extern double MULTIPLIER_FILL_SPEED;
  extern int MULTIPLIER_FONT_SIZE;
  extern int MULTIPLIER_FACTOR_RIGHT_X;
  extern int MULTIPLIER_FACTOR_Y;

  extern int HIGHSCORE_BAR_HALT_TIME;
  extern double HIGHSCORE_BAR_SPEED;
  extern int HIGHSCORE_BAR_START_Y;
  extern int HIGHSCORE_BAR_DIFFICULTY_START_X;
  extern int HIGHSCORE_BAR_PLACES_START_X;
  extern int HIGHSCORE_BAR_PLACE_SCORE_SPACING;
  extern int HIGHSCORE_BAR_SCORE_PLACE_SPACING;
  extern int HIGHSCORE_BAR_PLACECOUNT;
  extern int HIGHSCORE_BAR_SCOREDIGITS;



  /**
    SCENES
  **/
  extern double LEVEL_SCENE_INTRO_CAMERA_ACCELERATION_TIME;
  extern double LEVEL_SCENE_INTRO_PLAYER_MOVE_SPEED;

  extern double LEVEL_SCENE_SUCCESS_PLAYER_ACCELERATION;

  extern int LEVEL_SCENE_FAILURE_TIME;
  extern int LEVEL_SCENE_FAILURE_PLAYER_PARTICLES;

  extern int LEVEL_SCENE_QUIT_TIME;

  extern int LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_X;
  extern int LEVEL_SCENE_NEW_HIGHSCORE_TITLE_MIDDLE_Y;
  extern int LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_X;
  extern int LEVEL_SCENE_NEW_HIGHSCORE_SCORE_MIDDLE_Y;
  extern int LEVEL_SCENE_NEW_HIGHSCORE_FONT_SIZE;
  extern int LEVEL_SCENE_NEW_HIGHSCORE_TIME;





  /**
    MISC
  **/
  extern std::string HIGHSCORE_PATH;
  extern std::string DEFAULT_HIGHSCORE_PATH;

  extern int FADING_TIME;
  extern gfx::Color FADING_COLOR;
  extern int FONT_NORMAL_SIZE;

  extern double SPLASH_SPEED;
  extern int SPLASH_TIME;

  extern int SFX_BLOCK_EXPLOSION_MINIMUM[3-1];

  extern int DEBUG_STARTLEVEL;


  namespace config
  {
    void load();
  }


#endif // CONFIG_HPP
