#include "./Player.hpp"

using namespace std;

using namespace input;
using namespace geo;


/*
  Class Player
*/
  Player::Player()
  {
    x = 0;
    tx = 0;
    cc = 0;

    itemcountvector.resize(ITEM_TYPE_END);

    state = PLAYER_NORMAL;
  }


  Player::~Player()
  {

  }


  int Player::getTargetX() const
  {
    return tx;
  }


  void Player::setColumnCount(int cc)
  {
    this->cc = cc;
  }


  void Player::setX(double x)
  {
    FloatPoint::setX(x);
    this->x = (int)x;
    tx = this->x;
  }


  int Player::getItemCount(ITEM_TYPE type) const
  {
    return itemcountvector[type];
  }


  void Player::addItem(ITEM_TYPE type)
  {
    itemcountvector[type]++;
  }


  void Player::removeItem(ITEM_TYPE type)
  {
    if(itemcountvector[type] > 0)
      itemcountvector[type]--;
  }


  PLAYER_STATE Player::getState() const
  {
    return state;
  }


  void Player::setState(PLAYER_STATE state)
  {
    this->state = state;
  }


  bool Player::isItemFastcollect() const
  {
    return item_fastcollect;
  }


  int Player::getWidth()
  {
    if(media::gfx::player::normal.getFrameCount() != 0)
      return media::gfx::player::normal.getFrame(0).getWidth();
    else
      return 0;
  }


  int Player::getHeight()
  {
    if(media::gfx::player::normal.getFrameCount() != 0)
      return media::gfx::player::normal.getFrame(0).getHeight();
    else
      return 0;
  }


  void Player::update()
  {
    Timer::update();

    if(Input::isButtonHold(BUTTON_DOWN))
      item_fastcollect = true;
    else
      item_fastcollect = false;


    if(Input::isButtonHold(BUTTON_LEFT) && x > 0)
      tx = x - 1;
    if(Input::isButtonHold(BUTTON_RIGHT) && x < cc - 1)
      tx = x + 1;


    if(x != tx)
    {
      s8 dir;
      double step, remain;

      dir = tx - x;
      step = Timer::getPerSecond(PLAYER_SPEED_X);
      remain = fabs(FloatPoint::getX() - tx);

      if(remain <= step)
      {
        x = tx;
        FloatPoint::setX(tx);
      }
      else
      {
        FloatPoint::setX(FloatPoint::getX() + step * dir);
      }
    }
  }

