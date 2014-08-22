#ifndef PLAYER_HPP
#define PLAYER_HPP

  #include <cmath>
  #include "framework.hpp"

  #include "./config.hpp"
  #include "./media.hpp"


  class Player: public geo::FloatPoint, public util::Timer
  {
    public:

      Player();
      ~Player();


      /* Position */
        int getTargetX() const;
        void setColumnCount(int cc);
        void setX(double x);


      /* Items */
        int getItemCount(ITEM_TYPE type) const;
        void addItem(ITEM_TYPE type);
        void removeItem(ITEM_TYPE type);


      /* State */
        PLAYER_STATE getState() const;
        void setState(PLAYER_STATE state);


      /* Fastcollect */
        bool isItemFastcollect() const;


      /* Size */
        static int getWidth();
        static int getHeight();


      /* Loop */
        void update();


    private:

      /* Data */
        int x; /* Column */
        int tx; /* Target Column */
        int cc; /* Column count */


        std::vector<int> itemcountvector;
        bool item_fastcollect;

        PLAYER_STATE state;

  };

#endif // PLAYER_HPP
