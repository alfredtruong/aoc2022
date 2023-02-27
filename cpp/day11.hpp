#ifndef __DAY11_HPP
#define __DAY11_HPP

namespace day11 {

class Monkey
{
private:
  int m_id;
  int m_n_inspections;
  std::deque<int> m_items;
  std::vector<std::string> m_operation;
  int m_worry_divisor;
  int m_test_divisor;
  int m_true_false_target_monkey[2];

public:
  Monkey(const std::vector<std::string> &monkey_input,bool divide_worry_by_three=false);
  ~Monkey();

  void show_monkey();
  void parse_monkey_input_line(const std::vector<std::string> &split_colon,bool verbose=false);
  int get_id();
  int get_n_inspections();
  int get_worry_divisor();
  int get_num_items();
  std::deque<int> get_items();
  void pass_item(int &,int &,int &);
  void receive_item(int item);
  int parse_operation_number(std::string operation_string,int worry);
  int compute_new_worry(int worry);
  bool test_new_worry(int new_worry);
};

class MonkeyBusiness
{
private:
  std::vector<Monkey> m_monkeys;
  int m_current_round;

public:
  MonkeyBusiness(std::string filepath,bool divide_worry_by_three=true);
  ~MonkeyBusiness();
  void show_monkey_items();
  void show_monkey_worry_divisor();
  void show_monkey_n_inspections();

  void populate_monkeys(std::string filepath,bool divide_worry_by_three=true);
  void do_round(bool verbose=false);
  void take_turn(int monkey_id,bool verbose=false);
};

}

void day11_part1();
void day11_part2();

#endif // __DAY11_HPP
