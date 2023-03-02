#include "../utils.hpp"

#include <fstream> // std::fstream
#include <string> // std::string
#include <algorithm> // std::sort
#include <vector> // std::vector
#include <numeric> // std::accumulate

std::string test_input
(
R"(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000)"
);

void Task1(std::istream& file)
{
  int sum = 0;
  int ans = 0;
  std::string line;
  while (std::getline(file,line))
  {
    sum = line.empty() ? (ans = std::max(ans,sum),0) : sum + std::stoi(line);
  }

  ans = std::max(ans,sum);

  OUT ( ans );
}

void Task2(std::istream& file)
{
  std::vector<int> t;
  int sum = 0;
  std::string line;
  while (std::getline(file,line))
  {
    sum = line.empty() ? (t.push_back(sum),0) : sum + std::stoi(line);
  }
  t.push_back(sum);

  // sort top totals
  std::sort(t.begin(),t.end(),std::greater<int>());

  // aggregate top 3 totals
  int ans = 0;
  ans = std::accumulate(t.begin(),t.begin()+3,0);

  OUT ( ans );
}

void Task1_example()
{
  Task1(str_to_ss(test_input));
}
void Task1_actual()
{
  std::fstream f;
  f.open("../../input/day01_1.txt");
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
  f.open("../../input/day01_1.txt");
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
