#include "utils/utils.hpp"
#include "day8.hpp"

namespace day8
{

treehouse::treehouse(std::string filepath)
{
  read_file(filepath);
}

treehouse::~treehouse()
{

}

void treehouse::read_file(std::string filepath)
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

std::vector<int> treehouse::parse_line(std::string line)
{
  std::vector<int> row;
  for (auto c : line)
  {
    int num = utils::char_to_int(c);
    row.push_back(num);
  }
  return row;
}

void treehouse::count_visible_locations(bool verbose)
{
  int visible_count=0;
  for (int row=0;row<m_rows;row++)
  {
    for (int col=0;col<m_cols;col++)
    {
      if (is_visible(row,col,verbose))
      {
        visible_count++;
      }
      else
      {
        if (verbose) std::cout << __func__ << " " << row << "/" << col << " not visible" << std::endl;
      }
    }
  }
  std::cout << __func__ << " total visible = " << visible_count << std::endl;
}

void treehouse::best_scenic_score(bool verbose)
{
  int best_x=-1;
  int best_y=-1;
  int best_score=-1;

  for (int row=0;row<m_rows;row++)
  {
    for (int col=0;col<m_cols;col++)
    {
      int score = scenic_score(row,col,verbose);
      if (score > best_score)
      {
        best_x = row;
        best_y = col;
        best_score = score;
      }
    }
  }
  std::cout << __func__ << " best scenic score = " << best_score << std::endl;
}

bool treehouse::is_visible(int row,int col,bool verbose)
{
  if (
    (row==0) ||
    (row==m_rows-1) ||
    (col==0) ||
    (col==m_cols-1)
  )
  {
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << " boundaries always visible" << std::endl;
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
      if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << " visible from some direction" << std::endl;
      return true;
    }
    else
    {
      // otherwise NOT visible
      if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << " not boundary and no direction visible" << std::endl;
      return false;
    }
  }
}

bool treehouse::is_visible_from_left(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int y=col;
  while (y>0)
  {
    y--; // never called from boundary
    if (m_forest[row][y]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
      return false;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
    }
  }
  return true;
}

bool treehouse::is_visible_from_right(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int y=col;
  while (y<m_cols-1)
  {
    y++; // never called from boundary
    if (m_forest[row][y]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
      return false;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
    }
  }
  return true;
}


bool treehouse::is_visible_from_top(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int x=row;
  while (x>0)
  {
    x--; // never called from boundary
    if (m_forest[x][col]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
      return false;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
    }
  }
  return true;
}

bool treehouse::is_visible_from_bottom(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int x=row;
  while (x<m_rows-1)
  {
    x++; // never called from boundary
    if (m_forest[x][col]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
      return false;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
    }
  }
  return true;
}

int treehouse::scenic_score(int row,int col,bool verbose)
{
  if (
    (row==0) ||
    (row==m_rows-1) ||
    (col==0) ||
    (col==m_cols-1)
  )
  {
    // boundaries have 0 scenic score
    return 0;
  }
  else
  {
    // check interior
    int score_left   = scenic_score_on_left(row,col,verbose);
    int score_top    = scenic_score_on_top(row,col,verbose);
    int score_right  = scenic_score_on_right(row,col,verbose);
    int score_bottom = scenic_score_on_bottom(row,col,verbose);
    return score_left*score_top*score_right*score_bottom;
  }
}

int treehouse::scenic_score_on_left(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int y=col;
  while (y>0)
  {
    y--; // never called from boundary
    if (m_forest[row][y]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << row << "/" << y << " = " << m_forest[row][y] << ", score = " << col-y << std::endl;
      return col-y;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
    }
  }
  if (verbose) std::cout << "\t" << "visible from boundary " << row << "/" << y << " = " << m_forest[row][y] << ", score = " << col-y << std::endl;
  return col-y;
}

int treehouse::scenic_score_on_right(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int y=col;
  while (y<m_cols-1)
  {
    y++; // never called from boundary
    if (m_forest[row][y]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << row << "/" << y << " = " << m_forest[row][y] << ", score = " << y-col << std::endl;
      return y-col;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << row << "/" << y << " = " << m_forest[row][y] << std::endl;
    }
  }
  if (verbose) std::cout << "\t" << "visible from boundary " << row << "/" << y << " = " << m_forest[row][y] << ", score = " << y-col << std::endl;
  return y-col;
}


int treehouse::scenic_score_on_top(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int x=row;
  while (x>0)
  {
    x--; // never called from boundary
    if (m_forest[x][col]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << x << "/" << col << " = " << m_forest[x][col] << ", score = " << row-x << std::endl;
      return row-x;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
    }
  }
  if (verbose) std::cout << "\t" << "visible from boundary " << x << "/" << col << " = " << m_forest[x][col] << ", score = " << row-x << std::endl;
  return row-x;
}

int treehouse::scenic_score_on_bottom(int row,int col,bool verbose)
{
  if (verbose) std::cout << row << "/" << col << " = " << m_forest[row][col] << " " << __func__ << std::endl;
  int x=row;
  while (x<m_rows-1)
  {
    x++; // never called from boundary
    if (m_forest[x][col]>=m_forest[row][col])
    {
      if (verbose) std::cout << "\t" << "hidden by " << x << "/" << col << " = " << m_forest[x][col] << ", score = " << x-row << std::endl;
      return x-row;
    }
    else
    {
      if (verbose) std::cout << "\t" << "visible from " << x << "/" << col << " = " << m_forest[x][col] << std::endl;
    }
  }
  if (verbose) std::cout << "\t" << "visible from boundary " << x << "/" << col << " = " << m_forest[x][col] << ", score = " << x-row << std::endl;
  return x-row;
}

void treehouse::show_forest()
{
  utils::display_vecvec(m_forest,"m_forest","");
}

void day8_part1();
void day8_part2();

void part_1_tree_visibility(std::string blurb,std::string filepath)
{
  treehouse a(filepath);
  //a.show_forest();
  a.count_visible_locations();
}

void part_2_scenic_score(std::string blurb,std::string filepath)
{
  treehouse a(filepath);
  a.best_scenic_score();
}

}

void day8_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day8::part_1_tree_visibility("test data","../input/day08_0.txt");
  day8::part_1_tree_visibility("test data","../input/day08_1.txt");
}

void day8_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day8::part_2_scenic_score("test data","../input/day08_0.txt");
  day8::part_2_scenic_score("test data","../input/day08_1.txt");
}



