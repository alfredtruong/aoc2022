#include "utils/utils.hpp"
#include "day5.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace day5 {

ElveShip::ElveShip(const std::string filepath)
{
  read_input_file(filepath,false);
  initialize_cargo_hold(false,false);
}

ElveShip::~ElveShip()
{
}

void ElveShip::read_input_file(const std::string filepath,bool debug)
{
  if (debug) std::cout << "[" << __func__ << "] " << std::endl;

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

  if (debug) std::cout << "m_cargo_instructions = " << m_cargo_instructions.size() << std::endl;
  if (debug) std::cout << "m_instructions = " << m_instructions.size() << std::endl;

  // finished reading file
  f.close();
}

std::vector<int> ElveShip::identify_stack_centres(bool debug)
{
  if (debug) std::cout << "[" << __func__ << "] " << std::endl;

  std::string stack_identifier_line = m_cargo_instructions[m_cargo_instructions.size()-1]; // last line
  std::vector<int> stack_centres;
  for (int i=0;i<stack_identifier_line.length();i++)
  {
    if (stack_identifier_line[i]!=' ')
    {
      stack_centres.push_back(i);
    }
  }

  if (debug) utils::display_vec<int>(stack_centres);

  return stack_centres;
}

void ElveShip::initialize_cargo_hold(bool verbose,bool debug)
{
  // identify stacks from raw string
  std::vector<int> stack_centres = identify_stack_centres();

  // populate m_cargo_hold_stacks with empty stack containers
  for (int i=0;i<stack_centres.size();i++)
  {
    std::vector<char> empty_stack;
    m_cargo_hold_stacks.push_back(empty_stack);
  }

  // populate m_cargo_hold_stacks stacks
  for (auto it = m_cargo_instructions.rbegin()+1;it!=m_cargo_instructions.rend();it++) // ignore stack number and populate stacks in reverse order
  {
    std::string cargo_string = *it;
    if (debug) std::cout << "cargo_string = " << cargo_string << std::endl;
    for (int i=0;i<stack_centres.size();i++) // loop over stacks / stack_centres
    {
      if (cargo_string[stack_centres[i]] != ' ') // if there is something to populate, populate it
      {
        m_cargo_hold_stacks[i].push_back(cargo_string[stack_centres[i]]);
      }
    }
  }

  // show what you've populated
  if (verbose) show_cargo_hold(false);
}

int ElveShip::size_of_biggest_stack(bool debug)
{
  if (debug) std::cout << "[" << __func__ << "] " << std::endl;

  int max_size = 0;
  for (auto this_stack : m_cargo_hold_stacks)
  {
    if (debug) std::cout << "this_stack_size = " << this_stack.size() << ", max_size = " << max_size << std::endl;
    if (this_stack.size()>max_size)
      max_size = this_stack.size();
  }

  if (debug) std::cout << "max_size = " << max_size << std::endl;

  return (int)max_size;
}

void ElveShip::show_cargo_hold(bool debug)
{
  if (debug) std::cout << "[" << __func__ << "] " << std::endl;
  if (debug) for (int x=0;x<m_cargo_hold_stacks.size();x++) utils::display_vec<char>(m_cargo_hold_stacks[x]);

  // show stack size
  std::cout << "size\t";
  for (int x=0;x<m_cargo_hold_stacks.size();x++) std::cout << "\t" << (int)m_cargo_hold_stacks.size(); // stacks count from 1
  std::cout << std::endl;

  // show stack identifier
  std::cout << "name\t";
  for (int x=0;x<m_cargo_hold_stacks.size();x++) std::cout << "\t" << x+1; // stacks count from 1
  std::cout << std::endl;

  // draw one layer at a time
  int max_size = size_of_biggest_stack(false);
  for (int y=0;y<max_size;y++)
  {
    // draw line
    std::cout << "level " << y << "\t";
    for (int x=0;x<m_cargo_hold_stacks.size();x++)
    {
      if (debug) std::cout << "x = " << x << ", y = " << y << ", item = " << m_cargo_hold_stacks[x][y] << std::endl;
      if (debug) std::cout << "stack_size = " << m_cargo_hold_stacks[x].size() << ", y = " << y << std::endl;
      if (y < m_cargo_hold_stacks[x].size())
      {
        std::cout << "\t" << m_cargo_hold_stacks[x][y]; // contents still in range
      }
      else
      {
        std::cout << "\t."; // no more contents in this stack
      }
    }
    std::cout << std::endl; // next line
  }
}

