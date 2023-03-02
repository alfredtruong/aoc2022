#include "../utils.hpp"

#include <fstream> // std::fstream
#include <string>
#include <string_view>

// char str[] vs std::string str;
// https://www.programiz.com/cpp-programming/strings

inline std::string test_input =
R"(Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3

Monkey 1:
  Starting items: 54, 65, 75, 74
  Operation: new = old + 6
  Test: divisible by 19
    If true: throw to monkey 2
    If false: throw to monkey 0

Monkey 2:
  Starting items: 79, 60, 97
  Operation: new = old * old
  Test: divisible by 13
    If true: throw to monkey 1
    If false: throw to monkey 3

Monkey 3:
  Starting items: 74
  Operation: new = old + 3
  Test: divisible by 17
    If true: throw to monkey 0
    If false: throw to monkey 1)";

struct Monkey
{
  std::list<int64_t> items; // list of items held
  char op;
  int64_t opValue;
  int64_t divBy; // worry divisor
  int toMonkeyIfPass; // target monkey if false
  int toMonkeyIfFail; // target monkey if true
  int64_t inspections = 0;

  int64_t operator <=> (const Monkey& m)
  {
    return inspections - m.inspections; // spaceship operator
  }
};

std::string getLine(std::istream& file)
{
  std::string line;
  getline(file,line);
  return line;
}

void Task1(std::istream& file)
{
  auto ans = 0;

  std::vector<Monkey> monkeys;
  std::string line;
  while(file)
  {
    Monkey monkey;
    std::string tmp;
    std::stringstream ss;
  }
}

void Task2(std::istream& file)
{
}

void Task1_example(std::string str)
{
  Task1(str_to_ss(str));
}

void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day11_1.txt");
  Task1(f);
  f.close();
}

void Task2_example(std::string str)
{
  Task2(str_to_ss(str));
}

void Task2_actual()
{
  std::fstream f;
  f.open("../../input/day11_1.txt");
  Task2(f);
  f.close();
}

int main()
{
  Task1_example(test_input);
  Task1_actual();

  Task2_example(test_input);
  Task2_actual();
  return 0;
}
