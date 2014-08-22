#include "./MorphTile.hpp"

using namespace std;


#define gen_nodes(a, b, c, d, e, f, g, h) (((a) << 0) | ((b) << 2) | ((c) << 4) | ((d) << 6) | ((e) << 8) | ((f) << 10) | ((g) << 12) |  ((h) << 14))

u16 old_nodemap[] =
{
  gen_nodes(2,2,1,0,0,1,2,2), /* 0 */
  gen_nodes(2,2,1,0,0,0,0,1), /* 1 */
  gen_nodes(2,2,2,2,1,0,0,1), /* 2 */

  gen_nodes(2,2,1,1,1,1,2,2), /* 3 */
  gen_nodes(2,2,1,1,2,2,1,1), /* 4 */
  gen_nodes(2,2,2,2,1,1,1,1), /* 5 */

  gen_nodes(0,0,0,1,1,0,0,0), /* 6 */
  gen_nodes(0,0,0,1,1,1,1,0), /* 7 */
  gen_nodes(0,0,0,0,0,1,1,0), /* 8 */

  gen_nodes(2,2,2,2,1,1,2,2), /* 9 */
  gen_nodes(1,1,1,1,1,1,2,2), /* 10 */
  gen_nodes(2,2,1,1,1,1,1,1), /* 11 */

  gen_nodes(2,2,1,1,1,0,0,1), /* 12 */
  gen_nodes(2,2,1,0,0,1,1,1), /* 13 */
  gen_nodes(1,0,0,1,1,1,2,2), /* 14 */



  gen_nodes(1,0,0,0,0,1,2,2), /* 15 */
  gen_nodes(0,0,0,0,0,0,0,0), /* 16 */
  gen_nodes(0,1,2,2,1,0,0,0), /* 17 */

  gen_nodes(1,1,2,2,1,1,2,2), /* 18 */
  gen_nodes(2,2,2,2,2,2,2,2), /* 19 */
  gen_nodes(1,1,2,2,1,1,2,2), /* 20 */

  gen_nodes(0,1,1,1,1,0,0,0), /* 21 */
  gen_nodes(1,1,1,1,1,1,1,1), /* 22 */
  gen_nodes(1,0,0,0,0,1,1,1), /* 23 */

  gen_nodes(1,1,2,2,2,2,2,2), /* 24 */
  gen_nodes(1,1,2,2,1,1,1,1), /* 25 */
  gen_nodes(1,1,1,1,2,2,1,1), /* 26 */

  gen_nodes(0,1,1,1,2,2,1,0), /* 27 */
  gen_nodes(1,0,0,1,2,2,1,1), /* 28 */
  gen_nodes(1,1,1,0,0,1,2,2), /* 29 */



  gen_nodes(1,0,0,1,2,2,2,2), /* 30 */
  gen_nodes(0,0,0,1,2,2,1,0), /* 31 */
  gen_nodes(0,1,2,2,2,2,1,0), /* 32 */

  gen_nodes(1,1,1,1,2,2,2,2), /* 33 */
  gen_nodes(2,2,1,1,2,2,1,1), /* 34 */
  gen_nodes(1,1,2,2,2,2,1,1), /* 35 */

  gen_nodes(0,1,1,0,0,0,0,0), /* 36 */
  gen_nodes(1,1,1,0,0,0,0,1), /* 37 */
  gen_nodes(1,0,0,0,0,0,0,1), /* 38 */

  gen_nodes(2,2,1,1,2,2,2,2), /* 39 */
  gen_nodes(2,2,2,2,2,2,1,1), /* 40 */
  gen_nodes(1,1,1,1,1,1,1,1), /* 41 */

  gen_nodes(0,1,2,2,1,1,1,0), /* 42 */
  gen_nodes(1,1,2,2,1,0,0,1), /* 43 */
  gen_nodes(1,1,1,1,1,1,1,1), /* 44 */
};



