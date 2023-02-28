#ifndef __DAY12_HPP
#define __DAY12_HPP

#include <unordered_set>

namespace day12 {

class ShortestPath
{
private:
  int m_rows;
  int m_cols;
  int m_move_count;
  std::pair<int,int> m_S_point;
  std::pair<int,int> m_E_point;
  std::vector<std::vector<int>> m_hill;
  std::set<std::pair<int,int>> m_visited_locations; // memory of all previously visited locations
  std::set<std::pair<int,int>> m_live_locations; // location of path heads

  bool m_end_to_start;
  std::pair<int,int> *m_terminal_point;

public:
  ShortestPath(std::string filepath,bool end_to_start=true,bool verbose=false);
  bool finished();
  void visit_point(const std::pair<int,int> &point,bool verbose=false,std::string blurb="");
  void read_hill_input(std::string filepath,bool verbose = false);
  int get_hill_value_at_point(const std::pair<int,int> &point);
  void print_point(std::string blurb,const std::pair<int,int> &point);
  void add_point_if_traversible(const std::pair<int,int> &point,const std::pair<int,int> &new_point,std::string blurb,bool verbose = false);
  void explore_adjacent_locations(const std::pair<int,int> &point,bool verbose=false);
  void explore_neighbours(bool verbose=false);
  void steps_to_terminal_point(bool verbose=false);
  void steps_from_lowest_points(bool verbose = false);
};

}

void day12_part1();
void day12_part2();

#endif // __DAY12_HPP
