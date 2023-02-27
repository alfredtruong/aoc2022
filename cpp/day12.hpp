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
  std::pair<int,int> m_start_point;
  std::pair<int,int> m_end_point;
  std::vector<std::vector<int>> m_hill;
  std::set<std::pair<int,int>> m_visited_locations; // memory of all previously visited locations
  std::set<std::pair<int,int>> m_live_locations; // location of path heads
  bool m_finished;

public:
  ShortestPath(std::string filepath,bool verbose=false)
  {
    read_hill_input(filepath);
    if (verbose) utils::display_vecvec<int>(m_hill);
  }

  void initialize()
  {
    m_finished=false;
    m_move_count=0;
    m_visited_locations.clear();
    m_live_locations.clear();
    visit_point(m_end_point);
  }

  bool finished()
  {
    if (m_visited_locations.find(m_start_point)==m_visited_locations.end())
      return false;
    else
    {
      std::cout << "moves = " << m_move_count << std::endl;
      return true;
    }
  }

  bool finished(const std::pair<int,int> &start_point)
  {
    if (m_visited_locations.find(start_point)==m_visited_locations.end())
      return false;
    else
    {
      std::cout << "moves = " << m_move_count << std::endl;
      return true;
    }
  }

  void visit_point(const std::pair<int,int> &point)
  {
    m_visited_locations.insert(point);
    m_live_locations.insert(point);
  }

  void read_hill_input(std::string filepath,bool verbose = false)
  {
    std::fstream f;
    f.open(filepath,std::ios::in);
    std::string line;

    int i=0;
    while(std::getline(f,line))
    {
      std::vector<int> row;
      for(int j=0;j<line.length();j++)
      {
        if (line[j]=='S')
        {
          m_start_point.first=i;
          m_start_point.second=j;
          if (verbose) print_point("start",m_start_point);
          if (verbose) std::cout<<std::endl;
          row.push_back(1);
        }
        else if (line[j]=='E')
        {
          m_end_point.first=i;
          m_end_point.second=j;
          if (verbose) print_point("end",m_end_point);
          if (verbose) std::cout<<std::endl;
          row.push_back(26);
        }
        else
        {
          row.push_back((int)line[j]-96);
        }
      }
      m_hill.push_back(row);
      i++;
    }
    m_rows=(int)m_hill.size();
    m_cols=(int)m_hill[0].size();
  }

  int get_hill_value_at_point(const std::pair<int,int> &point)
  {
    return m_hill[point.first][point.second];
  }

  void print_point(std::string blurb,const std::pair<int,int> &point)
  {
    std::cout << blurb << "=[" << point.first << "," << point.second << "]";
  }

  void add_point_if_traversible(const std::pair<int,int> &point,const std::pair<int,int> &new_point,std::string blurb,bool verbose = false)
  {
    int current_hill_value = get_hill_value_at_point(point);
    int new_hill_value = get_hill_value_at_point(new_point);
    if (verbose) print_point(blurb,new_point);
    if (new_hill_value>= (current_hill_value-1))
    {
      if (verbose) std::cout << "traverse=ok,";
      if (m_visited_locations.find(new_point)==m_visited_locations.end())
      {
        if (verbose) std::cout << "visited=no,TRY";
        visit_point(new_point);
      }
      else
      {
        if (verbose) std::cout << "visited=yes";
      }
    }
    else
    {
      if (verbose) std::cout << "traverse=no";
    }
    if (verbose) std::cout << std::endl;
  }

  void explore_adjacent_locations(const std::pair<int,int> &point,bool verbose=false)
  {
    if (verbose) print_point("[current]",point);
    if (verbose) std::cout << std::endl;
    // up
    if (point.first>0)
    {
      std::pair<int,int> new_point(point.first-1,point.second);
      add_point_if_traversible(point,new_point,"up");
    }
    // down
    if (point.first<m_rows-1)
    {
      std::pair<int,int> new_point(point.first+1,point.second);
      add_point_if_traversible(point,new_point,"down");
    }
    // left
    if (point.second>0)
    {
      std::pair<int,int> new_point(point.first,point.second-1);
      add_point_if_traversible(point,new_point,"left");
    }
    // right
    if (point.second<m_cols-1)
    {
      std::pair<int,int> new_point(point.first,point.second+1);
      add_point_if_traversible(point,new_point,"right");
    }
  }

  void explore_neighbours(bool verbose=false)
  {
    m_move_count++;

    std::set<std::pair<int,int>> copy_live_locations = m_live_locations;
    for (auto point : copy_live_locations)
    {
      explore_adjacent_locations(point);
    }
    for (auto point : copy_live_locations)
    {
      m_live_locations.erase(point);
    }
    if (verbose) std::cout << "[" << m_move_count << "] live locations = " << m_live_locations.size() << std::endl;
  }

  void steps_to_start_point()
  {
    initialize();
    while (!finished())
    {
      explore_neighbours();
    }
  }

  void min_steps_to_lowest_points()
  {
    std::vector<std::pair<int,int>> starting_points;
    for (int i=0;i<m_rows;i++)
    {
      for (int j=0;j<m_cols;j++)
      {
        if (m_hill[i][j]==1)
        {
          std::pair<int,int> start_point(i,j);
          starting_points.push_back(start_point);
        }
      }
    }
    std::cout << "n lowest points = " << starting_points.size() << std::endl;
    for (auto starting_point : starting_points)
    {
      initialize();
      while (!finished(starting_point))
      {
        explore_neighbours();
      }
    }
  }
};

}

void day12_part1();
void day12_part2();

#endif // __DAY12_HPP
