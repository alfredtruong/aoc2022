#include "utils/utils.hpp"
#include "day8.hpp"

namespace day8 {

class treehouse
{
private:
  int m_rows;
  int m_cols;
  std::vector<std::vector<int>> m_forest;

public:
  treehouse(std::string filepath)
  {
    read_file(filepath);
  }

  void read_file(std::string filepath)
  {
    std::fstream f;
    f.open(filepath,std::ios::in); // read only

    std::string line;
    while (std::getline(f,line))
    {
      m_forest.push_back(parse_line(line));
    }

    // assume input is square array
    m_rows = m_forest.size();
    m_cols = m_forest[0].size();
  }

  std::vector<int> parse_line(std::string line)
  {
    std::vector<int> row;
    for (auto c : line)
    {
      int num = utils::char_to_int(c);
      row.push_back(num);
    }
    return row;
  }

  void count_visible_locations()
  {
    int visible_count=0;
    for (int row=0;row<m_rows;row++)
    {
      for (int col=0;col<m_cols;col++)
      {
        if (is_visible(row,col,true))
        {
          visible_count++;
        }
        else
        {
          std::cout << __func__ << " " << row << "/" << col << " not visible" << std::endl;
        }
      }
    }
  }

  bool is_visible(int row,int col,bool verbose)
  {
    //std::cout << row << "/" << col << " (" << m_forest[row][col] << ")" << std::endl;
    if (
      (row==0) ||
      (row==m_rows-1) ||
      (col==0) ||
      (col==m_cols-1)
    )
    {
      // boundaries always visible
      return true;
    }
    else
    {
      // check interior
      if (
        is_visible_from_left(row,col,verbose) ||
        is_visible_from_top(row,col,verbose) ||
        is_visible_from_right(row,col,verbose) ||
        is_visible_from_bottom(row,col,verbose)
      )
      {
        // is visible from some side?
        return true;
      }
      else
      {
        // otherwise NOT visible
        return false;
      }
    }
  }

  bool is_visible_from_left(int row,int col,bool verbose)
  {
    std::cout << __func__;
    int y=col;
    while (y>0)
    {
      y--; // never called from boundary
      std::cout << " " << y;
      if (m_forest[row][y]>=m_forest[row][col])
      {
        if (verbose)
        {
          std::cout << row << "/" << col << " (" << m_forest[row][col] << ")";
          std::cout << " " << __func__ << " ";
          std::cout << row << "/" << y << " (" << m_forest[row][y] << ") ";
          std::cout << std::endl;
        }
        return false;
      }
    }
    return true;
  }

  bool is_visible_from_right(int row,int col,bool verbose)
  {
    std::cout << __func__;
    int y=col;
    while (y<m_cols-1)
    {
      y++; // never called from boundary
      std::cout << " " << y;
      if (m_forest[row][y]>=m_forest[row][col])
      {
        if (verbose)
        {
          std::cout << row << "/" << col << " (" << m_forest[row][col] << ")";
          std::cout << " " << __func__ << " ";
          std::cout << row << "/" << y << " (" << m_forest[row][y] << ") ";
          std::cout << std::endl;
        }
        return false;
      }
    }
    return true;
  }


  bool is_visible_from_top(int row,int col,bool verbose)
  {
    std::cout << __func__;
    int x=col;
    while (x>0)
    {
      x--; // never called from boundary
      std::cout << " " << x;
      if (m_forest[x][col]>=m_forest[row][col])
      {
        if (verbose)
        {
          std::cout << row << "/" << col << " (" << m_forest[row][col] << ")";
          std::cout << " " << __func__ << " ";
          std::cout << x << "/" << col << " (" << m_forest[x][col] << ") ";
          std::cout << std::endl;
        }
        return false;
      }
    }
    return true;
  }

  bool is_visible_from_bottom(int row,int col,bool verbose)
  {
    std::cout << __func__;
    int x=col;
    while (x<m_rows-1)
    {
      x++; // never called from boundary
      std::cout << " " << x;
      if (m_forest[x][col]>=m_forest[row][col])
      {
        if (verbose)
        {
          std::cout << row << "/" << col << " (" << m_forest[row][col] << ")";
          std::cout << " " << __func__ << " ";
          std::cout << x << "/" << col << " (" << m_forest[x][col] << ") ";
          std::cout << std::endl;
        }
        return false;
      }
    }
    return true;
  }

  void show_forest()
  {
    utils::display_vecvec(m_forest,"m_forest","");
  }

};

void part_1(std::string blurb,std::string filepath)
{
  treehouse a(filepath);
  a.show_forest();
  a.count_visible_locations();
}


}

void day8_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day8::part_1("test data","../input/day08_0.txt");
  //day8::part_1("test data","../input/day08_1.txt");
}

void day8_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day8::part_1("test data","../input/day08_0.txt");
  day8::part_1("test data","../input/day08_1.txt");
}
