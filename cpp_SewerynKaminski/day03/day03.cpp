#include "../utils.hpp"

#include <fstream> // std::fstream

inline std::string test_input =
R"(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)";

void Task1(std::istream& file)
{
  // find doubles
  auto find_doubles = [](std::string l1,std::string l2) -> uint64_t{ // []() -> return_type
    for (auto c1:l1) {
      for (auto c2:l2) {
        if (c1==c2)
          return c1+=c1 <= 'Z' ? -'A' + 27 : -'a' + 1;
      }
    }
    return 0;
  };

  int ans = 0;
  std::string line;
  while (std::getline(file,line))
  {
    // split on half
    auto half = line.length() / 2;
    auto left = line.substr(0,half);
    auto right = line.substr(half);
    ans += find_doubles(left,right);
  }
  OUT ( ans );
}

void Task2(std::istream& file)
{
  // find doubles
  auto find_badge = [](std::string l1,std::string l2,std::string l3) -> uint64_t{ // []() -> return_type
    for (auto c1:l1) {
      for (auto c2:l2) {
        for (auto c3:l3) {
        if (c1==c2 && c2==c3)
          return c1+=c1 <= 'Z' ? -'A' + 27 : -'a' + 1;
        }
      }
    }
    return 0;
  };

  int ans = 0;
  std::string line;
  while (file)
  {
    // get 3 lines
    std::string l1,l2,l3;
    std::getline(file,l1);
    std::getline(file,l2);
    std::getline(file,l3);
    ans += find_badge(l1,l2,l3);
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
  f.open("../../input/day03_1.txt");
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
  f.open("../../input/day03_1.txt");
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
