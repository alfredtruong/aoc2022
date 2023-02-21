#ifndef __DAY8_HPP
#define __DAY8_HPP

namespace day8 {

class treehouse
{
private:
  int m_rows;
  int m_cols;
  std::vector<std::vector<int>> m_forest;

public:
  treehouse(std::string filepath);
  ~treehouse();

  void read_file(std::string filepath);
  std::vector<int> parse_line(std::string line);
  void count_visible_locations(bool verbose=false);
  bool is_visible(int row,int col,bool verbose);
  bool is_visible_from_left(int row,int col,bool verbose);
  bool is_visible_from_right(int row,int col,bool verbose);
  bool is_visible_from_top(int row,int col,bool verbose);
  bool is_visible_from_bottom(int row,int col,bool verbose);

  void best_scenic_score(bool verbose=false);
  int scenic_score(int row,int col,bool verbose);
  int scenic_score_on_left(int row,int col,bool verbose);
  int scenic_score_on_right(int row,int col,bool verbose);
  int scenic_score_on_top(int row,int col,bool verbose);
  int scenic_score_on_bottom(int row,int col,bool verbose);

  void show_forest();
};

}

void day8_part1();
void day8_part2();

#endif // __DAY8_HPP
