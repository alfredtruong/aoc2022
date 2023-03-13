#ifndef __DAY17_HPP
#define __DAY17_HPP

#include <bitset>
#include <list>

namespace day17 {

class Cave
{
private:
  static const int WIDTH = 7;
  int m_rock_type_idx = 0;
  int m_rock_bottom_idx = 4;
  int m_rock_left_idx = 2;
  bool m_rock_is_settled = true;
  int m_blow_idx = 0;
  std::string m_blow;
  std::vector<std::bitset<WIDTH>> m_contents; // list as can pop levels in between

public:
  Cave(std::string);

  void show_details();
  void show_line(const auto& line,std::string blurb = "\n");
  void show_cave();

  void add(int);
  void add_test();

  bool is_line_empty(auto& line);
  void move_from_to(auto& line,int from_idx,int to_idx);

  void blow(int,bool = false);
  void blow_direction(int,bool,bool = false);
  void blow_minus(bool is_left = false,bool verbose = false);
  void blow_plus(bool is_left = false,bool verbose = false);
  void blow_el(bool is_left = false,bool verbose = false);
  void blow_pipe(bool is_left = false,bool verbose = false);
  void blow_block(bool is_left = false,bool verbose = false);
  void blow_test(int);

  void drop(int);
  void drop_minus();
  void drop_plus();
  void drop_el();
  void drop_pipe();
  void drop_block();
  void drop_test(int);

  void drop_shape(int,bool verbose = false);
  void drop_n_shapes(int n_shapes,bool verbose = false);
};

}

void day17_part1();
void day17_part2();

#endif // __DAY17_HPP
