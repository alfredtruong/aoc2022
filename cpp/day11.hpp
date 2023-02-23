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
  int m_test_divisor;
  int m_true_false_target_monkey[2];

public:
  Monkey(const std::vector<std::string> &monkey_input)
  {
    // parse monkey input to populate monkey attributes
    for (std::string line : monkey_input)
    {
      // std::cout << "[" << __func__ << "] " << line << std::endl;
      std::vector<std::string> split_colon = utils::split_string<std::string>(line,':');
      parse_monkey_input_line(split_colon,false);
    }

    show_monkey();
  }

  ~Monkey()
  {

  }

  void show_monkey()
  {
    std::cout << "[id] " << m_id << std::endl;
    utils::display_deque(m_items,"starting items");
    utils::display_vec(m_operation,"operation");
    std::cout << "[test divisor] " << m_test_divisor << std::endl;
    std::cout << "[true monkey] " << m_true_false_target_monkey[0] << std::endl;
    std::cout << "[false monkey] " << m_true_false_target_monkey[1] << std::endl;
  }

  void parse_monkey_input_line(const std::vector<std::string> &split_colon,bool verbose=false)
  {
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

  int pass_item()
  {
    if (m_items.size()==0)
      return -1; // do nothing
    else
    {
      m_n_inspections++; // increment counter
      int new_worry = compute_worry(m_items[0]); // inspect item in front
      bool test_result = test_new_worry(new_worry); // figure out where item will go
      m_items.pop_front(); // throw item to target monkey
      return test_result ? m_true_false_target_monkey[0] : m_true_false_target_monkey[1]; // return target monkey
    }
  }

  void receive_item(int item)
  {
    m_items.push_back(item); // receive item
  }

  int parse_operation_number(std::string operation_string,int worry)
  {
    return (operation_string == "old") ? worry : std::stoi(operation_string);
  }

  int compute_worry(int worry)
  {
    // parse left and right numbers
    int left_num = parse_operation_number(m_operation[0],worry);
    int right_num = parse_operation_number(m_operation[2],worry);

    // perform operation as required
    if (m_operation[1] == "+")
      return left_num + right_num;
    else if (m_operation[1] == "-")
      return left_num - right_num;
    else if (m_operation[1] == "*")
      return left_num * right_num;
    else if (m_operation[1] == "/")
      return left_num / right_num;
    else
      exit(1);
  }

  bool test_new_worry(int item_worry)
  {
    // compute result of test
    item_worry /= 3;
    return (item_worry % m_test_divisor) == 0;
  }

  int get_n_inspections()
  {
    return m_n_inspections;
  }
};

class MonkeyBusiness
{
private:
  std::vector<Monkey> m_monkeys;

public:
  MonkeyBusiness(std::string filepath)
  {
    populate_monkeys(filepath);
  }

  ~MonkeyBusiness()
  {
  }

  void populate_monkeys(std::string filepath)
  {
    std::fstream f;
    std::string line;
    f.open(filepath,std::ios::in);
    std::vector<std::string> monkey_input;

    while (std::getline(f,line))
    {
      //std::cout << line << std::endl;
      // aggregate lines associated to particular monkey
      if (line.length()==0)
      {
        // build and remember monkey
        m_monkeys.push_back(Monkey(monkey_input));

        // prep next monkey
        monkey_input.clear();
      }
      else
      {
        monkey_input.push_back(line);
      }

    }
  }
};

}

void day11_part1();
void day11_part2();

#endif // __DAY11_HPP
