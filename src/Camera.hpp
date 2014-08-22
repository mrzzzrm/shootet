#ifndef CAMERA_HPP
#define CAMERA_HPP

  #include "framework.hpp"

  class Camera
  {
    public:

      Camera();
      ~Camera();


      /* Position */
        const geo::FloatPoint &getPosition() const;
        void setPosition(const geo::FloatPoint &position);


      /* Offset */
        const geo::FloatVector &getOffset() const;
        void setOffset(const geo::FloatVector &offset);


      /* Position + Offset */
        double getX() const;
        double getY() const;



    private:

      /* Data */
        geo::FloatPoint position;
        geo::FloatVector offset;
  };

#endif // CAMERA_HPP
