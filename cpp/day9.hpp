#ifndef __DAY9_HPP
#define __DAY9_HPP

#include <cstdlib>

namespace day9 {

class rope_movements
{
private:
  std::vector<std::vector<std::string>> m_instructions;
  std::set<std::pair<int,int>> m_tail_visited;
  std::pair<int,int> m_head_position;
  std::pair<int,int> m_tail_position;

public:
  rope_movements(std::string filepath,bool verbose=false)
  {
    // initialize positions
    initialize_position(m_head_position);
    initialize_position(m_tail_position);

    // initialize tail visited container
    m_tail_visited.insert(m_tail_position);

    // read and apply instructions
    read_instructions(filepath);
    apply_instructions(verbose);

    // display how many places visited
    std::cout << m_tail_visited.size() << std::endl;
  }

  void read_instructions(std::string filepath)
  {
    m_instructions = utils::parse_file<std::string>(filepath,' ',false);
  }

  void apply_instructions(bool verbose)
  {
    for (auto instruction : m_instructions)
    {
      move_head(instruction,verbose);
    }
  }
  void initialize_position(std::pair<int,int> &p)
  {
    p.first=0;
    p.second=0;
  }

  void print_head_position()
  {
    print_position(m_head_position,"head");
  }

  void print_tail_position()
  {
    print_position(m_tail_position,"tail");
  }

  void print_position(std::pair<int,int> &p,std::string name)
  {
    std::cout << name << " : " << p.first << "/" << p.second << std::endl;
  }

  void move_head(std::vector<std::string> instruction,bool verbose)
  {
    if (verbose) std::cout << __func__ << std::endl;
    if (verbose) utils::display_vec<std::string>(instruction);

    std::string direction = instruction[0];
    int times = std::stoi(instruction[1]);
    if (direction == "U")
    {
      for (int i=0;i<times;i++)
      {
        if (verbose) std::cout << "[head before]\t";
        if (verbose) print_head_position();
        m_head_position.second++;
        if (verbose) std::cout << "[head after]\t";
        if (verbose) print_head_position();
        move_tail(verbose);
      }
    }
    else if (direction == "D")
    {
      for (int i=0;i<times;i++)
      {
        if (verbose) std::cout << "[head before]\t";
        if (verbose) print_head_position();
        m_head_position.second--;
        if (verbose) std::cout << "[head after]\t";
        if (verbose) print_head_position();
        move_tail(verbose);
      }
    }
    else if (direction == "L")
    {
      for (int i=0;i<times;i++)
      {
        if (verbose) std::cout << "[head before]\t";
        if (verbose) print_head_position();
        m_head_position.first--;
        if (verbose) std::cout << "[head after]\t";
        if (verbose) print_head_position();
        move_tail(verbose);
      }
    }
    else if (direction == "R")
    {
      for (int i=0;i<times;i++)
      {
        if (verbose) std::cout << "[head before]\t";
        if (verbose) print_head_position();
        m_head_position.first++;
        if (verbose) std::cout << "[head after]\t";
        if (verbose) print_head_position();
        move_tail(verbose);
      }
    }
  }

  void move_tail(bool verbose)
  {
    //if (verbose) std::cout << __func__ << std::endl;
    if (verbose) std::cout << "[tail before]\t\t";
    if (verbose) print_tail_position();

    int x_distance = m_head_position.first - m_tail_position.first;
    int y_distance = m_head_position.second - m_tail_position.second;

    if (std::abs(x_distance)<2 && std::abs(y_distance)<2)
    {
      // connected either diagonally or on a line
      if (verbose) std::cout << "[tail after]\t\tdid not move, chg(x)=" << x_distance << ", chg(y)=" << y_distance << std::endl;
      return;
    }
    else
    {
      if (x_distance==0 && y_distance==2)
      {
        m_tail_position.second++;
      }
      else if (x_distance==1 && y_distance==2)
      {
        m_tail_position.first++;
        m_tail_position.second++;
      }
      else if (x_distance==2 && y_distance==1)
      {
        m_tail_position.first++;
        m_tail_position.second++;
      }
      else if (x_distance==2 && y_distance==0)
      {
        m_tail_position.first++;
      }
      else if (x_distance==2 && y_distance==-1)
      {
        m_tail_position.first++;
        m_tail_position.second--;
      }
      else if (x_distance==1 && y_distance==-2)
      {
        m_tail_position.first++;
        m_tail_position.second--;
      }
      else if (x_distance==0 && y_distance==-2)
      {
        m_tail_position.second--;
      }
      else if (x_distance==-1 && y_distance==-2)
      {
        m_tail_position.first--;
        m_tail_position.second--;
      }
      else if (x_distance==-2 && y_distance==-1)
      {
        m_tail_position.first--;
        m_tail_position.second--;
      }
      else if (x_distance==-2 && y_distance==0)
      {
        m_tail_position.first--;
      }
      else if (x_distance==-2 && y_distance==1)
      {
        m_tail_position.first--;
        m_tail_position.second++;
      }
      else if (x_distance==-1 && y_distance==2)
      {
        m_tail_position.first--;
        m_tail_position.second++;
      }
      else
      {
        exit(1);
      }
    }
    if (verbose) std::cout << "[tail after]\t\t";
    if (verbose) print_tail_position();

    // add tail location to data structure if it's not been visited before
    if (m_tail_visited.find(m_tail_position)==m_tail_visited.end())
    {
      //std::pair<int,int> save_me(m_tail_position);
      //m_tail_visited.insert(save_me);

      m_tail_visited.insert(m_tail_position);
    }
  }
};

}

void day9_part1();
void day9_part2();

#endif // __DAY9_HPP
