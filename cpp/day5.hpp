#ifndef __DAY5_HPP
#define __DAY5_HPP

namespace day5
{

/*
    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
*/
class ElveShip
{
private:
  std::vector<std::string> m_cargo_instructions;
  std::vector<std::string> m_instructions;
  std::vector<std::vector<char>> m_cargo_hold_stacks;

public:
  ElveShip(const std::string fn);
  ~ElveShip();

  void read_input_file(const std::string,bool);
  std::vector<int> identify_stack_centres();
  void initialize_cargo_hold();
  int size_of_biggest_stack();
  void show_cargo_hold();
  void move_from_x_to_y(int x,int y);
  void move_n_from_x_to_y(int n,int x,int y);
  void parse_instruction(const std::string instruction,int &move_n,int &from_x, int &to_y);
  void execute_instructions();
};


}
void day5_part1();
void day5_part2();

#endif // __DAY5_HPP
