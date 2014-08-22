#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP


  #include <list>
  #include <vector>
  #include <iostream>

  #include <SDL/SDL.h>

  #include "etc/int.h"
  #include "./__assert.hpp"



  namespace input
  {
    enum BUTTON
    {
    #if defined(PLATFORM_WIZ)
      BUTTON_VOLUP,
      BUTTON_VOLDOWN,
    #endif
    #if defined(PLATFORM_CAANOO)
      BUTTON_HOME,
    #endif
    #if defined(PLATFORM_WIZ)
      BUTTON_VOLUP,
      BUTTON_VOLDOWN,
    #endif

      BUTTON_UP,
      BUTTON_DOWN,
      BUTTON_LEFT,
      BUTTON_RIGHT,
      BUTTON_A,
      BUTTON_B,
      BUTTON_X,
      BUTTON_Y,
      BUTTON_L,
      BUTTON_R,
      BUTTON_START,
      BUTTON_SELECT,
      BUTTON_LAST
    };


    enum KEY
    {
      KEY_UNKNOWN	= SDLK_UNKNOWN,
      KEY_FIRST	= SDLK_FIRST,

    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_PANDORA)

      KEY_BACKSPACE	= SDLK_BACKSPACE,
      KEY_TAB	= SDLK_TAB,
      KEY_CLEAR	= SDLK_CLEAR,
      KEY_RETURN	= SDLK_RETURN,
      KEY_PAUSE	= SDLK_PAUSE,
      KEY_ESCAPE	= SDLK_ESCAPE,
      KEY_SPACE	= SDLK_SPACE,
      KEY_EXCLAIM	= SDLK_EXCLAIM,
      KEY_QUOTEDBL	= SDLK_QUOTEDBL,
      KEY_HASH	= SDLK_HASH,
      KEY_DOLLAR	= SDLK_DOLLAR,
      KEY_AMPERSAND	= SDLK_AMPERSAND,
      KEY_QUOTE	= SDLK_QUOTE,
      KEY_LEFTPAREN	= SDLK_LEFTPAREN,
      KEY_RIGHTPAREN = SDLK_RIGHTPAREN,
      KEY_ASTERISK = SDLK_ASTERISK,
      KEY_PLUS = SDLK_PLUS,
      KEY_COMMA	= SDLK_COMMA,
      KEY_MINUS	= SDLK_MINUS,
      KEY_PERIOD = SDLK_PERIOD,
      KEY_SLASH	= SDLK_SLASH,

      KEY_0	= SDLK_0,
      KEY_1	= SDLK_1,
      KEY_2	= SDLK_2,
      KEY_3	= SDLK_3,
      KEY_4	= SDLK_4,
      KEY_5	= SDLK_5,
      KEY_6	= SDLK_6,
      KEY_7	= SDLK_7,
      KEY_8	= SDLK_8,
      KEY_9	= SDLK_9,

      KEY_COLON	= SDLK_COLON,
      KEY_SEMICOLON	= SDLK_SEMICOLON,
      KEY_LESS = SDLK_LESS,
      KEY_EQUALS = SDLK_EQUALS,
      KEY_GREATER	= SDLK_GREATER,
      KEY_QUESTION	= SDLK_QUESTION,
      KEY_AT = SDLK_AT,
      KEY_LEFTBRACKET	= SDLK_LEFTBRACKET,
      KEY_BACKSLASH	= SDLK_BACKSLASH,
      KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET,
      KEY_CARET	= SDLK_CARET,
      KEY_UNDERSCORE = SDLK_UNDERSCORE,
      KEY_BACKQUOTE	= SDLK_BACKQUOTE,

      KEY_A	= SDLK_a,
      KEY_B	= SDLK_b,
      KEY_C	= SDLK_c,
      KEY_D	= SDLK_d,
      KEY_E	= SDLK_e,
      KEY_F	= SDLK_f,
      KEY_G	= SDLK_g,
      KEY_H	= SDLK_h,
      KEY_I	= SDLK_i,
      KEY_J	= SDLK_j,
      KEY_K	= SDLK_k,
      KEY_L	= SDLK_l,
      KEY_M	= SDLK_m,
      KEY_N	= SDLK_n,
      KEY_O	= SDLK_o,
      KEY_P	= SDLK_p,
      KEY_Q	= SDLK_q,
      KEY_R	= SDLK_r,
      KEY_S	= SDLK_s,
      KEY_T	= SDLK_t,
      KEY_U	= SDLK_u,
      KEY_V	= SDLK_v,
      KEY_W	= SDLK_w,
      KEY_X	= SDLK_x,
      KEY_Y	= SDLK_y,
      KEY_Z	= SDLK_z,

      KEY_DELETE = SDLK_DELETE,

      KEY_KP_0 = SDLK_KP0,
      KEY_KP_1 = SDLK_KP1,
      KEY_KP_2 = SDLK_KP2,
      KEY_KP_3 = SDLK_KP3,
      KEY_KP_4 = SDLK_KP4,
      KEY_KP_5 = SDLK_KP5,
      KEY_KP_6 = SDLK_KP6,
      KEY_KP_7 = SDLK_KP7,
      KEY_KP_8 = SDLK_KP8,
      KEY_KP_9 = SDLK_KP9,
      KEY_KP_PERIOD = SDLK_KP_PERIOD,
      KEY_KP_DIVIDE = SDLK_KP_DIVIDE,
      KEY_KP_MULTIPLY = SDLK_KP_MULTIPLY,
      KEY_KP_MINUS = SDLK_KP_MINUS,
      KEY_KP_PLUS = SDLK_KP_PLUS,
      KEY_KP_ENTER = SDLK_KP_ENTER,
      KEY_KP_EQUALS = SDLK_KP_EQUALS,

      KEY_UP = SDLK_UP,
      KEY_DOWN = SDLK_DOWN,
      KEY_RIGHT = SDLK_RIGHT,
      KEY_LEFT = SDLK_LEFT,
      KEY_INSERT = SDLK_INSERT,
      KEY_HOME = SDLK_HOME,
      KEY_END = SDLK_END,
      KEY_PAGEUP = SDLK_PAGEUP,
      KEY_PAGEDOWN = SDLK_PAGEDOWN,

      KEY_F1 = SDLK_F1,
      KEY_F2 = SDLK_F2,
      KEY_F3 = SDLK_F3,
      KEY_F4 = SDLK_F4,
      KEY_F5 = SDLK_F5,
      KEY_F6 = SDLK_F6,
      KEY_F7 = SDLK_F7,
      KEY_F8 = SDLK_F8,
      KEY_F9 = SDLK_F9,
      KEY_F10 = SDLK_F10,
      KEY_F11 = SDLK_F11,
      KEY_F12 = SDLK_F12,
      KEY_F13 = SDLK_F13,
      KEY_F14 = SDLK_F14,
      KEY_F15 = SDLK_F15,

      KEY_NUMLOCK = SDLK_NUMLOCK,
      KEY_CAPSLOCK = SDLK_CAPSLOCK,
      KEY_SCROLLOCK = SDLK_SCROLLOCK,
      KEY_RSHIFT = SDLK_RSHIFT,
      KEY_LSHIFT = SDLK_LSHIFT,
      KEY_RCTRL = SDLK_RCTRL,
      KEY_LCTRL = SDLK_LCTRL,
      KEY_RALT = SDLK_RALT,
      KEY_LALT = SDLK_LALT,
    #endif

      KEY_LAST = SDLK_LAST
    };



    class Input
    {
      public:

        /* Update */
          static void update();


        /* Check buttons */
          static bool isButtonPressed(BUTTON _button);
          static bool isButtonReleased(BUTTON _button);
          static bool isButtonHold(BUTTON _button);


        /* Check keys via KEY */
          static bool isKeyPressed(KEY _key);
          static bool isKeyReleased(KEY _key);
          static bool isKeyHold(KEY _key);


        /* Check keys via ASCII */
          static bool isKeyPressed(unsigned char _key);
          static bool isKeyReleased(unsigned char _key);
          static bool isKeyHold(unsigned char _key);


        /* Read keyboard */
          static char getCharInQueue(uint index);
          static int getFirstCharInQueue();
          static int getLastCharInQueue();


      private:

      #if defined(PLATFORM_WIZ)
        enum INTERNAL_BUTTON
        {
          I_JB_UP,
          I_JB_UP_LEFT,
          I_JB_LEFT,
          I_JB_DOWN_LEFT,
          I_JB_DOWN,
          I_JB_DOWN_RIGHT,
          I_JB_RIGHT,
          I_JB_UP_RIGHT,
          I_JB_START,
          I_JB_SELECT,
          I_JB_L,
          I_JB_R,
          I_JB_A,
          I_JB_B,
          I_JB_X,
          I_JB_Y,
          I_JB_VOLUP,
          I_JB_VOLDOWN
        };
      #elif defined(PLATFORM_CAANOO)
        enum INTERNAL_BUTTON
        {
          I_JB_A,
          I_JB_X,
          I_JB_B,
          I_JB_Y,
          I_JB_L,
          I_JB_R,
          I_JB_HOME,
          I_JB_SELECT = 8,
          I_JB_START,
        };
      #elif defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
        enum INTERNAL_BUTTON
        {
          I_KB_UP = SDLK_UP,
          I_KB_DOWN = SDLK_DOWN,
          I_KB_LEFT = SDLK_LEFT,
          I_KB_RIGHT = SDLK_RIGHT,
          I_KB_A = SDLK_a,
          I_KB_B = SDLK_d,
          I_KB_X = SDLK_s,
          I_KB_Y = SDLK_w,
          I_KB_L = SDLK_q,
          I_KB_R = SDLK_e,
          I_KB_START = SDLK_RETURN,
          I_KB_SELECT = SDLK_RSHIFT,
        };
      #elif defined(PLATFORM_PANDORA)
        enum INTERNAL_BUTTON
        {
          I_KB_UP = SDLK_UP,
          I_KB_DOWN = SDLK_DOWN,
          I_KB_LEFT = SDLK_LEFT,
          I_KB_RIGHT = SDLK_RIGHT,
          I_KB_A = SDLK_HOME,
          I_KB_B = SDLK_END,
          I_KB_X = SDLK_PAGEDOWN,
          I_KB_Y = SDLK_PAGEUP,
          I_KB_L = SDLK_RSHIFT,
          I_KB_R = SDLK_RALT,
          I_KB_START = SDLK_LALT,
          I_KB_SELECT = SDLK_LCTRL,
        };
      #endif


      private:

        /* Data */
          struct button
          {
            static std::vector<bool> pressed;
            static std::vector<bool> released;
            static std::vector<bool> hold;
          };

          struct key
          {
            static std::vector<bool> pressed;
            static std::vector<bool> released;
            static std::vector<bool> hold;
          };

          struct queue
          {
            static uint first;
            static uint last;
            static std::list<char> list;
          };

          static SDL_Joystick *joystick;


        /* Internals */
          static KEY getKey(unsigned char key);

    };
  }


  /* Check if a known platform is defined */
    #if (!defined(PLATFORM_WINDOWS) && !defined(PLATFORM_LINUX) && !defined(PLATFORM_PANDORA) && !defined(PLATFORM_WIZ) && !defined(PLATFORM_CAANOO))
      #error No known platform defined!
    #endif


#endif // INPUT_INPUT_HPP
