#include "./media.hpp"

using namespace std;
using namespace util;
using namespace error;


namespace media
{
  namespace gfx
  {
    namespace gui
    {
      ::gfx::Animation left;
      ::gfx::Animation right;
      ::gfx::Animation border;
      ::gfx::Animation item[ITEM_TYPE_END];
      ::gfx::Animation multiplier;
    }

    namespace mainmenu
    {
      ::gfx::Animation background;
      ::gfx::Animation main[MAINMENU_MAIN_END][2];
      ::gfx::Animation sub[MAINMENU_SUB_END][2];
      ::gfx::Animation title;
      ::gfx::Animation howto[2 /*HOWTO_COUNT*/];
    }

    namespace pause
    {
      ::gfx::Animation box;
      ::gfx::Animation selection[PAUSE_SELECTION_END][2];
    }


    namespace player
    {
      ::gfx::Animation normal;
      ::gfx::Animation shooting;
    }

    namespace splash
    {
      ::gfx::Image splash[2/*SPLASH_COUNT*/];
    }

    ::gfx::Animation quad;
    ::gfx::Animation cursor;
    ::gfx::Animation rocket;
    ::gfx::Animation item[ITEM_TYPE_END];

    ::gfx::Animation new_highscore;


    ::gfx::Image particle;


    ::font::ImageFont font;


  }


  namespace font
  {
    ::font::TtfFont font;
    ::font::TtfFont item_count;
    ::font::TtfFont score;
    ::font::TtfFont multiplier;
    ::font::TtfFont new_highscore;
  }


  namespace sfx
  {
    ::audio::Sound block_explosion[3];
    ::audio::Sound player_explosion;
    ::audio::Sound shot;
    ::audio::Sound accept;
    ::audio::Sound deny;
    ::audio::Sound item_rocket;
    ::audio::Sound item_stop;
    ::audio::Sound item_rapidfire;
    ::audio::Sound item_bomb;
  }


  namespace music
  {
    ::audio::Track track[2/*MUSIC_TRACK_COUNT*/];
  }