void ElveShip::move_from_x_to_y(int x,int y)
{
  char item = m_cargo_hold_stacks[x-1].back();
  m_cargo_hold_stacks[x-1].pop_back();
  m_cargo_hold_stacks[y-1].push_back(item);
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

void ElveShip::move_n_from_x_to_y_for_crate_mover_9001(int n,int x,int y)
{
  // copy n from x to y
  std::copy(
    m_cargo_hold_stacks[x-1].end()-n,
    m_cargo_hold_stacks[x-1].end(),
    std::back_insert_iterator<std::vector<char>>(m_cargo_hold_stacks[y-1])
  );

  // remove n from x
  for (int i=0;i<n;i++)
  {
    m_cargo_hold_stacks[x-1].pop_back();
  }
  /*
  std::erase(
    m_cargo_hold_stacks[x-1].end()-n,
    m_cargo_hold_stacks[x-1].end()
  );
  */
}



void ElveShip::parse_instruction(const std::string instruction,int &move_n,int &from_x, int &to_y)
{
  // move 1 from 2 to 1
  std::vector<std::string> parsed_instruction = utils::split_string<std::string>(instruction,' ');
  move_n = std::stoi(parsed_instruction[1]);
  from_x = std::stoi(parsed_instruction[3]);
  to_y = std::stoi(parsed_instruction[5]);
}

void ElveShip::execute_instructions(bool verbose)
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

    // show cargo hold
    if (verbose)
    {
      std::cout << "instruction " << i+1 << " = " << m_instructions[i] << std::endl;
      show_cargo_hold();
    }
  }
}

void ElveShip::execute_instructions_for_crate_mover_9001(bool verbose)
{
  for (int i=0;i<m_instructions.size();i++)
  {
    // parse instruction
    int move_n=0;
    int from_x=0;
    int to_y=0;
    parse_instruction(m_instructions[i],move_n,from_x,to_y);

    // do instruction
    move_n_from_x_to_y_for_crate_mover_9001(move_n,from_x,to_y);

    // show cargo hold
    if (verbose)
    {
      std::cout << "instruction " << i+1 << " = " << m_instructions[i] << std::endl;
      show_cargo_hold();
    }
  }
}

void ElveShip::show_top()
{
  std::cout << std::endl << "top = ";
  for (int x=0;x<m_cargo_hold_stacks.size();x++) std::cout << m_cargo_hold_stacks[x][m_cargo_hold_stacks[x].size()-1];
  std::cout << std::endl;
}

void part_5_parse_and_execute_instructions(std::string blurb,std::string filepath)
{
  // crate mover 9000
  ElveShip ship(filepath);
  ship.execute_instructions();
  ship.show_top();
}

void part_5_parse_and_execute_instructions_for_crate_mover_9001(std::string blurb,std::string filepath)
{

  // crate mover 9001
  ElveShip ship(filepath);
  ship.execute_instructions_for_crate_mover_9001(false);
  ship.show_top();
}

}

void day5_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day5::part_5_parse_and_execute_instructions("test data","../input/day05_0.txt");
  day5::part_5_parse_and_execute_instructions("test data","../input/day05_1.txt");
}

void day5_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day5::part_5_parse_and_execute_instructions_for_crate_mover_9001("test data","../input/day05_0.txt");
  day5::part_5_parse_and_execute_instructions_for_crate_mover_9001("test data","../input/day05_1.txt");
}
