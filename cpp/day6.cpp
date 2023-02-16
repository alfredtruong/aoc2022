#include "utils/utils.hpp"
#include "day6.hpp"

namespace day6 {

void part_1(std::string blurb,std::string filename)
{
  /*
  std::cout << rock_paper_scissors_score('A','Y') << std::endl;
  std::cout << rock_paper_scissors_score('B','X') << std::endl;
  std::cout << rock_paper_scissors_score('C','Z') << std::endl;
  */

  std::vector<std::vector<std::string>> data = read_csv(filename,' ',false);

  int tournament_score = 0;
  int games_played = 0;
  for (auto x : data)
  {
    std::string opponent_move = x[0];
    std::string my_move = x[1];
    int this_score = rock_paper_scissors_score(opponent_move[0],my_move[0]);
    //std::cout << this_score << std::endl;
    tournament_score += this_score;
    games_played++;
  }

  std::cout << "games_played = " << games_played << std::endl;
  std::cout << "tournament score = " << tournament_score << std::endl;
}


}

void day6_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day6::part_1("test data","../input/day02_0.txt");
  day6::part_1("test data","../input/day02_1.txt");
}

void day6_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day6::part_1("test data","../input/day02_0.txt");
  day6::part_1("test data","../input/day02_1.txt");
}