  void load()
  {
    /**
      Load Gfx
    **/
    try
    {
      /* gui */
        media::gfx::gui::left.load("dat/gui/left.ani");
        media::gfx::gui::right.load("dat/gui/right.ani");
        media::gfx::gui::border.load("dat/gui/border.ani");
        for(int i = 0; i < ITEM_TYPE_END; i++)
        {
          media::gfx::gui::item[i].load(string("dat/gui/item_") + i + string(".ani"));
        }

        media::gfx::gui::multiplier.load("dat/gui/multiplier.ani");


      /* mainmenu */
        media::gfx::mainmenu::background.load("dat/mainmenu/background.ani");
        media::gfx::mainmenu::title.load("dat/mainmenu/title.ani");

        for(int m = 0; m < MAINMENU_MAIN_END; m++)
        {
          media::gfx::mainmenu::main[m][0].load(string("dat/mainmenu/main_") + m + string("_disabled.ani"));
          media::gfx::mainmenu::main[m][1].load(string("dat/mainmenu/main_") + m + string("_enabled.ani"));
        }

        for(int s = 0; s < MAINMENU_SUB_END; s++)
        {
          media::gfx::mainmenu::sub[s][0].load(string("dat/mainmenu/sub_") + s + string("_disabled.ani"));
          media::gfx::mainmenu::sub[s][1].load(string("dat/mainmenu/sub_") + s + string("_enabled.ani"));
        }

        for(int ht = 0; ht < 2 /* HOWTO_COUNT */; ht++)
        {
          media::gfx::mainmenu::howto[ht].load(string("dat/mainmenu/howto_") + ht + string(".ani"));
        }

      /* pause */
        media::gfx::pause::box.load("dat/pause/box.ani");

        for(int s = 0; s < PAUSE_SELECTION_END; s++)
        {
          media::gfx::pause::selection[s][0].load(string("dat/pause/") + s + string("_disabled.ani"));
          media::gfx::pause::selection[s][1].load(string("dat/pause/") + s + string("_enabled.ani"));
        }


      /* Player */
        media::gfx::player::normal.load("dat/player/normal.ani");
        media::gfx::player::shooting.load("dat/player/shooting.ani");


      /* Splashs */
        for(int s = 0; s < 2; s++)
        {
          media::gfx::splash::splash[s].load(string("dat/splash/splash_") + s + string(".png"));
        }


      /* etc */
        media::gfx::quad.load("dat/quad.ani");
        media::gfx::cursor.load("dat/cursor.ani");
        media::gfx::rocket.load("dat/rocket.ani");

        for(int i = 0; i < ITEM_TYPE_END; i++)
        {
          media::gfx::item[i].load(string("dat/item/") + i + string(".ani"));
        }

        media::gfx::new_highscore.load("dat/new_highscore.ani");


      /* Particle */
        media::gfx::particle.load("dat/particle.bmp");


      /* Font */
        media::gfx::font.load("dat/font.bmp");
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading gfx: " << exception.getDescription();
    }


    /**
      Load Font
    **/
    try
    {
      media::font::font.load("dat/font/FreeUniversal-Bold.ttf", FONT_NORMAL_SIZE);
      media::font::item_count.load("dat/font/FreeUniversal-Bold.ttf", ITEM_COUNT_FONT_SIZE);
      media::font::score.load("dat/font/FreeUniversal-Bold.ttf", SCORE_FONT_SIZE);
      media::font::multiplier.load("dat/font/FreeUniversal-Bold.ttf", MULTIPLIER_FONT_SIZE);
      media::font::new_highscore.load("dat/font/FreeUniversal-Bold.ttf", LEVEL_SCENE_NEW_HIGHSCORE_FONT_SIZE);
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading fonts: " << exception.getDescription();
    }

    /**
    	Load Sounds
    **/
    try
    {
      for(int e = 0; e < 3; e++)
      {
        media::sfx::block_explosion[e].load(string("dat/sfx/block_explosion_") + integer_to_string(e) + ".wav");
      }

      media::sfx::player_explosion.load(string("dat/sfx/player_explosion.wav"));
      media::sfx::shot.load(string("dat/sfx/shot.wav"));
      media::sfx::accept.load(string("dat/sfx/accept.wav"));
      media::sfx::deny.load(string("dat/sfx/deny.wav"));
      media::sfx::item_rocket.load(string("dat/sfx/item_rocket.wav"));
      media::sfx::item_stop.load(string("dat/sfx/item_stop.wav"));
      media::sfx::item_rapidfire.load(string("dat/sfx/item_rapidfire.wav"));
      media::sfx::item_bomb.load(string("dat/sfx/item_bomb.wav"));
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading sounds: " << exception.getDescription();
    }


    /**
    	Load Music
    **/
    try
    {
      for(int t = 0; t < 2/* MUSIC_TRACK_COUNT */; t++)
      {
        media::music::track[t].load(string("dat/music/track_") + integer_to_string(t) + ".ogg");
      }
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst loading music: " << exception.getDescription();
    }







    /**
      Verify Media
    **/
    try
    {
      if(media::gfx::player::normal.getFrameCount() == 0)
        throw Exception() << "Player(normal) has no frames, has to have at least one";

      if(media::gfx::player::shooting.getFrameCount() == 0)
        throw Exception() << "Player(shooting) has no frames, has to have at least one";

      if(media::gfx::pause::box.getFrameCount() == 0)
        throw Exception() << "Pause/box has no frames, has to have at least one";

      if(media::gfx::gui::multiplier.getFrameCount() == 0)
        throw Exception() << "Multiplier has no frames, has to have at least one";
    }
    catch(Exception &exception)
    {
      throw Exception() << "Error whilst verifying media: '" << exception.getDescription() << "'";
    }


  }


  void free()
  {
    /**
    	Sfx
    **/
    for(int e = 0; e < 3; e++)
    {
      media::sfx::block_explosion[e].clear();
    }

    media::sfx::player_explosion.clear();
    media::sfx::shot.clear();
    media::sfx::accept.clear();
    media::sfx::deny.clear();
    media::sfx::item_rocket.clear();
    media::sfx::item_stop.clear();
    media::sfx::item_rapidfire.clear();
    media::sfx::item_bomb.clear();


    /**
    	Font
    **/
    media::font::font.clear();
    media::font::item_count.clear();
    media::font::score.clear();
    media::font::multiplier.clear();
    media::font::new_highscore.clear();
  }
}
