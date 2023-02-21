#include "utils/utils.hpp"
#include "day9.hpp"

namespace day9
{

rope_section::rope_section(int id = 0)
{
  // identifier
  m_section_id = id;

  // initialize positions
  initialize_position(m_head_position);
  initialize_position(m_tail_position);

  // initialize tail visited container
  m_tail_visited.insert(m_tail_position);

  //print_head_position();
  //print_tail_position();
}

rope_section::~rope_section()
{
}

void rope_section::initialize_position(std::pair<int,int> &p)
{
  p.first=0;
  p.second=0;
}

void rope_section::read_instructions(std::string filepath)
{
  m_instructions = utils::parse_file<std::string>(filepath,' ',false);
}

int rope_section::get_section_id()
{
  return m_section_id;
}

void rope_section::print_head_position()
{
  print_position(m_head_position,"head");
}

void rope_section::print_tail_position()
{
  print_position(m_tail_position,"tail");
}

void rope_section::print_position(std::pair<int,int> &p,std::string name)
{
  std::cout << name << " : " << p.first << "/" << p.second << std::endl;
}

void rope_section::count_tail_locations()
{
  // display how many places visited
  std::cout << m_tail_visited.size() << std::endl;
}

void rope_section::apply_all_instructions(bool verbose)
{
  for (auto instruction : m_instructions)
    apply_instruction(instruction,verbose);
}

void rope_section::apply_instruction(std::vector<std::string> instruction,bool verbose)
{
  //m_tail_instructions.clear();
  if (verbose) utils::display_vec<std::string>(instruction,"head instruction");

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
      update_tail(verbose);
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
      update_tail(verbose);
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
      update_tail(verbose);
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
      update_tail(verbose);
    }
  }
  else if (direction == "UR")
  {
    for (int i=0;i<times;i++)
    {
      if (verbose) std::cout << "[head before]\t";
      if (verbose) print_head_position();
      m_head_position.first++;
      m_head_position.second++;
      if (verbose) std::cout << "[head after]\t";
      if (verbose) print_head_position();
      update_tail(verbose);
    }
  }
  else if (direction == "DR")
  {
    for (int i=0;i<times;i++)
    {
      if (verbose) std::cout << "[head before]\t";
      if (verbose) print_head_position();
      m_head_position.first++;
      m_head_position.second--;
      if (verbose) std::cout << "[head after]\t";
      if (verbose) print_head_position();
      update_tail(verbose);
    }
  }
  else if (direction == "DL")
  {
    for (int i=0;i<times;i++)
    {
      if (verbose) std::cout << "[head before]\t";
      if (verbose) print_head_position();
      m_head_position.first--;
      m_head_position.second--;
      if (verbose) std::cout << "[head after]\t";
      if (verbose) print_head_position();
      update_tail(verbose);
    }
  }
  else if (direction == "UL")
  {
    for (int i=0;i<times;i++)
    {
      if (verbose) std::cout << "[head before]\t";
      if (verbose) print_head_position();
      m_head_position.first--;
      m_head_position.second++;
      if (verbose) std::cout << "[head after]\t";
      if (verbose) print_head_position();
      update_tail(verbose);
    }
  }
  else
  {
    std::cout << "head direction not recognised" << std::endl;
    exit(1);
  }
  if (verbose) utils::display_vecvec<std::string>(m_tail_instructions,"tail_instructions");
}

