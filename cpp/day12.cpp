#include "utils/utils.hpp"
#include "day12.hpp"

namespace day12 {

void part_1(std::string blurb,std::string filepath)
{

}

void part_2(std::string blurb,std::string filepath)
{

}



void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  ShortestPath sp("../input/day12_ex1.txt");
  sp.steps_to_start_point();
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  ShortestPath sp("../input/day12_1.txt");
  sp.steps_to_start_point();
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
  ShortestPath sp("../input/day12_ex1.txt");
  sp.min_steps_to_lowest_points();
}

void part_2()
{
  std::cout << "part 2" << std::endl;
  ShortestPath sp("../input/day12_1.txt");
  sp.min_steps_to_lowest_points();
}



}

void day12_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day12::part_1_ex1();
  day12::part_1();
}

void day12_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day12::part_2_ex2();
  day12::part_2();
}