u16 nodemap[] =
{
  gen_nodes(2,2,1,0,0,1,2,2), /* 0 */
  gen_nodes(2,2,1,0,0,0,0,1), /* 1 */
  gen_nodes(2,2,2,2,1,0,0,1), /* 2 */

  gen_nodes(2,2,1,1,1,1,2,2), /* 3 */
  gen_nodes(2,2,2,2,1,1,1,1), /* 4 */

  gen_nodes(0,0,0,1,1,0,0,0), /* 5 */
  gen_nodes(0,0,0,1,1,1,1,0), /* 6 */
  gen_nodes(0,0,0,0,0,1,1,0), /* 8 */

  gen_nodes(2,2,1,1,1,1,1,1), /* 11 */
  gen_nodes(1,1,1,1,2,2,1,1), /* 26 */

  gen_nodes(1,1,1,1,1,1,2,2), /* 10 */
  gen_nodes(1,1,2,2,1,1,1,1), /* 25 */

  gen_nodes(2,2,2,2,1,1,2,2), /* 9 */
  gen_nodes(1,1,2,2,2,2,2,2), /* 24 */





  gen_nodes(1,0,0,0,0,1,2,2), /* 15 */
  gen_nodes(0,0,0,0,0,0,0,0), /* 16 */
  gen_nodes(0,1,2,2,1,0,0,0), /* 17 */

  gen_nodes(1,1,1,1,2,2,2,2), /* 33 */
  gen_nodes(1,1,2,2,2,2,1,1), /* 35 */

  gen_nodes(0,1,1,1,1,0,0,0), /* 21 */
  gen_nodes(2,2,2,2,2,2,2,2), /* 19 */
  gen_nodes(1,0,0,0,0,1,1,1), /* 23 */

  gen_nodes(2,2,1,1,1,0,0,1), /* 12 */
  gen_nodes(0,1,1,1,2,2,1,0), /* 27 */

  gen_nodes(1,1,1,0,0,1,2,2), /* 29 */
  gen_nodes(0,1,2,2,1,1,1,0), /* 42 */

  gen_nodes(2,2,1,1,2,2,2,2), /* 39 */
  gen_nodes(2,2,2,2,2,2,1,1), /* 40 */





  gen_nodes(1,0,0,1,2,2,2,2), /* 30 */
  gen_nodes(0,0,0,1,2,2,1,0), /* 31 */
  gen_nodes(0,1,2,2,2,2,1,0), /* 32 */

  gen_nodes(1,1,2,2,1,1,2,2), /* 18 */
  gen_nodes(2,2,1,1,2,2,1,1), /* 34 */

  gen_nodes(0,1,1,0,0,0,0,0), /* 36 */
  gen_nodes(1,1,1,0,0,0,0,1), /* 37 */
  gen_nodes(1,0,0,0,0,0,0,1), /* 38 */

  gen_nodes(2,2,1,0,0,1,1,1), /* 13 */
  gen_nodes(1,0,0,1,2,2,1,1), /* 28 */

  gen_nodes(1,0,0,1,1,1,2,2), /* 14 */
  gen_nodes(1,1,2,2,1,0,0,1), /* 43 */



  gen_nodes(1,1,1,1,1,1,1,1), /* X */
  gen_nodes(1,1,1,1,1,1,1,1), /* X */
};


MorphTile::MorphTile(int id)
{
  nodes = nodemap[id];
}


MorphTile::~MorphTile()
{

}


u8 MorphTile::getNode(u8 index) const
{
  return (nodes & (3 << (index * 2))) >> (index * 2);
}


void MorphTile::setNode(u8 index, u8 mode)
{   ;
  nodes &= ~(3<<(index * 2));
  nodes |= (mode << (index * 2));
}

int MorphTile::getId() const
{
  for(int id = 0; id < 45; id++)
  {
    if(nodemap[id] == nodes)
      return id;
  }

  /* Error */
  for(int n = 0; n < 8; n++)
  {
    cout << (int)getNode(n);
  }
  throw error::Exception() << "No such id for nodes "<<(void*)nodes;

}


void MorphTile::setId(int id)
{
  nodes = nodemap[id];
}


bool MorphTile::isTopOpen() const
{
  if(getNode(0) < 2)
    return true;
  else if(getNode(1) < 2)
    return true;
  else
    return false;
}


bool MorphTile::isBottomOpen() const
{
  if(getNode(4) < 2)
    return true;
  else if(getNode(5) < 2)
    return true;
  else
    return false;
}


bool MorphTile::isLeftOpen() const
{
  if(getNode(6) < 2)
    return true;
  else if(getNode(7) < 2)
    return true;
  else
    return false;
}


bool MorphTile::isRightOpen() const
{
  if(getNode(2) < 2)
    return true;
  else if(getNode(3) < 2)
    return true;
  else
    return false;
}
