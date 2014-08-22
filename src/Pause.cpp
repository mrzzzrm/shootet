#include "./Pause.hpp"

using namespace input;

/*
  Class Pause
*/
  Pause::Pause()
  {
    selection = PAUSE_CONTINUE;
  }


  Pause::~Pause()
  {

  }

  PAUSE_SELECTION Pause::getSelection()
  {
    return (PAUSE_SELECTION)selection;
  }


  int Pause::getBoxWidth()
  {
    if(media::gfx::pause::box.getFrameCount() != 0)
      return media::gfx::pause::box.getFrame(0).getWidth();
    else
      return 0;
  }


  int Pause::getBoxHeight()
  {
    if(media::gfx::pause::box.getFrameCount() != 0)
      return media::gfx::pause::box.getFrame(0).getHeight();
    else
      return 0;
  }

  void Pause::update()
  {
    if(Input::isButtonPressed(BUTTON_UP) && (int)selection > 0)
      (int)selection--;
    if(Input::isButtonPressed(BUTTON_DOWN) && (int)selection < PAUSE_SELECTION_END - 1)
      (int)selection++;
  }


