#include "utils/utils.hpp"
#include "day11.hpp"
#include <algorithm>

namespace day11 {

Monkey::Monkey(const std::vector<std::string> &monkey_input, bool divide_worry_by_three)
{
  // parse monkey input to populate monkey attributes
  for (std::string line : monkey_input)
  {
    // std::cout << "[" << __func__ << "] " << line << std::endl;
    std::vector<std::string> split_colon = utils::split_string<std::string>(line,':');
    parse_monkey_input_line(split_colon,false);
  }

  if (divide_worry_by_three)
    m_worry_divisor = 3;
  else
    m_worry_divisor = 1;

  // show_monkey();
}

Monkey::~Monkey() {}

void Monkey::show_monkey()
{
  std::cout << "[id] " << m_id << std::endl;
  utils::display_deque(m_items,"starting items");
  utils::display_vec(m_operation,"operation");
  std::cout << "[test divisor] " << m_test_divisor << std::endl;
  std::cout << "[true monkey] " << m_true_false_target_monkey[0] << std::endl;
  std::cout << "[false monkey] " << m_true_false_target_monkey[1] << std::endl;
  std::cout << "[worry divisor] " << m_worry_divisor << std::endl;
  std::cout << std::endl;
}

void Monkey::parse_monkey_input_line(const std::vector<std::string> &split_colon,bool verbose)
{
  //std::cout << __func__ << std::endl;
  //utils::display_vec(split_colon);

  if (split_colon.size()==1)
  {
    auto split = utils::split_string<std::string>(split_colon[0],' ');
    m_id = std::stoi(split.back());
    if (verbose) std::cout << "[id] " << m_id << std::endl;
  }
  else if (split_colon[0] == "  Starting items")
  {
    auto split = utils::split_string<std::string>(split_colon[1],',');
    for (auto x : split) m_items.push_back(std::stoi(x));
    if (verbose) utils::display_deque(m_items,"starting items");
  }
  else if (split_colon[0] == "  Operation")
  {
    auto split = utils::split_string<std::string>(split_colon[1],'=');
    m_operation = utils::split_string<std::string>(split[1],' ');
    if (verbose) utils::display_vec(m_operation,"operation");
  }
  else if (split_colon[0] == "  Test")
  {
    auto split = utils::split_string<std::string>(split_colon[1],' ');
    m_test_divisor = std::stoi(split.back());
    if (verbose) std::cout << "[test divisor] " << m_test_divisor << std::endl;
  }
  else if (split_colon[0] == "    If true")
  {
    auto split = utils::split_string<std::string>(split_colon[1],' ');
    m_true_false_target_monkey[0] = std::stoi(split.back());
    if (verbose) std::cout << "[true monkey] " << m_true_false_target_monkey[0] << std::endl;
  }
  else if (split_colon[0] == "    If false")
  {
    auto split = utils::split_string<std::string>(split_colon[1],' ');
    m_true_false_target_monkey[1] = std::stoi(split.back());
    if (verbose) std::cout << "[false monkey] " << m_true_false_target_monkey[1] << std::endl;
  }
  else
  {
    std::cout << __func__ << " not recognized" << std::endl;
    exit(1);
  }
}

int Monkey::get_id()
{
  return m_id;
}

int Monkey::get_n_inspections()
{
  return m_n_inspections;
}

int Monkey::get_worry_divisor()
{
  return m_worry_divisor;
}

int Monkey::get_num_items()
{
  return m_items.size();
}

std::deque<int> Monkey::get_items()
{
  return m_items;
}

void Monkey::pass_item(int &old_worry,int &new_worry,int &target_monkey)
{
  m_n_inspections++; // increment counter
  old_worry = get_items()[0]; // inspect item in front
  new_worry = compute_new_worry(old_worry); // inspect item in front
  bool test_result = test_new_worry(new_worry); // figure out where item will go
  target_monkey = test_result ? m_true_false_target_monkey[0] : m_true_false_target_monkey[1]; // return target monkey
  //utils::display_deque<int>(m_items,"before");
  m_items.pop_front(); // throw item to target monkey
  //utils::display_deque<int>(m_items,"after");
}

void Monkey::receive_item(int item)
{
  m_items.push_back(item); // receive item
}

int Monkey::parse_operation_number(std::string operation_string,int worry)
{
  return (operation_string == "old") ? worry : std::stoi(operation_string);
}

int Monkey::compute_new_worry(int worry)
{
  //std::cout << __func__ << std::endl;
  // parse left and right numbers
  int left_num = parse_operation_number(m_operation[1],worry);
  int right_num = parse_operation_number(m_operation[3],worry);

  // perform operation as required
  int new_worry;
  if (m_operation[2] == "+")
    new_worry = left_num + right_num;
  else if (m_operation[2] == "-")
    new_worry = left_num - right_num;
  else if (m_operation[2] == "*")
    new_worry = left_num * right_num;
  else if (m_operation[2] == "/")
    new_worry = left_num / right_num;
  else
    exit(1);

  // return new worry
  if (m_worry_divisor!=1)
  return new_worry /= m_worry_divisor;
}

bool Monkey::test_new_worry(int new_worry)
{
  // compute result of test
  return (new_worry % m_test_divisor) == 0;
}

MonkeyBusiness::MonkeyBusiness(std::string filepath,bool divide_worry_by_three)
{
  populate_monkeys(filepath,divide_worry_by_three);

  m_current_round = 0;
  //show_monkey_items();

  for (int i=0;i<20;i++)
  {
    do_round();
  }
  show_monkey_n_inspections();
}

MonkeyBusiness::~MonkeyBusiness() {}

void MonkeyBusiness::show_monkey_items()
{
  std::cout << "round[" << m_current_round << "]" << std::endl;
  for (int i=0;i<m_monkeys.size();i++)
  {
    utils::display_deque<int>(m_monkeys[i].get_items(),std::to_string(i));
  }
}

void MonkeyBusiness::show_monkey_n_inspections()
{
  std::vector<int> monkey_n_inspections;

  for (int i=0;i<m_monkeys.size();i++)
  {
    monkey_n_inspections.push_back(m_monkeys[i].get_n_inspections());
    std::cout << "monkey[" << i << "] inspected " << monkey_n_inspections[i] << " items" << std::endl;
  }

  // sort
  std::sort(monkey_n_inspections.begin(),monkey_n_inspections.end(),std::greater<int>()); // default sorts ascending
  std::cout << monkey_n_inspections[0] << std::endl;
  std::cout << monkey_n_inspections[1] << std::endl;
  std::cout << monkey_n_inspections[0] * monkey_n_inspections[1] << std::endl;

}

void MonkeyBusiness::show_monkey_worry_divisor()
{
  for (int i=0;i<m_monkeys.size();i++)
  {
    std::cout << "monkey[" << i << "] worry_divisor " << m_monkeys[i].get_worry_divisor() << std::endl;
  }
}
void MonkeyBusiness::populate_monkeys(std::string filepath,bool divide_worry_by_three)
{
  std::fstream f;
  std::string line;
  f.open(filepath,std::ios::in);
  std::vector<std::string> monkey_input;

  while (std::getline(f,line) || monkey_input.size() != 0)
  {
    //std::cout << line << std::endl;
    //std::cout << m_monkeys.size() << std::endl;
    // aggregate lines associated to particular monkey
    if (line.length()==0)
    {
      m_monkeys.push_back(Monkey(monkey_input,divide_worry_by_three)); // build and remember monkey
      monkey_input.clear(); // prep next monkey
    }
    else
    {
      monkey_input.push_back(line);
      //utils::display_vec<std::string>(monkey_input);
      line.clear();
    }
  }
}

void MonkeyBusiness::do_round(bool verbose)
{
  for (int i=0;i<m_monkeys.size();i++)
  {
    take_turn(i,false);
  }

  m_current_round++;
  if (verbose) show_monkey_items();
}

void MonkeyBusiness::take_turn(int monkey_id,bool verbose)
{
  Monkey *this_monkey = &m_monkeys[monkey_id]; // must * and & to avoid copying monkey

  while (this_monkey->get_num_items()!=0)
  {
    int this_item_old_worry;
    int this_item_new_worry;
    int receiving_monkey;
    this_monkey->pass_item(this_item_old_worry,this_item_new_worry,receiving_monkey); // this monkey passes item
    m_monkeys[receiving_monkey].receive_item(this_item_new_worry); // receiving monkey receives item

    if (verbose)
      std::cout
      << "this_monkey[" << this_monkey->get_id() << "] gave item with old_worry[" << this_item_old_worry << "]"
      << " to receiving_monkey[" << receiving_monkey << "] with new_worry[" << this_item_new_worry << "]"
      << std::endl;
  }
}

void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  MonkeyBusiness mb("../input/day11_ex1.txt");
  mb.show_monkey_worry_divisor();
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  MonkeyBusiness mb("../input/day11_1.txt");
  mb.show_monkey_worry_divisor();
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
  MonkeyBusiness mb("../input/day11_ex1.txt",false);
  mb.show_monkey_worry_divisor();
}

void part_2()
{
  std::cout << "part 2" << std::endl;
}



}

void day11_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day11::part_1_ex1();
  day11::part_1();
}

void day11_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day11::part_2_ex2();
  //day11::part_2();
}

