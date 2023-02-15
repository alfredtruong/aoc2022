#include "utils/utils.hpp"
#include "day5.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace day5 {

ElveShip::ElveShip(const std::string filename)
{
  read_input_file(filename,false);
  initialize_cargo_hold();
}

ElveShip::~ElveShip()
{
}

void ElveShip::read_input_file(const std::string filepath,bool debug)
{
  // open file
  std::fstream f;
  f.open(filepath,std::ios::in);

  bool populate_initial_cargo_hold = true;
  std::string line;
  while (std::getline(f,line))
  {
    if (debug) std::cout << line.length() << "|" << line;
    // look for empty line separator between m_cargo_instructions and m_instructions
    if (line.length()==0)
    {
      populate_initial_cargo_hold = false; // finished reading stack info, remaining info is for m_instructions
    }
    else
    {
      if (populate_initial_cargo_hold)
      {
        if (debug) std::cout << " : m_cargo_instructions";
        m_cargo_instructions.push_back(line);
      }
      else
      {
        if (debug) std::cout << " : m_instructions";
        m_instructions.push_back(line);
      }
    }
    if (debug) std::cout << std::endl;
  }

  if (debug) std::cout << m_cargo_instructions.size() << std::endl;
  if (debug) std::cout << m_instructions.size() << std::endl;

  // finished reading file
  f.close();
}

std::vector<int> ElveShip::identify_stack_centres()
{
  std::string stack_identifier_line = m_cargo_instructions[m_cargo_instructions.size()-1]; // last line
  std::vector<int> stack_centres;
  for (int i=0;i<stack_identifier_line.length();i++)
  {
    if (stack_identifier_line[i]!=' ')
    {
      stack_centres.push_back(i);
    }
  }
  return stack_centres;
}

void ElveShip::initialize_cargo_hold()
{
  // identify stacks from raw string
  std::vector<int> stack_centres = identify_stack_centres();

  // populate m_cargo_hold_stacks with empty stack containers
  for (int i=0;i<stack_centres.size();i++)
  {
    std::vector<char> s;
    m_cargo_hold_stacks.push_back(s);
  }

  // populate m_cargo_hold_stacks stacks
  for (auto it = m_cargo_instructions.rbegin()+1;it!=m_cargo_instructions.rend();it++) // ignore stack number (reverse) header
  {
    std::string cargo_string = *it;
    for (int i=0;i<stack_centres.size();i++) // loop over stacks
    {
      if (cargo_string[i] != ' ') // if there is something to populate, populate it
      {
        m_cargo_hold_stacks[i].push_back(cargo_string[stack_centres[i]]);
      }
    }
  }

  // show what you've populated
  show_cargo_hold();
}

int ElveShip::size_of_biggest_stack()
{
  int max_size = 0;
  for (auto s : m_cargo_hold_stacks)
  {
    if (s.size()>max_size)
      max_size = s.size();
  }
  return (int)max_size;
}

void ElveShip::show_cargo_hold()
{
  // draw stack identifier
  for (int x=0;x<m_cargo_hold_stacks.size();x++)
  {
    std::cout << " " << x+1;
  }
  std::cout << std::endl;

  // draw one layer at a time
  int max_size = size_of_biggest_stack();
  for (int y=0;y<max_size;y++)
  {
    for (int x=0;x<m_cargo_hold_stacks.size();x++)
    {
      if (m_cargo_hold_stacks[x].size() <= y)
      {
        std::cout << " " << m_cargo_hold_stacks[x][y]; // contents still in range
      }
      else
      {
        std::cout << " " << " "; // no more contents in this stack
      }
    }
    std::cout << std::endl;

  }
}

void ElveShip::move_from_x_to_y(int x,int y)
{
  char item = m_cargo_hold_stacks[x].back();
  m_cargo_hold_stacks[x].pop_back();
  m_cargo_hold_stacks[y].push_back(item);
}

void ElveShip::move_n_from_x_to_y(int n,int x,int y)
{
  int i=0;
  while(i<n)
  {
    move_from_x_to_y(x,y);
    i++;
  }
}

void ElveShip::parse_instruction(const std::string instruction,int &move_n,int &from_x, int &to_y)
{
  // move 1 from 2 to 1
  std::vector<std::string> parsed_instruction = utils::split_string<std::string>(instruction,' ');
  move_n = std::stoi(parsed_instruction[1]);
  from_x = std::stoi(parsed_instruction[3]);
  to_y = std::stoi(parsed_instruction[5]);
}

void ElveShip::execute_instructions()
{
  for (int i=0;i<m_instructions.size();i++)
  {
    // parse instruction
    int move_n=0;
    int from_x=0;
    int to_y=0;
    parse_instruction(m_instructions[i],move_n,from_x,to_y);

    // do instruction
    move_n_from_x_to_y(move_n,from_x,to_y);

    // show m_cargo_hold
    std::cout << "[" << i << "] " << m_instructions[i] << std::endl;
    show_cargo_hold();
  }
}


void part_5(std::string blurb,std::string filename)

{
  /*
  std::cout << rock_paper_scissors_score('A','Y') << std::endl;
  std::cout << rock_paper_scissors_score('B','X') << std::endl;
  std::cout << rock_paper_scissors_score('C','Z') << std::endl;
  */

  ElveShip a(filename);

}


}

void day5_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day5::part_5("test data","../input/day05_0.txt");
  //day5::part_1_tournament_score("test data","../input/day05_1.txt");
}

void day5_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  //day5::part_2_tournament_score("test data","../input/day05_0.txt");
  //day5::part_2_tournament_score("test data","../input/day05_1.txt");
}
