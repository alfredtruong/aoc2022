#include "utils/utils.hpp"
#include "day2.hpp"

namespace day2 {
/* key
A/B/C = computer
X/Y/Z = me

rock      A X
paper     B Y
scissors  C Z
*/

/* do I win or lose?
w = win
l = lose
d = draw

   X  Y  Z
A  0  1 -1
B -1  0  1
C  1 -1  0
*/

/* player = total score = play value + win-lose value
   X  Y  Z
A  4  8  3
B  1  5  9
C  7  2  6
*/

/* player = played value
   X  Y  Z
A  1  2  3
B  1  2  3
C  1  2  3
*/
int play_value(char my_move)
{
  if (my_move == 'X')
    return 1; // rock
  else if (my_move == 'Y')
    return 2; // paper
  else if (my_move == 'Z')
    return 3; // scissors
  else
    exit(1);
}

/* player win-lose value
   X  Y  Z
A  3  6  0
B  0  3  6
C  6  0  3
*/
int win_lose_value(const char opponent_move,const char my_move)
{
  if (
    ((opponent_move == 'A') && (my_move == 'Y')) || // they rock, I paper
    ((opponent_move == 'B') && (my_move == 'Z')) || // they paper, I scissors
    ((opponent_move == 'C') && (my_move == 'X'))    // they scissors, I rock
  )
    return 6; // win
  else if (
    ((opponent_move == 'A') && (my_move == 'X')) || // they rock, I rock
    ((opponent_move == 'B') && (my_move == 'Y')) || // they paper, I paper
    ((opponent_move == 'C') && (my_move == 'Z'))    // they scissors, I scissors
  )
    return 3; // draw
  else if (
    ((opponent_move == 'A') && (my_move == 'Z')) || // they rock, I scissors
    ((opponent_move == 'B') && (my_move == 'X')) || // they paper, I rock
    ((opponent_move == 'C') && (my_move == 'Y'))    // they scissors, I paper
  )
    return 0; // lose
  else
    exit(1);
}

int rock_paper_scissors_score(const char opponent_move,const char my_move)
{
  return play_value(my_move) + win_lose_value(opponent_move,my_move);
}

void part_1_tournament_score(std::string blurb,std::string filepath)
{
  /*
  std::cout << rock_paper_scissors_score('A','Y') << std::endl;
  std::cout << rock_paper_scissors_score('B','X') << std::endl;
  std::cout << rock_paper_scissors_score('C','Z') << std::endl;
  */

  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filepath,' ',false);

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

int required_outcome_outcome_value(char required_outcome)
{
  if (required_outcome == 'X')
    return 0; // lose
  else if (required_outcome == 'Y')
    return 3; // draw
  else if (required_outcome == 'Z')
    return 6; // win
  else
    exit(1);
}

/*
X = need to lose
Y = need to draw
Z = need to win
*/
int required_outcome_play_value(const char opponent_move,const char required_outcome)
{
  if (
    ((opponent_move == 'A') && (required_outcome == 'Y')) || // they rock, draw = I rock
    ((opponent_move == 'B') && (required_outcome == 'X')) || // they paper, lose = I rock
    ((opponent_move == 'C') && (required_outcome == 'Z'))    // they scissors, win = I rock
  )
    return 1; // rock
  else if (
    ((opponent_move == 'A') && (required_outcome == 'Z')) || // they rock, win = I paper
    ((opponent_move == 'B') && (required_outcome == 'Y')) || // they paper, draw = I paper
    ((opponent_move == 'C') && (required_outcome == 'X'))    // they scissors, lose = I paper
  )
    return 2; // paper
  else if (
    ((opponent_move == 'A') && (required_outcome == 'X')) || // they rock, lose = I scissors
    ((opponent_move == 'B') && (required_outcome == 'Z')) || // they paper, win = I scissors
    ((opponent_move == 'C') && (required_outcome == 'Y'))    // they scissors, draw = I scissors
  )
    return 3; // scissors
  else
    exit(1);
}

int required_outcome_score(const char opponent_move,const char required_outcome)
{
  return required_outcome_play_value(opponent_move,required_outcome) + required_outcome_outcome_value(required_outcome);
}

void part_2_tournament_score(std::string blurb,std::string filepath)
{
  /*
  std::cout << rock_paper_scissors_score('A','Y') << std::endl;
  std::cout << rock_paper_scissors_score('B','X') << std::endl;
  std::cout << rock_paper_scissors_score('C','Z') << std::endl;
  */

  std::vector<std::vector<std::string>> data = utils::parse_file<std::string>(filepath,' ',false);

  int tournament_score = 0;
  int games_played = 0;
  for (auto x : data)
  {
    std::string opponent_move = x[0];
    std::string required_outcome = x[1];
    int this_score = required_outcome_score(opponent_move[0],required_outcome[0]);
    //std::cout << this_score << std::endl;
    tournament_score += this_score;
    games_played++;
  }

  std::cout << "games_played = " << games_played << std::endl;
  std::cout << "tournament score = " << tournament_score << std::endl;
}

}

void day2_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day2::part_1_tournament_score("test data","../input/day02_0.txt");
  day2::part_1_tournament_score("test data","../input/day02_1.txt");
}

void day2_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day2::part_2_tournament_score("test data","../input/day02_0.txt");
  day2::part_2_tournament_score("test data","../input/day02_1.txt");
}
