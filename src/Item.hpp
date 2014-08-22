#ifndef ITEM_HPP
#define ITEM_HPP

  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"



  class Item: public geo::FloatPoint
  {
    public:

      Item(ITEM_TYPE type, const geo::FloatPoint &position);
      ~Item();


      /* Type */
        ITEM_TYPE getType() const;


      /* Height */
        static int getHeight(ITEM_TYPE type);


    private:

      /* Data */
        ITEM_TYPE type;
  };

#endif // ITEM_HPP
