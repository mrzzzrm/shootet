#ifndef UTIL_CSV_HPP
#define UTIL_CSV_HPP

  #include <list>
  #include <sstream>
  #include <vector>
  #include <fstream>
  #include <string>
  #include <sstream>

  #include "util/out.hpp"
  #include "util/Path.hpp"
  #include "error/Exception.hpp"

  #include "./std.hpp"

  namespace util
  {

    class Csv
    {
      public:

        Csv();
        Csv(const Path &path, const std::string &seperators = std::string(","));
        Csv(const std::string &text, const std::string &seperatorss = std::string(","));
        Csv(const Csv &csv);
        ~Csv();


        /* Load */
          void load(const Path &path, const std::string &seperatorss = std::string(","));
          void load(const std::string &text, const std::string &seperatorss = std::string(","));
          void load(const Csv &csv);


        /* Clear */
          void clear();


        /* Read */
          u32 getLineCount() const;
          u32 getCellCount(u32 line) const;

          bool hasCell(u32 line, u32 cell) const;
          bool isInteger(u32 line, u32 cell) const;
          bool isFloat(u32 line, u32 cell) const;

          const std::string &getString(u32 line, u32 cell) const;
          u32 getInteger(u32 line, u32 cell) const;
          double getFloat(u32 line, u32 cell) const;


        /* Write */
          void setString(u32 line, u32 cell, const std::string &_string);
          void setInteger(u32 line, u32 cell, int _integer);
          void setFloat(u32 line, u32 cell, double _float);


        /* Defaults */
          void setDefaultString(const std::string &_string);
          void setDefaultInteger(int _integer);
          void setDefaultFloat(double _float);


        /* To string */
          std::string toString() const;


        /* Operators */
          Csv &operator=(const Csv &csv);


      private:

        /* Data */
          std::vector<std::vector<std::string> > linevector;

          struct
          {
            std::string _string;
            int _integer;
            double _float;
          }def;


        /* Internals */
          void init();
    };
  }

#endif // UTIL_CSV_HPP
