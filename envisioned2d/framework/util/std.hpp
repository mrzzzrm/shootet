#ifndef UTIL_STD_HPP
#define UTIL_STD_HPP

  #include <map>
  #include <list>
  #include <vector>
  #include <queue>
  #include <iostream>
  #include <fstream>
  #include <string>


  #include "error/Exception.hpp"
  #include "util/Path.hpp"
  #include "util/out.hpp"

  namespace util
  {

    /* List */
      template<typename T> void list_delete_all_and_clear(std::list<T*> &list);
      template<typename T> typename std::list<T*>::iterator list_erase_and_delete(std::list<T*> &list, typename std::list<T*>::iterator &i);
      template<typename T> std::list<T*> list_copy(const std::list<T*> &list);


    /* Vector */
      template<typename T> void vector_delete_all_and_clear(std::vector<T*> &vector);
      template<typename T> typename std::vector<T*>::iterator vector_erase_and_delete(std::vector<T*> &vector, typename std::vector<T*>::iterator &i);
      template<typename T> std::vector<T*> vector_copy(const std::vector<T*> &vector);


    /* Map */
      template<typename TKey, typename TValue> void map_delete_all_and_clear(std::map<TKey, TValue*> &map);
      template<typename TKey, typename TValue> std::map<TKey, TValue*> map_copy(const std::map<TKey, TValue*> &map);


    /* IO streams */
      std::string file_to_string(const Path &path);
      void string_to_file(const std::string &string, const Path &path);

  }

  #include "./std.tpp"


#endif // UTIL_STD_HPP
