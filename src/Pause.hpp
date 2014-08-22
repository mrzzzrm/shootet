#ifndef PAUSE_HPP
#define PAUSE_HPP

  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"


  class Pause
  {
    public:

      Pause();
      ~Pause();


      /* Selection */
        PAUSE_SELECTION getSelection();


      /* Size */
        static int getBoxWidth();
        static int getBoxHeight();


      /* Update */
        void update();



    private:

      /* Data */
        int selection;
  };


#endif // PAUSE_HPP
