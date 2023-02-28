#include "utils/utils.hpp"
#include "day12.hpp"

namespace day12 {



ShortestPath::ShortestPath(std::string filepath,bool end_to_start,bool verbose)
{
  read_hill_input(filepath);
  if (verbose) utils::display_vecvec<int>(m_hill);

  m_move_count=0;
  m_visited_locations.clear();
  m_live_locations.clear();

  m_end_to_start = end_to_start;
  if (m_end_to_start)
    std::cout << "E to S" << std::endl;
  else
    std::cout << "S to E" << std::endl;
}

bool ShortestPath::finished()
{
  if (m_visited_locations.find(*m_terminal_point)==m_visited_locations.end())
    return false;
  else
  {
    std::cout << "moves = " << m_move_count << std::endl;
    return true;
  }
}

void ShortestPath::visit_point(const std::pair<int,int> &point,bool verbose,std::string blurb)
{
  m_visited_locations.insert(point);
  m_live_locations.insert(point);

  if (verbose)
    print_point(blurb,point);
}

void ShortestPath::read_hill_input(std::string filepath,bool verbose)
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
        m_S_point.first=i;
        m_S_point.second=j;
        if (verbose) print_point("S",m_S_point);
        if (verbose) std::cout<<std::endl;
        row.push_back(1);
      }
      else if (line[j]=='E')
      {
        m_E_point.first=i;
        m_E_point.second=j;
        if (verbose) print_point("E",m_E_point);
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

int ShortestPath::get_hill_value_at_point(const std::pair<int,int> &point)
{
  return m_hill[point.first][point.second];
}

void ShortestPath::print_point(std::string blurb,const std::pair<int,int> &point)
{
  std::cout << blurb << "=[" << point.first << "," << point.second << "]";
}

void ShortestPath::add_point_if_traversible(const std::pair<int,int> &point,const std::pair<int,int> &new_point,std::string blurb,bool verbose)
{
  int current_hill_value = get_hill_value_at_point(point);
  int new_hill_value = get_hill_value_at_point(new_point);
  if (verbose) print_point(blurb,new_point);

  //std::cout << "current = " << current_hill_value << ", new = " << new_hill_value << std::endl;
  bool cond;
  if (m_end_to_start)
    cond = (current_hill_value-1)<=new_hill_value;
  else
    cond = (current_hill_value+1)>=new_hill_value;

  if (cond)
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

void ShortestPath::explore_adjacent_locations(const std::pair<int,int> &point,bool verbose)
{
  if (verbose) print_point("[current]",point);
  if (verbose) std::cout << std::endl;
  // up
  if (point.first>0)
  {
    std::pair<int,int> new_point(point.first-1,point.second);
    add_point_if_traversible(point,new_point,"up",verbose);
  }
  // down
  if (point.first<m_rows-1)
  {
    std::pair<int,int> new_point(point.first+1,point.second);
    add_point_if_traversible(point,new_point,"down",verbose);
  }
  // left
  if (point.second>0)
  {
    std::pair<int,int> new_point(point.first,point.second-1);
    add_point_if_traversible(point,new_point,"left",verbose);
  }
  // right
  if (point.second<m_cols-1)
  {
    std::pair<int,int> new_point(point.first,point.second+1);
    add_point_if_traversible(point,new_point,"right",verbose);
  }
}

void ShortestPath::explore_neighbours(bool verbose)
{
  m_move_count++;

  std::set<std::pair<int,int>> copy_live_locations = m_live_locations;
  for (auto point : copy_live_locations)
  {
    explore_adjacent_locations(point,verbose);
  }
  for (auto point : copy_live_locations)
  {
    m_live_locations.erase(point);
  }
  if (verbose) std::cout << "[" << m_move_count << "] live locations = " << m_live_locations.size() << std::endl;
}

void ShortestPath::steps_to_terminal_point(bool verbose)
{
  // load starting points
  if (m_end_to_start)
    visit_point(m_E_point,verbose,"[start point] ");
  else
    visit_point(m_S_point,verbose,"[start point] ");

  // load terminal points
  if (m_end_to_start)
    m_terminal_point = &m_S_point;
  else
    m_terminal_point = &m_E_point;

  std::cout << "n starting points = " << m_visited_locations.size() << std::endl;
  while (!finished())
    explore_neighbours();
}

void ShortestPath::steps_from_lowest_points(bool verbose)
{
  // load starting points
  if (m_end_to_start)
    visit_point(m_E_point,verbose,"[start point] ");
  else
  {
    for (int i=0;i<m_rows;i++)
    {
      for (int j=0;j<m_cols;j++)
      {
        if (m_hill[i][j]==1)
        {
          std::pair<int,int> start_point(i,j);
          visit_point(start_point,verbose,"[start point] ");
        }
      }
    }
  }

  // load terminal points
  if (m_end_to_start)
    m_terminal_point = &m_S_point;
  else
    m_terminal_point = &m_E_point;
  std::cout << "[terminal point] " << m_terminal_point->first << ":" << m_terminal_point->second << std::endl;

  std::cout << "n starting points = " << m_visited_locations.size() << std::endl;
  while (!finished())
    explore_neighbours();
}



void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  ShortestPath sp("../input/day12_ex1.txt");
  sp.steps_to_terminal_point();

  ShortestPath sp2("../input/day12_ex1.txt",false);
  sp2.steps_to_terminal_point();
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  ShortestPath sp("../input/day12_1.txt");
  sp.steps_to_terminal_point(true);

  ShortestPath sp2("../input/day12_1.txt",false);
  sp2.steps_to_terminal_point(true);
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
  ShortestPath sp("../input/day12_ex1.txt");
  sp.steps_from_lowest_points(true);

  std::cout << "part 2 example" << std::endl;
  ShortestPath sp2("../input/day12_ex1.txt",false);
  sp2.steps_from_lowest_points(true);
}

void part_2()
{
  std::cout << "part 2" << std::endl;
  ShortestPath sp("../input/day12_1.txt");
  sp.steps_from_lowest_points(true);

  std::cout << "part 2" << std::endl;
  ShortestPath sp2("../input/day12_1.txt",false);
  sp2.steps_from_lowest_points(true);
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

