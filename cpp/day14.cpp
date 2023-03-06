#include "utils/utils.hpp"
#include "day14.hpp"

namespace day14 {

/*
std::ostream& operator<<(std::ostream& o,const Point& p){
  o << "x = " << p.x << ", y = " << p.y << std::endl;
  return o;
}
*/
void part_1_ex()
{
  std::cout << "part 1 example" << std::endl;
  Cave c("../input/day14_ex.txt");
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  Cave c("../input/day14_1.txt");
}

void part_2_ex()
{
  std::cout << "part 2 example" << std::endl;
  Cave c("../input/day14_ex.txt",true);
}

void part_2()
{
  std::cout << "part 2" << std::endl;
  Cave c("../input/day14_1.txt",true);
}

}

void day14_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day14::part_1_ex();
  day14::part_1();
}

void day14_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day14::part_2_ex();
  day14::part_2();
}

