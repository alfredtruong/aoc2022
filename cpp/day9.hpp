#ifndef __DAY9_HPP
#define __DAY9_HPP

#include <cstdlib>

namespace day9 {

class rope_section
{
private:
  int m_section_id;
  std::vector<std::vector<std::string>> m_instructions;
  std::vector<std::vector<std::string>> m_tail_instructions; // for tail to act as next head
  std::set<std::pair<int,int>> m_tail_visited;
  std::pair<int,int> m_head_position;
  std::pair<int,int> m_tail_position;

public:
  rope_section(int);
  ~rope_section();
  void read_instructions(std::string filepath);
  void apply_all_instructions(bool verbose=false);
  void apply_instruction(std::vector<std::string> instruction,bool verbose=false);
  void update_tail(bool verbose);
  void initialize_position(std::pair<int,int> &p);
  int get_section_id();
  void print_head_position();
  void print_tail_position();
  void print_position(std::pair<int,int> &p,std::string name);
  void count_tail_locations();
  std::vector<std::vector<std::string>> get_tail_instructions();
};

class rope
{
private:
  std::vector<rope_section> m_rope; // .front() is head, .back() is tail

public:
  rope(int n_sections);
  void read_instructions(std::string filepath);
  void apply_all_instructions(bool verbose);
  void print_head_position();
  void print_tail_position();
  void count_tail_locations();
  void count_all_tail_locations();
};


}

void day9_part1();
void day9_part2();

#endif // __DAY9_HPP
