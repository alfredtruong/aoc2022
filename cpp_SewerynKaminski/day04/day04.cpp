#include "../utils.hpp"

#include <fstream> // std::fstream
#include <iostream>
#include <functional>

inline std::string test_input =
R"(2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8
)";

auto ignore(int i)
{
  return [i](std::istream &o)->std::istream& {
    return o.ignore(i,'\0');
  };
}

struct Section
{
  int start;
  int end;
};

std::istream& operator>>(std::istream& o, std::function<std::istream&(std::istream&)> f)
{
  f(o);
}

auto& operator>>(std::istream& o,Section &s)
{
  return ((o.peek()=='\n') ? o >> ignore(1) : o) >> s.start >> ignore(1) >> s.end;
}

void Task1(std::istream& file)
{
  auto fully_contains = [](const Section &s1,const Section &s2)
  {
    return s1.start <= s2.start && s2.end <= s1.end;
  };

  int ans=0;
  Section s1,s2;
  while (file >> s1 >> ignore(1) >> s2)
  {
    if (fully_contains(s1,s2) || fully_contains(s2,s1))
    {
      ans++;
    }
  }
  OUT ( ans );
}

void Task2(std::istream& file)
{
  auto overlap = [](const Section &s1,const Section &s2)
  {
    return s1.start <= s2.end && s1.end >= s2.start;
  };

  int ans=0;
  Section s1,s2;
  while (file >> s1 >> ignore(1) >> s2)
  {
    if (overlap(s1,s2) || overlap(s2,s1))
    {
      ans++;
    }
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
  f.open("../../input/day04_1.txt");
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
  f.open("../../input/day04_1.txt");
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
