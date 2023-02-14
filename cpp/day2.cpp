#include "utils/utils.hpp"
#include "day2.hpp"

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

void part_1_tournament_score(std::string blurb,std::string filename)
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
    std::string opponent_choice = x[0];
    std::string my_choice = x[1];
    int this_score = rock_paper_scissors_score(opponent_choice[0],my_choice[0]);
    //std::cout << this_score << std::endl;
    tournament_score += this_score;
    games_played++;
  }

  std::cout << "games_played = " << games_played << std::endl;
  std::cout << "tournament score = " << tournament_score << std::endl;
}

void day2_part1()
{
  part_1_tournament_score("test data","../input/day02_0.txt");
  part_1_tournament_score("test data","../input/day02_1.txt");
}
