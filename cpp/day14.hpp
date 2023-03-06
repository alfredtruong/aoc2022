#ifndef __DAY14_HPP
#define __DAY14_HPP

#include <string>
#include <iostream>

namespace day14 {


class Cave
{
private:
  static const int m_starting_x = 500;
  static const int m_starting_y = 0;

  std::vector<std::vector<std::pair<int,int>>> m_input_rock_formations;
  std::map<std::pair<int,int>,char> m_cave;
  int m_x_min = m_starting_x; //std::numeric_limits<int>::max();
  int m_x_max = m_starting_x; //std::numeric_limits<int>::min();
  int m_y_min = m_starting_y; //std::numeric_limits<int>::max();
  int m_y_max = m_starting_y; //std::numeric_limits<int>::min();
  bool m_cave_full = false;
  int m_n_sand = 0;

public:
  Cave(std::string filepath,bool add_floor=false)
  {
    parse_file(filepath);
    populate_rocks();

    // show limits
    std::cout << "x-limits: min = " << m_x_min << ", max = " << m_x_max << std::endl;
    std::cout << "y-limits: min = " << m_y_min << ", max = " << m_y_max << std::endl;

    if (add_floor)
      add_infinite_floor();

    // show limits
    std::cout << "x-limits: min = " << m_x_min << ", max = " << m_x_max << std::endl;
    std::cout << "y-limits: min = " << m_y_min << ", max = " << m_y_max << std::endl;

    show_cave();
    add_sand();
    show_cave();
    std::cout << "max sand = " << m_n_sand << std::endl;
  }

  void add_sand()
  {
    while (!m_cave_full)
      drop_grain_of_sand();
  }

  void parse_file(std::string filepath)
  {
    // open file
    std::fstream f;
    f.open(filepath,std::ios::in);

    // parse each line
    std::string line;
    while (std::getline(f,line))
    {
      std::vector<std::pair<int,int>> vp = parse_line(line);
      m_input_rock_formations.push_back(vp);
    }

    // close file handler
    f.close();

    // read rock formations
    std::cout << m_input_rock_formations.size() << std::endl;
  }

  std::vector<std::pair<int,int>> parse_line(std::string line,bool verbose=false)
  {
    std::vector<std::pair<int,int>> line_points;
    if (verbose) std::cout << line << std::endl;

    std::string sep = " -> ";
    int idx_start = 0;
    int idx_stop = 0;
    bool do_parse = true; // force parse on last point
    while (do_parse)
    {
      idx_stop = line.find(sep,idx_start);
      if (idx_stop == std::string::npos)
      {
        idx_stop = line.length(); // no more found, do last one
        do_parse = false; // dont do again
      }
      std::string x_comma_y = line.substr(idx_start,idx_stop-idx_start);
      idx_start = idx_stop + sep.length(); // prep for next parse

      // save down point
      //std::cout << idx_start << " " << idx_stop << " " << x_comma_y << std::endl;
      //Point p(x_comma_y);

      std::pair<int,int> p = convert_x_comma_y(x_comma_y);
      line_points.push_back(p);
      //std::cout << p << std::endl;
    }

    if (verbose) std::cout << line_points.size() << std::endl;

    return line_points;
  }

  std::pair<int,int> convert_x_comma_y(std::string x_comma_y)
  {
    //std::cout << __func__ << std::endl;
    std::stringstream ss(x_comma_y); // break up "10,20" into Point(10,20)
    std::string str;
    std::getline(ss,str,','); // read stream to delimiter or fail
    int x=std::stoi(str);
    std::getline(ss,str,','); // read stream to delimiter or fail
    int y=std::stoi(str);

    return std::pair<int,int>(x,y);
  }

  void populate_point(const std::pair<int,int>& p,const char &c,bool update_limits = false,bool verbose = false)
  {
    if (verbose) std::cout << "\t[" << m_cave.size() << "] (" << p.first << "," << p.second << ") = " << c << std::endl;

    // set point
    m_cave[p] = c;

    // compute extremals
    if (update_limits)
    {
      if (p.first < m_x_min) m_x_min = p.first;
      if (p.first > m_x_max) m_x_max = p.first;
      if (p.second < m_y_min) m_y_min = p.second;
      if (p.second > m_y_max) m_y_max = p.second;
    }
  }

