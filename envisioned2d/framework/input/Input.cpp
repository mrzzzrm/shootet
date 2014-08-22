#include "./Input.hpp"


using namespace std;



namespace input
{
  SDL_Joystick *Input::joystick = NULL;

  vector<bool> Input::button::pressed(BUTTON_LAST + 1, false);
  vector<bool> Input::button::released(BUTTON_LAST + 1, false);
  vector<bool> Input::button::hold(BUTTON_LAST + 1, false);

  vector<bool> Input::key::pressed(KEY_LAST + 1, false);
  vector<bool> Input::key::released(KEY_LAST + 1, false);
  vector<bool> Input::key::hold(KEY_LAST + 1, false);

  uint Input::queue::first = 0;
  uint Input::queue::last = 0;
  list<char> Input::queue::list;


  void Input::update()
  {
    __input__assert_open();

    SDL_Event event;


  #if defined(PLATFORM_WIZ) || defined(PLATFORM_CAANOO)
    /* Open SDL Joystick */
      if(joystick == NULL)
      {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
        if((joystick = SDL_JoystickOpen(0)) == NULL)
          throw Exception() << "Couldn't open joystick";
      }
  #endif


    /* Reset pressed and released */
      fill(button::pressed.begin(), button::pressed.end(), false);
      fill(button::released.begin(), button::released.end(), false);
      fill(key::pressed.begin(), key::pressed.end(), false);
      fill(key::released.begin(), key::released.end(), false);


    /* Poll */
      while(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          /* System Events */
            /* Quit */
              case SDL_QUIT:
                exit(EXIT_SUCCESS);
              break;


          /* Keyboard Events */
            /* Pressed */
              case SDL_KEYDOWN:

                /* BUTTON */
                  switch(event.key.keysym.sym)
                  {
                  #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_PANDORA)
                    case I_KB_UP: button::pressed[BUTTON_UP] = true; button::hold[BUTTON_UP] = true; break;
                    case I_KB_DOWN: button::pressed[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = true; break;
                    case I_KB_LEFT: button::pressed[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = true; break;
                    case I_KB_RIGHT: button::pressed[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = true; break;
                    case I_KB_A: button::pressed[BUTTON_A] = true; button::hold[BUTTON_A] = true; break;
                    case I_KB_B: button::pressed[BUTTON_B] = true; button::hold[BUTTON_B] = true; break;
                    case I_KB_X: button::pressed[BUTTON_X] = true; button::hold[BUTTON_X] = true; break;
                    case I_KB_Y: button::pressed[BUTTON_Y] = true; button::hold[BUTTON_Y] = true; break;
                    case I_KB_L: button::pressed[BUTTON_L] = true; button::hold[BUTTON_L] = true; break;
                    case I_KB_R: button::pressed[BUTTON_R] = true; button::hold[BUTTON_R] = true; break;
                    case I_KB_START: button::pressed[BUTTON_START] = true; button::hold[BUTTON_START] = true; break;
                    case I_KB_SELECT: button::pressed[BUTTON_SELECT] = true; button::hold[BUTTON_SELECT] = true; break;
                  #endif

                    default: break;
                  }

                /* KEYBOARD */
                #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_PANDORA)

                  key::pressed[event.key.keysym.sym] = true;
                  key::hold[event.key.keysym.sym] = true;

                  if(event.key.keysym.sym <= 0xff)
                  {
                    char c = event.key.keysym.sym;

                    if(isgraph(c) || c == ' ')
                    {
                      /* Add to list */
                        /* Convert with modifiers(shift, etc) */
                        queue::list.push_back(event.key.keysym.sym);
                          queue::last++;

                        if(queue::list.size() > 32)
                        {
                          queue::list.pop_front();
                            queue::first++;
                        }
                    }
                  }


                #endif

              break;


            /* Released */
              case SDL_KEYUP:

                /* BUTTON */
                  switch(event.key.keysym.sym)
                  {
                  #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_PANDORA)
                    case I_KB_UP: button::released[BUTTON_UP] = true; button::hold[BUTTON_UP] = false; break;
                    case I_KB_DOWN: button::released[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = false; break;
                    case I_KB_LEFT: button::released[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = false; break;
                    case I_KB_RIGHT: button::released[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = false; break;
                    case I_KB_A: button::released[BUTTON_A] = true; button::hold[BUTTON_A] = false; break;
                    case I_KB_B: button::released[BUTTON_B] = true; button::hold[BUTTON_B] = false; break;
                    case I_KB_X: button::released[BUTTON_X] = true; button::hold[BUTTON_X] = false; break;
                    case I_KB_Y: button::released[BUTTON_Y] = true; button::hold[BUTTON_Y] = false; break;
                    case I_KB_L: button::released[BUTTON_L] = true; button::hold[BUTTON_L] = false; break;
                    case I_KB_R: button::released[BUTTON_R] = true; button::hold[BUTTON_R] = false; break;
                    case I_KB_START: button::released[BUTTON_START] = true; button::hold[BUTTON_START] = false; break;
                    case I_KB_SELECT: button::released[BUTTON_SELECT] = true; button::hold[BUTTON_SELECT] = false; break;
                  #endif

                    default: break;
                  }

                /* KEYBOARD */
                #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_PANDORA)
                    key::released[event.key.keysym.sym] = true;
                    key::hold[event.key.keysym.sym] = false;
                #endif

              break;


          /* Joystickbutton - Events */
            /* Pressed */
              case SDL_JOYBUTTONDOWN:
                switch(event.jbutton.button)
                {
                #if defined(PLATFORM_WIZ) || defined(PLATFORM_CAANOO)
                #if defined(PLATFORM_WIZ)
                  case I_JB_UP: button::pressed[BUTTON_UP] = true; button::hold[BUTTON_UP] = true; break;
                  case I_JB_UP_LEFT:
                    button::pressed[BUTTON_UP] = true; button::hold[BUTTON_UP] = true;
                    button::pressed[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = true;
                  break;

                  case I_JB_LEFT: button::pressed[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = true; break;
                  case I_JB_DOWN_LEFT:
                    button::pressed[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = true;
                    button::pressed[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = true;
                  break;

                  case I_JB_DOWN: button::pressed[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = true; break;
                  case I_JB_DOWN_RIGHT:
                    button::pressed[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = true;
                    button::pressed[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = true;
                  break;

                  case I_JB_RIGHT: button::pressed[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = true; break;
                  case I_JB_UP_RIGHT:
                    button::pressed[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = true;
                    button::pressed[BUTTON_UP] = true; button::hold[BUTTON_UP] = true;
                  break;
                #endif

                  case I_JB_START: button::pressed[BUTTON_START] = true; button::hold[BUTTON_START] = true; break;
                  case I_JB_SELECT: button::pressed[BUTTON_SELECT] = true; button::hold[BUTTON_SELECT] = true; break;

                  case I_JB_L: button::pressed[BUTTON_L] = true; button::hold[BUTTON_L] = true; break;
                  case I_JB_R: button::pressed[BUTTON_R] = true; button::hold[BUTTON_R] = true; break;

                  case I_JB_A: button::pressed[BUTTON_A] = true; button::hold[BUTTON_A] = true; break;
                  case I_JB_B: button::pressed[BUTTON_B] = true; button::hold[BUTTON_B] = true; break;
                  case I_JB_X: button::pressed[BUTTON_X] = true; button::hold[BUTTON_X] = true; break;
                  case I_JB_Y: button::pressed[BUTTON_Y] = true; button::hold[BUTTON_Y] = true; break;

                #if defined(PLATFORM_CAANOO)
                  case I_JB_HOME: button::pressed[BUTTON_HOME] = true; button::hold[BUTTON_HOME] = true; break;
                #endif

                #if defined(PLATFORM_WIZ)
                  case I_JB_VOLUP: button::pressed[BUTTON_VOLUP] = true; button::hold[BUTTON_VOLUP] = true; break;
                  case I_JB_VOLDOWN: button::pressed[BUTTON_VOLDOWN] = true; button::hold[BUTTON_VOLDOWN] = true; break;
                #endif
                #endif
                }

              break;


            /* Released */
              case SDL_JOYBUTTONUP:
                switch(event.jbutton.button)
                {
                #if defined(PLATFORM_WIZ) || defined(PLATFORM_CAANOO)
                #if defined(PLATFORM_WIZ)
                  case I_JB_UP: button::released[BUTTON_UP] = true; button::hold[BUTTON_UP] = false; break;
                  case I_JB_UP_LEFT:
                    button::released[BUTTON_UP] = true; button::hold[BUTTON_UP] = false;
                    button::released[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = false;
                  break;

                  case I_JB_LEFT: button::released[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = false; break;
                  case I_JB_DOWN_LEFT:
                    button::released[BUTTON_LEFT] = true; button::hold[BUTTON_LEFT] = false;
                    button::released[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = false;
                  break;

                  case I_JB_DOWN: button::released[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = false; break;
                  case I_JB_DOWN_RIGHT:
                    button::released[BUTTON_DOWN] = true; button::hold[BUTTON_DOWN] = false;
                    button::released[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = false;
                  break;

                  case I_JB_RIGHT: button::released[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = false; break;
                  case I_JB_UP_RIGHT:
                    button::released[BUTTON_RIGHT] = true; button::hold[BUTTON_RIGHT] = false;
                    button::released[BUTTON_UP] = true; button::hold[BUTTON_UP] = false;
                  break;
                #endif

                  case I_JB_START: button::released[BUTTON_START] = true; button::hold[BUTTON_START] = false; break;
                  case I_JB_SELECT: button::released[BUTTON_SELECT] = true; button::hold[BUTTON_SELECT] = false; break;

                  case I_JB_L: button::released[BUTTON_L] = true; button::hold[BUTTON_L] = false; break;
                  case I_JB_R: button::released[BUTTON_R] = true; button::hold[BUTTON_R] = false; break;

                  case I_JB_A: button::released[BUTTON_A] = true; button::hold[BUTTON_A] = false; break;
                  case I_JB_B: button::released[BUTTON_B] = true; button::hold[BUTTON_B] = false; break;
                  case I_JB_X: button::released[BUTTON_X] = true; button::hold[BUTTON_X] = false; break;
                  case I_JB_Y: button::released[BUTTON_Y] = true; button::hold[BUTTON_Y] = false; break;

                #if defined(PLATFORM_CAANOO)
                  case I_JB_HOME: button::released[BUTTON_HOME] = true; button::hold[BUTTON_HOME] = false; break;
                #endif

                #if defined(PLATFORM_WIZ)
                  case I_JB_VOLUP: button::released[BUTTON_VOLUP] = true; button::hold[BUTTON_VOLUP] = true; break;
                  case I_JB_VOLDOWN: button::released[BUTTON_VOLDOWN] = true; button::hold[BUTTON_VOLDOWN] = true; break;
                #endif
                #endif
                }

              break;


        }
      }


    /* Joystickaxis - Gamepad */
    #if defined(PLATFORM_CAANOO)
      if(joystick != NULL)
      {
        int axisx, axisy;

        /* Analyse joystick */
          axisx = SDL_JoystickGetAxis(joystick, 0);
          axisy = SDL_JoystickGetAxis(joystick, 1);


        /* Released */
          if(button::hold[BUTTON_LEFT] && axisx > -0x4000) button::released[BUTTON_LEFT] = true;
          if(button::hold[BUTTON_RIGHT] && axisx < 0x4000) button::released[BUTTON_RIGHT] = true;
          if(button::hold[BUTTON_UP] && axisy > -0x4000) button::released[BUTTON_UP] = true;
          if(button::hold[BUTTON_DOWN] && axisy < 0x4000) button::released[BUTTON_DOWN] = true;


        /* Pressed / Hold */
          if(axisx < -0x4000)
          {
            if(!button::hold[BUTTON_LEFT])
              button::pressed[BUTTON_LEFT] = true;

            button::hold[BUTTON_LEFT] = true;
          }
          else if (axisx  > 0x4000)
          {
            if(!button::hold[BUTTON_RIGHT])
              button::pressed[BUTTON_RIGHT] = true;

            button::hold[BUTTON_RIGHT] = true;
          }
          else
          {
            button::hold[BUTTON_LEFT] = false;
            button::hold[BUTTON_RIGHT] = false;
          }


          if(axisy < -0x4000)
          {
            if(!button::hold[BUTTON_UP])
              button::pressed[BUTTON_UP] = true;

            button::hold[BUTTON_UP] = true;
          }
          else if (axisy > 0x4000)
          {
            if(!button::hold[BUTTON_DOWN])
              button::pressed[BUTTON_DOWN] = true;

            button::hold[BUTTON_DOWN] = true;
          }
          else
          {
            button::hold[BUTTON_UP] = false;
            button::hold[BUTTON_DOWN] = false;
          }

      }
    #endif
  }


  bool Input::isButtonPressed(BUTTON _button)
  {
    return button::pressed[_button];
  }


  bool Input::isButtonReleased(BUTTON _button)
  {
    return button::released[_button];
  }


  bool Input::isButtonHold(BUTTON _button)
  {
    return button::hold[_button];
  }


  bool Input::isKeyPressed(KEY _key)
  {
    return key::pressed[_key];
  }


  bool Input::isKeyReleased(KEY _key)
  {
    return key::released[_key];
  }


  bool Input::isKeyHold(KEY _key)
  {
    return key::hold[_key];
  }


  bool Input::isKeyPressed(unsigned char _key)
  {
    return key::pressed[getKey(_key)];
  }


  bool Input::isKeyReleased(unsigned char _key)
  {
    return key::released[getKey(_key)];
  }


  bool Input::isKeyHold(unsigned char _key)
  {
    return key::hold[getKey(_key)];
  }


  char Input::getCharInQueue(uint index)
  {
    if(index < queue::first || index > queue::last)
      return 0;

    std::list<char>::iterator i = queue::list.begin();
    advance(i, index - queue::first);

    return *i;
  }


  int Input::getFirstCharInQueue()
  {
    return queue::first;
  }


  int Input::getLastCharInQueue()
  {
    return queue::last;
  }


  KEY Input::getKey(unsigned char key)
  {
    return (KEY)key;
  }


}


