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
  int m_rock_bottom_left_idx = 2;
  int m_rock_bottom_right_idx = 2;
  bool m_rock_is_settled = false;
  std::list<std::bitset<WIDTH>> m_contents; // list as can pop levels in between

public:
  Cave() {
    //add_rock_test();
    blow_minus_test();
    //blow_plus_test();
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

  blow_minus_test()
  {
    bool verbose = true;
    add_rock_minus();
    show_cave();
    blow_minus(true,verbose);
    blow_minus(true,verbose);
    blow_minus(true,verbose);
    blow_minus(true,verbose);
    blow_minus(true,verbose);
    blow_minus(false,verbose);
    blow_minus(false,verbose);
    blow_minus(false,verbose);
    blow_minus(false,verbose);
    blow_minus(false,verbose);
    blow_minus(false,verbose);
    show_cave();
  }

  blow_plus_test()
  {
    bool verbose = true;
    add_rock_plus();
    show_cave();
    blow_plus(true,verbose);
    blow_plus(true,verbose);
    blow_plus(true,verbose);
    blow_plus(true,verbose);
    blow_plus(true,verbose);
    blow_plus(true,verbose);
    blow_plus(false,verbose);
    blow_plus(false,verbose);
    blow_plus(false,verbose);
    blow_plus(false,verbose);
    blow_plus(false,verbose);
    blow_plus(false,verbose);
    show_cave();
  }

  void show_line(const auto& line,std::string blurb = "\n")
  {
    for (int i=0;i<WIDTH;i++)
    {
      if (line[i])
        std::cout << '#';
      else
        std::cout << '.';
    }

    std::cout << blurb;
  }

  void show_cave()
  {
    std::cout <<
    "height = " << m_contents.size() <<
    ", rock settled = " << m_rock_is_settled <<
    ", rock bottom left = " << m_rock_bottom_left_idx <<
    ", rock bottom right = " << m_rock_bottom_right_idx <<
    std::endl;

    for (auto it=m_contents.rbegin();it!=m_contents.rend();it++)
    {
      show_line(*it,"");
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
    m_rock_is_settled = false;
    m_rock_bottom_left_idx = 2;
    m_rock_bottom_right_idx = 5;

    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0111100);
  }

  void add_rock_plus()
  {
    m_rock_is_settled = false;
    m_rock_bottom_left_idx = 3;
    m_rock_bottom_right_idx = 3;

    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0001000);
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0001000);
  }

  void add_rock_el()
  {
    m_rock_is_settled = false;
    m_rock_bottom_left_idx = 5;
    m_rock_bottom_right_idx = 5;

    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0010000);
    m_contents.emplace_back(0b0010000);
  }

  void add_rock_pipe()
  {
    m_rock_is_settled = false;
    m_rock_bottom_left_idx = 2;
    m_rock_bottom_right_idx = 2;

    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
  }

  void add_rock_block()
  {
    m_rock_is_settled = false;
    m_rock_bottom_left_idx = 2;
    m_rock_bottom_right_idx = 3;

    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0);
    m_contents.emplace_back(0b0001100);
    m_contents.emplace_back(0b0001100);
  }

  bool is_line_empty(auto& line)
  {
      return line.any();
  }

  void blow(bool is_left)
  {
    switch (m_rock_idx)
    {
    case 0:
      blow_minus(is_left);
      break;
    case 1:
      blow_plus(is_left);
      break;
    case 2:
      blow_el(is_left);
      break;
    case 3:
      blow_pipe(is_left);
      break;
    case 4:
      blow_block(is_left);
      break;
    }
  }

  void move_from_to(auto& line,int from_idx,int to_idx)
  {
    line[from_idx]=false;
    line[to_idx]=true;
  }
  void blow_minus(bool is_left = false,bool verbose = false)
  {
    std::stringstream blurb;

    // only care about top line
    auto& line = m_contents.back();
    int centre_offset = 0;
    if (is_left)
    {
      // only move left if (1) not at edge and (2) not trapped by settled rock
      if (m_rock_bottom_left_idx>centre_offset)
      {
        if (!line[m_rock_bottom_left_idx-1])
        {
          move_from_to(line,m_rock_bottom_right_idx,m_rock_bottom_left_idx-1);
          m_rock_bottom_left_idx--;
          m_rock_bottom_right_idx--;
          if (verbose) blurb << " blow left" << std::endl;
        }
        else
        {
          if (verbose) blurb << " blocked by settled rock" << std::endl;
        }
      }
      else
      {
        if (verbose) blurb << " already left-most" << std::endl;
      }
      if (verbose) show_line(line,blurb.str());
    }
    else
    {
      // only move right if (1) not at edge and (2) not trapped by settled rock
      if (m_rock_bottom_right_idx<(WIDTH-1-centre_offset))
      {
        if (!line[m_rock_bottom_right_idx+1])
        {
          move_from_to(line,m_rock_bottom_left_idx,m_rock_bottom_right_idx+1);
          m_rock_bottom_left_idx++;
          m_rock_bottom_right_idx++;
          if (verbose) blurb << " blow right" << std::endl;
        }
        else
        {
          if (verbose) blurb << " blocked by settled rock" << std::endl;
        }
      }
      else
      {
        if (verbose) blurb << " already right-most" << std::endl;
      }
      if (verbose) show_line(line,blurb.str());
    }
  }

  void blow_plus(bool is_left = false,bool verbose = false)
  {
    std::stringstream blurb;

    auto iter = m_contents.end();
    auto& line = *(--iter);
    auto& top_line = *(--iter);
    auto& middle_line = *(--iter);
    auto& bottom_line = *(--iter);

    show_line(top_line);
    show_line(middle_line);
    show_line(bottom_line);
    // care about 3 lines

    int centre_offset = 1;

    if (is_left)
    {
      // only move left if (1) not at edge and (2) not trapped by settled rock
      if (m_rock_bottom_left_idx>centre_offset)
      {
        if (!line[m_rock_bottom_left_idx-1])
        {
          top_line >>= 1;
          middle_line;
          bottom_line >>= 1;
          m_rock_bottom_left_idx--;
          m_rock_bottom_right_idx--;
          if (verbose) blurb << " blow left" << std::endl;
        }
        else
        {
          if (verbose) blurb << " blocked by settled rock" << std::endl;
        }
      }
      else
      {
        if (verbose) blurb << " already left-most" << std::endl;
      }
      if (verbose) show_line(line,blurb.str());
    }
    else
    {
      // only move right if (1) not at edge and (2) not trapped by settled rock
      if (m_rock_bottom_right_idx<(WIDTH-1-centre_offset))
      {
        if (!line[m_rock_bottom_right_idx+1])
        {
          //line <<= 1;
          m_rock_bottom_right_idx++;
          line[m_rock_bottom_right_idx]=true;
          line[m_rock_bottom_left_idx]=false;
          m_rock_bottom_left_idx++;
          if (verbose) blurb << " blow right" << std::endl;
        }
        else
        {
          if (verbose) blurb << " blocked by settled rock" << std::endl;
        }
      }
      else
      {
        if (verbose) blurb << " already right-most" << std::endl;
      }
      if (verbose) show_line(line,blurb.str());
    }



  }


  void blow_el(bool is_left = false)
  {

  }

  void blow_pipe(bool is_left = false)
  {

  }

  void blow_block(bool is_left = false)
  {

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
