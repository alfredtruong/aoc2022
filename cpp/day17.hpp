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
  std::list<std::bitset<WIDTH>> m_contents; // list as can pop levels in between

public:
  Cave() {
    add_rock_minus();

    show_cave();
  }

  add_rock_test() {
    add_rock_minus();
    show_cave();
    m_contents.clear();

    add_rock_plus();
    show_cave();
    m_contents.clear();

    add_rock_el();
    show_cave();
    m_contents.clear();

    add_rock_pipe();
    show_cave();
    m_contents.clear();

    add_rock_block();
    show_cave();
    m_contents.clear();
  }

  void show_bitset(auto& bs)
  {
    for (int i=WIDTH-1;i>=0;i--)
    {
      if (bs[i])
        std::cout << '#';
      else
        std::cout << '.';
    }
  }
  void show_cave()
  {
    std::cout << m_contents.size() << std::endl;

    for (auto it=m_contents.rbegin();it!=m_contents.rend();it++)
    {
      show_bitset(*it);
      std::cout << "\t" << (*it).any() << std::endl;
    }
  }

  void add_rock()
  {
    switch (m_rock_idx)
    {
    case 0:
      add_rock_minus();
      break;
    case 1:
      add_rock_plus();
      break;
    case 2:
      add_rock_el();
      break;
    case 3:
      add_rock_pipe();
      break;
    case 4:
      add_rock_block();
      break;
    }
  }

  void add_rock_minus()
  {
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b00011110);
  }

  void add_rock_plus()
  {
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0001000);
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0001000);
  }

  void add_rock_el()
  {
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
  }

  void add_rock_pipe()
  {
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0010000);
    m_contents.emplace_back(0b0010000);
    m_contents.emplace_back(0b0010000);
    m_contents.emplace_back(0b0010000);
  }

  void add_rock_block()
  {
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0011000);
    m_contents.emplace_back(0b0011000);
  }

  void drop_rock()
  {
    switch (m_rock_idx)
    {
    case 0:
      drop_rock_minus();
      break;
    case 1:
      drop_rock_plus();
      break;
    case 2:
      drop_rock_el();
      break;
    case 3:
      drop_rock_pipe();
      break;
    case 4:
      drop_rock_block();
      break;
    }
  }

  void drop_rock_minus()
  {

  }

  void drop_rock_plus()
  {

  }

  void drop_rock_el()
  {

  }

  void drop_rock_pipe()
  {

  }

  void drop_rock_block()
  {

  }

};

}

void day17_part1();
void day17_part2();

#endif // __DAY17_HPP
