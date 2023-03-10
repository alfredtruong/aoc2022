#ifndef __DAY17_HPP
#define __DAY17_HPP

#include <bitset>
#include <list>

namespace day17 {

static const std::string rocks = R"(####

.#.
###
.#.

..#
..#
###

#
#
#
#

##
##)";

class Cave
{
private:
  static const int WIDTH = 7;
  int m_rock_idx = 0;
  int m_blow_idx = 0;
  int m_rock_bottom_lhs= 2;
  int m_rock_bottom_rhs= 2;
  bool m_rock_is_settled = true;
  std::string m_blow;
  std::list<std::bitset<WIDTH>> m_contents; // list as can pop levels in between

public:
  Cave(std::string);

  void show_line(const auto& line,std::string blurb = "\n");
  void show_cave();

  void add();
  void add_minus();
  void add_plus();
  void add_el();
  void add_pipe();
  void add_block();
  void add_test();

  bool is_line_empty(auto& line);
  void move_from_to(auto& line,int from_idx,int to_idx);

  void drop_one_shape(bool verbose = false);

  void blow_once(bool verbose = false);
  void blow(bool is_left);
  void blow_minus(bool is_left = false,bool verbose = false);
  void blow_plus(bool is_left = false,bool verbose = false);
  void blow_el(bool is_left = false,bool verbose = false);
  void blow_pipe(bool is_left = false,bool verbose = false);
  void blow_block(bool is_left = false,bool verbose = false);
  void blow_minus_test();
  void blow_plus_test();
  void blow_el_test();
  void blow_pipe_test();
  void blow_block_test();

  void drop_once();
  void drop_minus();
  void drop_plus();
  void drop_el();
  void drop_pipe();
  void drop_block();
  void drop_minus_test();
  void drop_plus_test();
  void drop_el_test();
  void drop_pipe_test();
  void drop_block_test();



};

}

void day17_part1();
void day17_part2();

#endif // __DAY17_HPP
