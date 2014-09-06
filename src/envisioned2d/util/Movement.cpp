#include "./Movement.hpp"

using namespace std;
using namespace geo;
using namespace error;


namespace util
{

  Movement::Movement()
  {

  }


  Movement::Movement(const geo::FloatVector &vector)
  {
    Movement::load(vector);
  }


  Movement::Movement(const Movement &movement)
  {
    if(&movement == this)
      return;

    Movement::load(movement);
  }


  Movement::~Movement()
  {
    clear();
  }


  void Movement::load(const geo::FloatVector &vector)
  {
    /*
      Atm this doesn't change anything but the base vector.
      All accelerations remain untouched
    */

    /* Load base */
      FloatVector::load(vector);
  }


  void Movement::load(const Movement &movement)
  {
    clear();

    FloatVector::load(movement);

    timer = movement.timer;

    accelerationmap.clear();
    for(map<u32, FloatVector*>::const_iterator i = movement.accelerationmap.begin(); i != movement.accelerationmap.end(); i++)
    {
      accelerationmap[i->first] = new FloatVector(*(i->second));
    }
  }


  void Movement::clear()
  {
    for(map<u32, FloatVector*>::iterator i = accelerationmap.begin(); i != accelerationmap.end(); i++)
    {
      delete i->second;
    }
    accelerationmap.clear();

    FloatVector::clear();
    timer.clear();
  }


  void Movement::update()
  {
    timer.update();

    for(map<u32, FloatVector*>::iterator i = accelerationmap.begin(); i != accelerationmap.end(); i++)
    {
      this->FloatVector::operator+=(timer.getPerSecond(*(i->second)));
    }
  }

  bool Movement::isAccelerationSet(u32 index) const
  {
    std::map<u32, FloatVector*>::const_iterator i;

    if(accelerationmap.find(index) == accelerationmap.end())
      return false;
    else
      return true;
  }


  const FloatVector &Movement::getAcceleration(u32 index) const
  {
    std::map<u32, FloatVector*>::const_iterator i;

    if((i = accelerationmap.find(index)) == accelerationmap.end())
      throw Exception() << "No such acceleration with index '" << index << "'";
    else
      return *(i->second);
  }


  void Movement::setAcceleration(u32 index, const geo::FloatVector &acceleration)
  {
    if(accelerationmap[index] == NULL)
      accelerationmap[index] = new FloatVector(acceleration);
    else
      accelerationmap[index]->load(acceleration);
  }


  Movement &Movement::operator=(const FloatVector &vector)
  {
    load(vector);
    return *this;
  }


  Movement &Movement::operator=(const Movement &movement)
  {
    load(movement);
    return *this;
  }

}

