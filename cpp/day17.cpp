#include "utils/utils.hpp"
#include "day17.hpp"

// https://old.reddit.com/r/adventofcode/comments/zo81kq/2022_day_17_part_1_heights_of_the_tower/

namespace day17 {


Cave::Cave(std::string filepath)
{
  //int i=1'000'000;

  std::fstream f;
  f.open(filepath,std::ios::in);
  std::getline(f,m_blow);

  //add_test();
  //blow_test(0);
  //blow_test(1);
  //blow_test(2);
  //blow_test(3);
  //blow_test(4);

  //drop_test(0);
  //drop_test(1);
  //drop_test(2);
  //drop_test(3);
  //drop_test(4);

  f.close();
}

void Cave::drop_n_shapes(int n_shapes,bool verbose)
{
  for (int i=0;i<n_shapes;i++)
  {
    drop_shape(m_rock_type_idx,verbose);
    std::cout << "[" << i << "] " << m_contents.size() << std::endl;
  }
}

void Cave::drop_test(int rock_type_idx)
{
  add(rock_type_idx);
  for (int i=0;i<10;i++)
  {
    show_cave();
    drop(rock_type_idx);
  }
  show_cave();
}

void Cave::add_test() {
  add(0);
  show_cave();
  m_contents.clear();

  add(1);
  show_cave();
  m_contents.clear();

  add(2);
  show_cave();
  m_contents.clear();

  add(3);
  show_cave();
  m_contents.clear();

  add(4);
  show_cave();
  m_contents.clear();
}

void Cave::blow_test(int rock_type_idx)
{
  bool verbose = true;
  add(rock_type_idx);
  show_cave();
  for (int i=0;i<10;i++) blow_direction(rock_type_idx,true,verbose);
  for (int i=0;i<10;i++) blow_direction(rock_type_idx,false,verbose);
  show_cave();
}

void Cave::show_line(const auto& line,std::string blurb)
{
  for (int i=0;i<WIDTH;i++)
  {
    if (line[i])
      std::cout << '#';
    else
      std::cout << '.';
  }

  std::cout << blurb;
}

void Cave::show_details()
{
  std::cout <<
  "height = " << m_contents.size() <<
  ", rock settled = " << m_rock_is_settled <<
  ", rock bottom idx = " << m_rock_bottom_idx <<
  ", rock left idx = " << m_rock_left_idx <<
  std::endl;

}
void Cave::show_cave()
{
  show_details();
  for (auto it=m_contents.rbegin();it!=m_contents.rend();it++)
    show_line(*it,"\n");

  std::cout << std::endl;

}

void Cave::add(int rock_type_idx)
{
  // add rock init
  m_rock_is_settled = false;
  m_rock_bottom_idx = m_contents.size()-1+4;
  m_rock_left_idx = 2;

  // empty rows
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);
  m_contents.emplace_back(0b0);

  // add specific rock
  switch (rock_type_idx)
  {
  case 0:
    m_contents.emplace_back(0b0111100);
    break;
  case 1:
    m_contents.emplace_back(0b0001000);
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0001000);
    break;
  case 2:
    m_contents.emplace_back(0b0011100);
    m_contents.emplace_back(0b0010000);
    m_contents.emplace_back(0b0010000);
    break;
  case 3:
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
    m_contents.emplace_back(0b0000100);
    break;
  case 4:
    m_contents.emplace_back(0b0001100);
    m_contents.emplace_back(0b0001100);
    break;
  }
}

bool Cave::is_line_empty(auto& line)
{
    return !line.any();
}

void Cave::move_from_to(auto& line,int from_idx,int to_idx)
{
  line[from_idx]=false;
  line[to_idx]=true;
}

void Cave::blow(int rock_type_idx, bool verbose)
{
  char blow_char = m_blow[m_blow_idx];
  //std::cout << "blow_char : " << blow_char << ", " << m_blow_idx << std::endl;

  if (blow_char == '<')
  {
    if (verbose) std::cout << "<" << std::endl;
    blow_direction(rock_type_idx,true);
  }
  else if (blow_char == '>')
  {
    if (verbose) std::cout << ">" << std::endl;
    blow_direction(rock_type_idx,false);
  }
  else
  {
    std::cout << "unrecognised blow : " << blow_char << std::endl;
  }

  m_blow_idx = (m_blow_idx+1) % m_blow.length();
}

