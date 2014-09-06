#ifndef COLLISION_RECTMAP_TPP
#define COLLISION_RECTMAP_TPP


  template<typename TCollMap>
  bool RectMap::isCollision(
                             const CollMapClipping<TCollMap> &collmapclipping,
                             const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                             const geo::IntRect &rect1,
                             const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
  {
    if(collmapclipping.getCollMap() != NULL)
      isCollision(*collmapclipping.getCollMap(), pos1, pos2, rect1, *(geo::IntRect*)collmapclipping.getCollMap(), alignment1, alignment2);
    else
      return false;
  }



#endif // COLLISION_RECTMAP_TPP
