#include "../utils.hpp"

#include <fstream> // std::fstream
#include <string>
#include <string_view>

// char str[] vs std::string str;
// https://www.programiz.com/cpp-programming/strings

inline std::string test_input_1 =
R"(noop
addx 3
addx -5)";


inline std::string test_input_2 =
R"(addx 15
addx -11
addx 6
addx -3
addx 5
addx -1
addx -8
addx 13
addx 4
noop
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx 5
addx -1
addx -35
addx 1
addx 24
addx -19
addx 1
addx 16
addx -11
noop
noop
addx 21
addx -15
noop
noop
addx -3
addx 9
addx 1
addx -3
addx 8
addx 1
addx 5
noop
noop
noop
noop
noop
addx -36
noop
addx 1
addx 7
noop
noop
noop
addx 2
addx 6
noop
noop
noop
noop
noop
addx 1
noop
noop
addx 7
addx 1
noop
addx -13
addx 13
addx 7
noop
addx 1
addx -33
noop
noop
noop
addx 2
noop
noop
noop
addx 8
noop
addx -1
addx 2
addx 1
noop
addx 17
addx -9
addx 1
addx 1
addx -3
addx 11
noop
noop
addx 1
noop
addx 1
noop
noop
addx -13
addx -19
addx 1
addx 3
addx 26
addx -30
addx 12
addx -1
addx 3
addx 1
noop
noop
noop
addx -9
addx 18
addx 1
addx 2
noop
noop
addx 9
noop
noop
noop
addx -1
addx 2
addx -37
addx 1
addx 3
noop
addx 15
addx -21
addx 22
addx -6
addx 1
noop
addx 2
addx 1
noop
addx -10
noop
noop
addx 20
addx 1
addx 2
addx 2
addx -6
addx -11
noop
noop
noop)";

class CPU
{
  int _X = 1; // register
  int _cycle = 0;
  int _sum = 0;
  std::string lcd;

  void tick()
  {
    if ( ( (_X - 1) <= (_cycle % 40 ) ) && ( (_cycle % 40 ) <= (_X + 1) )
    )
    {
      lcd[_cycle] = '#';
    }

    _cycle++;

    if ( (_cycle + 20) % 40 == 0)
    {
      _sum += _X * _cycle;
    }
  }

public:
  CPU() {
    lcd.resize (6 * 40,' '); // setup string size
  }

  void noop() {
    tick();
  }

  void addx(int x)
  {
    tick();
    tick();
    _X += x;
  }

  // getter
  inline auto sum()
  {
    return _sum;
  }

  inline auto lcd_line(int n)
  {
    return std::string_view(lcd).substr(n*40,40);
  }

  void execute(std::string_view op)
  {
    switch (op[0])
    {
    case 'n': // noop
      noop();
      break;
    case 'a': // addx
      addx(std::atoi(op.substr(5).data()));
      break;
    }
  }
};

void Task1(std::istream& file)
{
  std::string op;

  CPU cpu;
  while (std::getline(file,op))
  {
    cpu.execute(op);
  }
  int ans = cpu.sum();

  OUT ( ans );
}

void Task2(std::istream& file)
{
  std::string op;

  CPU cpu;
  while (std::getline(file,op))
  {
    cpu.execute(op);
  }
  int ans = cpu.sum();

  OUT ( ans );
}

void Task1_example(std::string str)
{
  Task1(str_to_ss(str));
}

void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day10_1.txt");
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
  f.open("../../input/day10_1.txt");
  Task2(f);
  f.close();
}

int main()
{
  Task1_example(test_input_1);
  Task1_example(test_input_2);
  Task1_actual();

  Task2_example(test_input_1);
  Task2_actual();
  return 0;
}