void Cave::blow_direction(int rock_type_idx,bool is_left,bool verbose)
{
  // block specific rock
  switch (rock_type_idx)
  {
  case 0:
    blow_minus(is_left,verbose);
    break;
  case 1:
    blow_plus(is_left,verbose);
    break;
  case 2:
    blow_jay(is_left,verbose);
    break;
  case 3:
    blow_pipe(is_left,verbose);
    break;
  case 4:
    blow_block(is_left,verbose);
    break;
  }
}

void Cave::blow_minus(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // only care about top line
  auto& line1 = m_contents[m_rock_bottom_idx];

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx>0)
    {
      if (
        !line1[m_rock_left_idx-1]
      )
      {
        move_from_to(line1,m_rock_left_idx+3,m_rock_left_idx-1);
        m_rock_left_idx--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose) show_line(line1,blurb.str());
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx<(WIDTH-1-1))
    if (m_rock_left_idx<(WIDTH-1-3))
    {
      if (
        !line1[m_rock_left_idx+3+1]
      )
      {
        move_from_to(line1,m_rock_left_idx,m_rock_left_idx+3+1);
        m_rock_left_idx++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose) show_line(line1,blurb.str());
  }
}

void Cave::blow_plus(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 3 lines
  auto& line1 = m_contents[m_rock_bottom_idx+2];
  auto& line2 = m_contents[m_rock_bottom_idx+1];
  auto& line3 = m_contents[m_rock_bottom_idx];

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx>0)
    {
      if (
        !line1[m_rock_left_idx  ] &&
        !line2[m_rock_left_idx-1] &&
        !line3[m_rock_left_idx  ]
      )
      {
        move_from_to(line1,m_rock_left_idx+1,m_rock_left_idx  );
        move_from_to(line2,m_rock_left_idx+2,m_rock_left_idx-1);
        move_from_to(line3,m_rock_left_idx+1,m_rock_left_idx  );
        m_rock_left_idx--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx<(WIDTH-1-2))
    {
      if (
        !line1[m_rock_left_idx+2] &&
        !line2[m_rock_left_idx+3] &&
        !line3[m_rock_left_idx+2]
      )
      {
        move_from_to(line1,m_rock_left_idx+1,m_rock_left_idx+2);
        move_from_to(line2,m_rock_left_idx,  m_rock_left_idx+3);
        move_from_to(line3,m_rock_left_idx+1,m_rock_left_idx+2);
        m_rock_left_idx++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
}

void Cave::blow_jay(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 3 lines
  auto& line1 = m_contents[m_rock_bottom_idx+2];
  auto& line2 = m_contents[m_rock_bottom_idx+1];
  auto& line3 = m_contents[m_rock_bottom_idx];

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx>0)
    {
      if (
        !line1[m_rock_left_idx+1] &&
        !line2[m_rock_left_idx+1] &&
        !line3[m_rock_left_idx-1]
      )
      {
        move_from_to(line1,m_rock_left_idx+2,m_rock_left_idx+1);
        move_from_to(line2,m_rock_left_idx+2,m_rock_left_idx+1);
        move_from_to(line3,m_rock_left_idx+2,m_rock_left_idx-1);
        m_rock_left_idx--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx<(WIDTH-1-2))
    {
      if (
        !line1[m_rock_left_idx+3] &&
        !line2[m_rock_left_idx+3] &&
        !line3[m_rock_left_idx+3]
      )
      {
        move_from_to(line1,m_rock_left_idx+2,m_rock_left_idx+3);
        move_from_to(line2,m_rock_left_idx+2,m_rock_left_idx+3);
        move_from_to(line3,m_rock_left_idx,  m_rock_left_idx+3);
        m_rock_left_idx++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
    }
  }
}

void Cave::blow_pipe(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 4 lines
  auto& line1 = m_contents[m_rock_bottom_idx+3];
  auto& line2 = m_contents[m_rock_bottom_idx+2];
  auto& line3 = m_contents[m_rock_bottom_idx+1];
  auto& line4 = m_contents[m_rock_bottom_idx];

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx>0)
    {
      if (
        !line1[m_rock_left_idx-1] &&
        !line2[m_rock_left_idx-1] &&
        !line3[m_rock_left_idx-1] &&
        !line4[m_rock_left_idx-1]
      )
      {
        move_from_to(line1,m_rock_left_idx,m_rock_left_idx-1);
        move_from_to(line2,m_rock_left_idx,m_rock_left_idx-1);
        move_from_to(line3,m_rock_left_idx,m_rock_left_idx-1);
        move_from_to(line4,m_rock_left_idx,m_rock_left_idx-1);
        m_rock_left_idx--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
      show_line(line4,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx<(WIDTH-1-0))
    {
      if (
        !line1[m_rock_left_idx+1] &&
        !line2[m_rock_left_idx+1] &&
        !line3[m_rock_left_idx+1] &&
        !line4[m_rock_left_idx+1]
      )
      {
        move_from_to(line1,m_rock_left_idx,m_rock_left_idx+1);
        move_from_to(line2,m_rock_left_idx,m_rock_left_idx+1);
        move_from_to(line3,m_rock_left_idx,m_rock_left_idx+1);
        move_from_to(line4,m_rock_left_idx,m_rock_left_idx+1);
        m_rock_left_idx++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
      show_line(line3,blurb.str());
      show_line(line4,blurb.str());
    }
  }
}

void Cave::blow_block(bool is_left,bool verbose)
{
  std::stringstream blurb;

  // care about 4 lines
  auto& line1 = m_contents[m_rock_bottom_idx+1];
  auto& line2 = m_contents[m_rock_bottom_idx];

  if (is_left)
  {
    // only move left if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx>0)
    {
      if (
        !line1[m_rock_left_idx-1] &&
        !line2[m_rock_left_idx-1]
      )
      {
        move_from_to(line1,m_rock_left_idx+1,m_rock_left_idx-1);
        move_from_to(line2,m_rock_left_idx+1,m_rock_left_idx-1);
        m_rock_left_idx--;
        if (verbose) blurb << " blow left" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already left-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
    }
  }
  else
  {
    // only move right if (1) not at edge and (2) not trapped by settled rock
    if (m_rock_left_idx<(WIDTH-1-1))
    {
      if (
        !line1[m_rock_left_idx+2] &&
        !line2[m_rock_left_idx+2]
      )
      {
        move_from_to(line1,m_rock_left_idx,m_rock_left_idx+2);
        move_from_to(line2,m_rock_left_idx,m_rock_left_idx+2);
        m_rock_left_idx++;
        if (verbose) blurb << " blow right" << std::endl;
      }
      else
      {
        if (verbose) blurb << " blocked by settled rock" << std::endl;
      }
    }
    else
    {
      if (verbose) blurb << " already right-most" << std::endl;
    }
    if (verbose)
    {
      show_line(line1,blurb.str());
      show_line(line2,blurb.str());
    }
  }
}

void Cave::drop_shape(int rock_type_idx,bool verbose)
{
  add(rock_type_idx);
  if (verbose) show_cave();
  do
  {
    blow(rock_type_idx);
    drop(rock_type_idx);
    if (verbose) show_cave();
  } while (!m_rock_is_settled);
  if (verbose) std::cout << std::endl;
}

void Cave::drop(int rock_type_idx)
{
  switch (rock_type_idx)
  {
  case 0:
    drop_minus();
    break;
  case 1:
    drop_plus();
    break;
  case 2:
    drop_jay();
    break;
  case 3:
    drop_pipe();
    break;
  case 4:
    drop_block();
    break;
  }

  if (m_rock_is_settled)
    m_rock_type_idx = (m_rock_type_idx+1)%5;
  else
    m_rock_bottom_idx--;

}

void Cave::drop_minus()
{
  auto& line1 = m_contents[m_rock_bottom_idx];
  auto& below = m_contents[m_rock_bottom_idx-1];

  // check if will settle
  if (
    m_contents.size()==1 ||
    below[m_rock_left_idx  ] ||
    below[m_rock_left_idx+1] ||
    below[m_rock_left_idx+2] ||
    below[m_rock_left_idx+3]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_left_idx  ]=true;
    below[m_rock_left_idx+1]=true;
    below[m_rock_left_idx+2]=true;
    below[m_rock_left_idx+3]=true;

    // zap top
    line1[m_rock_left_idx  ]=false;
    line1[m_rock_left_idx+1]=false;
    line1[m_rock_left_idx+2]=false;
    line1[m_rock_left_idx+3]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}


void Cave::drop_plus()
{
  auto& line1 = m_contents[m_rock_bottom_idx+2];
  auto& line2 = m_contents[m_rock_bottom_idx+1];
  auto& line3 = m_contents[m_rock_bottom_idx  ];
  auto& below = m_contents[m_rock_bottom_idx-1];

  // check if will settle
  if (
    m_contents.size()==3 ||
    below[m_rock_left_idx  ] ||
    below[m_rock_left_idx+1] ||
    below[m_rock_left_idx+2]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    line3[m_rock_left_idx  ]=true;
    below[m_rock_left_idx+1]=true;
    line3[m_rock_left_idx+2]=true;

    // zap top
    line2[m_rock_left_idx  ]=false;
    line1[m_rock_left_idx+1]=false;
    line2[m_rock_left_idx+2]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_jay()
{
  auto& line1 = m_contents[m_rock_bottom_idx+2];
  auto& line2 = m_contents[m_rock_bottom_idx+1];
  auto& line3 = m_contents[m_rock_bottom_idx  ];
  auto& below = m_contents[m_rock_bottom_idx-1];

  // check if will settle
  if (
    m_contents.size()==3 ||
    below[m_rock_left_idx  ] ||
    below[m_rock_left_idx+1] ||
    below[m_rock_left_idx+2]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_left_idx  ]=true;
    below[m_rock_left_idx+1]=true;
    below[m_rock_left_idx+2]=true;

    // zap top
    line3[m_rock_left_idx  ]=false;
    line3[m_rock_left_idx+1]=false;
    line1[m_rock_left_idx+2]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_pipe()
{
  auto& line1 = m_contents[m_rock_bottom_idx+3];
  auto& line2 = m_contents[m_rock_bottom_idx+2];
  auto& line3 = m_contents[m_rock_bottom_idx+1];
  auto& line4 = m_contents[m_rock_bottom_idx  ];
  auto& below = m_contents[m_rock_bottom_idx-1];

  // check if will settle
  if (
    m_contents.size()==4 ||
    below[m_rock_left_idx]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_left_idx]=true;

    // zap top
    line1[m_rock_left_idx]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void Cave::drop_block()
{
  auto& line1 = m_contents[m_rock_bottom_idx+1];
  auto& line2 = m_contents[m_rock_bottom_idx  ];
  auto& below = m_contents[m_rock_bottom_idx-1];

  // check if will settle
  if (
    m_contents.size()==2 ||
    below[m_rock_left_idx  ] ||
    below[m_rock_left_idx+1]
  )
  {
    // yes, done
    m_rock_is_settled = true;
  }
  else
  {
    // move down
    below[m_rock_left_idx  ]=true;
    below[m_rock_left_idx+1]=true;

    // zap top
    line1[m_rock_left_idx  ]=false;
    line1[m_rock_left_idx+1]=false;

    // remove top if empty
    if (is_line_empty(line1))
      m_contents.pop_back();
  }
}

void part_1_ex1()
{
  std::cout << "part 1 example" << std::endl;
  Cave c("../input/day17_ex.txt");
  c.drop_n_shapes(2022,false);
}

void part_1()
{
  std::cout << "part 1" << std::endl;
  Cave c("../input/day17_1.txt");
  c.drop_n_shapes(2022,false);
}

void part_2_ex2()
{
  std::cout << "part 2 example" << std::endl;
}

void part_2()
{
  std::cout << "part 2" << std::endl;
}



}

void day17_part1()
{
  std::cout << __func__ << std::endl << std::endl;
  day17::part_1_ex1();
  day17::part_1();
}

void day17_part2()
{
  std::cout << __func__ << std::endl << std::endl;
  day17::part_2_ex2();
  day17::part_2();
}
