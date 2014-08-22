#include "./Camera.hpp"

using namespace std;

using namespace geo;


/*
  Class Camera
*/
  Camera::Camera()
  {

  }


  Camera::~Camera()
  {

  }


  const FloatPoint &Camera::getPosition() const
  {
    return position;
  }


  void Camera::setPosition(const FloatPoint &position)
  {
    this->position = position;
  }


  const FloatVector &Camera::getOffset() const
  {
    return offset;
  }


  void Camera::setOffset(const FloatVector &offset)
  {
    this->offset = offset;
  }


  double Camera::getX() const
  {
    return position.getX() + offset.getX();
  }


  double Camera::getY() const
  {
    return position.getY() + offset.getY();
  }


