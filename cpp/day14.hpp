#ifndef __DAY14_HPP
#define __DAY14_HPP

#include <string>
#include <iostream>

namespace day14 {


class Cave
{
private:
  static const int m_starting_x = 500;
  static const int m_starting_y = 0;

  std::vector<std::vector<std::pair<int,int>>> m_input_rock_formations;
  std::map<std::pair<int,int>,char> m_cave;
  int m_x_min = m_starting_x; //std::numeric_limits<int>::max();
  int m_x_max = m_starting_x; //std::numeric_limits<int>::min();
  int m_y_min = m_starting_y; //std::numeric_limits<int>::max();
  int m_y_max = m_starting_y; //std::numeric_limits<int>::min();
  bool m_cave_full = false;
  int m_n_sand = 0;

public:
  Cave(std::string filepath,bool add_floor);
  void add_sand();
  void parse_file(std::string filepath);
  std::vector<std::pair<int,int>> parse_line(std::string line,bool verbose=false);
  std::pair<int,int> convert_x_comma_y(std::string x_comma_y);
  void populate_point(const std::pair<int,int>& p,const char &c,bool update_limits = false,bool verbose = false);
  void populate_rocks(bool verbose = false);
  void add_infinite_floor();
  void populate_rock_line(const std::pair<int,int>& p1,const std::pair<int,int>& p2,bool verbose = false);
  void show_cave();
  void drop_grain_of_sand(bool verbose = false);
};

}

void day14_part1();
void day14_part2();

#endif // __DAY14_HPP
