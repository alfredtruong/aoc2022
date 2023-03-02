#include "../utils.hpp"

#include <fstream> // std::fstream

inline std::string test_input =
R"(A Y
B X
C Z)";

void Task1(std::istream& file)
{
  // define function within function
  auto score = [](auto a,auto b){
    return ((4+b-a) % 3) * 3 + b + 1;
  };

  int ans = 0;
  std::string line;
  while (std::getline(file,line))
  {
    char a = line[0] - 'A';
    char b = line[2] - 'X';
    ans += score(a,b);
  }
  /*
  0 - rock
  1 - paper
  2 - scissors
  (4 + 2 - 0) % 3 = 0 lost
  (4 + 0 - 0) % 3 = 1 remis
  (4 + 1 - 0) % 3 = 2 win
  */

  OUT ( ans );
}

void Task2(std::istream& file)
{
  // define function within function
  auto score = [](auto a,auto b){
    return ((4+b-a) % 3) * 3 + b + 1;
  };

  int ans = 0;
  std::string line;
  while (std::getline(file,line))
  {
    char a = line[0] - 'A';
    char b = line[2] - 'X';
    ans += score(a,(2+a+b)%3);
  }

  OUT ( ans );
}

void Task1_example()
{
  Task1(str_to_ss(test_input));
}
void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day02_1.txt");
  Task1(f);
  f.close();
}
void Task2_example()
{
  Task2(str_to_ss(test_input));
}
void Task2_actual()
{
  std::fstream f;
  f.open("../../input/day02_1.txt");
  Task2(f);
  f.close();
}

int main()
{
  Task1_example();
  Task1_actual();
  Task2_example();
  Task2_actual();
  return 0;
}