  void populate_rocks(bool verbose = false)
  {
    for (auto vp : m_input_rock_formations)
    {
      // populate first point
      if (verbose) std::cout << "\tstarting point" << std::endl;
      populate_point(vp[0],'#',true);

      // score out remaining points
      for (int i=1;i<vp.size();i++)
        populate_rock_line(vp[i-1],vp[i]);

      if (verbose) std::cout << std::endl;
    }
  }

  void add_infinite_floor()
  {
    // actual floor
    int floor_y = m_y_max+2;
    int floor_x_min = m_x_min-floor_y;
    int floor_x_max = m_x_max+floor_y;

    // add left to right
    for (int x=floor_x_min;x<=floor_x_max;x++)
      populate_point(std::pair<int,int>(x,floor_y),'#',true);
  }

  void populate_rock_line(const std::pair<int,int>& p1,const std::pair<int,int>& p2,bool verbose = false)
  {
    // figure out which direction to populate in
    if (p1.first==p2.first)
    {
      if (verbose) std::cout << "\ty changes" << std::endl;
      int y = p1.second;
      do
      {
        if (p1.second<p2.second)
          y++;
        else
          y--;

        populate_point(std::pair<int,int>(p1.first,y),'#',true);
      } while (y != p2.second);
    }
    else if (p1.second==p2.second)
    {
      if (verbose) std::cout << "\tx changes" << std::endl;
      int x = p1.first;
      do
      {
        if (p1.first<p2.first)
          x++;
        else
          x--;

        populate_point(std::pair<int,int>(x,p1.second),'#',true);
      } while (x != p2.first);
    }
    else
    {
      exit(1);
    }
  }

  void show_cave()
  {
    for (int y=m_y_min;y<=m_y_max;y++)
    {
      std::cout << "[" << y << "]\t";
      for (int x=m_x_min;x<=m_x_max;x++)
      {
        std::pair<int,int> p(x,y);
        if (m_cave.find(p)==m_cave.end())
          std::cout << '.';
        else
          std::cout << m_cave[p];
      }
      std::cout << std::endl;
    }
  }

  void drop_grain_of_sand(bool verbose = false)
  {
    int sand_x = m_starting_x;
    int sand_y = m_starting_y;
    int n_moves = 0;
    bool is_settled = false;

    while (!is_settled)
    {
      // std::cout << "check " << sand_x << "," << sand_y << std::endl;

      // dropping to infinity?
      if (sand_y > m_y_max)
      {
        is_settled = true;
        m_cave_full = true;
      }

      //std::cout << "\tsand position = " << sand_x << "," << sand_y << ", moves = " << n_moves << std::endl;
      if (m_cave.find(std::pair<int,int>(sand_x,sand_y+1))==m_cave.end())
      {
        // move down
        sand_y++;
        n_moves++;
      }
      else if (m_cave.find(std::pair<int,int>(sand_x-1,sand_y+1))==m_cave.end())
      {
        // move down left
        sand_x--;
        sand_y++;
        n_moves++;
      }
      else if (m_cave.find(std::pair<int,int>(sand_x+1,sand_y+1))==m_cave.end())
      {
        // move down right
        sand_x++;
        sand_y++;
        n_moves++;
      }
      else
      {
        if ((sand_x == m_starting_x) && (sand_y == m_starting_y))
          m_cave_full = true;

        // final sand position
        is_settled = true;
        populate_point(std::pair<int,int>(sand_x,sand_y),'o');
        m_n_sand++;
        if (verbose) std::cout << "settled at " << sand_x << "," << sand_y << std::endl;
        if (verbose) show_cave();
      }
    }
  }

};

}

void day14_part1();
void day14_part2();

#endif // __DAY14_HPP
