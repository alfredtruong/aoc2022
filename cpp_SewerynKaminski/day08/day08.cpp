#include "../utils.hpp"

#include <fstream> // std::fstream
#include <iostream>
#include <vector>
#include <list>

inline std::string test_input =
R"(30373
25512
65332
33549
35390)";


void Task1(std::istream& file)
{
  // find doubles
  std::vector<std::string> trees;
  std::vector<std::string> visible_trees;
  std::string line;
  while (file >> line)
  {
    trees.push_back(line);
    visible_trees.push_back(std::string(line.length(),'0'));
  }

  const size_t HEIGHT = trees.size();
  const size_t WIDTH = trees[0].length();

  auto fun = [&trees, &visible_trees](char& vo, size_t x, size_t y)
  {
    int v=trees[y][x];
    if(v>vo)
    {
      visible_trees[y][x] |= '1';
      vo=v;
    }
  };

  char vo1;
  char vo2;

  // horizontal scan
  for (auto y=0;y<HEIGHT;y++)
  {
    vo1='/';
    vo2='/';
    for (auto x=0;x<WIDTH;x++)
    {
      fun(vo1,x,y);
      fun(vo2,WIDTH-x-1,y);
    }
  }

  // vertical scan
  for (auto x=0;x<WIDTH;x++)
  {
    vo1='/';
    vo2='/';
    for (auto y=0;y<HEIGHT;y++)
    {
      fun(vo1,x,y);
      fun(vo2,x,HEIGHT-y-1);
    }
  }

  auto ans=0;
  for (auto &l : visible_trees)
  {
    for (auto &v : l)
    {
      ans += v=='1';
    }
  }

  OUT ( ans );
}

void Task2(std::istream& file)
{
}


void Task1_example()
{
  Task1(str_to_ss(test_input));
}
void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day08_1.txt");
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
  f.open("../../input/day08_1.txt");
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
