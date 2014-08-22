#ifndef MEDIA_HPP
#define MEDIA_HPP

  #include "framework.hpp"


  #include "./Pause.hpp"
  #include "./Item.hpp"

  namespace media
  {
    namespace gfx
    {
      namespace gui
      {
        extern ::gfx::Animation left;
        extern ::gfx::Animation right;
        extern ::gfx::Animation border;
        extern ::gfx::Animation item[ITEM_TYPE_END];
        extern ::gfx::Animation multiplier;
      }

      namespace mainmenu
      {
        extern ::gfx::Animation background;
        extern ::gfx::Animation main[MAINMENU_MAIN_END][2];
        extern ::gfx::Animation sub[MAINMENU_SUB_END][2];
        extern ::gfx::Animation title;
        extern ::gfx::Animation howto[2 /*HOWTO_COUNT*/];
      }

      namespace pause
      {
        extern ::gfx::Animation box;
        extern ::gfx::Animation selection[PAUSE_SELECTION_END][2];
      }

      namespace player
      {
        extern ::gfx::Animation normal;
        extern ::gfx::Animation shooting;
      }

      namespace splash
      {
        extern ::gfx::Image splash[2/*SPLASH_COUNT*/];
      }

      extern ::gfx::Animation quad;
      extern ::gfx::Animation cursor;
      extern ::gfx::Animation rocket;
      extern ::gfx::Animation item[ITEM_TYPE_END];


      extern ::gfx::Animation new_highscore;


      extern ::gfx::Image particle;


      extern ::font::ImageFont font;
    }


    namespace font
    {
      extern ::font::TtfFont font;
      extern ::font::TtfFont item_count;
      extern ::font::TtfFont score;
      extern ::font::TtfFont multiplier;
      extern ::font::TtfFont new_highscore;
    }


    namespace sfx
    {
      extern ::audio::Sound block_explosion[3];
      extern ::audio::Sound player_explosion;
      extern ::audio::Sound shot;
      extern ::audio::Sound accept;
      extern ::audio::Sound deny;
      extern ::audio::Sound item_rocket;
      extern ::audio::Sound item_stop;
      extern ::audio::Sound item_rapidfire;
      extern ::audio::Sound item_bomb;
    }


    namespace music
    {
      extern ::audio::Track track[2/*MUSIC_TRACK_COUNT*/];
    }


    void load();
    void free();
  }


#endif // MEDIA_HPP
