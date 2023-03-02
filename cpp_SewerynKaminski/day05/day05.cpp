#include "../utils.hpp"

#include <fstream> // std::fstream
#include <iostream>
#include <vector>
#include <list>
inline std::string test_input =
R"(    [D]
[N] [C]
[Z] [M] [P]
 1   2   3

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2
)";

std::vector<std::list<char>> parseCrates(std::istream &file)
{
  std::string line;
  std::vector<std::list<char>> stacks;
  while (std::getline(file,line))
  {
    // parse file up to instructions
    if (line[1]=='1')
      break; // 1 2 3 line

    int cols = (line.length()+1)/4;
    stacks.resize(cols);
    for (int i=0;i<cols;i++)
    {
      auto c=line[1+i*4];
      if (c>' ')
      {
        stacks[i].push_back(c);
      }
    }
  }
  getline(file,line); // skip empty line
  return stacks;
}

std::string top_of_each_stack(std::vector<std::list<char>> &stacks)
{
  std::string ans;
  for (auto &stack:stacks)
  {
    ans.append(&stack.front(),1);
  }
  return ans;
}

void Task1(std::istream& file)
{
  // find doubles
  auto stacks = parseCrates(file);

  std::string ans;
  std::string line;
  while (std::getline(file,line))
  {
    // move 1 from 2 to 1
    std::stringstream ss(line);
    std::string trash;
    int len,from,to;
    ss >> trash >> len >> trash >> from >> trash >> to;
    for (int i=0;i<len;i++)
    {
      auto c=stacks[from-1].front(); // item to move
      stacks[from-1].pop_front(); // from stack
      stacks[to-1].push_front(c); // to stack
    }
  }

  ans = top_of_each_stack(stacks);
  OUT ( ans );
}

void Task2(std::istream& file)
{
  // find doubles
  auto stacks = parseCrates(file);

  std::string ans;
  std::string line;
  while (std::getline(file,line))
  {
    // move 1 from 2 to 1
    std::stringstream ss(line);
    std::string trash;
    int len,from,to;
    ss >> trash >> len >> trash >> from >> trash >> to;
    auto it=stacks[to-1].begin(); // to stack
    for (int i=0;i<len;i++)
    {
      auto c=stacks[from-1].front(); // from stack
      stacks[from-1].pop_front(); // from stack
      stacks[to-1].insert(it,c); // to stack
    }
  }

  ans = top_of_each_stack(stacks);
  OUT ( ans );
}


void Task1_example()
{
  Task1(str_to_ss(test_input));
}
void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day05_1.txt");
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
  f.open("../../input/day05_1.txt");
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
