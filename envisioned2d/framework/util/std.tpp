#ifndef UTIL_STD_TPP
#define UTIL_STD_TPP

  namespace util
  {
    /**
          LIST
    **/
    template<typename T>
    void list_delete_all_and_clear(std::list<T*> &list)
    {
      for(typename std::list<T*>::iterator i = list.begin(); i != list.end(); i++)
      {
        if(*i != NULL)
          delete *i;
      }

      list.clear();
    }


    template<typename T>
    typename std::list<T*>::iterator list_erase_and_delete(std::list<T*> &list, typename std::list<T*>::iterator &i)
    {
      if(*i != NULL)
        delete *i;

      return list.erase(i);
    }



    template<typename T>
    std::list<T*> list_copy(const std::list<T*> &list)
    {
      std::list<T*> reslist;

      for(typename std::list<T*>::const_iterator i = list.begin(); i != list.end(); i++)
      {
        if(*i != NULL)
          reslist.push_back(new T(*(*i)));
        else
          reslist.push_back(NULL);
      }

      return reslist;
    }



    /**
          VECTOR
    **/
    template<typename T>
    void vector_delete_all_and_clear(std::vector<T*> &vector)
    {
      for(uint e = 0; e < vector.size(); e++)
      {
        if(vector[e] != NULL)
          delete vector[e];
      }

      vector.clear();
    }


    template<typename T>
    typename std::vector<T*>::iterator vector_erase_and_delete(std::vector<T*> &vector, typename std::vector<T*>::iterator &i)
    {
      if(*i != NULL)
        delete *i;

      return vector.erase(i);
    }


    template<typename T>
    std::vector<T*> vector_copy(const std::vector<T*> &vector)
    {
      std::vector<T*> resvector(vector.size());

      for(uint e = 0; e < vector.size(); e++)
      {
        if(vector[e] != NULL)
          resvector[e] = new T(*vector[e]);
        else
          resvector[e] = NULL;
      }

      return resvector;
    }



    /**
          MAP
    **/
    template<typename TKey, typename TValue>
    void map_delete_all_and_clear(std::map<TKey, TValue*> &map)
    {
      for(typename std::map<TKey, TValue*>::iterator i = map.begin(); i != map.end(); i++)
      {
        if(i->second != NULL)
          delete i->second;
      }

      map.clear();
    }


    template<typename TKey, typename TValue>
    std::map<TKey, TValue*> map_copy(const std::map<TKey, TValue*> &map)
    {
      std::map<TKey, TValue*> resmap;

      for(typename std::map<TKey, TValue*>::const_iterator i = map.begin(); i != map.end(); i++)
      {
        if(i->second != NULL)
          resmap[i->first] = new TValue(*(i->second));
        else
          resmap[i->first] = NULL;
      }

      return resmap;
    }
  }

#endif // UTIL_STD_TPP
