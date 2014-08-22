#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP




  /* Audio */
    #include "./audio/audio.hpp"


  /* Collision */
    #include "collision/collision.hpp"


  /* Etc */
    #include "./etc/int.h"
    #include "./etc/Alignment.hpp"

  /* Exception */
    #include "./error/Exception.hpp"

  /* Font */
    #include "./font/font.hpp"

  /* Geo */
    #include "./geo/geo.hpp"

  /* Gfx */
    #include "./gfx/gfx.hpp"

  /* Input */
    #include "./input/Input.hpp"

  /* Tmx */
    #include "./tmx/tmx.hpp"

  /* Util */
    #include "./util/util.hpp"

  /* Particle */
    #include "particle/Particle.hpp"
    #include "particle/ParticleFrame.hpp"
    #include "particle/ParticleProfile.hpp"
    #include "particle/ParticleManager.hpp"


  /* Xml */
    #include "xml/Xml.hpp"



  namespace env2d
  {
    void open(int w, int h, int bpp = 16, bool fullscreen = false, bool show_cursor = false);
    void close();
  }


#endif
