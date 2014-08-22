#ifndef MORPHTILE_HPP
#define MORPHTILE_HPP

  #include <iostream>
  #include "framework.hpp"

  class MorphTile
  {
    public:

      MorphTile(int id);
      ~MorphTile();


      /* Node */
        u8 getNode(u8 index) const;
        void setNode(u8 index, u8 mode);


      /* Id */
        int getId() const;
        void setId(int id);


      /* Check open */
        bool isTopOpen() const;
        bool isBottomOpen() const;
        bool isLeftOpen() const;
        bool isRightOpen() const;


    private:

      /* Data */
        u16 nodes;


  };

#endif // MORPHTILE_HPP
