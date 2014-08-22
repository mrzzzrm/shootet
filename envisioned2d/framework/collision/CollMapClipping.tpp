#ifndef COLLISION_COLLMAPCLIPPING_TPP
#define COLLISION_COLLMAPCLIPPING_TPP

/*
  Class CollMapClipping<TCollMap>
*/
  template<typename TCollMap>
  CollMapClipping<TCollMap>::CollMapClipping()
  {
    init();
  }


  template<typename TCollMap>
  CollMapClipping<TCollMap>::CollMapClipping(const TCollMap *collmap, const geo::IntRect &blitrect)
  {
    init();
    load(collmap, blitrect);
  }



  template<typename TCollMap>
  CollMapClipping<TCollMap>::CollMapClipping(const CollMapClipping<TCollMap> &pixelmapclipping)
  {
    if(&pixelmapclipping == this)
      return;

    init();
    load(pixelmapclipping);
  }


  template<typename TCollMap>
  CollMapClipping<TCollMap>::~CollMapClipping()
  {
    clear();
  }


  template<typename TCollMap>
  void CollMapClipping<TCollMap>::load(const TCollMap *collmap, const geo::IntRect &blitrect)
  {
    clear();

    this->collmap = collmap;

    geo::IntRect::load(blitrect);
  }


  template<typename TCollMap>
  void CollMapClipping<TCollMap>::load(const CollMapClipping<TCollMap> &collmapclipping)
  {
    clear();

    collmap = collmapclipping.collmap;

    geo::IntRect::load(collmapclipping);
  }


  template<typename TCollMap>
  void CollMapClipping<TCollMap>::clear()
  {
    init();
    geo::IntRect::clear();
  }



  template<typename TCollMap>
  const TCollMap *CollMapClipping<TCollMap>::getCollMap() const
  {
    return collmap;
  }


  template<typename TCollMap>
  void CollMapClipping<TCollMap>::setCollMap(const TCollMap *collmap)
  {
    this->collmap = collmap;
  }


  template<typename TCollMap>
  template<typename TCollMap2>
  bool CollMapClipping<TCollMap>::isCollision(
                                                  const TCollMap2 &collmap2,
                                                  const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                                                  const geo::IntRect &rect2,
                                                  const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
  {
    if(collmap != NULL && collmap2.collmap != NULL)
      return collmap->isCollision(*collmap2.collmap, pos1, pos2, *(geo::IntRect*)this, rect2, alignment1, alignment2);
    else
      return false;
  }


  template<typename TCollMap>
  template<typename TCollMap2>
  bool CollMapClipping<TCollMap>::isCollision(
                                              const CollMapClipping<TCollMap2> &collmapclipping2,
                                              const geo::IntPoint &pos1, const geo::IntPoint &pos2,
                                              const etc::Alignment &alignment1, const etc::Alignment &alignment2) const
  {
    if(collmap != NULL && collmapclipping2.collmap != NULL)
      return collmap->isCollision(*collmapclipping2.collmap, pos1, pos2, *(geo::IntRect*)this, collmapclipping2, alignment1, alignment2);
    else
      return false;
  }


  template<typename TCollMap>
  CollMapClipping<TCollMap> &CollMapClipping<TCollMap>::operator=(const CollMapClipping<TCollMap> &collmapclipping)
  {
    load(collmapclipping);
    return *this;
  }


  template<typename TCollMap>
  void CollMapClipping<TCollMap>::init()
  {
    collmap = NULL;
  }


#endif