void rope_section::update_tail(bool verbose)
{
  // input for next section
  std::vector<std::string> tail_instruction;

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
      tail_instruction.push_back("U");
      tail_instruction.push_back("1");
    }
    else if (
      (x_distance==1 && y_distance==2) ||
      (x_distance==2 && y_distance==2) ||
      (x_distance==2 && y_distance==1)
    )
    {
      m_tail_position.first++;
      m_tail_position.second++;
      tail_instruction.push_back("UR");
      tail_instruction.push_back("1");
    }
    else if (x_distance==2 && y_distance==0)
    {
      m_tail_position.first++;
      tail_instruction.push_back("R");
      tail_instruction.push_back("1");
    }
    else if (
      (x_distance==2 && y_distance==-1) ||
      (x_distance==2 && y_distance==-2) ||
      (x_distance==1 && y_distance==-2)
    )
    {
      m_tail_position.first++;
      m_tail_position.second--;
      tail_instruction.push_back("DR");
      tail_instruction.push_back("1");
    }
    else if (x_distance==0 && y_distance==-2)
    {
      m_tail_position.second--;
      tail_instruction.push_back("D");
      tail_instruction.push_back("1");
    }
    else if (
      (x_distance==-1 && y_distance==-2) ||
      (x_distance==-2 && y_distance==-2) ||
      (x_distance==-2 && y_distance==-1)
    )
    {
      m_tail_position.first--;
      m_tail_position.second--;
      tail_instruction.push_back("DL");
      tail_instruction.push_back("1");
    }
    else if (x_distance==-2 && y_distance==0)
    {
      m_tail_position.first--;
      tail_instruction.push_back("L");
      tail_instruction.push_back("1");
    }
    else if (
      (x_distance==-2 && y_distance==1) ||
      (x_distance==-2 && y_distance==2) ||
      (x_distance==-1 && y_distance==2)
    )
    {
      m_tail_position.first--;
      m_tail_position.second++;
      tail_instruction.push_back("UL");
      tail_instruction.push_back("1");
    }
    else
    {
      std::cout << "tail direction not recognised, " << x_distance << " " << y_distance << std::endl;
      exit(1);
    }
    m_tail_instructions.push_back(tail_instruction);
  }
  if (verbose) std::cout << "[tail after]\t\t";
  if (verbose) print_tail_position();

  // add tail location to data structure if it's not been visited before
  if (m_tail_visited.find(m_tail_position)==m_tail_visited.end())
  {
    //std::pair<int,int> save_me(m_tail_position);
    //m_tail_visited.insert(save_me);
    if (verbose) std::cout << "[" << this->m_section_id << " tail visits] " << m_tail_position.first << " " << m_tail_position.second << std::endl;
    m_tail_visited.insert(m_tail_position);
  }
}

std::vector<std::vector<std::string>> rope_section::get_tail_instructions()
{
  return m_tail_instructions;
}

rope::rope(int n_sections)
{
  for (int i=0;i<n_sections;i++)
  {
    rope_section r(i);
    m_rope.push_back(r);
  }
}

void rope::read_instructions(std::string filepath)
{
  m_rope.front().read_instructions(filepath);
}

void rope::apply_all_instructions(bool verbose)
{
  m_rope[0].apply_all_instructions();
  for (int i=1;i<m_rope.size();i++)
  {
    std::vector<std::vector<std::string>> tail_instructions = m_rope[i-1].get_tail_instructions(); // moves from leading tail
    if (verbose) utils::display_vecvec<std::string>(tail_instructions,"generated tail instructions");

    for (auto instruction : tail_instructions)
    {
      m_rope[i].apply_instruction(instruction);
    }
  }
}

void rope::print_head_position()
{
  m_rope.front().print_head_position();
}

void rope::print_tail_position()
{
  m_rope.back().print_tail_position();
}

void rope::count_tail_locations()
{
  m_rope.back().count_tail_locations();
}

void rope::count_all_tail_locations()
{
  for (auto section : m_rope)
  {
      std::cout << section.get_section_id() << " ";
      section.count_tail_locations();
  }
}

void part_1_rope_section(std::string blurb,std::string filepath)
{
  rope_section rs;

  rs.read_instructions(filepath);
  rs.apply_all_instructions(false);
  rs.count_tail_locations();

  rs.print_head_position();
  rs.print_tail_position();
}

void part_2_full_rope(std::string blurb,std::string filepath)
{
  rope r(9);

  r.read_instructions(filepath);
  r.apply_all_instructions(false);
  r.print_head_position();
  r.print_tail_position();
  r.count_tail_locations();
  r.count_all_tail_locations();
}

}

void day9_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day9::part_1_rope_section("test data","../input/day09_0.txt");
  day9::part_1_rope_section("test data","../input/day09_1.txt");
}

void day9_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day9::part_2_full_rope("test data","../input/day09_0.txt");
  day9::part_2_full_rope("test data","../input/day09_2.txt");
  day9::part_2_full_rope("test data","../input/day09_1.txt");
}
